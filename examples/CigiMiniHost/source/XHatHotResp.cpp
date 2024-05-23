// XHatHotResp.cpp: Body of the XHatHotResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XHatHotResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XHatHotResp::XHatHotResp()
{

}

XHatHotResp::~XHatHotResp()
{

}


void XHatHotResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiHatHotRespV4 *InPckt = (CigiHatHotRespV4 *)Packet;

   printf("===> HatHotResp <===\n");

   printf("HatHotID ==> %d\n",InPckt->GetHatHotID());
   printf("Valid ==> %d\n",InPckt->GetValid());
   printf("Hat ==> %f\n",InPckt->GetHat());
   printf("Hot ==> %f\n",InPckt->GetHot());
   printf("ReqType ==> %d\n",InPckt->GetReqType());
   printf("HostFrame ==> %d\n",InPckt->GetHostFrame());


}
