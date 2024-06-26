/** <pre>
 *  The SDK is used to create and format CIGI compliant messages.
 *  Copyright (c) 2001-2005 The Boeing Company
 *
 *  This library is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or (at
 *  your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation,
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  FILENAME:   CigiIncomingMsg.cpp
 *  LANGUAGE:   C++
 *  CLASS:      UNCLASSIFIED
 *  PROJECT:    Common Image Generator Interface (CIGI) SDK
 *
 *  PROGRAM DESCRIPTION:
 *  ...
 *
 *  MODIFICATION NOTES:
 *  DATE     NAME                                SCR NUMBER
 *  DESCRIPTION OF CHANGE........................
 *
 *  07/29/2015 Chas Whitley                       Version 4.0.0
 *  Initial Release for CIGI 4.0 compatibility.
 *
 *  12/07/2018 Paul Slade                       Version 4.0.2
 *  -Modified RegisterUserPacket to not return error if the packet type is just 
 *  not required by this session type.
 *  -Moved byte swap determination into CheckFirstPacket() as we need to know if
 *  byte swap is required in order to read PacketSize and Packet ID of the first
 *  packet when receiving Cigi4.
 *  -Added byte swap of PacketSize and PacketID for Cigi4
 *  -Fixed GetFirstPacket() and GetNextPacket() to work with Cigi4
 *  -Fixed V3 AtmosCtrl and CelestialCtrl
 *  -Fixed registration of V3 user defined packets
 *
 *  07/26/2019 Chas Whitley                       Version 4.0.3
 *  -Added the following to SignalJump()
 *     case CigiSignalType::SigEntityPositionCtrl: // chas
 *        (*iSig)->OnEntityPositionCtrl(Packet);
 *        break;
 *     case CigiSignalType::SigAnimationCtrl: // chas
 *        (*iSig)->OnAnimationControl(Packet);
 *        break;
 *
 *  11/04/2019 Scott Devine                       Version 4.0.4
 *  -Added the following to ProcessIncomingMsg()
	Cigi_uint16 minExtensionDataPacketID = ProcessingVersion.CigiMajorVersion < 4 ?201 : 0x1000;
	Cigi_uint16 maxExtensionDataPacketID = ProcessingVersion.CigiMajorVersion < 4 ?255 : 0xfffe;
	if( CnvtDta.ProcID == CigiProcessType::ProcNone && CnvtDta.CnvtPacketID == 0 &&
		PacketID >= minExtensionDataPacketID && PacketID <= maxExtensionDataPacketID ) {
		CnvtDta.CnvtPacketID = PacketID;
		CnvtDta.ProcID = CigiProcessType::ProcStd;;
	}
 *
 * </pre>
 *  Author: The Boeing Company
 *
 */

#define _EXPORT_CCL_

#include "CigiIncomingMsg.h"
#include "CigiExceptions.h"
#include "CigiAllPackets.h"

#include "CigiVersionID.h"
#include "CigiSignalType.h"
#include "CigiDefaultPacket.h"
#include "CigiSession.h"
#include "CigiSwapping.h"


// ====================================================================
// Construction/Destruction
// ====================================================================

// ================================================
// CigiIncomingMsg
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
CigiIncomingMsg::CigiIncomingMsg()
: Iteration(false)
, CrntPacket(NULL)
, ReadBufferPos(0)
, Swap(false)
, DefaultPckt(NULL)
{
   DefaultPckt = new CigiDefaultPacket;

   for(int ndx=0;ndx<0x10000;ndx++)
      IncomingHandlerTbl[ndx] = 0;

   ClearTbls(true);

   for(int ndx=0;ndx<CigiSignalType::SigMax;ndx++)
      SignalTbl[ndx] = CigiSignalType::SigNone;

   ReaderVersion.SetCigiVersion(0,0);
   ProcessingVersion.SetCigiVersion(0,0);
   MostMatureCigiVersionReceived.SetCigiVersion(0,0);
}

// ================================================
// ~CigiIncomingMsg
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
CigiIncomingMsg::~CigiIncomingMsg()
{
   int ndx;

   ClearTbls(true);

   for(ndx=0;ndx<0x10000;ndx++)
  {
      // Events
      if( !EventList[ndx].empty() ) EventList[ndx].clear();

      // Call Backs
      CallBackList[ndx].clear();
   }

   // Signals
   SignalList.clear();

#if 0  // chas - this is broken...need to fix later
   // Default Packet
   if(DefaultPckt != NULL)
      delete DefaultPckt;
#endif
}


// ====================================================================
// Processing
// ====================================================================

// ================================================
// ProcessIncomingMsg
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::ProcessIncomingMsg(Cigi_uint8 *Buff, int Size)
{
   if(Iteration)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiCalledOutOfSequenceException();
#endif
      return(CIGI_ERROR_CALLED_OUT_OF_SEQUENCE);
   }

   if(Size < 12) 
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiImproperPacketException();
#endif
      return(CIGI_ERROR_IMPROPER_PACKET);
   }

   Swap = false;
   int stat = CheckFirstPacket(Buff);
   if(stat != CIGI_SUCCESS)
      return(stat);


   Cigi_uint8 *Dta = Buff;
   int ReadCnt = 0;

   // Process the message
   while(ReadCnt < Size)
   {
      Cigi_uint16 PacketSize;
      Cigi_uint16 PacketID;

      if( ProcessingVersion.CigiMajorVersion >= 4 )
      {
	 PackPointer pBuff;
	 pBuff.c = Buff+ReadCnt;
	 if (Swap) {
	     CigiSwap2(&PacketSize, pBuff.s++);
	     CigiSwap2(&PacketID, pBuff.s++);
	 }
	 else {
	     PacketSize = *pBuff.s++;
	     PacketID = *pBuff.s++;
	 }
      }
      else
      {
         PacketID = *Dta;
         PacketSize = *(Dta+1);
      }

      if(PacketSize == 0)
         break;

      CigiBasePacket *tPckt = IncomingHandlerTbl[PacketID];

      CigiCnvtInfoType::Type CnvtDta;
      tPckt->GetCnvt(ReaderVersion,CnvtDta);

	  Cigi_uint16 minExtensionDataPacketID = ProcessingVersion.CigiMajorVersion < 4 ?201 : 0x1000;
	  Cigi_uint16 maxExtensionDataPacketID = ProcessingVersion.CigiMajorVersion < 4 ?255 : 0xfffe;
	  if( CnvtDta.ProcID == CigiProcessType::ProcNone && CnvtDta.CnvtPacketID == 0 &&
	  	PacketID >= minExtensionDataPacketID && PacketID <= maxExtensionDataPacketID ) {
	  	CnvtDta.CnvtPacketID = PacketID;
	  	CnvtDta.ProcID = CigiProcessType::ProcStd;;
	  }

      switch(CnvtDta.ProcID)
      {
      case CigiProcessType::ProcStd:   // Most Packets
      case CigiProcessType::ProcVarSize:
         tPckt->Unpack(Dta,Swap,NULL);
         ProcessPacket(CnvtDta.CnvtPacketID,tPckt);
         break;

      case CigiProcessType::ProcEntity:  // Entity Control Packets
         tPckt->Unpack(Dta,Swap,ATbl);
         ProcessPacket(CnvtDta.CnvtPacketID,tPckt);
         break;

      case CigiProcessType::ProcEnvCtrl:
         {
            // Environment Control Packets
            // Atmosphere Control Packets
            // & Celestial Sphere Control Packets
            tPckt->Unpack(Dta,Swap,&EnvHoldObj);
            CigiBaseEnvCtrl *pEnv = (CigiBaseEnvCtrl *)tPckt;
            pEnv->FillHold(&EnvHoldObj);

            if(ProcessingVersion.CigiMajorVersion >= 3)
            {
               // From V3 or above
               if(ReaderVersion.CigiMajorVersion >= 3)
               {
                  // To V3 or above (we shouldn't ever get here as these should be ProcStd)
                  ProcessPacket(CnvtDta.CnvtPacketID,tPckt);
               }
               else
               {
                  // To V1 or V2
                  // V1 Env Ctrl & V2 Env Ctrl have the same ID number
                  EnvHoldObj.SetPacketID(CIGI_ENV_CTRL_PACKET_ID_V2);
                  if(ProcessingVersion.CigiMajorVersion == 1)
                  {
                     EnvHoldObj.SetPacketSize(CIGI_ENV_CTRL_PACKET_SIZE_V1);
                  }
                  else
                  {
                     EnvHoldObj.SetPacketSize(CIGI_ENV_CTRL_PACKET_SIZE_V2);
                  }
                  ProcessPacket(CIGI_ENV_CTRL_PACKET_ID_V2,&EnvHoldObj);
               }
            }
            else  // V1 or V2
            {
               if(ReaderVersion.CigiMajorVersion >= 4)
               {
                  // To V4 or above
                  EnvHoldObj.SetPacketID(CIGI_ATMOS_CTRL_PACKET_ID_V4);
                  EnvHoldObj.SetPacketSize(CIGI_ATMOS_CTRL_PACKET_SIZE_V4);
                  ProcessPacket(CIGI_ATMOS_CTRL_PACKET_ID_V4,&EnvHoldObj);

                  EnvHoldObj.SetPacketID(CIGI_CELESTIAL_CTRL_PACKET_ID_V4);
                  EnvHoldObj.SetPacketSize(CIGI_CELESTIAL_CTRL_PACKET_SIZE_V4);
                  ProcessPacket(CIGI_CELESTIAL_CTRL_PACKET_ID_V4,&EnvHoldObj);
               }
	       else if (ReaderVersion.CigiMajorVersion >= 3)
	       {
		   // To V3
		   EnvHoldObj.SetPacketID(CIGI_ATMOS_CTRL_PACKET_ID_V3);
		   EnvHoldObj.SetPacketSize(CIGI_ATMOS_CTRL_PACKET_SIZE_V3);
		   ProcessPacket(CIGI_ATMOS_CTRL_PACKET_ID_V3, &EnvHoldObj);

		   EnvHoldObj.SetPacketID(CIGI_CELESTIAL_CTRL_PACKET_ID_V3);
		   EnvHoldObj.SetPacketSize(CIGI_CELESTIAL_CTRL_PACKET_SIZE_V3);
		   ProcessPacket(CIGI_CELESTIAL_CTRL_PACKET_ID_V3, &EnvHoldObj);
	       }
	       else
               {
                  // To V1 or V2
                  // V1 Env Ctrl & V2 Env Ctrl have the same ID number
                  EnvHoldObj.SetPacketID(CIGI_ENV_CTRL_PACKET_ID_V2);
                  if(ProcessingVersion.CigiMajorVersion == 1)
                  {
                     EnvHoldObj.SetPacketSize(CIGI_ENV_CTRL_PACKET_SIZE_V1);
                  }
                  else
                  {
                     EnvHoldObj.SetPacketSize(CIGI_ENV_CTRL_PACKET_SIZE_V2);
                  }
                  ProcessPacket(CIGI_ENV_CTRL_PACKET_ID_V2,tPckt);
               }
            }
         }

         break;

      case CigiProcessType::ProcShortArtPartToArtPart:
         {
            // A special case of CIGI version 3 and later
            //  Short Articulated Part being converted
            //  to a CIGI Version 1 or 2 Articulated Part
            tPckt->Unpack(Dta,Swap,&EnvHoldObj);
            CigiBaseShortArtPartCtrl *pSArtPart = (CigiBaseShortArtPartCtrl *)tPckt;
            Cigi_uint8 ArtPartID1 = pSArtPart->GetArtPart1();
            Cigi_uint8 ArtPartID2 = pSArtPart->GetArtPart2();
            CigiArtPartCtrlV3 tArtPart;
            pSArtPart->SpecialConversion(ReaderVersion,ArtPartID1,&tArtPart);
            ProcessPacket(CnvtDta.CnvtPacketID,&tArtPart);
            if(ArtPartID2 != ArtPartID1)
            {
               CigiArtPartCtrlV3 tArtPart2;
               pSArtPart->SpecialConversion(ReaderVersion,ArtPartID2,&tArtPart2);
               ProcessPacket(CnvtDta.CnvtPacketID,&tArtPart2);
            }
         }

         break;

      case CigiProcessType::ProcIGCtrl:
         // IG Control Packets
         // If the Session is a Host session or
         //  this is not the first packet to be
         //  processed, an IG Control packet
         //  should not be here and will skipped
         //  and not processed.
         if(Session->IsIG() && (ReadCnt == 0))
         {
            tPckt->Unpack(Dta,false,NULL);

            CigiBaseIGCtrl *tIGCtrl = (CigiBaseIGCtrl *)tPckt;
 //           Swap = tIGCtrl->GetSwap(); // This is moved to CheckFirstPacket()

            ProcessPacket(CnvtDta.CnvtPacketID,tPckt);
         }
         break;

      case CigiProcessType::ProcSOF:
         // Start Of Frame Packets
         // If the Session is an IG session or
         //  this is not the first packet to be
         //  processed, a Start-Of-Frame packet
         //  should not be here and will skipped
         //  and not processed.
         if(Session->IsHost() && (ReadCnt == 0))
         {
            tPckt->Unpack(Dta,false,NULL);

            CigiBaseSOF *tSOF = (CigiBaseSOF *)tPckt;
//            Swap = tSOF->GetSwap(); // This is moved to CheckFirstPacket()

            ProcessPacket(CnvtDta.CnvtPacketID,tPckt);
         }
         break;

      case CigiProcessType::TwoPassCnvtProcNone:
      case CigiProcessType::TwoPassCnvtProcStd:
         // Packets requiring unpacking to determine
         //  final conversion method
         tPckt->Unpack(Dta,Swap,NULL);

         tPckt->GetCnvt(ReaderVersion,CnvtDta);

         if(CnvtDta.ProcID == CigiProcessType::TwoPassCnvtProcStd)
            ProcessPacket(CnvtDta.CnvtPacketID,tPckt);

         break;
      default:
         break;
      }

      // Go to the next packet
      Dta += PacketSize;
      ReadCnt += PacketSize;
   }

   return(CIGI_SUCCESS);

}

