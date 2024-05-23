/** <pre>
 *  The CIGI MiniHost
 *  Copyright (c) 2004 The Boeing Company
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  
 *  
 *  FILENAME:   MiniHost.cpp
 *  LANGUAGE:   C++
 *  CLASS:      UNCLASSIFIED
 *  PROJECT:    Multi-Purpose Viewer
 *  
 *  PROGRAM DESCRIPTION: 
 *  This class contains the data and methods necessary to
 *   handle the network interface.
 *  
 *  MODIFICATION NOTES:
 *  DATE     NAME                                SCR NUMBER
 *  DESCRIPTION OF CHANGE........................
 *  
 *  03/29/2004 Andrew Sampson                       MPV_CR_DR_1
 *  Initial Release.
 * </pre>
 *  The Boeing Company
 *  1.0
 */


#include "Network.h"  // network includes winsock2.h which must be included before windows.h


// Tiny XML includes
#define TINYXML_USE_STL
#define TIXML_USE_STL

#include <tinyxml.h>
#include <tinystr.h>


// CIGI related includes
// From CCL
#include <CigiHostSession.h>
#include <CigiExceptions.h>
#include "CigiIGCtrlV4.h"
#include "CigiEntityPositionCtrlV4.h"
#include "CigiConfClampEntityCtrlV4.h"
#include "CigiCompCtrlV4.h"
#include "CigiShortCompCtrlV4.h"
#include "CigiArtPartCtrlV4.h"
#include "CigiShortArtPartCtrlV4.h"
#include "CigiVelocityCtrlV4.h"
#include "CigiEnvRgnCtrlV4.h"
#include "CigiCelestialCtrlV4.h"
#include "CigiAtmosCtrlV4.h"
#include "CigiWeatherCtrlV4.h"
#include "CigiMaritimeSurfaceCtrlV4.h"
#include "CigiWaveCtrlV4.h"
#include "CigiTerrestrialSurfaceCtrlV4.h"
#include "CigiViewCtrlV4.h"
#include "CigiSensorCtrlV4.h"
#include "CigiMotionTrackCtrlV4.h"
#include "CigiEarthModelDefV4.h"
#include "CigiAccelerationCtrlV4.h"
#include "CigiViewDefV4.h"
#include "CigiCollDetSegDefV4.h"
#include "CigiCollDetVolDefV4.h"
#include "CigiHatHotReqV4.h"
#include "CigiLosSegReqV4.h"
#include "CigiLosVectReqV4.h"
#include "CigiPositionReqV4.h"
#include "CigiEnvCondReqV4.h"
#include "CigiSymbolSurfaceDefV4.h"
#include "CigiSymbolTextDefV4.h"
#include "CigiSymbolCircleDefV4.h"
#include "CigiSymbolPolygonDefV4.h"
#include "CigiSymbolCloneV4.h"
#include "CigiSymbolCtrlV4.h"
#include "CigiShortSymbolCtrlV4.h"
#include "CigiSymbolTexturedCircleDefV4.h"
#include "CigiSymbolTexturedPolygonDefV4.h"
#include "CigiEntityCtrlV4.h"
#include "CigiAnimationCtrlV4.h"


// Handling routines
#include "XSOF.h"
#include "XHatHotResp.h"
#include "XHatHotXResp.h"
#include "XLosResp.h"
#include "XLosXResp.h"
#include "XSensorResp.h"
#include "XSensorXResp.h"
#include "XPositionResp.h"
#include "XWeatherCondResp.h"
#include "XAerosolResp.h"
#include "XMaritimeSurfaceResp.h"
#include "XTerrestrialSurfaceResp.h"
#include "XCollDetSegResp.h"
#include "XCollDetVolResp.h"
#include "XAnimationStop.h"
#include "XEventNotification.h"
#include "XIGMsg.h"



// System includes
#include <stdio.h>

#include <iostream>
#include <list>

#ifdef WIN32
#include <Windows.h>
#include <conio.h>
#endif

#include <time.h>

// Special database information structure
typedef struct Database_info
{
   int id;
   double lat;
   double lon;
   double alt;
} DbInfo;



using namespace std;


// ================================================
// Global variables
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

// Networking class/object
Network network;

// CIGI specific 
static CigiHostSession *HostSn;
static CigiOutgoingMsg *OmsgPtr;
static CigiIncomingMsg *ImsgPtr;
//static DefaultProc DefaultPckt;

