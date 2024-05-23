// XShortSymbolCtrlV4.cpp: Body of the XShortSymbolCtrlV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XShortSymbolCtrlV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XShortSymbolCtrlV4::XShortSymbolCtrlV4()
{

}

XShortSymbolCtrlV4::~XShortSymbolCtrlV4()
{

}


void XShortSymbolCtrlV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiShortSymbolCtrlV4 *InPckt = (CigiShortSymbolCtrlV4 *)Packet;

   printf("===> ShortSymbolCtrl <===\n");

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

   int ndx = 0;
   for(ndx=0;ndx<2;ndx++)
   {
      printf("Datum %d type = %d : ",ndx,InPckt->GetDatumType(ndx));
      switch(InPckt->GetDatumType(ndx))
      {
      case 0:
         printf("None\n");
         break;
      case 1:
         printf("SurfaceIdDatumType\n");
         printf("Datum %d: Surface ID = %d\n",ndx,InPckt->GetUIntDatum(ndx));
         break;
      case 2:
         printf("ParentIdDatumType\n");
         printf("Datum %d: Parent ID = %d\n",ndx,InPckt->GetUIntDatum(ndx));
         break;
      case 3:
         printf("LayerDatumType\n");
         printf("Datum %d: Layer = %d\n",ndx,InPckt->GetUIntDatum(ndx));
         break;
      case 4:
         printf("FlashDutyCycleDatumType\n");
         printf("Datum %d: Flash Duty Cycle = %d\n",ndx,InPckt->GetUIntDatum(ndx));
         break;
      case 5:
         printf("FlashPeriodDatumType\n");
         printf("Datum %d: Flash Period = %f\n",ndx,InPckt->GetFloatDatum(ndx));
         break;
      case 6:
         printf("UPositionDatumType\n");
         printf("Datum %d: U Position = %f\n",ndx,InPckt->GetFloatDatum(ndx));
         break;
      case 7:
         printf("VPositionDatumType\n");
         printf("Datum %d: V Position = %f\n",ndx,InPckt->GetFloatDatum(ndx));
         break;
      case 8:
         printf("RotationDatumType\n");
         printf("Datum %d: Rotation = %f\n",ndx,InPckt->GetFloatDatum(ndx));
         break;
      case 9:
         printf("ColorDatumType\n");
         Cigi_uint8 tRed,tGreen,tBlue,tAlpha;
         tRed = tGreen = tBlue = tAlpha = 0;
         InPckt->GetColorDatum(ndx,tRed,tGreen,tBlue,tAlpha);
         printf("Datum %d: Color:\n\t\t=> Red = %d\n\t\t=> Green = %d\n\t\t=> Blue = %d\n\t\t=> Alpha = %d\n",
            ndx,tRed,tGreen,tBlue,tAlpha);
         break;
      case 10:
         printf("ScaleUDatumType\n");
         printf("Datum %d: U Scale = %f\n",ndx,InPckt->GetFloatDatum(ndx));
         break;
      case 11:
         printf("ScaleVDatumType\n");
         printf("Datum %d: V Scale = %f\n",ndx,InPckt->GetFloatDatum(ndx));
         break;
      default:
         printf("\n");
         break;
      }
   }
}

