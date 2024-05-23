// XTerrestrialSurfaceCtrl.cpp: Body of the XTerrestrialSurfaceCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XTerrestrialSurfaceCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XTerrestrialSurfaceCtrl::XTerrestrialSurfaceCtrl()
{

}

XTerrestrialSurfaceCtrl::~XTerrestrialSurfaceCtrl()
{

}


void XTerrestrialSurfaceCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiTerrestrialSurfaceCtrlV4 *InPckt = (CigiTerrestrialSurfaceCtrlV4 *)Packet;

   printf("===> TerrestrialSurfaceCtrl <===\n");

   printf("EntityRgnID ==> %d\n",InPckt->GetEntityRgnID());
   printf("SurfaceCondID ==> %d\n",InPckt->GetSurfaceCondID());
   printf("SurfaceCondEn ==> %d\n",InPckt->GetSurfaceCondEn());
   if( InPckt->GetScope() == 0 )
	   printf("Scope ==> 0: Global\n" );
   else if( InPckt->GetScope() == 1 )
	   printf("Scope ==> 1: Regional\n" );
   else if( InPckt->GetScope() == 2  )
	   printf("Scope ==> 2: Enitiy\n" );
   printf("Severity ==> %d\n",InPckt->GetSeverity());
   printf("Coverage ==> %d\n",InPckt->GetCoverage());


}
