// XLosResp.cpp: Body of the XLosResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XLosResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XLosResp::XLosResp()
{

}

XLosResp::~XLosResp()
{

}


void XLosResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiLosRespV4 *InPckt = (CigiLosRespV4 *)Packet;

   printf("===> LosResp <===\n");

   printf("LosID ==> %d\n",InPckt->GetLosID());
   printf("Valid ==> %d\n",InPckt->GetValid());
   printf("EntityIDValid ==> %d\n",InPckt->GetEntityIDValid());
   printf("Visible ==> %d\n",InPckt->GetVisible());
   printf("RespCount ==> %d\n",InPckt->GetRespCount());
   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("HostFrame ==> %d\n",InPckt->GetHostFrame());
   printf("Range ==> %f\n",InPckt->GetRange());


}