static CigiIGCtrlV4 CIGC;
static CigiEntityPositionCtrlV4 COwn;
static CigiConfClampEntityCtrlV4 ConfClampEntity;
static CigiCompCtrlV4 CompCtrl;
static CigiShortCompCtrlV4 ShortCompCtrl;
static CigiArtPartCtrlV4 ArtPartCtrl;
static CigiShortArtPartCtrlV4 ShortArtPartCtrl;
static CigiVelocityCtrlV4 VelocityCtrl;
static CigiEnvRgnCtrlV4 EnvRgnCtrl;
static CigiCelestialCtrlV4 CelestialCtrl;
static CigiAtmosCtrlV4 AtmosCtrl;
static CigiWeatherCtrlV4 WeatherCtrl;
static CigiMaritimeSurfaceCtrlV4 MaritimeSurfaceCtrl;
static CigiWaveCtrlV4 WaveCtrl;
static CigiTerrestrialSurfaceCtrlV4 TerrestrialSurfaceCtrl;
static CigiViewCtrlV4 ViewCtrl;
static CigiSensorCtrlV4 SensorCtrl;
static CigiMotionTrackCtrlV4 MotionTrackCtrl;
static CigiEarthModelDefV4 EarthModelDef;
static CigiAccelerationCtrlV4 AccelerationCtrl;
static CigiViewDefV4 ViewDef;
static CigiCollDetSegDefV4 CollDetSegDef;
static CigiCollDetVolDefV4 CollDetVolDef;
static CigiHatHotReqV4 HatHotReq;
static CigiLosSegReqV4 LosSegReq;
static CigiLosVectReqV4 LosVectReq;
static CigiPositionReqV4 PositionReq;
static CigiEnvCondReqV4 EnvCondReq;
static CigiSymbolSurfaceDefV4 SymbolSurfaceDef;
static CigiSymbolTextDefV4 SymbolTextDef;
static CigiSymbolCircleDefV4 SymbolCircleDef;
static CigiSymbolPolygonDefV4 SymbolPolygonDefV4;
static CigiSymbolCloneV4 SymbolClone;
static CigiSymbolCtrlV4 SymbolCtrl;
static CigiShortSymbolCtrlV4 ShortSymbolCtrl;
static CigiSymbolTexturedCircleDefV4 SymbolTexturedCircleDef;
static CigiSymbolTexturedPolygonDefV4 SymbolTexturedPolygonDef;
static CigiEntityCtrlV4 EntityCtrl;
static CigiAnimationCtrlV4 AnimationCtrl;

static XSOF Pr_SOF;
static XHatHotResp Pr_HatHotResp;
static XHatHotXResp Pr_HatHotXResp;
static XLosResp Pr_LosResp;
static XLosXResp Pr_LosXResp;
static XSensorResp Pr_SensorResp;
static XSensorXResp Pr_SensorXResp;
static XPositionResp Pr_PositionResp;
static XWeatherCondResp Pr_WeatherCondResp;
static XAerosolResp Pr_AerosolResp;
static XMaritimeSurfaceResp Pr_MaritimeSurfaceResp;
static XTerrestrialSurfaceResp Pr_TerrestrialSurfaceResp;
static XCollDetSegResp Pr_CollDetSegResp;
static XCollDetVolResp Pr_CollDetVolResp;
static XAnimationStop Pr_AnimationStop;
static XEventNotification Pr_EventNotification;
static XIGMsg Pr_IGMsg;

// CIGI network message buffers and information
int recvLen;
static unsigned char *pCigiOutBuf;

#define RECV_BUFFER_SIZE 32768
static unsigned char CInBuf[RECV_BUFFER_SIZE];

static int CigiInSz;
static int CigiOutSz;

static int Port_H2IG;
static int Port_IG2H;
static string IGAddr;

// The database information
int CurrentDB;

std::list<DbInfo *> dblist;
std::list<DbInfo *>::iterator idbl;



// ================================================
// Pre-declaration of Local routines
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void ReadConfig(void);
int init_cigi_if(void);





