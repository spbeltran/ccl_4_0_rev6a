// XSymbolSurfaceDefV4.cpp: Body of the XSymbolSurfaceDefV4 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolSurfaceDefV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolSurfaceDefV4::XSymbolSurfaceDefV4()
{

}

XSymbolSurfaceDefV4::~XSymbolSurfaceDefV4()
{

}


void XSymbolSurfaceDefV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolSurfaceDefV4 *InPckt = (CigiSymbolSurfaceDefV4 *)Packet;

   printf("===> SymbolSurfaceDefV4 <===\n");

   printf("Surface ID = %d\n",InPckt->GetSurfaceID());

   printf("Surface State = %d : ",InPckt->GetSurfaceState());
   switch(InPckt->GetSurfaceState())
   {
   case 0:
      printf("Active\n");
      break;
   case 1:
      printf("Destroyed\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Attach State = %d : ",InPckt->GetAttached());
   switch(InPckt->GetAttached())
   {
   case 0:
      printf("EntityAttached\n");
      break;
   case 1:
      printf("ViewAttached\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("BillBoard State = %d : ",InPckt->GetBillboardState());
   switch(InPckt->GetBillboardState())
   {
   case 0:
      printf("NotBillboard\n");
      break;
   case 1:
      printf("Billboard\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Perspective Growth = %d : ",InPckt->GetPerspectiveGrowth());
   switch(InPckt->GetPerspectiveGrowth())
   {
   case 0:
      printf("Disable\n");
      break;
   case 1:
      printf("Enable\n");
      break;
   default:
      printf("\n");
      break;
   }

   if(InPckt->GetAttached() == CigiBaseSymbolSurfaceDef::EntityAttached)
   {
      printf("Entity ID = %d\n",InPckt->GetEntityID());
      printf("X Offset = %f\n",InPckt->GetXOffset());
      printf("Y Offset = %f\n",InPckt->GetYOffset());
      printf("Z Offset = %f\n",InPckt->GetZOffset());
      printf("Yaw = %f\n",InPckt->GetYaw());
      printf("Pitch = %f\n",InPckt->GetPitch());
      printf("Roll = %f\n",InPckt->GetRoll());
      printf("Width = %f\n",InPckt->GetWidth());
      printf("Height = %f\n",InPckt->GetHeight());
   }
   else
   {
      printf("View ID = %d\n",InPckt->GetViewID());
      printf("Left Edge Position = %f\n",InPckt->GetLeftEdgePosition());
      printf("Right Edge Position = %f\n",InPckt->GetRightEdgePosition());
      printf("Top Edge Position = %f\n",InPckt->GetTopEdgePosition());
      printf("Bottom Edge Position = %f\n",InPckt->GetBottomEdgePosition());
   }

   printf("Minimum U Coordinate = %f\n",InPckt->GetMinU());
   printf("Maximum U Coordinate = %f\n",InPckt->GetMaxU());
   printf("Minimum V Coordinate = %f\n",InPckt->GetMinV());
   printf("Maximum V Coordinate = %f\n",InPckt->GetMaxV());

}