// ================================================
// CheckFirstPacket
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::CheckFirstPacket(Cigi_uint8 *Buff)
{
   // IG Ctrl for IGs & SOF or Hosts
   // Get version
   //   verify valid version
   //   switch version if needed
   //   switch MostMatureCigiVersionReceived if needed
   Cigi_uint16 SOF_PacketID = 101;
   Cigi_uint16 IGCTRL_PacketID = 1;
   Cigi_uint16 PacketID = *Buff;


   // Get the CIGI version used by the message
   CigiVersionID tVer;

   // Get the Major CIGI version used by the message
   //  The version ID is in the same location in all
   //    IGCtrl & SOF packets version 3 or earlier.
   tVer.CigiMajorVersion = *(Buff + 2);
   // check if version 4 or later
   if( ( tVer.CigiMajorVersion == 0xff ) || 
       ( tVer.CigiMajorVersion == 0x00 ) )  {
         tVer.CigiMajorVersion = *(Buff + 4 );
         SOF_PacketID = 0xffff;
         IGCTRL_PacketID = 0x0000;

	 // Determine if byte swapping is required using the Cigi4 method
	 Swap = ((*(Cigi_uint16 *)Buff & 0xff) == 0);
	 if (Swap)
	     CigiSwap2(&PacketID, Buff + 2);
	 else
	     PacketID = *(Cigi_uint16 *)(Buff + 2);
   }
   else if (tVer.CigiMajorVersion == 3) {
       // Determine if byte swapping is required using the Cigi3 method
       Swap = ((*(Cigi_uint16 *)(Buff + 6)) == 0x80);
   }

   bool IsSOF = false;

   if(tVer.CigiMajorVersion >= 3)
   {
   // Verify that this is a valid packet to receive
	   if(Session->IsHost())
	   {
		  if(PacketID != SOF_PacketID)
		  {
			 // A host must receive a SOF Packet
#ifndef CIGI_NO_EXCEPT
			 throw CigiMissingStartOfFrameException();
#endif
			 return(CIGI_ERROR_MISSING_SOF_PACKET);
		  }

		  IsSOF = true;
	   }
	   else
	   {
		  if(PacketID != IGCTRL_PacketID)
		  {
			 // An IG must receive an IG Control Packet
#ifndef CIGI_NO_EXCEPT
			 throw CigiMissingIgControlException();
#endif
			 return(CIGI_ERROR_MISSING_IG_CONTROL_PACKET);
		  }
	   }

   // CIGI versions 1 & 2 have minor versions of 0
   // If the CIGI Major version is 3 later, the
   //   Minor version must be determined.
      //  Unfortunately The minor version ID is in different locations
      int Minor = 0;
      if(IsSOF)
         Minor = (int) *(Buff + 5);
      else
         Minor = (int) *(Buff + 4);
      if( tVer.CigiMajorVersion >= 4 ) Minor = (int) *(Buff + 7);
      tVer.CigiMinorVersion = (Minor >> 4) & 0x0000000f;
   } // end if(tVer.CigiMajorVersion <= 3)

   // Verify that the version is a known version
   bool ValidVer = tVer.IsKnownCigiVersion();

   // if not valid determine best match version
   if(!ValidVer)
      tVer.BestCigiVersion();

   // Check the version against the current processing version
   if(tVer != ProcessingVersion)
   {
      // Change processing to the new version
      ProcessingVersion = tVer;
      ClearTbls(false);

      if(Session->IsHost())
      {
         if(tVer.CigiMajorVersion == 4)
            SetIncomingHostV4Tbls();
         else if(tVer.CigiMajorVersion == 3)
            SetIncomingHostV3Tbls();
         else if(tVer.CigiMajorVersion == 2)
            SetIncomingHostV2Tbls();
         else if(tVer.CigiMajorVersion == 1)
            SetIncomingHostV1Tbls();
      }
      else
      {
         if(tVer.CigiMajorVersion == 4)
            SetIncomingIGV4Tbls();
         else if(tVer.CigiMajorVersion == 3)
            SetIncomingIGV3Tbls();
         else if(tVer.CigiMajorVersion == 2)
            SetIncomingIGV2Tbls();
         else if(tVer.CigiMajorVersion == 1)
            SetIncomingIGV1Tbls();
      }

      // Call back user code so it can re-register user defined extension packet classes
      if (VersionChangeCallback() != NULL) {
	  VersionChangeCallback()(tVer.CigiMajorVersion, tVer.CigiMinorVersion, VersionChangeCallbackUser());
      }
   }

   if(tVer.GetCombinedCigiVersion() >
      MostMatureCigiVersionReceived.GetCombinedCigiVersion())
   {
      MostMatureCigiVersionReceived = tVer;
      Session->SetMostMatureReceivedCigiVersion(tVer);
   }

   return(CIGI_SUCCESS);
}


// ================================================
// ProcessPacket
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::ProcessPacket(int PcktId, CigiBasePacket *Pckt)
{

#ifndef CIGI_NO_EVENT_PROCESSING
   // Process all Event handlers for this packet
   if(!EventList[PcktId].empty())
   {
      list<CigiBaseEventProcessor *>::iterator iEvent = EventList[PcktId].begin();
      while(iEvent != EventList[PcktId].end())
      {
         (*iEvent)->OnPacketReceived(Pckt);
         iEvent++;
      }
   }
#endif

#ifndef CIGI_NO_CALLBACK
   // Process all Callbacks for this packet
   if(!CallBackList[PcktId].empty())
   {
      list<CigiCBProcessor>::iterator iCB = CallBackList[PcktId].begin();
      while(iCB != CallBackList[PcktId].end())
      {
         (*iCB)(Pckt);
         iCB++;
      }
   }
#endif

#ifndef CIGI_NO_SIGNAL_PROCESSING
   // Process all Signal handlers
   SignalJump(PcktId,Pckt);
#endif

}


