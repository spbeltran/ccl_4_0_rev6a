// XTrajectory.cpp: Body of the XTrajectory class.
//
//////////////////////////////////////////////////////////////////////

#include "XAccelerationCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XAccelerationCtrl::XAccelerationCtrl()
{

}

XAccelerationCtrl::~XAccelerationCtrl()
{

}


void XAccelerationCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiAccelerationCtrlV4 *InPckt = (CigiAccelerationCtrlV4 *)Packet;

   printf("===> Acceleration Control <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("PartID ==> %d\n",InPckt->GetArtPartID());
   printf("ApplyToArtPart ==> %d\n",InPckt->GetArtPartApply());
   if( InPckt->GetCoordSys() == 0 ) 
	printf("CoordSystem ==> %d: World/Parent\n",InPckt->GetCoordSys());
   else
	printf("CoordSystem ==> %d: Local\n",InPckt->GetCoordSys());
   printf("AccelX ==> %f\n",InPckt->GetAccelX());
   printf("AccelY ==> %f\n",InPckt->GetAccelY());
   printf("AccelZ ==> %f\n",InPckt->GetAccelZ());
   printf("AccelRoll ==> %f\n",InPckt->GetAccelRoll());
   printf("AccelPitch ==> %f\n",InPckt->GetAccelPitch());
   printf("AccelYaw ==> %f\n",InPckt->GetAccelYaw());


}
