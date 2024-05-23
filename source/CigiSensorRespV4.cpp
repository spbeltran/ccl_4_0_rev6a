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
 *  FILENAME:   CigiSensorRespV4.cpp
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
 *  09/17/2003 Greg Basler                       CIGI_CR_DR_1
 *  Initial Release.
 *  
 *  01/21/2005 Greg Basler                       Version 1.5
 *  Defined _EXPORT_CCL_ for exporting the class in a Windows DLL.
 *  
 *  01/21/2005 Greg Basler                       Version 1.5
 *  Removed the inline defnitions for the PackedPointer union.
 *  
 *  04/14/2006 Greg Basler                       Version 1.7.0
 *  Modified the class constructor to initialize the MinorVersion member 
 *  variable.
 *  
 *  06/23/2006 Greg Basler                       Version 1.7.1
 *  Changed native char and unsigned char types to CIGI types Cigi_int8 and 
 *  Cigi_uint8.
 *  
 *  07/29/2015 Chas Whitley                      Version 4.0.0
 *  Initial Release for CIGI 4.0 compatibility.
 *  Based on CigiSensorRespV3.cpp
 *
 * </pre>
 *  Author: The Boeing Company
 *
 */

#define _EXPORT_CCL_

#include "CigiSensorRespV4.h"
#include "CigiSwapping.h"
#include "CigiExceptions.h"


// ====================================================================
// Construction/Destruction
// ====================================================================


// ================================================
// CigiSensorRespV4
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
CigiSensorRespV4::CigiSensorRespV4()
{

   PacketID = CIGI_SENSOR_RESP_PACKET_ID_V4;
   PacketSize = CIGI_SENSOR_RESP_PACKET_SIZE_V4;
   Version = 4;
   MinorVersion = 0;

   ViewID = 0;
   SensorID = 0;
   SensorStat = Searching;
   EntityTgt = false;
   EntityID = 0;
   GateSzX = 0;
   GateSzY = 0;
   GateXoff = 0.0;
   GateYoff = 0.0;
   FrameCntr = 0;
   TrackPntLat = 0.0;
   TrackPntLon = 0.0;
   TrackPntAlt = 0.0;

}

// ================================================
// ~CigiSensorRespV4
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
CigiSensorRespV4::~CigiSensorRespV4()
{

}

// ====================================================================
// Pack and Unpack
// ====================================================================

// ================================================
// Pack
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiSensorRespV4::Pack(CigiBasePacket * Base, Cigi_uint8 * Buff, void *Spec) const
{
   PackPointer CDta;

   CigiBaseSensorResp * Data = ( CigiBaseSensorResp *)Base;

   CDta.c = Buff;

   *CDta.s++ = PacketSize;
   *CDta.s++ = PacketID;

   *CDta.c++ = Data->SensorID;
   Cigi_uint8 HDta = (Cigi_uint8)(Data->SensorStat & 0x03);
   *CDta.c++ = HDta;
   *CDta.s++ = Data->ViewID;

   *CDta.s++ = Data->GateSzX;
   *CDta.s++ = Data->GateSzY;
   *CDta.f++ = Data->GateXoff;
   *CDta.f++ = Data->GateYoff;
   *CDta.l++ = Data->FrameCntr;

   return(PacketSize);

}

// ================================================
// Unpack
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int CigiSensorRespV4::Unpack(Cigi_uint8 * Buff, bool Swap, void *Spec)
{
   PackPointer CDta;

   CDta.c = Buff;

   CDta.c += 4;  // Step over packet id and size

   if(!Swap)
   {
      SensorID = *CDta.c++;

      Cigi_uint8 HDta = *CDta.c++;
      SensorStat = (SensorStatGrp)(HDta & 0x03);

      ViewID = *CDta.s++;

      GateSzX = *CDta.s++;
      GateSzY = *CDta.s++;
      GateXoff = *CDta.f++;
      GateYoff = *CDta.f++;
      FrameCntr = *CDta.l++;
   }
   else
   {
      SensorID = *CDta.c++;

      Cigi_uint8 HDta = *CDta.c++;
      SensorStat = (SensorStatGrp)(HDta & 0x03);

      CigiSwap2(&ViewID, CDta.s++);

      CigiSwap2(&GateSzX, CDta.s++);
      CigiSwap2(&GateSzY, CDta.s++);
      CigiSwap4(&GateXoff, CDta.f++);
      CigiSwap4(&GateYoff, CDta.f++);
      CigiSwap4(&FrameCntr, CDta.l++);
   }

   return(PacketSize);

}



// ====================================================================
// Accessors
// ====================================================================


