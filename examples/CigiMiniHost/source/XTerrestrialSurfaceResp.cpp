// XTerrestrialSurfaceResp.cpp: Body of the XTerrestrialSurfaceResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XTerrestrialSurfaceResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XTerrestrialSurfaceResp::XTerrestrialSurfaceResp()
{

}

XTerrestrialSurfaceResp::~XTerrestrialSurfaceResp()
{

}


void XTerrestrialSurfaceResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiTerrestrialSurfaceRespV4 *InPckt = (CigiTerrestrialSurfaceRespV4 *)Packet;

   printf("===> XTerrestrialSurfaceResp <===\n");

   printf("RequestID ==> %d\n",InPckt->GetRequestID());
   printf("SurfaceConditionID ==> %d\n",InPckt->GetSurfaceConditionID());


}
