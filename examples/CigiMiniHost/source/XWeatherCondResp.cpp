// XWeatherCondResp.cpp: Body of the XWeatherCondResp class.
//
//////////////////////////////////////////////////////////////////////

#include "XWeatherCondResp.h"

#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XWeatherCondResp::XWeatherCondResp()
{

}

XWeatherCondResp::~XWeatherCondResp()
{

}


void XWeatherCondResp::OnPacketReceived(CigiBasePacket *Packet)
{
CigiWeatherCondRespV4 *InPckt = (CigiWeatherCondRespV4 *)Packet;

   printf("===> WeatherCondResp <===\n");

   printf("RequestID ==> %d\n",InPckt->GetRequestID());
   printf("Humidity ==> %d\n",InPckt->GetHumidity());
   printf("AirTemp ==> %f\n",InPckt->GetAirTemp());
   printf("Visibility ==> %f\n",InPckt->GetVisibility());
   printf("HorizWindSp ==> %f\n",InPckt->GetHorizWindSp());
   printf("VertWindSp ==> %f\n",InPckt->GetVertWindSp());
   printf("WindDir ==> %f\n",InPckt->GetWindDir());
   printf("BaroPress ==> %f\n",InPckt->GetBaroPress());


}