// ================================================
// Main
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int main(int argc, char* argv[])
{
   CigiInSz = 0;
   
   ReadConfig();
   
   if(dblist.empty())
   {
      cout << "\n\nNo Database Information!\n\n";
      return(0);
   }
   
   init_cigi_if();
   
   /* CIGI messaging */
   CigiOutgoingMsg &Omsg = *OmsgPtr;
   
 
   
   // Initialize ownship position
   idbl = dblist.begin();
   COwn.SetLat((*idbl)->lat);
   COwn.SetLon((*idbl)->lon);
   COwn.SetAlt((*idbl)->alt);
   COwn.SetYaw(0.0);
   COwn.SetPitch(0.0);
   COwn.SetRoll(0.0);

   
   ConfClampEntity.SetLat((*idbl)->lat);
   ConfClampEntity.SetLon((*idbl)->lon);
   ConfClampEntity.SetYaw(0.0);
   ConfClampEntity.SetEntityID( 0xdead );

   Omsg.BeginMsg();

   while( !_kbhit() )
   {
//      system("cls");
      cout << "================================\n";
      cout << "Frame: " << Omsg.GetFrameCnt() << endl;
      cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";
      /* process incoming CIGI message - this should be short */
      if( CigiInSz > 0 ) {
         try {
            ImsgPtr->ProcessIncomingMsg((unsigned char *)CInBuf,CigiInSz);
         }
         catch( CigiException &theException ){
            std::cout << "getNetMessages - Exception: " << theException.what() << std::endl;
         }
      }

      cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n";


      // load the IG Control
	static unsigned long timestamp = 0;
    timestamp += 8; //dummy timestamp
	 CIGC.SetTimeStamp( timestamp );
     CIGC.SetTimeStampValid( true );
      Omsg << CIGC;
      
      /* Update ownship position and ConfClampEntity */
      double olat = COwn.GetLat();
      COwn.SetLat(olat + 0.0000137);
      ConfClampEntity.SetLat(olat + 0.0000137);

      Omsg << COwn;
//      Omsg << ConfClampEntity;
//      Omsg << CompCtrl;
//      Omsg << ShortCompCtrl;
//      Omsg << ArtPartCtrl;
//      Omsg << ShortArtPartCtrl;
//      Omsg << VelocityCtrl;
//      Omsg << EnvRgnCtrl;
//      Omsg << CelestialCtrl;
//      Omsg << AtmosCtrl;
//      Omsg << WeatherCtrl;
//		Omsg << MaritimeSurfaceCtrl;
//		Omsg << WaveCtrl;
//		Omsg << TerrestrialSurfaceCtrl;
//		Omsg << ViewCtrl;
//		Omsg << SensorCtrl;
//		Omsg << MotionTrackCtrl;
//		Omsg << EarthModelDef;
//		Omsg << AccelerationCtrl;
//		Omsg << ViewDef;
//		Omsg << CollDetSegDef;
//		Omsg << CollDetVolDef;
//		Omsg << HatHotReq;
//		Omsg << LosSegReq;
//		Omsg << LosVectReq;
//		Omsg << PositionReq;
//		Omsg << EnvCondReq;
//		Omsg << SymbolSurfaceDef;
//		Omsg << SymbolTextDef;
//		Omsg << SymbolCircleDef;
//		Omsg << SymbolPolygonDefV4;
//		Omsg << SymbolClone;
//       Omsg << SymbolCtrl;
//		Omsg << ShortSymbolCtrl;
//		Omsg << SymbolTexturedCircleDef;
//		Omsg << SymbolTexturedPolygonDef;
//		Omsg << EntityCtrl;
//		Omsg << AnimationCtrl;


      // Do packaging here to 
      // Package msg
      try {
         Omsg.PackageMsg(&pCigiOutBuf,CigiOutSz);
      } catch( CigiException &theException ){
         std::cout << "getNetMessages - Exception: " << theException.what() << std::endl;
      }


      // wait for Start Of Frame
      time_t HoldTime;
      bool RcvrProc = false;
      time_t CheckTime = time(&HoldTime);
      while(!RcvrProc)
      {
         if((CigiInSz = network.recv( CInBuf, RECV_BUFFER_SIZE )) > 0)
            RcvrProc = true;
         else
         {
            time_t TstTime = time(&HoldTime);
            if((TstTime - CheckTime) > 1)
            {
               cout << "Did not receive SOF\n";
               RcvrProc = true;
               CigiInSz = 0;
            }
         }
      }


      if(pCigiOutBuf != NULL)
      {
         if(CigiInSz > 0)
            Omsg.UpdateIGCtrl(pCigiOutBuf,CInBuf);
         else
            Omsg.UpdateIGCtrl(pCigiOutBuf,NULL);


         // send CIGI message
         int sentBytes = network.send(pCigiOutBuf,CigiOutSz);
      }

      Omsg.FreeMsg();   // Frees the buffer containing the message that was just sent
   }
   
   // shut down the network
   network.closeSocket();
   
//   delete HostSn;
   
   return 0;
}



