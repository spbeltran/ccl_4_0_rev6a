// XShortCompCtrl.cpp: Body of the XShortCompCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XShortCompCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XShortCompCtrl::XShortCompCtrl()
{

}

XShortCompCtrl::~XShortCompCtrl()
{

}


void XShortCompCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiShortCompCtrlV4 *InPckt = (CigiShortCompCtrlV4 *)Packet;

   bool ok = true;

   printf("===> ShortCompCtrl <===\n");

   printf("CompID ==> %d\n",InPckt->GetCompID());
   printf("InstanceID ==> %d\n",InPckt->GetInstanceID());
   printf("CompClassV4 ==> %d\n",InPckt->GetCompClassV4());
   printf("CompState ==> %d\n",InPckt->GetCompState());
   printf("CompData ==> %d\n",InPckt->GetLongCompData(0));
   printf("CompData ==> %d\n",InPckt->GetLongCompData(1));

}
