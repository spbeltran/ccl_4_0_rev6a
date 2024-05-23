// XSymbolCircleDefV4.cpp: Body of the XSymbolCircleDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolCircleDefV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolCircleDefV4::XSymbolCircleDefV4()
{

}

XSymbolCircleDefV4::~XSymbolCircleDefV4()
{

}


void XSymbolCircleDefV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolCircleDefV4 *InPckt = (CigiSymbolCircleDefV4 *)Packet;

   printf("===> SymbolCircleDefV4 <===\n");

   printf("Symbol ID = %d\n",InPckt->GetSymbolID());

   printf("Drawing Style = %d : ",InPckt->GetDrawingStyle());
   switch(InPckt->GetDrawingStyle())
   {
   case 0:
      printf("Line\n");
      break;
   case 1:
      printf("Fill\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Stipple Pattern = 0x%08x\n",InPckt->GetStipplePattern());
   printf("Line Width = %f\n",InPckt->GetLineWidth());
   printf("Stipple Pattern Length = %f\n",InPckt->GetStipplePatternLen());


   //   Circle Data
   int CircleCnt = InPckt->GetCircleCount();
   int ndx = 0;
   for(ndx=0;ndx<CircleCnt;ndx++)
   {
      CigiCircleSymbolDataV4 *Circle =
         (CigiCircleSymbolDataV4 *)InPckt->GetCircle(ndx);
	  printf("====Circle Symbol Data: %d of %d\n", ndx+1, CircleCnt );
      printf("Center U Position = %f\n",Circle->GetCenterUPosition());
      printf("Center V Position = %f\n",Circle->GetCenterVPosition());
      printf("Radius		  = %f\n",Circle->GetRadius());
      printf("Inner Radius	  = %f\n",Circle->GetInnerRadius());
      printf("Start Angle	  = %f\n",Circle->GetStartAngle());
      printf("End Angle	  = %f\n",Circle->GetEndAngle());
   }

}

