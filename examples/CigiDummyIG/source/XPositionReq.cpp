// XPostionReq.cpp: Body of the XPostionReq class.
//
//////////////////////////////////////////////////////////////////////

#include "XPositionReq.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XPositionReq::XPositionReq()
{

}

XPositionReq::~XPositionReq()
{

}


void XPositionReq::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiPositionReqV4 *InPckt = (CigiPositionReqV4 *)Packet;

   bool ok = true;

   printf("===> PositionReq <===\n");

   printf("ObjectID ==> %d\n",InPckt->GetObjectID());
   printf("ArtPartID ==> %d\n",InPckt->GetArtPartID());

	if( InPckt->GetUpdateMode() == 0 )
	   printf("Update Mode ==> 0: One-Shot\n" );
	else if( InPckt->GetUpdateMode() == 1 )
	   printf("Update Mode ==> 1: Continuous\n" );

	if( InPckt->GetObjectClass() == 0 )
	   printf("Object Class ==> 0: Entity\n" );
	else if( InPckt->GetObjectClass() == 1 )
	   printf("Object Class ==> 1: Articulated Part\n" );
	else if( InPckt->GetObjectClass() == 2 )
	   printf("Object Class ==> 2: View\n" );
	else if( InPckt->GetObjectClass() == 3 )
	   printf("Object Class ==> 3: View Group\n" );
	else if( InPckt->GetObjectClass() == 4 )
	   printf("Object Class ==> 4: Motion Tracker\n" );

	if( InPckt->GetCoordSys() == 0 )
	   printf("Coord Sys ==> 0: Geodetic\n" );
	else if( InPckt->GetCoordSys() == 1 )
	   printf("Coord Sys ==> 1: Parent Entity\n" );
	else if( InPckt->GetCoordSys() == 2 )
	   printf("Coord Sys ==> 2: Submodel\n" );


}
