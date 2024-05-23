// XEnvRgnCtrl.cpp: Body of the XEnvRgnCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XEnvRgnCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XEnvRgnCtrl::XEnvRgnCtrl()
{

}

XEnvRgnCtrl::~XEnvRgnCtrl()
{

}


void XEnvRgnCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiEnvRgnCtrlV4 *InPckt = (CigiEnvRgnCtrlV4 *)Packet;

   printf("===> EnvRgnCtrl <===\n");

   printf("RegionID ==> %d\n",InPckt->GetRegionID());
   if( InPckt->GetRgnState() == 0 ) 
	printf("RgnState ==> 0: Inactive\n");
   else if( InPckt->GetRgnState() == 1 ) 
	printf("RgnState ==> 1: Active\n");
   else if( InPckt->GetRgnState() == 2 ) 
	printf("RgnState ==> 2: Destroyed\n");

   if( InPckt->GetWeatherProp() == 0 )
	printf("WeatherProp ==> 0: Use Last\n" );
   else 
	printf("WeatherProp ==> 1: Merge\n" );

   if( InPckt->GetAerosol() == 0 )
	printf("Aerosol ==> 0: Use Last\n" );
   else 
	printf("Aerosol ==> 1: Merge\n" );

   if( InPckt->GetMaritimeSurface()  == 0 )
	printf("MaritimeSurface ==> 0: Use Last\n" );
   else 
	printf("MaritimeSurface ==> 1: Merge\n" );

   if( InPckt->GetTerrestrialSurface() == 0 )
	printf("TerrestrialSurface ==> 0: Use Last\n" );
   else 
	printf("TerrestrialSurface ==> 1: Merge\n" );

   printf("Lat ==> %f\n",InPckt->GetLat());
   printf("Lon ==> %f\n",InPckt->GetLon());
   printf("XSize ==> %f\n",InPckt->GetXSize());
   printf("YSize ==> %f\n",InPckt->GetYSize());
   printf("CornerRadius ==> %f\n",InPckt->GetCornerRadius());
   printf("Rotation ==> %f\n",InPckt->GetRotation());
   printf("Transition ==> %f\n",InPckt->GetTransition());


}
