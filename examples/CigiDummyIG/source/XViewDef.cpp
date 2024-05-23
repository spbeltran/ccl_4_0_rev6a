// XViewDef.cpp: Body of the XViewDef class.
//
//////////////////////////////////////////////////////////////////////

#include "XViewDef.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XViewDef::XViewDef()
{

}

XViewDef::~XViewDef()
{

}


void XViewDef::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiViewDefV4 *InPckt = (CigiViewDefV4 *)Packet;

   printf("===> ViewDef <===\n");

   printf("ViewID ==> %d\n",InPckt->GetViewID());
   printf("GroupID ==> %d\n",InPckt->GetGroupID());
   printf("FOVNearEn ==> %d\n",InPckt->GetFOVNearEn());
   printf("FOVFarEn ==> %d\n",InPckt->GetFOVFarEn());
   printf("FOVLeftEn ==> %d\n",InPckt->GetFOVLeftEn());
   printf("FOVRightEn ==> %d\n",InPckt->GetFOVRightEn());
   printf("FOVTopEn ==> %d\n",InPckt->GetFOVTopEn());
   printf("FOVBottomEn ==> %d\n",InPckt->GetFOVBottomEn());

	if( InPckt->GetPixelReplicateMode() == 0 )
	   printf("Pixel Replication Mode ==> 0: None\n" );
	else if( InPckt->GetPixelReplicateMode() == 1 )
	   printf("Pixel Replication Mode ==> 1: 1 x 2\n" );
	else if( InPckt->GetPixelReplicateMode() == 2 )
	   printf("Pixel Replication Mode ==> 2: 2 x 1\n" );
	else if( InPckt->GetPixelReplicateMode() == 3 )
	   printf("Pixel Replication Mode ==> 3: 2 x 2\n" );

	if( InPckt->GetMirrorMode() == 0 )
	   printf("Mirror Mode ==> 0: None\n" );
	else if( InPckt->GetMirrorMode() == 1 )
	   printf("Mirror Mode ==> 1: Horizontal\n" );
	else if( InPckt->GetMirrorMode() == 2 )
	   printf("Mirror Mode ==> 2: Vertical\n" );
	else if( InPckt->GetMirrorMode() == 3 )
	   printf("Mirror Mode ==> 3: Horizontal and Vertical\n" );

	if( InPckt->GetProjectionType() == 0 )
	   printf("ProjectionType ==> 0: Perspective\n");
	else
	   printf("ProjectionType ==> 1: Orthographic\n" );
   printf("Reorder ==> %d\n",InPckt->GetReorder());
   printf("ViewType ==> %d\n",InPckt->GetViewType());
   printf("FOVNear ==> %f\n",InPckt->GetFOVNear());
   printf("FOVFar ==> %f\n",InPckt->GetFOVFar());
   printf("FOVLeft ==> %f\n",InPckt->GetFOVLeft());
   printf("FOVRight ==> %f\n",InPckt->GetFOVRight());
   printf("FOVTop ==> %f\n",InPckt->GetFOVTop());
   printf("FOVBottom ==> %f\n",InPckt->GetFOVBottom());


}