// ================================================
// Read Configuration
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void ReadConfig(void)
{
   
   TiXmlNode *bnode = NULL;  // base node
   
   TiXmlText *Port_To_Cigi = NULL;
   TiXmlText *Port_From_Cigi = NULL;
   TiXmlText *IG_Addr = NULL;
   
   TiXmlHandle *hConfig = NULL; // pointer to a Config handle
   
   TiXmlElement *Config = NULL;
   
   TiXmlText *DbDta = NULL;
   
   
   
   
   TiXmlDocument doc("MiniHost.def");
   bool stat = doc.LoadFile();
   
   //set default values
   Port_H2IG = 8000;
   Port_IG2H = 8001;
   IGAddr = "127.0.0.1";
   
   
   if(stat)
   {
      bnode = doc.FirstChild("MiniHostInitialization");
      
      if(bnode == NULL)
         stat = false;  // The file is not a Mission Function Initialization file
   }
   
   
   if(stat)
   {
      // get base configuration
      Config = bnode->FirstChildElement("Config");
      
      if(Config != NULL)
      {
         hConfig = new TiXmlHandle(Config);
         
         
         IG_Addr = hConfig->FirstChildElement("IG_Addr").Child(0).Text();
         if(IG_Addr)
            IGAddr = IG_Addr->Value();
         
         Port_To_Cigi = hConfig->FirstChildElement("Port_To_IG").Child(0).Text();
         Port_H2IG = (Port_To_Cigi) ? atoi(Port_To_Cigi->Value()) : 8000;
         
         Port_From_Cigi = hConfig->FirstChildElement("Port_From_IG").Child(0).Text();
         Port_IG2H = (Port_From_Cigi) ? atoi(Port_From_Cigi->Value()) : 8001;
         
         delete hConfig;
         
      }
      
      
      
      // get Database configuration
      Config = bnode->FirstChildElement("DBase");
      
      while(Config != NULL)
      {
         hConfig = new TiXmlHandle(Config);
         
         DbInfo *pDbInfo = new DbInfo;
         
         DbDta = hConfig->FirstChildElement("ID").Child(0).Text();
         pDbInfo->id = (DbDta) ? atoi(DbDta->Value()) : 5;
         
         DbDta = hConfig->FirstChildElement("Lat").Child(0).Text();
         pDbInfo->lat = (DbDta) ? atof(DbDta->Value()) : 0.0;
         
         DbDta = hConfig->FirstChildElement("Lon").Child(0).Text();
         pDbInfo->lon = (DbDta) ? atof(DbDta->Value()) : 0.0;
         
         DbDta = hConfig->FirstChildElement("Alt").Child(0).Text();
         pDbInfo->alt = (DbDta) ? atof(DbDta->Value()) : 0.0;
         
         dblist.push_back(pDbInfo);
         
         Config = Config->NextSiblingElement("DBase");
      }
      
   }
   
}



