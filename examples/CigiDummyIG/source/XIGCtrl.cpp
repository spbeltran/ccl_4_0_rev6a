// XIGCtrl.cpp: Body of the XIGCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XIGCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XIGCtrl::XIGCtrl()
{

}

XIGCtrl::~XIGCtrl()
{

}


void XIGCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
#if 0
   CigiIGCtrlV4 *InPckt = (CigiIGCtrlV4 *)Packet;

   bool ok = true;

   printf("===> IGCtrl <===\n");

   printf("Version ==> %d\n",InPckt->GetVersion());
   printf("MinorVersion ==> %d\n",InPckt->GetMinorVersion());
   printf("DatabaseID ==> %d\n",InPckt->GetDatabaseID());
   printf("IGMode ==> %d\n",InPckt->GetIGMode());
   printf("TimestampValid ==> %d\n",InPckt->GetTimeStampValid());
   printf("FrameCntr ==> %d\n",InPckt->GetFrameCntr());
   printf("TimeStampV4 ==> %d\n",InPckt->GetTimeStamp());
   printf("Last Recd IG Frame  ==> %d\n",InPckt->GetLastRcvdIGFrame());

   if(InPckt->GetSmoothingEn())
      printf("Smoothing Enabled\n");
   else
      printf("Smoothing Disabled\n");
#endif

}
