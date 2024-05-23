// XEnvCondReq.cpp: Body of the XEnvCondReq class.
//
//////////////////////////////////////////////////////////////////////

#include "XEnvCondReq.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XEnvCondReq::XEnvCondReq()
{

}

XEnvCondReq::~XEnvCondReq()
{

}


void XEnvCondReq::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiEnvCondReqV4 *InPckt = (CigiEnvCondReqV4 *)Packet;

   bool ok = true;

   printf("===> EnvCondReq <===\n");

   printf("ReqID ==> %d\n",InPckt->GetReqID());
   printf("ReqType ==> %d\n",InPckt->GetReqType());

	if( InPckt->GetReqType() == 0 )
	   printf("Request Type ==> 0: Maritime Surface Conditions\n" );
	else if( InPckt->GetReqType() == 1 )
	   printf("Request Type ==> 1: Terrestial Surface Conditions\n" );
	else if( InPckt->GetReqType() == 2 )
	   printf("Request Type ==> 2: GeodeticWeather Conditions\n" );
	else if( InPckt->GetReqType() == 3 )
	   printf("Request Type ==> 3: EntityAerosol Concentrations\n" );

   printf("Lat ==> %f\n",InPckt->GetLat());
   printf("Lon ==> %f\n",InPckt->GetLon());
   printf("Alt ==> %f\n",InPckt->GetAlt());


}
