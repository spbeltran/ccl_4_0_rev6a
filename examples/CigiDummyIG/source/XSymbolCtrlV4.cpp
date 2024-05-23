// XSymbolCtrlV3_3.cpp: Body of the XSymbolCtrlV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolCtrlV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolCtrlV4::XSymbolCtrlV4()
{

}

XSymbolCtrlV4::~XSymbolCtrlV4()
{

}


void XSymbolCtrlV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolCtrlV4 *InPckt = (CigiSymbolCtrlV4 *)Packet;

   printf("===> SymbolCtrl <===\n");

   printf("Symbol ID = %d\n",InPckt->GetSymbolID());

   printf("Symbol State = %d : ",InPckt->GetSymbolState());
   switch(InPckt->GetSymbolState())
   {
   case 0:
      printf("Hidden\n");
      break;
   case 1:
      printf("Visible\n");
      break;
   case 2:
      printf("Destroyed\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Attach State = %d : ",InPckt->GetAttachState());
   switch(InPckt->GetAttachState())
   {
   case 0:
      printf("Detach\n");
      break;
   case 1:
      printf("Attach\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Flash Control = %d : ",InPckt->GetFlashCtrl());
   switch(InPckt->GetFlashCtrl())
   {
   case 0:
      printf("Continue\n");
      break;
   case 1:
      printf("Reset\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Inherit Color = %d : ",InPckt->GetInheritColor());
   switch(InPckt->GetInheritColor())
   {
   case 0:
      printf("NotInherit\n");
      break;
   case 1:
      printf("Inherit\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Parent ID = %d\n",InPckt->GetParentSymbolID());
   printf("Surface ID = %d\n",InPckt->GetSurfaceID());
   printf("Layer ID = %d\n",InPckt->GetLayer());
   printf("Flash Duty Cycle percentage = %d\n",InPckt->GetFlashDutyCycle());
   printf("Flash Period = %f\n",InPckt->GetFlashPeriod());
   printf("U Position = %f\n",InPckt->GetUPosition());
   printf("V Position = %f\n",InPckt->GetVPosition());
   printf("Rotation = %f\n",InPckt->GetRotation());
   printf("Red = %d\n",InPckt->GetRed());
   printf("Green = %d\n",InPckt->GetGreen());
   printf("Blue = %d\n",InPckt->GetBlue());
   printf("Alpha = %d\n",InPckt->GetAlpha());
   printf("U Scale = %f\n",InPckt->GetScaleU());
   printf("V Scale = %f\n",InPckt->GetScaleV());

}

