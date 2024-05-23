// XIGMsg.cpp: Body of the XIGMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "XIGMsg.h"
#include "string.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XIGMsg::XIGMsg()
{

}

XIGMsg::~XIGMsg()
{

}


void XIGMsg::OnPacketReceived(CigiBasePacket *Packet)
{
CigiIGMsgV4 *InPckt = (CigiIGMsgV4 *)Packet;

   printf("===> XIGMsg <===\n");

   printf("MsgID ==> %d\n",InPckt->GetMsgID());
   printf("MsgLen ==> %d\n",InPckt->GetMsgLen());

   printf("Msg ==> %s\n",InPckt->GetMsg());


}
