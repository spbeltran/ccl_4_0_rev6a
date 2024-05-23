// XLosSegReq.cpp: Body of the XLosSegReq class.
//
//////////////////////////////////////////////////////////////////////

#include "XLosSegReq.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XLosSegReq::XLosSegReq()
{

}

XLosSegReq::~XLosSegReq()
{

}


void XLosSegReq::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiLosSegReqV4 *InPckt = (CigiLosSegReqV4 *)Packet;

   printf("===> LosSegReq <===\n");

   printf("Source Entity ID ==> %d\n",InPckt->GetEntityID());
   printf("Destination Entity ID ==> %d\n",InPckt->GetDestEntityID());
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


   printf("DstXoff ==> %f\n",InPckt->GetDstXoff());
   printf("DstYoff ==> %f\n",InPckt->GetDstYoff());
   printf("DstZoff ==> %f\n",InPckt->GetDstZoff());
	if( InPckt->GetDstCoordSys() == 0 )
	   printf("Destination Coord Sys ==> 0: Geodetic\n" );
	else if( InPckt->GetDstCoordSys() == 1 )
	   printf("Destination Coord Sys ==> 1: Entity\n" );

   printf("DestinationEntityValid ==> %d\n",InPckt->GetDestEntityIDValid());
   printf("AlphaThresh ==> %d\n",InPckt->GetAlphaThresh());
   printf("Mask ==> %d\n",InPckt->GetMask());
   printf("UpdatePeriod ==> %d\n",InPckt->GetUpdatePeriod());


}
