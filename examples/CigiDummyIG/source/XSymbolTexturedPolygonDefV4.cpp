// XSymbolPolygonDefV4.cpp: Body of the XSymbolLineDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolTexturedPolygonDefV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolTexturedPolygonDefV4::XSymbolTexturedPolygonDefV4()
{

}

XSymbolTexturedPolygonDefV4::~XSymbolTexturedPolygonDefV4()
{

}


void XSymbolTexturedPolygonDefV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolTexturedPolygonDefV4 *InPckt = (CigiSymbolTexturedPolygonDefV4 *)Packet;

   printf("===> SymbolTexturedPolygonDefV4 <===\n");


   printf("Symbol ID = %d\n",InPckt->GetSymbolID());
   printf("Texture ID = %d\n",InPckt->GetTextureID());

   printf("Drawing Primitive = %d : ",InPckt->GetPrimitive());
   switch(InPckt->GetPrimitive())
   {
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
      printf("Undefined\n");
      break;
   }

   printf("Texture Filter = %d : ",InPckt->GetTextureFilter());
   switch(InPckt->GetTextureFilter())
   {
   case 0:
      printf("Nearest\n");
      break;
   case 1:
      printf("Linear\n");
      break;
   }

   printf("Texture Wrap = %d : ",InPckt->GetTextureWrap());
   switch(InPckt->GetTextureWrap())
   {
   case 0:
      printf("Repeat\n");
      break;
   case 1:
      printf("Clamp\n");
      break;
   }
   printf("Vertex count = %d\n",InPckt->GetVertexCount());


   //   Circle Data
   int VtxCnt = InPckt->GetVertexCount();
   int ndx = 0;
   for(ndx=0;ndx<VtxCnt;ndx++)
   {
      CigiVertexSymbolTextureDataV4 *Vtx =
         (CigiVertexSymbolTextureDataV4 *)InPckt->GetVertex(ndx);

      printf("Vertex U Position = %f\n",Vtx->GetVertexU());
      printf("Vertex V Position = %f\n",Vtx->GetVertexV());
      printf("Vertex S Coordinate = %f\n",Vtx->GetSTexCoord());
      printf("Vertex T Coordinate= %f\n",Vtx->GetTTexCoord());
   }

}

