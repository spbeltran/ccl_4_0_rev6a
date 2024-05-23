// XSymbolTexturedCircleDefV4.cpp: Body of the XSymbolTexturedCircleDefV4 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolTexturedCircleDefV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolTexturedCircleDefV4::XSymbolTexturedCircleDefV4()
{

}

XSymbolTexturedCircleDefV4::~XSymbolTexturedCircleDefV4()
{

}


void XSymbolTexturedCircleDefV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolTexturedCircleDefV4 *InPckt = (CigiSymbolTexturedCircleDefV4 *)Packet;

   printf("===> SymbolTexturedCircleDef <===\n");

   printf("SymbolID ==> %d\n",InPckt->GetSymbolID());
   printf("TextureID ==> %d\n",InPckt->GetTextureID());
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
   printf("Number of Circles = %d\n",InPckt->GetCircleCount());


}