// ================================================
// Initialize interface to CIGI
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int init_cigi_if(void){
   int err_status = 0;
   
   /* open sockets to CIGI */
   // hostemu-ip-addr, hostemu-socket, local-socket
   printf("init_cigi_if: initializing ports to CIGI\n");
   bool netstatus = network.openSocket( 
      IGAddr.c_str(), 
      Port_H2IG, 
      Port_IG2H );
   
   if( !netstatus ) {
      printf( "could not connect to CIGI IG server\n" );
      exit( 1 );
   } else {
      printf( "successfully connected to CIGI IG server\n" );
   }
   
   
   HostSn = new CigiHostSession(1,32768,2,32768);
   
   CigiOutgoingMsg &Omsg = HostSn->GetOutgoingMsgMgr();
   CigiIncomingMsg &Imsg = HostSn->GetIncomingMsgMgr();
   OmsgPtr = &Omsg;
   ImsgPtr = &Imsg;
   
   HostSn->SetCigiVersion(4,0);
   HostSn->SetSynchronous(true);
   
   Imsg.SetReaderCigiVersion(4,0);
   Imsg.UsingIteration(false);
   
   // set up a default handler for unhandled packets
//   Imsg.RegisterEventProcessor(0, (CigiBaseEventProcessor *) &DefaultPckt);
   
   // register SOF
   Imsg.RegisterEventProcessor(CIGI_SOF_PACKET_ID_V4, (CigiBaseEventProcessor *) &Pr_SOF);
   Imsg.RegisterEventProcessor(CIGI_HAT_HOT_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_HatHotResp);
   Imsg.RegisterEventProcessor(CIGI_HAT_HOT_XRESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_HatHotXResp);
   Imsg.RegisterEventProcessor(CIGI_LOS_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_LosResp);
   Imsg.RegisterEventProcessor(CIGI_LOS_XRESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_LosXResp);
   Imsg.RegisterEventProcessor(CIGI_SENSOR_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_SensorResp);
   Imsg.RegisterEventProcessor(CIGI_SENSOR_XRESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_SensorXResp);
   Imsg.RegisterEventProcessor(CIGI_POSITION_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_PositionResp);
   Imsg.RegisterEventProcessor(CIGI_WEATHER_COND_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_WeatherCondResp);
   Imsg.RegisterEventProcessor(CIGI_AEROSOL_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_AerosolResp);
   Imsg.RegisterEventProcessor(CIGI_MARITIME_SURFACE_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_MaritimeSurfaceResp);
   Imsg.RegisterEventProcessor(CIGI_TERRESTRIAL_SURFACE_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_TerrestrialSurfaceResp);
   Imsg.RegisterEventProcessor(CIGI_COLL_DET_SEG_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_CollDetSegResp);
   Imsg.RegisterEventProcessor(CIGI_COLL_DET_VOL_RESP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_CollDetVolResp);
   Imsg.RegisterEventProcessor(CIGI_ANIMATION_STOP_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_AnimationStop);
   Imsg.RegisterEventProcessor(CIGI_EVENT_NOTIFICATION_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_EventNotification);
   Imsg.RegisterEventProcessor(CIGI_IG_MSG_PACKET_ID_V4,
                              (CigiBaseEventProcessor *) &Pr_IGMsg);


#if 0


	Imsg.RegisterEventProcessor(0, (CigiBaseEventProcessor *) &AllProc);


   // Register all the callback processors
   Imsg.RegisterCallBack(CIGI_SOF_PACKET_ID_V3,
                              (CigiCBProcessor) &YSOF);
   Imsg.RegisterCallBack(CIGI_COLL_DET_SEG_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YCollDetSegResp);
   Imsg.RegisterCallBack(CIGI_LOS_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YLosResp);
   Imsg.RegisterCallBack(CIGI_LOS_XRESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YLosXResp);
   Imsg.RegisterCallBack(CIGI_HAT_HOT_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YHatHotResp);
   Imsg.RegisterCallBack(CIGI_HAT_HOT_XRESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YHatHotXResp);
   Imsg.RegisterCallBack(CIGI_COLL_DET_VOL_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YCollDetVolResp);
   Imsg.RegisterCallBack(CIGI_POSITION_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YPositionResp);
   Imsg.RegisterCallBack(CIGI_WEATHER_COND_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YWeatherCondResp);
   Imsg.RegisterCallBack(CIGI_AEROSOL_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YAerosolResp);
   Imsg.RegisterCallBack(CIGI_MARITIME_SURFACE_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YMaritimeSurfaceResp);
   Imsg.RegisterCallBack(CIGI_TERRESTRIAL_SURFACE_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YTerrestrialSurfaceResp);
   Imsg.RegisterCallBack(CIGI_ANIMATION_STOP_PACKET_ID_V4,
                              (CigiCBProcessor) &YAnimationStop);
   Imsg.RegisterCallBack(CIGI_EVENT_NOTIFICATION_PACKET_ID_V4,
                              (CigiCBProcessor) &YEventNotification);
   Imsg.RegisterCallBack(CIGI_IG_MSG_PACKET_ID_V4,
                              (CigiCBProcessor) &YIGMsg);
   Imsg.RegisterCallBack(CIGI_SENSOR_RESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YSensorResp);
   Imsg.RegisterCallBack(CIGI_SENSOR_XRESP_PACKET_ID_V4,
                              (CigiCBProcessor) &YSensorXResp);

	Imsg.RegisterCallBack(0, (CigiCBProcessor) &YDeflt);



   // Register the signal processor object
   Imsg.RegisterSignalProcessor(&SigProc);

#endif
   //Register animation stop
   
   // initialize the IG Control
   CIGC.SetIGMode(CigiBaseIGCtrl::Operate);
   
   
   // initialize the Ownship
   //  the other parameters are set by CigiEntityCtrlV4
   COwn.SetEntityID(0);
   COwn.SetParentID(0);
   
   
   return err_status;
}









