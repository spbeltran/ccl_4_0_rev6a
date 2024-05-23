// XEntityCtrl.cpp: Body of the XEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XAnimationCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XAnimationCtrl::XAnimationCtrl()
{

}

XAnimationCtrl::~XAnimationCtrl()
{

}


void XAnimationCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiAnimationCtrlV4 *InPckt = (CigiAnimationCtrlV4 *)Packet;

   bool ok = true;

   printf("===> AnimationCtrl <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("AnimationID ==> %d\n",InPckt->GetAnimationID());
   printf("Animation Speed ==> %f\n",InPckt->GetAnimationSpeed());
   printf("Alpha ==> %d\n",InPckt->GetAlpha());

   printf("Animation Sate = %d : ",InPckt->GetAnimationState());
   switch(InPckt->GetAnimationState())
   {
   case 0:
      printf("Stop\n");
      break;
   case 1:
      printf("Play\n");
      break;
   }
   printf("Animation Frame Position Reset = %d : ",InPckt->GetAnimationFrameResetMode());
   switch(InPckt->GetAnimationFrameResetMode())
   {
   case 0:
      printf("Continue\n");
      break;
   case 1:
      printf("Reset\n");
      break;
   }
   printf("Animation Loop Mode = %d : ",InPckt->GetAnimationLoopMode());
   switch(InPckt->GetAnimationLoopMode())
   {
   case 0:
      printf("One-Shot\n");
      break;
   case 1:
      printf("Continuous\n");
      break;
   }

   printf("Inherit Alpha = %d : ",InPckt->GetInheritAlpha());
   switch(InPckt->GetInheritAlpha())
   {
   case 0:
      printf("Not Inherited\n");
      break;
   case 1:
      printf("Inherited\n");
      break;
   }
}
