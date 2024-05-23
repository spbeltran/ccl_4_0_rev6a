// XCollDetVolDef.cpp: Body of the XCollDetVolDef class.
//
//////////////////////////////////////////////////////////////////////

#include "XCollDetVolDef.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XCollDetVolDef::XCollDetVolDef()
{

}

XCollDetVolDef::~XCollDetVolDef()
{

}


void XCollDetVolDef::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiCollDetVolDefV4 *InPckt = (CigiCollDetVolDefV4 *)Packet;

   bool ok = true;

   printf("===> CollDetVolDef <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("VolID ==> %d\n",InPckt->GetVolID());
   printf("VolEn ==> %d\n",InPckt->GetVolEn());
	if( InPckt->GetVolType() == 0 ) 
	   printf("VolType ==> 0: Sphere\n");
	else 
	   printf("VolType ==> 1: Cubiod\n");
   printf("Xoff ==> %f\n",InPckt->GetXoff());
   printf("Yoff ==> %f\n",InPckt->GetYoff());
   printf("Zoff ==> %f\n",InPckt->GetZoff());
   printf("HeightOrRadius ==> %f\n",InPckt->GetHeightOrRadius());
   printf("Width ==> %f\n",InPckt->GetWidth());
   printf("Depth ==> %f\n",InPckt->GetDepth());
   printf("Roll ==> %f\n",InPckt->GetRoll());
   printf("Pitch ==> %f\n",InPckt->GetPitch());
   printf("Yaw ==> %f\n",InPckt->GetYaw());


}