// ================================================
// SignalJump
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
bool CigiIncomingMsg::SignalJump(const Cigi_uint16 PacketID, CigiBasePacket *Packet)
{

   CigiSignalType::Type SignalId = SignalTbl[PacketID];

   bool Processed = false;

   list<CigiBaseSignalProcessing *>::iterator iSig;

   for(iSig=SignalList.begin();iSig!=SignalList.end();iSig++)
   {

      Processed = true;

      switch(SignalId)
      {
      case CigiSignalType::SigIGCtrl:
         (*iSig)->OnIGCtrl(Packet);
         break;
      case CigiSignalType::SigEntityCtrl:
         (*iSig)->OnEntityCtrl(Packet);
         break;
      case CigiSignalType::SigViewDef:
         (*iSig)->OnViewDef(Packet);
         break;
      case CigiSignalType::SigViewCtrl:
         (*iSig)->OnViewCtrl(Packet);
         break;
      case CigiSignalType::SigRateCtrl:
         (*iSig)->OnRateCtrl(Packet);
         break;
      case CigiSignalType::SigSensorCtrl:
         (*iSig)->OnSensorCtrl(Packet);
         break;
      case CigiSignalType::SigTrajectory:
         (*iSig)->OnTrajectory(Packet);
         break;
      case CigiSignalType::SigWeatherCtrl:
         (*iSig)->OnWeatherCtrl(Packet);
         break;
      case CigiSignalType::SigCollDetSegDef:
         (*iSig)->OnCollDetSegDef(Packet);
         break;
      case CigiSignalType::SigLosSegReq:
         (*iSig)->OnLosSegReq(Packet);
         break;
      case CigiSignalType::SigLosVectReq:
         (*iSig)->OnLosVectReq(Packet);
         break;
      case CigiSignalType::SigHatReq:
         (*iSig)->OnHatReq(Packet);
         break;
      case CigiSignalType::SigHotReq:
         (*iSig)->OnHotReq(Packet);
         break;
      case CigiSignalType::SigHatHotReq:
         (*iSig)->OnHatHotReq(Packet);
         break;
      case CigiSignalType::SigEnvCtrl:
         (*iSig)->OnEnvCtrl(Packet);
         break;
      case CigiSignalType::SigSpecEffDef:
         (*iSig)->OnSpecEffDef(Packet);
         break;
      case CigiSignalType::SigArtPartCtrl:
         (*iSig)->OnArtPartCtrl(Packet);
         break;
      case CigiSignalType::SigCollDetVolDef:
         (*iSig)->OnCollDetVolDef(Packet);
         break;
      case CigiSignalType::SigShortArtPartCtrl:
         (*iSig)->OnShortArtPartCtrl(Packet);
         break;
      case CigiSignalType::SigConfClampEntityCtrl:
         (*iSig)->OnConfClampEntityCtrl(Packet);
         break;
      case CigiSignalType::SigMaritimeSurfaceCtrl:
         (*iSig)->OnMaritimeSurfaceCtrl(Packet);
         break;
      case CigiSignalType::SigEnvRgnCtrl:
         (*iSig)->OnEnvRgnCtrl(Packet);
         break;
      case CigiSignalType::SigTerrestrialSurfaceCtrl:
         (*iSig)->OnTerrestrialSurfaceCtrl(Packet);
         break;
      case CigiSignalType::SigMotionTrackCtrl:
         (*iSig)->OnMotionTrackCtrl(Packet);
         break;
      case CigiSignalType::SigEarthModelDef:
         (*iSig)->OnEarthModelDef(Packet);
         break;
      case CigiSignalType::SigPostionReq:
         (*iSig)->OnPostionReq(Packet);
         break;
      case CigiSignalType::SigEnvCondReq:
         (*iSig)->OnEnvCondReq(Packet);
         break;
      case CigiSignalType::SigWaveCtrl:
         (*iSig)->OnWaveCtrl(Packet);
         break;
      case CigiSignalType::SigCompCtrl:
         (*iSig)->OnCompCtrl(Packet);
         break;
      case CigiSignalType::SigShortCompCtrl:
         (*iSig)->OnShortCompCtrl(Packet);
         break;
      case CigiSignalType::SigSOF:
         (*iSig)->OnSOF(Packet);
         break;
      case CigiSignalType::SigCollDetSegResp:
         (*iSig)->OnCollDetSegResp(Packet);
         break;
      case CigiSignalType::SigSensorResp:
         (*iSig)->OnSensorResp(Packet);
         break;
      case CigiSignalType::SigSensorXResp:
         (*iSig)->OnSensorXResp(Packet);
         break;
      case CigiSignalType::SigLosResp:
         (*iSig)->OnLosResp(Packet);
         break;
      case CigiSignalType::SigLosXResp:
         (*iSig)->OnLosXResp(Packet);
         break;
      case CigiSignalType::SigHatResp:
         (*iSig)->OnHatResp(Packet);
         break;
      case CigiSignalType::SigHotResp:
         (*iSig)->OnHotResp(Packet);
         break;
      case CigiSignalType::SigHatHotResp:
         (*iSig)->OnHatHotResp(Packet);
         break;
      case CigiSignalType::SigHatHotXResp:
         (*iSig)->OnHatHotXResp(Packet);
         break;
      case CigiSignalType::SigCollDetVolResp:
         (*iSig)->OnCollDetVolResp(Packet);
         break;
      case CigiSignalType::SigPositionResp:
         (*iSig)->OnPositionResp(Packet);
         break;
      case CigiSignalType::SigWeatherCondResp:
         (*iSig)->OnWeatherCondResp(Packet);
         break;
      case CigiSignalType::SigAerosolResp:
         (*iSig)->OnAerosolResp(Packet);
         break;
      case CigiSignalType::SigMaritimeSurfaceResp:
         (*iSig)->OnMaritimeSurfaceResp(Packet);
         break;
      case CigiSignalType::SigTerrestrialSurfaceResp:
         (*iSig)->OnTerrestrialSurfaceResp(Packet);
         break;
      case CigiSignalType::SigAnimationStop:
         (*iSig)->OnAnimationStop(Packet);
         break;
      case CigiSignalType::SigEventNotification:
         (*iSig)->OnEventNotification(Packet);
         break;
      case CigiSignalType::SigIGMsg:
         (*iSig)->OnIGMsg(Packet);
         break;
      case CigiSignalType::SigAtmosCtrl:
         (*iSig)->OnAtmosCtrl(Packet);
         break;
      case CigiSignalType::SigCelestialCtrl:
         (*iSig)->OnCelestialCtrl(Packet);
         break;
      case CigiSignalType::SigSymbolSurfaceDef:
         (*iSig)->OnSymbolSurfaceDef(Packet);
         break;
      case CigiSignalType::SigSymbolCtrl:
         (*iSig)->OnSymbolCtrl(Packet);
         break;
      case CigiSignalType::SigShortSymbolCtrl:
         (*iSig)->OnShortSymbolCtrl(Packet);
         break;
      case CigiSignalType::SigSymbolTextDef:
         (*iSig)->OnSymbolTextDef(Packet);
         break;
      case CigiSignalType::SigSymbolCircleDef:
         (*iSig)->OnSymbolCircleDef(Packet);
         break;
      case CigiSignalType::SigSymbolLineDef:
         (*iSig)->OnSymbolLineDef(Packet);
         break;
      case CigiSignalType::SigSymbolClone:
         (*iSig)->OnSymbolClone(Packet);
         break;

      case CigiSignalType::SigVelocityCtrl: // chas
         (*iSig)->OnVelocityCtrl(Packet);
         break;
      case CigiSignalType::SigAccelerationCtrl: // chas
         (*iSig)->OnAccelerationCtrl(Packet);
         break;
      case CigiSignalType::SigSymbolPolygonDef: // chas
         (*iSig)->OnSymbolPolygonDef(Packet);
         break;
      case CigiSignalType::SigSymbolTexturedCircleDef: // chas
         (*iSig)->OnSymbolTexturedCircleDef(Packet);
         break;
      case CigiSignalType::SigSymbolTexturedPolygonDef: // chas
         (*iSig)->OnSymbolTexturedPolygonDef(Packet);
         break;

      case CigiSignalType::SigEntityPositionCtrl: // chas
         (*iSig)->OnEntityPositionCtrl(Packet);
         break;

      case CigiSignalType::SigAnimationCtrl: // chas
         (*iSig)->OnAnimationControl(Packet);
         break;

      default:
         (*iSig)->OnUnrecognized(Packet);
         break;
      }
   }

   return(Processed);

}



// ====================================================================
// Accessors
// ====================================================================



// ================================================
// GetNextBuffToLoad
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Cigi_uint8 *CigiIncomingMsg::GetNextBuffToLoad(void)
{
   if(AvailBuff.empty())
   {
      CrntFillBuf = new CigiMessageBuffer(BufferSize);
   }
   else
   {
      CrntFillBuf = (*AvailBuff.begin());
      AvailBuff.pop_front();
   }

   if(CrntFillBuf != NULL)
   {
      Buffers.push_back(CrntFillBuf);
      CrntFillBuf->Active = true;
      CrntFillBuf->BufferFillCnt = 0;
      CrntFillBuf->DataPresent = false;
      CrntFillBuf->FillBufferPos = CrntFillBuf->Buffer;
      CrntFillBuf->Locked = false;
      CrntFillBuf->ValidIGCtrlSOF = false;
   }

   return(CrntFillBuf->Buffer);

}


// ================================================
// AdvanceCrntBuffer
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::AdvanceCrntBuffer(void)
{

   if(CrntMsgBuf != NULL)
   {
      if(!Buffers.empty())
      {
         list<CigiMessageBuffer *>::iterator iBuf = Buffers.begin();
         while(iBuf!=Buffers.end())
         {
            if(CrntMsgBuf == (*iBuf))
            {
               AvailBuff.push_back(CrntMsgBuf);
               iBuf = Buffers.erase(iBuf);
               break;
            }
            iBuf++;
         }
      }
   }

   if(Buffers.empty())
   {
      GetNextBuffToLoad();
   }

   CrntMsgBuf = (*Buffers.begin());

}


// ================================================
// GetFirstPacket
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
CigiBasePacket * CigiIncomingMsg::GetFirstPacket()
{
   bool Valid = true;
   CigiBasePacket *FirstPacket = NULL;

   if(!Iteration)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiCalledOutOfSequenceException();
#endif
      Valid = false;
   }

   int Size = CrntMsgBuf->BufferFillCnt;

   if((CrntMsgBuf == NULL) || (Size < 12))
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiImproperPacketException();
#endif
      Valid = false;
   }

   if(Valid)
   {
      int stat = CheckFirstPacket(CrntMsgBuf->Buffer);
      if(stat != CIGI_SUCCESS)
         Valid = false;
   }

   Cigi_uint16 PacketID = 0;
   Cigi_uint16 PacketSize = 0;

   if(Valid)
   {
      CrntPacket = CrntMsgBuf->Buffer;
      ReadBufferPos = 0;

      if (ProcessingVersion.CigiMajorVersion >= 4)
      {
	  PackPointer pBuff;
	  pBuff.c = CrntPacket;
	  if (Swap) {
	      CigiSwap2(&PacketSize, pBuff.s++);
	      CigiSwap2(&PacketID, pBuff.s++);
	  }
	  else {
	      PacketSize = *pBuff.s++;
	      PacketID = *pBuff.s++;
	  }
      }
      else
      {
	  PacketID = *CrntPacket;
	  PacketSize = *(CrntPacket + 1);
      }


      FirstPacket = IncomingHandlerTbl[PacketID];

      CigiCnvtInfoType::Type CnvtDta;
      FirstPacket->GetCnvt(ReaderVersion,CnvtDta);

      if(Session->IsHost())
      {
         if(CnvtDta.ProcID == CigiProcessType::ProcSOF)
         {
            FirstPacket->Unpack(CrntPacket,false,NULL);
         }
         else
         {
#ifndef CIGI_NO_EXCEPT
            throw CigiImproperPacketException();
#endif
            Valid = false;
         }
      }
      else
      {
         if(CnvtDta.ProcID == CigiProcessType::ProcIGCtrl)
         {
            FirstPacket->Unpack(CrntPacket,false,NULL);
         }
         else
         {
#ifndef CIGI_NO_EXCEPT
            throw CigiImproperPacketException();
#endif
            Valid = false;
         }
      }
   }

   if(Valid)
   {
      CrntPacket += PacketSize;
      ReadBufferPos += PacketSize;
   }
   else
      FirstPacket = NULL;

   return(FirstPacket);

}

