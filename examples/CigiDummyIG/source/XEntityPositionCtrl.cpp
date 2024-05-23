// XEntityPositionCtrl.cpp: Body of the XEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XEntityPositionCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XEntityPositionCtrl::XEntityPositionCtrl()
{

}

XEntityPositionCtrl::~XEntityPositionCtrl()
{

}


void XEntityPositionCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiEntityPositionCtrlV4 *InPckt = (CigiEntityPositionCtrlV4 *)Packet;

   bool ok = true;

   printf("===> EntityPositionCtrl <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("ParentID ==> %d\n",InPckt->GetParentID());

   printf("AttachState = %d : ",InPckt->GetAttachState());
   switch(InPckt->GetAttachState())
   {
   case 0:
      printf("Detach\n");
      break;
   case 1:
      printf("Attach\n");
      break;
   }

   printf("ClampState = %d : ",InPckt->GetClampState());
   switch(InPckt->GetClampState())
   {
   case 0:
      printf("No Clamp\n");
      break;
   case 1:
      printf("Altitude Clamp\n");
      break;
   case 2:
      printf("Altitude and Orientation Clamp\n");
      break;
   }

   printf("LatOrXoff ==> %f\n",InPckt->GetXoff());
   printf("LonOrYoff ==> %f\n",InPckt->GetYoff());
   printf("AltOrZoff ==> %f\n",InPckt->GetZoff());
   printf("Yaw ==> %f\n",InPckt->GetYaw());
   printf("Pitch ==> %f\n",InPckt->GetPitch());
   printf("Roll ==> %f\n",InPckt->GetRoll());
}
