// XWaveCtrl.cpp: Body of the XWaveCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XWaveCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XWaveCtrl::XWaveCtrl()
{

}

XWaveCtrl::~XWaveCtrl()
{

}


void XWaveCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiWaveCtrlV4 *InPckt = (CigiWaveCtrlV4 *)Packet;

   printf("===> WaveCtrl <===\n");

   printf("Entity/Rgn ID ==> %d\n",InPckt->GetEntityRgnID());
   printf("WaveID ==> %d\n",InPckt->GetWaveID());
   printf("WaveEn ==> %d\n",InPckt->GetWaveEn());
   if( InPckt->GetScope() == 0 )
	   printf("Scope ==> 0: Global\n" );
   else if( InPckt->GetScope() == 1 )
	   printf("Scope ==> 1: Regional\n" );
   else if( InPckt->GetScope() == 2  )
	   printf("Scope ==> 2: Enitiy-Assigned\n" );


   if( InPckt->GetBreaker() == 0 )
	   printf("Breaker ==> 0: Plunging\n" );
   else if( InPckt->GetBreaker() == 1 )
	   printf("Breaker ==> 1: Spilling\n" );
   else if( InPckt->GetBreaker() == 2  )
	   printf("Breaker ==> 2: Surging\n" );

   printf("WaveHt ==> %f\n",InPckt->GetWaveHt());
   printf("WaveLen ==> %f\n",InPckt->GetWaveLen());
   printf("Period ==> %f\n",InPckt->GetPeriod());
   printf("Direction ==> %f\n",InPckt->GetDirection());
   printf("PhaseOff ==> %f\n",InPckt->GetPhaseOff());
   printf("Leading ==> %f\n",InPckt->GetLeading());


}
