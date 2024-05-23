// XViewCtrl.cpp: Body of the XViewCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XViewCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XViewCtrl::XViewCtrl()
{

}

XViewCtrl::~XViewCtrl()
{

}


void XViewCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
CigiViewCtrlV4 *InPckt = (CigiViewCtrlV4 *)Packet;

   printf("===> ViewCtrl <===\n");

   printf("ViewID ==> %d\n",InPckt->GetViewID());
   printf("GroupID ==> %d\n",InPckt->GetGroupID());
   printf("XOffEn ==> %d\n",InPckt->GetXOffEn());
   printf("YOffEn ==> %d\n",InPckt->GetYOffEn());
   printf("ZOffEn ==> %d\n",InPckt->GetZOffEn());
   printf("RollEn ==> %d\n",InPckt->GetRollEn());
   printf("PitchEn ==> %d\n",InPckt->GetPitchEn());
   printf("YawEn ==> %d\n",InPckt->GetYawEn());
   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("XOff ==> %f\n",InPckt->GetXOff());
   printf("YOff ==> %f\n",InPckt->GetYOff());
   printf("ZOff ==> %f\n",InPckt->GetZOff());
   printf("Yaw ==> %f\n",InPckt->GetYaw());
   printf("Pitch ==> %f\n",InPckt->GetPitch());
   printf("Roll ==> %f\n",InPckt->GetRoll());

}
