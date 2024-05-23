// XCollDetVolResp.cpp: Body of the XCollDetVolResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XCollDetVolResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XCollDetVolResp::XCollDetVolResp()
{

}

XCollDetVolResp::~XCollDetVolResp()
{

}


void XCollDetVolResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiCollDetVolRespV4 *InPckt = (CigiCollDetVolRespV4 *)Packet;

   printf("===> CollDetVolResp <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("VolID ==> %d\n",InPckt->GetVolID());
   printf("CollType ==> %d\n",InPckt->GetCollType());
   printf("CollEntityID ==> %d\n",InPckt->GetCollEntityID());
   printf("CollVolID ==> %d\n",InPckt->GetCollVolID());


}
