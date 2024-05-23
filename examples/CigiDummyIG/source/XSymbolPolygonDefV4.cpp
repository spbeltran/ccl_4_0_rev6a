// XSymbolPolygonDefV4.cpp: Body of the XSymbolLineDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolPolygonDefV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolPolygonDefV4::XSymbolPolygonDefV4()
{

}

XSymbolPolygonDefV4::~XSymbolPolygonDefV4()
{

}


void XSymbolPolygonDefV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolPolygonDefV4 *InPckt = (CigiSymbolPolygonDefV4 *)Packet;

   printf("===> SymbolPolygonDefV4 <===\n");


   printf("Symbol ID = %d\n",InPckt->GetSymbolID());

   printf("Drawing Primitive = %d : ",InPckt->GetPrimitive());
   switch(InPckt->GetPrimitive())
   {
   case 0:
      printf("Points\n");
      break;
   case 1:
      printf("Lines\n");
      break;
   case 2:
      printf("LineStrip\n");
      break;
   case 3:
      printf("LineLoop\n");
      break;
   case 4:
      printf("Triangles\n");
      break;
   case 5:
      printf("TriangleStrip\n");
      break;
   case 6:
      printf("TriangleFan\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Stipple Pattern = 0x%08x\n",InPckt->GetStipplePattern());
   printf("Line Width = %f\n",InPckt->GetLineWidth());
   printf("Stipple Pattern Length = %f\n",InPckt->GetStipplePatternLen());


   //   Circle Data
   int VtxCnt = InPckt->GetVertexCount();
   int ndx = 0;
   for(ndx=0;ndx<VtxCnt;ndx++)
   {
      CigiVertexSymbolDataV4 *Vtx =
         (CigiVertexSymbolDataV4 *)InPckt->GetVertex(ndx);
	  printf("====Polygon Symbol Vertex Data: %d of %d\n", ndx+1, VtxCnt );
      printf("Vertex U Position = %f\n",Vtx->GetVertexU());
      printf("Vertex V Position = %f\n",Vtx->GetVertexV());
   }

}

