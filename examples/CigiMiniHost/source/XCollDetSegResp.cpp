// XCollDetSegResp.cpp: Body of the XCollDetSegResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XCollDetSegResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XCollDetSegResp::XCollDetSegResp()
{

}

XCollDetSegResp::~XCollDetSegResp()
{

}


void XCollDetSegResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiCollDetSegRespV4 *InPckt = (CigiCollDetSegRespV4 *)Packet;

   printf("===> CollDetSegResp <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("SegID ==> %d\n",InPckt->GetSegID());
   printf("CollType ==> %d\n",InPckt->GetCollType());
   printf("CollEntityID ==> %d\n",InPckt->GetCollEntityID());
   printf("Material ==> %d\n",InPckt->GetMaterial());
   printf("IntersectDist ==> %f\n",InPckt->GetIntersectDist());


}
