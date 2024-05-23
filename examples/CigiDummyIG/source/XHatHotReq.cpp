// XHatHotReq.cpp: Body of the XHatHotReq class.
//
//////////////////////////////////////////////////////////////////////

#include "XHatHotReq.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XHatHotReq::XHatHotReq()
{

}

XHatHotReq::~XHatHotReq()
{

}


void XHatHotReq::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiHatHotReqV4 *InPckt = (CigiHatHotReqV4 *)Packet;

   bool ok = true;

   printf("===> HatHotReq <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("HatHotID ==> %d\n",InPckt->GetHatHotID());
	if( InPckt->GetReqType() == 0 ) 
		printf("ReqType ==> 0: HAT\n");
	else if( InPckt->GetReqType() == 1 ) 
		printf("ReqType ==> 1: HOT\n");
	else if( InPckt->GetReqType() == 2 ) 
		printf("ReqType ==> 2: Extended\n");

	if( InPckt->GetSrcCoordSys() == 0 ) 
		printf("ReqType ==> 0: Geodetic\n");
	else if( InPckt->GetSrcCoordSys() == 1 ) 
		printf("ReqType ==> 1: Entity\n");

   printf("UpdatePeriod ==> %d\n",InPckt->GetUpdatePeriod());
   printf("Xoff ==> %f\n",InPckt->GetXoff());
   printf("Yoff ==> %f\n",InPckt->GetYoff());
   printf("Zoff ==> %f\n",InPckt->GetZoff());

}

