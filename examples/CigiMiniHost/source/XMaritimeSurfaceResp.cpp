// XMaritimeSurfaceResp.cpp: Body of the XMaritimeSurfaceResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XMaritimeSurfaceResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XMaritimeSurfaceResp::XMaritimeSurfaceResp()
{

}

XMaritimeSurfaceResp::~XMaritimeSurfaceResp()
{

}


void XMaritimeSurfaceResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiMaritimeSurfaceRespV4 *InPckt = (CigiMaritimeSurfaceRespV4 *)Packet;

   printf("===> MaritimeSurfaceResp <===\n");

   printf("RequestID ==> %d\n",InPckt->GetRequestID());
   printf("SurfaceHeight ==> %f\n",InPckt->GetSurfaceHeight());
   printf("WaterTemp ==> %f\n",InPckt->GetWaterTemp());
   printf("Clarity ==> %f\n",InPckt->GetClarity());


}
