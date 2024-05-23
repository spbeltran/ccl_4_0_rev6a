// XCelestialCtrl.cpp: Body of the XCelestialCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XCelestialCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XCelestialCtrl::XCelestialCtrl()
{

}

XCelestialCtrl::~XCelestialCtrl()
{

}


void XCelestialCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiCelestialCtrlV4 *InPckt = (CigiCelestialCtrlV4 *)Packet;

   printf("===> CigiCelestialCtrlV4 <===\n");

   printf("Hour ==> %d\n",InPckt->GetHour());
   printf("Minute ==> %d\n",InPckt->GetMinute());
   printf("Seconds ==> %.5f\n",InPckt->GetSeconds());
   printf("EphemerisEn ==> %d\n",InPckt->GetEphemerisEn());
   printf("SunEn ==> %d\n",InPckt->GetSunEn());
   printf("MoonEn ==> %d\n",InPckt->GetMoonEn());
   printf("StarEn ==> %d\n",InPckt->GetStarEn());
   printf("DateVld ==> %d\n",InPckt->GetDateVld());
   printf("Month ==> %d\n",InPckt->GetMonth());
   printf("Day ==> %d\n",InPckt->GetDay());
   printf("Year ==> %d\n",InPckt->GetYear());
   printf("StarInt ==> %f\n",InPckt->GetStarInt());


}
