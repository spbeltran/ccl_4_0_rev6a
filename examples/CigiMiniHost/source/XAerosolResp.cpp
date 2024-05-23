// XAerosolResp.cpp: Body of the XAerosolResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XAerosolResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XAerosolResp::XAerosolResp()
{

}

XAerosolResp::~XAerosolResp()
{

}


void XAerosolResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiAerosolRespV4 *InPckt = (CigiAerosolRespV4 *)Packet;

   printf("===> AerosolResp <===\n");

   printf("RequestID ==> %d\n",InPckt->GetRequestID());
   printf("LayerID ==> %d\n",InPckt->GetLayerID());
   printf("AerosolConcentration ==> %f\n",InPckt->GetAerosolConcentration());


}