// ================================================
// GetNextPacket
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
CigiBasePacket * CigiIncomingMsg::GetNextPacket()
{
   CigiBasePacket *tPckt = NULL;
   bool Valid = true;

   if((!Iteration) || (ReadBufferPos <= 0))
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiCalledOutOfSequenceException();
#endif
      Valid = false;
   }

   if(CrntMsgBuf == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiImproperPacketException();
#endif
      Valid = false;
   }

   while((Valid) && (tPckt == NULL))
   {
      if(ReadBufferPos < CrntMsgBuf->BufferFillCnt)
      {
         Cigi_uint16 PacketID;
         Cigi_uint16 PacketSize;

	 if (ProcessingVersion.CigiMajorVersion >= 4)
	 {
	     PackPointer pBuff;
	     pBuff.c = CrntPacket;
	     if (Swap) {
		 CigiSwap2(&PacketSize, pBuff.s++);
		 CigiSwap2(&PacketID, pBuff.s++);
	     }
	     else {
		 PacketSize = *pBuff.s++;
		 PacketID = *pBuff.s++;
	     }
	 }
	 else
	 {
	     PacketID = *CrntPacket;
	     PacketSize = *(CrntPacket + 1);
	 }

         tPckt = IncomingHandlerTbl[PacketID];

         CigiCnvtInfoType::Type CnvtDta;
         tPckt->GetCnvt(ReaderVersion,CnvtDta);

         switch(CnvtDta.ProcID)
         {
         case CigiProcessType::ProcStd:   // Most Packets
         case CigiProcessType::ProcVarSize:
            tPckt->Unpack(CrntPacket,Swap,NULL);
            break;

         case CigiProcessType::ProcEntity:  // Entity Control Packets
            tPckt->Unpack(CrntPacket,Swap,ATbl);
            break;

         case CigiProcessType::ProcEnvCtrl:
            {
               // Environment Control Packets
               // Atmosphere Control Packets
               // & Celestial Sphere Control Packets
               // This will fill the Environment Control
               //   Hold Ojbect and pass that as the packet
               // The user will have to process that to get
               //   the needed data
               tPckt->Unpack(CrntPacket,Swap,&EnvHoldObj);
               CigiBaseEnvCtrl *pEnv = (CigiBaseEnvCtrl *)tPckt;
               pEnv->FillHold(&EnvHoldObj);
               tPckt = &EnvHoldObj;
            }
            break;

         case CigiProcessType::TwoPassCnvtProcNone:
         case CigiProcessType::TwoPassCnvtProcStd:
            // Packets requiring unpacking to determine
            //  final conversion method
            tPckt->Unpack(CrntPacket,Swap,NULL);

            tPckt->GetCnvt(ReaderVersion,CnvtDta);

            if(CnvtDta.ProcID != CigiProcessType::TwoPassCnvtProcStd)
               tPckt = NULL;

            break;

         default:
            tPckt = NULL;
            break;
         }

         // Go to the next packet
         CrntPacket += PacketSize;
         ReadBufferPos += PacketSize;
      }
      else
         Valid = false;
   }


   return(tPckt);

}

// ================================================
// RegisterEventProcessor
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::RegisterEventProcessor(int PacketID, CigiBaseEventProcessor *EventMgr)
{

   if((PacketID < 0)||(PacketID > 0xffff))
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiValueOutOfRangeException("PacketID",PacketID,0,0xffff);
#endif
      return(CIGI_ERROR_VALUE_OUT_OF_RANGE);
   }

   if(EventMgr == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiNullPointerException();
#endif
      return(CIGI_ERROR_UNEXPECTED_NULL);
   }

   EventList[PacketID].push_back(EventMgr);

   return(CIGI_SUCCESS);

}

// ================================================
// UnregisterEventProcessor
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::UnregisterEventProcessor(int PacketID, CigiBaseEventProcessor *EventMgr)
{

   if((PacketID < 0)||(PacketID > 0xffff))
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiValueOutOfRangeException("PacketID",PacketID,0,0xffff);
#endif
      return(CIGI_ERROR_VALUE_OUT_OF_RANGE);
   }

   if(EventMgr == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiNullPointerException();
#endif
      return(CIGI_ERROR_UNEXPECTED_NULL);
   }

   list<CigiBaseEventProcessor *>::iterator iEvent = EventList[PacketID].begin();

   while(iEvent != EventList[PacketID].end())
   {
      if((*iEvent) == EventMgr)
      {
         iEvent = EventList[PacketID].erase(iEvent);
         break;
      }
      else
      {
         iEvent++;
      }
   }

   return(CIGI_SUCCESS);

}

// ================================================
// RegisterCallBack
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::RegisterCallBack(int PacketID, CigiCBProcessor CallBack)
{

   if((PacketID < 0)||(PacketID > 0xffff))
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiValueOutOfRangeException("PacketID",PacketID,0,0xffff);
#endif
      return(CIGI_ERROR_VALUE_OUT_OF_RANGE);
   }

   if(CallBack == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiNullPointerException();
#endif
      return(CIGI_ERROR_UNEXPECTED_NULL);
   }

   CallBackList[PacketID].push_back(CallBack);

   return(CIGI_SUCCESS);

}

// ================================================
// UnregisterCallBack
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::UnregisterCallBack(int PacketID, CigiCBProcessor CallBack)
{

   if((PacketID < 0)||(PacketID > 0xffff))
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiValueOutOfRangeException("PacketID",PacketID,0,0xffff);
#endif
      return(CIGI_ERROR_VALUE_OUT_OF_RANGE);
   }

   if(CallBack == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiNullPointerException();
#endif
      return(CIGI_ERROR_UNEXPECTED_NULL);
   }

   list<CigiCBProcessor>::iterator iCB = CallBackList[PacketID].begin();

   while(iCB != CallBackList[PacketID].end())
   {
      if((*iCB) == CallBack)
      {
         iCB = CallBackList[PacketID].erase(iCB);
         break;
      }
      else
      {
         iCB++;
      }
   }

   return(CIGI_SUCCESS);

}

// ================================================
// RegisterSignalProcessor
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::RegisterSignalProcessor(CigiBaseSignalProcessing *SignalMgr)
{
   if(SignalMgr == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiNullPointerException();
#endif
      return(CIGI_ERROR_UNEXPECTED_NULL);
   }

   SignalList.push_back(SignalMgr);

   return(CIGI_SUCCESS);

}

// ================================================
// UnregisterSignalProcessor
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::UnregisterSignalProcessor(CigiBaseSignalProcessing *SignalMgr)
{
   if(SignalMgr == NULL)
   {
#ifndef CIGI_NO_EXCEPT
      throw CigiNullPointerException();
#endif
      return(CIGI_ERROR_UNEXPECTED_NULL);
   }

   list<CigiBaseSignalProcessing *>::iterator iSig = SignalList.begin();

   while(iSig != SignalList.end())
   {
      if((*iSig) == SignalMgr)
      {
         iSig = SignalList.erase(iSig);
         break;
      }
      else
      {
         iSig++;
      }
   }

   return(CIGI_SUCCESS);

}

// ================================================
// RegisterUserPacket
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiIncomingMsg::RegisterUserPacket(CigiBasePacket *Packet,
                                        Cigi_uint16 PacketID,
                                        bool HostSend,
                                        bool IGSend)
{
   int stat = CIGI_ERROR_INVALID_USER_PACKET;
   bool valid = false;
   if (ProcessingVersion.CigiMajorVersion > 0) {
       Cigi_uint16 minUserPacketID = ProcessingVersion.CigiMajorVersion < 4 ? 201 : 0x1000;
       Cigi_uint16 maxUserPacketID = ProcessingVersion.CigiMajorVersion < 4 ? 255 : 0xfffe;
       valid = ((PacketID >= minUserPacketID) && (PacketID <= maxUserPacketID));
   }
   else {
       // We haven't yet received any CIGI packets so we do not know what version they will be,
       // so allow poath V3 and V4 ranges
       valid = (((PacketID >= 201) && (PacketID <= 255)) || ((PacketID >= 0x1000) && (PacketID <= 0xfffe)));
   }

   if(valid && (Packet != NULL))
   {
       stat = CIGI_SUCCESS;
       if((HostSend && Session->IsIG()) ||
	   (IGSend && Session->IsHost()))
       {
	IncomingHandlerTbl[PacketID] = Packet;
       }
   }
   return(stat);
}


// ================================================
// Clear Tables
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::ClearTbls(bool Complete)
{
   int ndx = 0;

   Cigi_uint16 minUserPacketID = ProcessingVersion.CigiMajorVersion < 4 ? 201 : 0x1000;

   for(ndx=0;ndx<minUserPacketID;ndx++)
   {
      if(IncomingHandlerTbl[ndx] != (CigiBasePacket *)DefaultPckt)
      {
         // delete IncomingHandlerTbl[ndx];
         IncomingHandlerTbl[ndx] = (CigiBasePacket *)DefaultPckt;
      }
   }

   if(Complete)
   {
      for(ndx= minUserPacketID;ndx<0x10000;ndx++)
      {
         if(IncomingHandlerTbl[ndx] != (CigiBasePacket *)DefaultPckt)
         {
            // delete IncomingHandlerTbl[ndx];
            IncomingHandlerTbl[ndx] = (CigiBasePacket *)DefaultPckt;
         }
      }
   }

}


