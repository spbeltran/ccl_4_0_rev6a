// XConfClampEntityCtrl.cpp: Body of the XConfClampEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XConfClampEntityCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XConfClampEntityCtrl::XConfClampEntityCtrl()
{

}

XConfClampEntityCtrl::~XConfClampEntityCtrl()
{

}


void XConfClampEntityCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiConfClampEntityCtrlV4 *InPckt = (CigiConfClampEntityCtrlV4 *)Packet;

   bool ok = true;

   printf("===> ConfClampEntityCtrl <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("Lat ==> %f\n",InPckt->GetLat());
   printf("Lon ==> %f\n",InPckt->GetLon());
   printf("Yaw ==> %f\n",InPckt->GetYaw());
}
