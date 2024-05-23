// XSymbolTextDefV3_3.cpp: Body of the XSymbolTextDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#include "XSymbolTextDefV4.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSymbolTextDefV4::XSymbolTextDefV4()
{

}

XSymbolTextDefV4::~XSymbolTextDefV4()
{

}


void XSymbolTextDefV4::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiSymbolTextDefV4 *InPckt = (CigiSymbolTextDefV4 *)Packet;

   printf("===> SymbolTextDefV4 <===\n");

   printf("Symbol ID = %d\n",InPckt->GetSymbolID());

   printf("Alignment State = %d : ",InPckt->GetAlignment());
   switch(InPckt->GetAlignment())
   {
   case 0:
      printf("TopLeft\n");
      break;
   case 1:
      printf("TopCenter\n");
      break;
   case 2:
      printf("TopRight\n");
      break;
   case 3:
      printf("CenterLeft\n");
      break;
   case 4:
      printf("Center\n");
      break;
   case 5:
      printf("CenterRight\n");
      break;
   case 6:
      printf("BottomLeft\n");
      break;
   case 7:
      printf("BottomCenter\n");
      break;
   case 8:
      printf("BottomRight\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Orientation State = %d : ",InPckt->GetOrientation());
   switch(InPckt->GetOrientation())
   {
   case 0:
      printf("LeftToRight\n");
      break;
   case 1:
      printf("TopToBottom\n");
      break;
   case 2:
      printf("RightToLeft\n");
      break;
   case 3:
      printf("BottomToTop\n");
      break;
   default:
      printf("\n");
      break;
   }

   printf("Font ID = %d\n",InPckt->GetFontID());
   printf("Font Size = %f\n",InPckt->GetFontSize());
   printf("Text = %s\n",(InPckt->GetText()).c_str());

}

