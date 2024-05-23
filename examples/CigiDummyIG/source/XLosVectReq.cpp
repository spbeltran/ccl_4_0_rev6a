// XLosVectReq.cpp: Body of the XLosVectReq class.
//
//////////////////////////////////////////////////////////////////////

#include "XLosVectReq.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XLosVectReq::XLosVectReq()
{

}

XLosVectReq::~XLosVectReq()
{

}


void XLosVectReq::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiLosVectReqV4 *InPckt = (CigiLosVectReqV4 *)Packet;

   bool ok = true;

   printf("===> LosVectReq <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("LosID ==> %d\n",InPckt->GetLosID());

	if( InPckt->GetReqType() == 0 )
	   printf("ReqType ==> 0: Basic\n" );
	else if( InPckt->GetReqType() == 1 )
	   printf("ReqType ==> 1: Extended\n" );

	if( InPckt->GetResponseCoordSys() == 0 )
	   printf("Response Coord Sys ==> 0: Geodetic\n" );
	else if( InPckt->GetResponseCoordSys() == 1 )
	   printf("Response Coord Sys ==> 1: Entity\n" );

   printf("UpdatePeriod ==> %d\n",InPckt->GetUpdatePeriod());

   printf("SrcXoff ==> %f\n",InPckt->GetSrcXoff());
   printf("SrcYoff ==> %f\n",InPckt->GetSrcYoff());
   printf("SrcZoff ==> %f\n",InPckt->GetSrcZoff());
	if( InPckt->GetSrcCoordSys() == 0 )
	   printf("Source Coord Sys ==> 0: Geodetic\n" );
	else if( InPckt->GetSrcCoordSys() == 1 )
	   printf("Source Coord Sys ==> 1: Entity\n" );

   printf("AlphaThresh ==> %d\n",InPckt->GetAlphaThresh());
   printf("VectAz ==> %f\n",InPckt->GetVectAz());
   printf("VectEl ==> %f\n",InPckt->GetVectEl());
   printf("MinRange ==> %f\n",InPckt->GetMinRange());
   printf("MaxRange ==> %f\n",InPckt->GetMaxRange());
   printf("Mask ==> %d\n",InPckt->GetMask());
   
}

