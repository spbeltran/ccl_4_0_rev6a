// XSymbolCloneV4.cpp: Body of the XSymbolCloneV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolCloneV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolCloneV4::XSymbolCloneV4()
{

}

XSymbolCloneV4::~XSymbolCloneV4()
{

}


void XSymbolCloneV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolCloneV4 *InPckt = (CigiSymbolCloneV4 *)Packet;

   printf("===> SymbolCloneV4 <===\n");

   printf("Symbol ID = %d\n",InPckt->GetSymbolID());

   printf("Source Type = %d : ",InPckt->GetSourceType());
   switch(InPckt->GetSourceType())
   {
   case 0:
      printf("Symbol\n");
      break;
   case 1:
      printf("Symbol Template\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Source ID = %d\n",InPckt->GetSourceID());

}

