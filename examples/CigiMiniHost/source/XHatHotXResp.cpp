// XHatHotXResp.cpp: implementation of the XHatHotXResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XHatHotXResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XHatHotXResp::XHatHotXResp()
{

}

XHatHotXResp::~XHatHotXResp()
{

}

void XHatHotXResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiHatHotXRespV4 *InPckt = (CigiHatHotXRespV4 *)Packet;

   printf("===> HatHotXResp <===\n");

   printf("HatHotID ==> %d\n",InPckt->GetHatHotID());
   printf("Valid ==> %d\n",InPckt->GetValid());
   printf("Hat ==> %f\n",InPckt->GetHat());
   printf("Hot ==> %f\n",InPckt->GetHot());
   printf("Material ==> %d\n",InPckt->GetMaterial());
   printf("NormAz ==> %f\n",InPckt->GetNormAz());
   printf("NormEl ==> %f\n",InPckt->GetNormEl());
   printf("HostFrame ==> %d\n",InPckt->GetHostFrame());

}
