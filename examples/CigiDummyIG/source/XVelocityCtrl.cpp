// XRateCtrl.cpp: Body of the XRateCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XVelocityCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XVelocityCtrl::XVelocityCtrl()
{

}

XVelocityCtrl::~XVelocityCtrl()
{

}


void XVelocityCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiVelocityCtrlV4 *InPckt = (CigiVelocityCtrlV4 *)Packet;

   bool ok = true;

   printf("===> VelocityCtrl <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("ArtPartID ==> %d\n",InPckt->GetArtPartID());
   printf("ApplyToArtPart ==> %d\n",InPckt->GetApplyToArtPart());
   if( InPckt->GetCoordSys() == 0 ) 
	printf("CoordSystem ==> %d: World/Parent\n",InPckt->GetCoordSys());
   else
	printf("CoordSystem ==> %d: Local\n",InPckt->GetCoordSys());
   printf("XRate ==> %f\n",InPckt->GetXRate());
   printf("YRate ==> %f\n",InPckt->GetYRate());
   printf("ZRate ==> %f\n",InPckt->GetZRate());
   printf("YawRate ==> %f\n",InPckt->GetYawRate());
   printf("PitchRate ==> %f\n",InPckt->GetPitchRate());
   printf("RollRate ==> %f\n",InPckt->GetRollRate());
}
