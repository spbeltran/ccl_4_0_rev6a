// XSOF.cpp: Body of the XSOF class.
//
//////////////////////////////////////////////////////////////////////

#include "XSOF.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSOF::XSOF()
{

}

XSOF::~XSOF()
{

}


void XSOF::OnPacketReceived(CigiBasePacket *Packet)
{
CigiSOFV4 *InPckt = (CigiSOFV4 *)Packet;

   printf("===> SOF <===\n");

   printf("Version ==> %d\n",InPckt->GetVersion());
   printf("MinorVersion ==> %d\n",InPckt->GetMinorVersion());
   printf("DatabaseID ==> %d\n",InPckt->GetDatabaseID());
   printf("IGMode ==> %d\n",InPckt->GetIGMode());
   printf("TimestampValid ==> %d\n",InPckt->GetTimeStampValid());
   printf("FrameCntr ==> %d\n",InPckt->GetFrameCntr());
   printf("TimeStampV4 ==> %d\n",InPckt->GetTimeStamp());
   printf("FrameCounter ==> %d\n",InPckt->GetFrameCntr());
   printf("Last Recd Host Frame ==> %d\n",InPckt->GetLastRcvdHostFrame());

   printf("EarthRefModel ==> %d\n",InPckt->GetEarthRefModel());
}
