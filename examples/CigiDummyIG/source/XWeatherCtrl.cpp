// XWeatherCtrl.cpp: Body of the XWeatherCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XWeatherCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XWeatherCtrl::XWeatherCtrl()
{

}

XWeatherCtrl::~XWeatherCtrl()
{

}


void XWeatherCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiWeatherCtrlV4 *InPckt = (CigiWeatherCtrlV4 *)Packet;

   printf("===> WeatherCtrl.h <===\n");

   printf("Entity/Region ID ==> %d\n",InPckt->GetEntityID());
   printf("LayerID ==> %d\n",InPckt->GetLayerID());
   printf("Humidity ==> %d\n",InPckt->GetHumidity());
   printf("WeatherEn ==> %d\n",InPckt->GetWeatherEn());
   printf("TopScudEn ==> %d\n",InPckt->GetTopScudEn());
   printf("BottomScudEn ==> %d\n",InPckt->GetBottomScudEn());
   printf("RandomWindsEn ==> %d\n",InPckt->GetRandomWindsEn());
   printf("RandomLightningEn ==> %d\n",InPckt->GetRandomLightningEn());
   printf("CloudType ==> %d\n",InPckt->GetCloudType());
   if( InPckt->GetScope() == 0 )
	   printf("Scope ==> 0: Global\n" );
   else if( InPckt->GetScope() == 1 )
	   printf("Scope ==> 1: Regional\n" );
   else if( InPckt->GetScope() == 2  )
	   printf("Scope ==> 2: Enitiy-Assigned\n" );
   printf("Scope ==> %d\n",InPckt->GetScope());
   printf("Severity ==> %d\n",InPckt->GetSeverity());
   printf("AirTemp ==> %f\n",InPckt->GetAirTemp());
   printf("VisibilityRng ==> %f\n",InPckt->GetVisibilityRng());
   printf("TopScudFreq ==> %f\n",InPckt->GetTopScudFreq());
   printf("BottomScudFreq ==> %f\n",InPckt->GetBottomScudFreq());
   printf("Coverage ==> %f\n",InPckt->GetCoverage());
   printf("BaseElev ==> %f\n",InPckt->GetBaseElev());
   printf("Thickness ==> %f\n",InPckt->GetThickness());
   printf("HorizWindSp ==> %f\n",InPckt->GetHorizWindSp());
   printf("VertWindSp ==> %f\n",InPckt->GetVertWindSp());
   printf("WindDir ==> %f\n",InPckt->GetWindDir());
   printf("BaroPress ==> %f\n",InPckt->GetBaroPress());
   printf("Aerosol ==> %f\n",InPckt->GetAerosol());


}
