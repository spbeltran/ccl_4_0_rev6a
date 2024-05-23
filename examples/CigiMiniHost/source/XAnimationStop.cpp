// XAnimationStop.cpp: Body of the XAnimationStop class.
//
//////////////////////////////////////////////////////////////////////

#include "XAnimationStop.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XAnimationStop::XAnimationStop()
{

}

XAnimationStop::~XAnimationStop()
{

}


void XAnimationStop::OnPacketReceived(CigiBasePacket *Packet)
{
CigiAnimationStopV4 *InPckt = (CigiAnimationStopV4 *)Packet;

   bool ok = true;

   printf("===> AnimationStop <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());


}