// ================================================
// SetIncomingV1Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingIGV1Tbls(void)
{

   IncomingHandlerTbl[CIGI_IG_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiIGCtrlV1;
   IncomingHandlerTbl[CIGI_ENTITY_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiEntityCtrlV1;
   IncomingHandlerTbl[CIGI_VIEW_DEF_PACKET_ID_V1] = (CigiBasePacket *) new CigiViewDefV1;
   IncomingHandlerTbl[CIGI_VIEW_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiViewCtrlV1;
   IncomingHandlerTbl[CIGI_RATE_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiRateCtrlV1;
   IncomingHandlerTbl[CIGI_SENSOR_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiSensorCtrlV1;
   IncomingHandlerTbl[CIGI_TRAJECTORY_DEF_PACKET_ID_V1] = (CigiBasePacket *) new CigiTrajectoryDefV1;
   IncomingHandlerTbl[CIGI_WEATHER_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiWeatherCtrlV1;
   IncomingHandlerTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V1] = (CigiBasePacket *) new CigiCollDetSegDefV1;
   IncomingHandlerTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V1] = (CigiBasePacket *) new CigiLosSegReqV1;
   IncomingHandlerTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V1] = (CigiBasePacket *) new CigiLosVectReqV1;
   IncomingHandlerTbl[CIGI_HAT_REQ_PACKET_ID_V1] = (CigiBasePacket *) new CigiHatReqV1;
   IncomingHandlerTbl[CIGI_ENV_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiEnvCtrlV1;
   IncomingHandlerTbl[CIGI_SPEC_EFF_DEF_PACKET_ID_V1] = (CigiBasePacket *) new CigiSpecEffDefV1;
   IncomingHandlerTbl[CIGI_ART_PART_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiArtPartCtrlV1;
   IncomingHandlerTbl[CIGI_COMP_CTRL_PACKET_ID_V1] = (CigiBasePacket *) new CigiCompCtrlV1;

}


// ================================================
// SetIncomingV1Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingHostV1Tbls(void)
{

   IncomingHandlerTbl[CIGI_SOF_PACKET_ID_V1] = (CigiBasePacket *) new CigiSOFV1;
   IncomingHandlerTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V1] = (CigiBasePacket *) new CigiCollDetSegRespV1;
   IncomingHandlerTbl[CIGI_SENSOR_RESP_PACKET_ID_V1] = (CigiBasePacket *) new CigiSensorRespV1;
   IncomingHandlerTbl[CIGI_LOS_RESP_PACKET_ID_V1] = (CigiBasePacket *) new CigiLosRespV1;
   IncomingHandlerTbl[CIGI_HAT_RESP_PACKET_ID_V1] = (CigiBasePacket *) new CigiHatRespV1;

}


// ================================================
// SetIncomingV2Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingIGV2Tbls(void)
{

   IncomingHandlerTbl[CIGI_IG_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiIGCtrlV2;
   IncomingHandlerTbl[CIGI_ENTITY_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiEntityCtrlV2;
   IncomingHandlerTbl[CIGI_VIEW_DEF_PACKET_ID_V2] = (CigiBasePacket *) new CigiViewDefV2;
   IncomingHandlerTbl[CIGI_VIEW_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiViewCtrlV2;
   IncomingHandlerTbl[CIGI_RATE_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiRateCtrlV2;
   IncomingHandlerTbl[CIGI_SENSOR_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiSensorCtrlV2;
   IncomingHandlerTbl[CIGI_TRAJECTORY_DEF_PACKET_ID_V2] = (CigiBasePacket *) new CigiTrajectoryDefV2;
   IncomingHandlerTbl[CIGI_WEATHER_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiWeatherCtrlV2;
   IncomingHandlerTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V2] = (CigiBasePacket *) new CigiCollDetSegDefV2;
   IncomingHandlerTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V2] = (CigiBasePacket *) new CigiLosSegReqV2;
   IncomingHandlerTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V2] = (CigiBasePacket *) new CigiLosVectReqV2;
   IncomingHandlerTbl[CIGI_HAT_REQ_PACKET_ID_V2] = (CigiBasePacket *) new CigiHatReqV2;
   IncomingHandlerTbl[CIGI_HOT_REQ_PACKET_ID_V2] = (CigiBasePacket *) new CigiHotReqV2;
   IncomingHandlerTbl[CIGI_ENV_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiEnvCtrlV2;
   IncomingHandlerTbl[CIGI_SPEC_EFF_DEF_PACKET_ID_V2] = (CigiBasePacket *) new CigiSpecEffDefV2;
   IncomingHandlerTbl[CIGI_ART_PART_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiArtPartCtrlV2;
   IncomingHandlerTbl[CIGI_COLL_DET_VOL_DEF_PACKET_ID_V2] = (CigiBasePacket *) new CigiCollDetVolDefV2;
   IncomingHandlerTbl[CIGI_COMP_CTRL_PACKET_ID_V2] = (CigiBasePacket *) new CigiCompCtrlV2;

}


// ================================================
// SetIncomingV2Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingHostV2Tbls(void)
{

   IncomingHandlerTbl[CIGI_SOF_PACKET_ID_V2] = (CigiBasePacket *) new CigiSOFV2;
   IncomingHandlerTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V2] = (CigiBasePacket *) new CigiCollDetSegRespV2;
   IncomingHandlerTbl[CIGI_SENSOR_RESP_PACKET_ID_V2] = (CigiBasePacket *) new CigiSensorRespV2;
   IncomingHandlerTbl[CIGI_LOS_RESP_PACKET_ID_V2] = (CigiBasePacket *) new CigiLosRespV2;
   IncomingHandlerTbl[CIGI_HAT_RESP_PACKET_ID_V2] = (CigiBasePacket *) new CigiHatRespV2;
   IncomingHandlerTbl[CIGI_HOT_RESP_PACKET_ID_V2] = (CigiBasePacket *) new CigiHotRespV2;
   IncomingHandlerTbl[CIGI_COLL_DET_VOL_RESP_PACKET_ID_V2] = (CigiBasePacket *) new CigiCollDetVolRespV2;
   IncomingHandlerTbl[CIGI_IG_MSG_PACKET_ID_V2] = (CigiBasePacket *) new CigiIGMsgV2;

}


// ================================================
// SetIncomingV3Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingIGV3Tbls(void)
{

   if(ProcessingVersion.CigiMinorVersion >= 2)
   {
      if(ProcessingVersion.CigiMinorVersion >= 3)
      {
         IncomingHandlerTbl[CIGI_IG_CTRL_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiIGCtrlV3_3;
         IncomingHandlerTbl[CIGI_ENTITY_CTRL_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiEntityCtrlV3_3;
         IncomingHandlerTbl[CIGI_SYMBOL_SURFACE_DEF_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiSymbolSurfaceDefV3_3;
         IncomingHandlerTbl[CIGI_SYMBOL_CONTROL_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiSymbolCtrlV3_3;
         IncomingHandlerTbl[CIGI_SHORT_SYMBOL_CONTROL_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiShortSymbolCtrlV3_3;
         IncomingHandlerTbl[CIGI_SYMBOL_TEXT_DEFINITION_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiSymbolTextDefV3_3;
         IncomingHandlerTbl[CIGI_SYMBOL_CIRCLE_DEFINITION_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiSymbolCircleDefV3_3;
         IncomingHandlerTbl[CIGI_SYMBOL_LINE_DEFINITION_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiSymbolLineDefV3_3;
         IncomingHandlerTbl[CIGI_SYMBOL_CLONE_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiSymbolCloneV3_3;
         IncomingHandlerTbl[CIGI_COMP_CTRL_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiCompCtrlV3_3;
         IncomingHandlerTbl[CIGI_SHORT_COMP_CTRL_PACKET_ID_V3_3] = (CigiBasePacket *) new CigiShortCompCtrlV3_3;
      }
      else
      {
         IncomingHandlerTbl[CIGI_IG_CTRL_PACKET_ID_V3_2] = (CigiBasePacket *) new CigiIGCtrlV3_2;
         IncomingHandlerTbl[CIGI_ENTITY_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiEntityCtrlV3;
         IncomingHandlerTbl[CIGI_COMP_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiCompCtrlV3;
         IncomingHandlerTbl[CIGI_SHORT_COMP_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiShortCompCtrlV3;
      }
      IncomingHandlerTbl[CIGI_RATE_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiRateCtrlV3_2;
      IncomingHandlerTbl[CIGI_HAT_HOT_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiHatHotReqV3_2;
      IncomingHandlerTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiLosSegReqV3_2;
      IncomingHandlerTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiLosVectReqV3_2;
   }
   else
   {
      IncomingHandlerTbl[CIGI_IG_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiIGCtrlV3;
      IncomingHandlerTbl[CIGI_ENTITY_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiEntityCtrlV3;
      IncomingHandlerTbl[CIGI_RATE_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiRateCtrlV3;
      IncomingHandlerTbl[CIGI_HAT_HOT_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiHatHotReqV3;
      IncomingHandlerTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiLosSegReqV3;
      IncomingHandlerTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiLosVectReqV3;
      IncomingHandlerTbl[CIGI_COMP_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiCompCtrlV3;
      IncomingHandlerTbl[CIGI_SHORT_COMP_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiShortCompCtrlV3;
   }

   IncomingHandlerTbl[CIGI_VIEW_DEF_PACKET_ID_V3] = (CigiBasePacket *) new CigiViewDefV3;
   IncomingHandlerTbl[CIGI_VIEW_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiViewCtrlV3;
   IncomingHandlerTbl[CIGI_SENSOR_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiSensorCtrlV3;
   IncomingHandlerTbl[CIGI_TRAJECTORY_DEF_PACKET_ID_V3] = (CigiBasePacket *) new CigiTrajectoryDefV3;
   IncomingHandlerTbl[CIGI_WEATHER_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiWeatherCtrlV3;
   IncomingHandlerTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V3] = (CigiBasePacket *) new CigiCollDetSegDefV3;
   IncomingHandlerTbl[CIGI_ATMOS_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiAtmosCtrlV3;
   IncomingHandlerTbl[CIGI_CELESTIAL_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiCelestialCtrlV3;
   IncomingHandlerTbl[CIGI_ART_PART_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiArtPartCtrlV3;
   IncomingHandlerTbl[CIGI_COLL_DET_VOL_DEF_PACKET_ID_V3] = (CigiBasePacket *) new CigiCollDetVolDefV3;
   IncomingHandlerTbl[CIGI_SHORT_ART_PART_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiShortArtPartCtrlV3;
   IncomingHandlerTbl[CIGI_CONF_CLAMP_ENTITY_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiConfClampEntityCtrlV3;
   IncomingHandlerTbl[CIGI_MARITIME_SURFACE_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiMaritimeSurfaceCtrlV3;
   IncomingHandlerTbl[CIGI_ENV_RGN_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiEnvRgnCtrlV3;
   IncomingHandlerTbl[CIGI_TERRESTRIAL_SURFACE_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiTerrestrialSurfaceCtrlV3;
   IncomingHandlerTbl[CIGI_MOTION_TRACK_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiMotionTrackCtrlV3;
   IncomingHandlerTbl[CIGI_EARTH_MODEL_DEF_PACKET_ID_V3] = (CigiBasePacket *) new CigiEarthModelDefV3;
   IncomingHandlerTbl[CIGI_POSITION_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiPositionReqV3;
   IncomingHandlerTbl[CIGI_ENV_COND_REQ_PACKET_ID_V3] = (CigiBasePacket *) new CigiEnvCondReqV3;
   IncomingHandlerTbl[CIGI_WAVE_CTRL_PACKET_ID_V3] = (CigiBasePacket *) new CigiWaveCtrlV3;

}


// ================================================
// SetIncomingV3Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingHostV3Tbls(void)
{

   if(ProcessingVersion.CigiMinorVersion >= 2)
   {
      IncomingHandlerTbl[CIGI_SOF_PACKET_ID_V3_2] = (CigiBasePacket *) new CigiSOFV3_2;
      IncomingHandlerTbl[CIGI_LOS_RESP_PACKET_ID_V3_2] = (CigiBasePacket *) new CigiLosRespV3_2;
      IncomingHandlerTbl[CIGI_LOS_XRESP_PACKET_ID_V3_2] = (CigiBasePacket *) new CigiLosXRespV3_2;
      IncomingHandlerTbl[CIGI_HAT_HOT_RESP_PACKET_ID_V3_2] = (CigiBasePacket *) new CigiHatHotRespV3_2;
      IncomingHandlerTbl[CIGI_HAT_HOT_XRESP_PACKET_ID_V3_2] = (CigiBasePacket *) new CigiHatHotXRespV3_2;
   }
   else
   {
      IncomingHandlerTbl[CIGI_SOF_PACKET_ID_V3] = (CigiBasePacket *) new CigiSOFV3;
      IncomingHandlerTbl[CIGI_LOS_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiLosRespV3;
      IncomingHandlerTbl[CIGI_LOS_XRESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiLosXRespV3;
      IncomingHandlerTbl[CIGI_HAT_HOT_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiHatHotRespV3;
      IncomingHandlerTbl[CIGI_HAT_HOT_XRESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiHatHotXRespV3;
   }

   IncomingHandlerTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiCollDetSegRespV3;
   IncomingHandlerTbl[CIGI_SENSOR_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiSensorRespV3;
   IncomingHandlerTbl[CIGI_SENSOR_XRESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiSensorXRespV3;
   IncomingHandlerTbl[CIGI_COLL_DET_VOL_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiCollDetVolRespV3;
   IncomingHandlerTbl[CIGI_POSITION_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiPositionRespV3;
   IncomingHandlerTbl[CIGI_WEATHER_COND_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiWeatherCondRespV3;
   IncomingHandlerTbl[CIGI_AEROSOL_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiAerosolRespV3;
   IncomingHandlerTbl[CIGI_MARITIME_SURFACE_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiMaritimeSurfaceRespV3;
   IncomingHandlerTbl[CIGI_TERRESTRIAL_SURFACE_RESP_PACKET_ID_V3] = (CigiBasePacket *) new CigiTerrestrialSurfaceRespV3;
   IncomingHandlerTbl[CIGI_ANIMATION_STOP_PACKET_ID_V3] = (CigiBasePacket *) new CigiAnimationStopV3;
   IncomingHandlerTbl[CIGI_EVENT_NOTIFICATION_PACKET_ID_V3] = (CigiBasePacket *) new CigiEventNotificationV3;
   IncomingHandlerTbl[CIGI_IG_MSG_PACKET_ID_V3] = (CigiBasePacket *) new CigiIGMsgV3;

}

// ================================================
// SetIncomingV4Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingIGV4Tbls(void)
{

   IncomingHandlerTbl[CIGI_IG_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiIGCtrlV4;
   IncomingHandlerTbl[CIGI_ENTITY_POSITION_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiEntityPositionCtrlV4;
   IncomingHandlerTbl[CIGI_CONF_CLAMP_ENTITY_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiConfClampEntityCtrlV4;
   IncomingHandlerTbl[CIGI_COMP_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiCompCtrlV4;
   IncomingHandlerTbl[CIGI_SHORT_COMP_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiShortCompCtrlV4;
   IncomingHandlerTbl[CIGI_SHORT_ART_PART_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiShortArtPartCtrlV4;
   IncomingHandlerTbl[CIGI_ART_PART_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiArtPartCtrlV4;
   IncomingHandlerTbl[CIGI_VELOCITY_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiVelocityCtrlV4;
   IncomingHandlerTbl[CIGI_ENV_RGN_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiEnvRgnCtrlV4;
   IncomingHandlerTbl[CIGI_CELESTIAL_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiCelestialCtrlV4;
   IncomingHandlerTbl[CIGI_ATMOS_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiAtmosCtrlV4;
   IncomingHandlerTbl[CIGI_WEATHER_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiWeatherCtrlV4;
   IncomingHandlerTbl[CIGI_MARITIME_SURFACE_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiMaritimeSurfaceCtrlV4;
   IncomingHandlerTbl[CIGI_WAVE_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiWaveCtrlV4;
   IncomingHandlerTbl[CIGI_TERRESTRIAL_SURFACE_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiTerrestrialSurfaceCtrlV4;
   IncomingHandlerTbl[CIGI_VIEW_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiViewCtrlV4;
   IncomingHandlerTbl[CIGI_SENSOR_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiSensorCtrlV4;
   IncomingHandlerTbl[CIGI_MOTION_TRACK_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiMotionTrackCtrlV4;
   IncomingHandlerTbl[CIGI_EARTH_MODEL_DEF_PACKET_ID_V4] = (CigiBasePacket *) new CigiEarthModelDefV4;
   IncomingHandlerTbl[CIGI_ACCELERATION_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiAccelerationCtrlV4;
   IncomingHandlerTbl[CIGI_VIEW_DEF_PACKET_ID_V4] = (CigiBasePacket *) new CigiViewDefV4;
   IncomingHandlerTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V4] = (CigiBasePacket *) new CigiCollDetSegDefV4;
   IncomingHandlerTbl[CIGI_COLL_DET_VOL_DEF_PACKET_ID_V4] = (CigiBasePacket *) new CigiCollDetVolDefV4;
   IncomingHandlerTbl[CIGI_HAT_HOT_REQ_PACKET_ID_V4] = (CigiBasePacket *) new CigiHatHotReqV4;
   IncomingHandlerTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V4] = (CigiBasePacket *) new CigiLosSegReqV4;
   IncomingHandlerTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V4] = (CigiBasePacket *) new CigiLosVectReqV4;
   IncomingHandlerTbl[CIGI_POSITION_REQ_PACKET_ID_V4] = (CigiBasePacket *) new CigiPositionReqV4;
   IncomingHandlerTbl[CIGI_ENV_COND_REQ_PACKET_ID_V4] = (CigiBasePacket *) new CigiEnvCondReqV4;
   IncomingHandlerTbl[CIGI_SYMBOL_SURFACE_DEF_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolSurfaceDefV4;
   IncomingHandlerTbl[CIGI_SYMBOL_TEXT_DEFINITION_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolTextDefV4;
   IncomingHandlerTbl[CIGI_SYMBOL_CIRCLE_DEFINITION_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolCircleDefV4;
   IncomingHandlerTbl[CIGI_SYMBOL_POLYGON_DEFINITION_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolPolygonDefV4;
   IncomingHandlerTbl[CIGI_SYMBOL_CLONE_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolCloneV4;
   IncomingHandlerTbl[CIGI_SYMBOL_CONTROL_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolCtrlV4;
   IncomingHandlerTbl[CIGI_SHORT_SYMBOL_CONTROL_PACKET_ID_V4] = (CigiBasePacket *) new CigiShortSymbolCtrlV4;
   IncomingHandlerTbl[CIGI_SYMBOL_TEXTURED_CIRCLE_DEFINITION_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolTexturedCircleDefV4;
   IncomingHandlerTbl[CIGI_SYMBOL_TEXTURED_POLYGON_DEFINITION_PACKET_ID_V4] = (CigiBasePacket *) new CigiSymbolTexturedPolygonDefV4;
   IncomingHandlerTbl[CIGI_ENTITY_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiEntityCtrlV4;
   IncomingHandlerTbl[CIGI_ANIMATION_CTRL_PACKET_ID_V4] = (CigiBasePacket *) new CigiAnimationCtrlV4;
}


// ================================================
// SetIncomingV4Tbls
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetIncomingHostV4Tbls(void)
{
   IncomingHandlerTbl[CIGI_SOF_PACKET_ID_V4] = (CigiBasePacket *) new CigiSOFV4;
   IncomingHandlerTbl[CIGI_HAT_HOT_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiHatHotRespV4;
   IncomingHandlerTbl[CIGI_HAT_HOT_XRESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiHatHotXRespV4;
   IncomingHandlerTbl[CIGI_LOS_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiLosRespV4;
   IncomingHandlerTbl[CIGI_LOS_XRESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiLosXRespV4;
   IncomingHandlerTbl[CIGI_SENSOR_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiSensorRespV4;
   IncomingHandlerTbl[CIGI_SENSOR_XRESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiSensorXRespV4;
   IncomingHandlerTbl[CIGI_POSITION_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiPositionRespV4;
   IncomingHandlerTbl[CIGI_WEATHER_COND_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiWeatherCondRespV4;
   IncomingHandlerTbl[CIGI_AEROSOL_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiAerosolRespV4;
   IncomingHandlerTbl[CIGI_MARITIME_SURFACE_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiMaritimeSurfaceRespV4;
   IncomingHandlerTbl[CIGI_TERRESTRIAL_SURFACE_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiTerrestrialSurfaceRespV4;

   IncomingHandlerTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiCollDetSegRespV4;
   IncomingHandlerTbl[CIGI_COLL_DET_VOL_RESP_PACKET_ID_V4] = (CigiBasePacket *) new CigiCollDetVolRespV4;
   IncomingHandlerTbl[CIGI_ANIMATION_STOP_PACKET_ID_V4] = (CigiBasePacket *) new CigiAnimationStopV4;
   IncomingHandlerTbl[CIGI_EVENT_NOTIFICATION_PACKET_ID_V4] = (CigiBasePacket *) new CigiEventNotificationV4;
   IncomingHandlerTbl[CIGI_IG_MSG_PACKET_ID_V4] = (CigiBasePacket *) new CigiIGMsgV4;

}


// ================================================
// SetReaderVersion
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CigiIncomingMsg::SetReaderVersion(CigiVersionID &Version)
{

   bool ChangeTbl = false;

   if((Version.CigiMajorVersion != ReaderVersion.CigiMajorVersion) ||
      (Version.CigiMinorVersion != ReaderVersion.CigiMinorVersion))
   {
      if(Version.IsKnownCigiVersion())
      {
         // Due to the way the system is organized at this time,
         // the tables only need to change if the major version
         // is changed.
         if(Version.CigiMajorVersion != ReaderVersion.CigiMajorVersion)
            ChangeTbl = true;

         ReaderVersion = Version;
      }
   }

   if(ChangeTbl)  
   {
      // Clear the Signal Table
      for(int ndx=0;ndx<CigiSignalType::SigMax;ndx++)
      {
         SignalTbl[ndx] = CigiSignalType::SigNone; 
      }

      // Set the correct table values
      if(ReaderVersion.CigiMajorVersion >= 4 )
      {
         if(Session->IsHost())
         {
            SignalTbl[CIGI_SOF_PACKET_ID_V4] = CigiSignalType::SigSOF;
            SignalTbl[CIGI_HAT_HOT_RESP_PACKET_ID_V4] = CigiSignalType::SigHatHotResp;
            SignalTbl[CIGI_HAT_HOT_XRESP_PACKET_ID_V4] = CigiSignalType::SigHatHotXResp;
            SignalTbl[CIGI_LOS_RESP_PACKET_ID_V4] = CigiSignalType::SigLosResp;
            SignalTbl[CIGI_LOS_XRESP_PACKET_ID_V4] = CigiSignalType::SigLosXResp;
            SignalTbl[CIGI_SENSOR_RESP_PACKET_ID_V4] = CigiSignalType::SigSensorResp;
            SignalTbl[CIGI_SENSOR_XRESP_PACKET_ID_V4] = CigiSignalType::SigSensorXResp;
            SignalTbl[CIGI_POSITION_RESP_PACKET_ID_V4] = CigiSignalType::SigPositionResp;
            SignalTbl[CIGI_WEATHER_COND_RESP_PACKET_ID_V4] = CigiSignalType::SigWeatherCondResp;
            SignalTbl[CIGI_AEROSOL_RESP_PACKET_ID_V4] = CigiSignalType::SigAerosolResp;
            SignalTbl[CIGI_MARITIME_SURFACE_RESP_PACKET_ID_V4] = CigiSignalType::SigMaritimeSurfaceResp;
            SignalTbl[CIGI_TERRESTRIAL_SURFACE_RESP_PACKET_ID_V4] = CigiSignalType::SigTerrestrialSurfaceResp;

            SignalTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V4] = CigiSignalType::SigCollDetSegResp;
            SignalTbl[CIGI_COLL_DET_VOL_RESP_PACKET_ID_V4] = CigiSignalType::SigCollDetVolResp;
            SignalTbl[CIGI_ANIMATION_STOP_PACKET_ID_V4] = CigiSignalType::SigAnimationStop;
            SignalTbl[CIGI_EVENT_NOTIFICATION_PACKET_ID_V4] = CigiSignalType::SigEventNotification;
            SignalTbl[CIGI_IG_MSG_PACKET_ID_V4] = CigiSignalType::SigIGMsg;
         }
         else
         {
            SignalTbl[CIGI_IG_CTRL_PACKET_ID_V4] = CigiSignalType::SigIGCtrl;
            SignalTbl[CIGI_ENTITY_POSITION_CTRL_PACKET_ID_V4] = CigiSignalType::SigEntityPositionCtrl;
            SignalTbl[CIGI_CONF_CLAMP_ENTITY_CTRL_PACKET_ID_V4] = CigiSignalType::SigConfClampEntityCtrl;
            SignalTbl[CIGI_COMP_CTRL_PACKET_ID_V4] = CigiSignalType::SigCompCtrl;
            SignalTbl[CIGI_SHORT_COMP_CTRL_PACKET_ID_V4] = CigiSignalType::SigShortCompCtrl;
            SignalTbl[CIGI_SHORT_ART_PART_CTRL_PACKET_ID_V4] = CigiSignalType::SigShortArtPartCtrl;
            SignalTbl[CIGI_ART_PART_CTRL_PACKET_ID_V4] = CigiSignalType::SigArtPartCtrl;
            SignalTbl[CIGI_VELOCITY_CTRL_PACKET_ID_V4] = CigiSignalType::SigVelocityCtrl;
            SignalTbl[CIGI_ENV_RGN_CTRL_PACKET_ID_V4] = CigiSignalType::SigEnvRgnCtrl;
            SignalTbl[CIGI_CELESTIAL_CTRL_PACKET_ID_V4] = CigiSignalType::SigCelestialCtrl;
            SignalTbl[CIGI_ATMOS_CTRL_PACKET_ID_V4] = CigiSignalType::SigAtmosCtrl;
            SignalTbl[CIGI_WEATHER_CTRL_PACKET_ID_V4] = CigiSignalType::SigWeatherCtrl;
            SignalTbl[CIGI_MARITIME_SURFACE_CTRL_PACKET_ID_V4] = CigiSignalType::SigMaritimeSurfaceCtrl;
            SignalTbl[CIGI_WAVE_CTRL_PACKET_ID_V4] = CigiSignalType::SigWaveCtrl;
            SignalTbl[CIGI_TERRESTRIAL_SURFACE_CTRL_PACKET_ID_V4] = CigiSignalType::SigTerrestrialSurfaceCtrl;
            SignalTbl[CIGI_VIEW_CTRL_PACKET_ID_V4] = CigiSignalType::SigViewCtrl;
            SignalTbl[CIGI_SENSOR_CTRL_PACKET_ID_V4] = CigiSignalType::SigSensorCtrl;
            SignalTbl[CIGI_MOTION_TRACK_CTRL_PACKET_ID_V4] = CigiSignalType::SigMotionTrackCtrl;
            SignalTbl[CIGI_EARTH_MODEL_DEF_PACKET_ID_V4] = CigiSignalType::SigEarthModelDef;
            SignalTbl[CIGI_ACCELERATION_CTRL_PACKET_ID_V4] = CigiSignalType::SigAccelerationCtrl;
            SignalTbl[CIGI_VIEW_DEF_PACKET_ID_V4] = CigiSignalType::SigViewDef;
            SignalTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V4] = CigiSignalType::SigCollDetSegDef;
            SignalTbl[CIGI_COLL_DET_VOL_DEF_PACKET_ID_V4] = CigiSignalType::SigCollDetVolDef;
            SignalTbl[CIGI_HAT_HOT_REQ_PACKET_ID_V4] = CigiSignalType::SigHatHotReq;
            SignalTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V4] = CigiSignalType::SigLosSegReq;
            SignalTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V4] = CigiSignalType::SigLosVectReq;
            SignalTbl[CIGI_POSITION_REQ_PACKET_ID_V4] = CigiSignalType::SigPostionReq;
            SignalTbl[CIGI_ENV_COND_REQ_PACKET_ID_V4] = CigiSignalType::SigEnvCondReq;
            SignalTbl[CIGI_SYMBOL_SURFACE_DEF_PACKET_ID_V4] = CigiSignalType::SigSymbolSurfaceDef;
            SignalTbl[CIGI_SYMBOL_TEXT_DEFINITION_PACKET_ID_V4] = CigiSignalType::SigSymbolTextDef;
            SignalTbl[CIGI_SYMBOL_CIRCLE_DEFINITION_PACKET_ID_V4] = CigiSignalType::SigSymbolCircleDef;
            SignalTbl[CIGI_SYMBOL_POLYGON_DEFINITION_PACKET_ID_V4] = CigiSignalType::SigSymbolPolygonDef;
            SignalTbl[CIGI_SYMBOL_CLONE_PACKET_ID_V4] = CigiSignalType::SigSymbolClone;
            SignalTbl[CIGI_SYMBOL_CONTROL_PACKET_ID_V4] = CigiSignalType::SigSymbolCtrl;
            SignalTbl[CIGI_SHORT_SYMBOL_CONTROL_PACKET_ID_V4] = CigiSignalType::SigShortSymbolCtrl;
            SignalTbl[CIGI_SYMBOL_TEXTURED_CIRCLE_DEFINITION_PACKET_ID_V4] = CigiSignalType::SigSymbolTexturedCircleDef;
            SignalTbl[CIGI_SYMBOL_TEXTURED_POLYGON_DEFINITION_PACKET_ID_V4] = CigiSignalType::SigSymbolTexturedPolygonDef;
            SignalTbl[CIGI_ENTITY_CTRL_PACKET_ID_V4] = CigiSignalType::SigEntityCtrl;
            SignalTbl[CIGI_ANIMATION_CTRL_PACKET_ID_V4] = CigiSignalType::SigAnimationCtrl;
         }
      }
      else if(ReaderVersion.CigiMajorVersion >= 3)
      {
         if(Session->IsHost())
         {
            SignalTbl[CIGI_SOF_PACKET_ID_V3] = CigiSignalType::SigSOF;
            SignalTbl[CIGI_LOS_RESP_PACKET_ID_V3] = CigiSignalType::SigLosResp;
            SignalTbl[CIGI_LOS_XRESP_PACKET_ID_V3] = CigiSignalType::SigLosXResp;
            SignalTbl[CIGI_HAT_HOT_RESP_PACKET_ID_V3] = CigiSignalType::SigHatHotResp;
            SignalTbl[CIGI_HAT_HOT_XRESP_PACKET_ID_V3] = CigiSignalType::SigHatHotXResp;
            SignalTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V3] = CigiSignalType::SigCollDetSegResp;
            SignalTbl[CIGI_SENSOR_RESP_PACKET_ID_V3] = CigiSignalType::SigSensorResp;
            SignalTbl[CIGI_SENSOR_XRESP_PACKET_ID_V3] = CigiSignalType::SigSensorXResp;
            SignalTbl[CIGI_COLL_DET_VOL_RESP_PACKET_ID_V3] = CigiSignalType::SigCollDetVolResp;
            SignalTbl[CIGI_POSITION_RESP_PACKET_ID_V3] = CigiSignalType::SigPositionResp;
            SignalTbl[CIGI_WEATHER_COND_RESP_PACKET_ID_V3] = CigiSignalType::SigWeatherCondResp;
            SignalTbl[CIGI_AEROSOL_RESP_PACKET_ID_V3] = CigiSignalType::SigAerosolResp;
            SignalTbl[CIGI_MARITIME_SURFACE_RESP_PACKET_ID_V3] = CigiSignalType::SigMaritimeSurfaceResp;
            SignalTbl[CIGI_TERRESTRIAL_SURFACE_RESP_PACKET_ID_V3] = CigiSignalType::SigTerrestrialSurfaceResp;
            SignalTbl[CIGI_ANIMATION_STOP_PACKET_ID_V3] = CigiSignalType::SigAnimationStop;
            SignalTbl[CIGI_EVENT_NOTIFICATION_PACKET_ID_V3] = CigiSignalType::SigEventNotification;
            SignalTbl[CIGI_IG_MSG_PACKET_ID_V3] = CigiSignalType::SigIGMsg;
         }
         else
         {
            SignalTbl[CIGI_IG_CTRL_PACKET_ID_V3] = CigiSignalType::SigIGCtrl;
            SignalTbl[CIGI_RATE_CTRL_PACKET_ID_V3] = CigiSignalType::SigRateCtrl;
            SignalTbl[CIGI_HAT_HOT_REQ_PACKET_ID_V3] = CigiSignalType::SigHatHotReq;
            SignalTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V3] = CigiSignalType::SigLosSegReq;
            SignalTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V3] = CigiSignalType::SigLosVectReq;

            SignalTbl[CIGI_ENTITY_CTRL_PACKET_ID_V3] = CigiSignalType::SigEntityCtrl;
            SignalTbl[CIGI_VIEW_DEF_PACKET_ID_V3] = CigiSignalType::SigViewDef;
            SignalTbl[CIGI_VIEW_CTRL_PACKET_ID_V3] = CigiSignalType::SigViewCtrl;
            SignalTbl[CIGI_SENSOR_CTRL_PACKET_ID_V3] = CigiSignalType::SigSensorCtrl;
            SignalTbl[CIGI_TRAJECTORY_DEF_PACKET_ID_V3] = CigiSignalType::SigTrajectory;
            SignalTbl[CIGI_WEATHER_CTRL_PACKET_ID_V3] = CigiSignalType::SigWeatherCtrl;
            SignalTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V3] = CigiSignalType::SigCollDetSegDef;
            SignalTbl[CIGI_ATMOS_CTRL_PACKET_ID_V3] = CigiSignalType::SigAtmosCtrl;
            SignalTbl[CIGI_CELESTIAL_CTRL_PACKET_ID_V3] = CigiSignalType::SigCelestialCtrl;
            SignalTbl[CIGI_ART_PART_CTRL_PACKET_ID_V3] = CigiSignalType::SigArtPartCtrl;
            SignalTbl[CIGI_COLL_DET_VOL_DEF_PACKET_ID_V3] = CigiSignalType::SigCollDetVolDef;
            SignalTbl[CIGI_SHORT_ART_PART_CTRL_PACKET_ID_V3] = CigiSignalType::SigShortArtPartCtrl;
            SignalTbl[CIGI_CONF_CLAMP_ENTITY_CTRL_PACKET_ID_V3] = CigiSignalType::SigConfClampEntityCtrl;
            SignalTbl[CIGI_MARITIME_SURFACE_CTRL_PACKET_ID_V3] = CigiSignalType::SigMaritimeSurfaceCtrl;
            SignalTbl[CIGI_ENV_RGN_CTRL_PACKET_ID_V3] = CigiSignalType::SigEnvRgnCtrl;
            SignalTbl[CIGI_TERRESTRIAL_SURFACE_CTRL_PACKET_ID_V3] = CigiSignalType::SigTerrestrialSurfaceCtrl;
            SignalTbl[CIGI_MOTION_TRACK_CTRL_PACKET_ID_V3] = CigiSignalType::SigMotionTrackCtrl;
            SignalTbl[CIGI_EARTH_MODEL_DEF_PACKET_ID_V3] = CigiSignalType::SigEarthModelDef;
            SignalTbl[CIGI_POSITION_REQ_PACKET_ID_V3] = CigiSignalType::SigPostionReq;
            SignalTbl[CIGI_ENV_COND_REQ_PACKET_ID_V3] = CigiSignalType::SigEnvCondReq;
            SignalTbl[CIGI_WAVE_CTRL_PACKET_ID_V3] = CigiSignalType::SigWaveCtrl;
            SignalTbl[CIGI_COMP_CTRL_PACKET_ID_V3] = CigiSignalType::SigCompCtrl;
            SignalTbl[CIGI_SHORT_COMP_CTRL_PACKET_ID_V3] = CigiSignalType::SigShortCompCtrl;

            SignalTbl[CIGI_SYMBOL_SURFACE_DEF_PACKET_ID_V3_3] = CigiSignalType::SigSymbolSurfaceDef;
            SignalTbl[CIGI_SYMBOL_CONTROL_PACKET_ID_V3_3] = CigiSignalType::SigSymbolCtrl;
            SignalTbl[CIGI_SHORT_SYMBOL_CONTROL_PACKET_ID_V3_3] = CigiSignalType::SigShortSymbolCtrl;
            SignalTbl[CIGI_SYMBOL_TEXT_DEFINITION_PACKET_ID_V3_3] = CigiSignalType::SigSymbolTextDef;
            SignalTbl[CIGI_SYMBOL_CIRCLE_DEFINITION_PACKET_ID_V3_3] = CigiSignalType::SigSymbolCircleDef;
            SignalTbl[CIGI_SYMBOL_LINE_DEFINITION_PACKET_ID_V3_3] = CigiSignalType::SigSymbolLineDef;
            SignalTbl[CIGI_SYMBOL_CLONE_PACKET_ID_V3_3] = CigiSignalType::SigSymbolClone;

         }
      }
      else if(ReaderVersion.CigiMajorVersion == 2)
      {
         if(Session->IsHost())
         {
            SignalTbl[CIGI_SOF_PACKET_ID_V2] = CigiSignalType::SigSOF;
            SignalTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V2] = CigiSignalType::SigCollDetSegResp;
            SignalTbl[CIGI_SENSOR_RESP_PACKET_ID_V2] = CigiSignalType::SigSensorResp;
            SignalTbl[CIGI_LOS_RESP_PACKET_ID_V2] = CigiSignalType::SigLosResp;
            SignalTbl[CIGI_HAT_RESP_PACKET_ID_V2] = CigiSignalType::SigHatResp;
            SignalTbl[CIGI_HOT_RESP_PACKET_ID_V2] = CigiSignalType::SigHotResp;
            SignalTbl[CIGI_COLL_DET_VOL_RESP_PACKET_ID_V2] = CigiSignalType::SigCollDetVolResp;
            SignalTbl[CIGI_IG_MSG_PACKET_ID_V2] = CigiSignalType::SigIGMsg;
         }
         else
         {
            SignalTbl[CIGI_IG_CTRL_PACKET_ID_V1] = CigiSignalType::SigIGCtrl;
            SignalTbl[CIGI_ENTITY_CTRL_PACKET_ID_V2] = CigiSignalType::SigEntityCtrl;
            SignalTbl[CIGI_VIEW_DEF_PACKET_ID_V2] = CigiSignalType::SigViewDef;
            SignalTbl[CIGI_VIEW_CTRL_PACKET_ID_V2] = CigiSignalType::SigViewCtrl;
            SignalTbl[CIGI_RATE_CTRL_PACKET_ID_V2] = CigiSignalType::SigRateCtrl;
            SignalTbl[CIGI_SENSOR_CTRL_PACKET_ID_V2] = CigiSignalType::SigSensorCtrl;
            SignalTbl[CIGI_TRAJECTORY_DEF_PACKET_ID_V2] = CigiSignalType::SigTrajectory;
            SignalTbl[CIGI_WEATHER_CTRL_PACKET_ID_V2] = CigiSignalType::SigWeatherCtrl;
            SignalTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V2] = CigiSignalType::SigCollDetSegDef;
            SignalTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V2] = CigiSignalType::SigLosSegReq;
            SignalTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V2] = CigiSignalType::SigLosVectReq;
            SignalTbl[CIGI_HAT_REQ_PACKET_ID_V2] = CigiSignalType::SigHatReq;
            SignalTbl[CIGI_HOT_REQ_PACKET_ID_V2] = CigiSignalType::SigHotReq;
            SignalTbl[CIGI_ENV_CTRL_PACKET_ID_V2] = CigiSignalType::SigEnvCtrl;
            SignalTbl[CIGI_SPEC_EFF_DEF_PACKET_ID_V2] = CigiSignalType::SigSpecEffDef;
            SignalTbl[CIGI_ART_PART_CTRL_PACKET_ID_V2] = CigiSignalType::SigArtPartCtrl;
            SignalTbl[CIGI_COLL_DET_VOL_DEF_PACKET_ID_V2] = CigiSignalType::SigCollDetVolDef;
            SignalTbl[CIGI_COMP_CTRL_PACKET_ID_V2] = CigiSignalType::SigCompCtrl;
         }
      }
      else if(ReaderVersion.CigiMajorVersion == 1)
      {
         if(Session->IsHost())
         {
            SignalTbl[CIGI_SOF_PACKET_ID_V1] = CigiSignalType::SigSOF;
            SignalTbl[CIGI_COLL_DET_SEG_RESP_PACKET_ID_V1] = CigiSignalType::SigCollDetSegResp;
            SignalTbl[CIGI_SENSOR_RESP_PACKET_ID_V1] = CigiSignalType::SigSensorResp;
            SignalTbl[CIGI_LOS_RESP_PACKET_ID_V1] = CigiSignalType::SigLosResp;
            SignalTbl[CIGI_HAT_RESP_PACKET_ID_V1] = CigiSignalType::SigHatResp;
         }
         else
         {
            SignalTbl[CIGI_IG_CTRL_PACKET_ID_V1] = CigiSignalType::SigIGCtrl;
            SignalTbl[CIGI_ENTITY_CTRL_PACKET_ID_V1] = CigiSignalType::SigEntityCtrl;
            SignalTbl[CIGI_VIEW_DEF_PACKET_ID_V1] = CigiSignalType::SigViewDef;
            SignalTbl[CIGI_VIEW_CTRL_PACKET_ID_V1] = CigiSignalType::SigViewCtrl;
            SignalTbl[CIGI_RATE_CTRL_PACKET_ID_V1] = CigiSignalType::SigRateCtrl;
            SignalTbl[CIGI_SENSOR_CTRL_PACKET_ID_V1] = CigiSignalType::SigSensorCtrl;
            SignalTbl[CIGI_TRAJECTORY_DEF_PACKET_ID_V1] = CigiSignalType::SigTrajectory;
            SignalTbl[CIGI_WEATHER_CTRL_PACKET_ID_V1] = CigiSignalType::SigWeatherCtrl;
            SignalTbl[CIGI_COLL_DET_SEG_DEF_PACKET_ID_V1] = CigiSignalType::SigCollDetSegDef;
            SignalTbl[CIGI_LOS_SEG_REQ_PACKET_ID_V1] = CigiSignalType::SigLosSegReq;
            SignalTbl[CIGI_LOS_VECT_REQ_PACKET_ID_V1] = CigiSignalType::SigLosVectReq;
            SignalTbl[CIGI_HAT_REQ_PACKET_ID_V1] = CigiSignalType::SigHatReq;
            SignalTbl[CIGI_ENV_CTRL_PACKET_ID_V1] = CigiSignalType::SigEnvCtrl;
            SignalTbl[CIGI_SPEC_EFF_DEF_PACKET_ID_V1] = CigiSignalType::SigSpecEffDef;
            SignalTbl[CIGI_ART_PART_CTRL_PACKET_ID_V1] = CigiSignalType::SigArtPartCtrl;
            SignalTbl[CIGI_COMP_CTRL_PACKET_ID_V1] = CigiSignalType::SigCompCtrl;
         }
      }
   }
}



