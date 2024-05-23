// XMaritimeSurfaceCtrl.cpp: Body of the XMaritimeSurfaceCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XMaritimeSurfaceCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XMaritimeSurfaceCtrl::XMaritimeSurfaceCtrl()
{

}

XMaritimeSurfaceCtrl::~XMaritimeSurfaceCtrl()
{

}


void XMaritimeSurfaceCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiMaritimeSurfaceCtrlV4 *InPckt = (CigiMaritimeSurfaceCtrlV4 *)Packet;

   bool ok = true;

   printf("===> MaritimeSurfaceCtrl <===\n");

   printf("EntityRgnID ==> %d\n",InPckt->GetEntityRgnID());
   printf("SurfaceCondEn ==> %d\n",InPckt->GetSurfaceCondEn());
   printf("WhitecapEn ==> %d\n",InPckt->GetWhitecapEn());
   if( InPckt->GetScope() == 0 )
	   printf("Scope ==> 0: Global\n" );
   else if( InPckt->GetScope() == 1 )
	   printf("Scope ==> 1: Regional\n" );
   else if( InPckt->GetScope() == 2  )
	   printf("Scope ==> 2: Enitiy-Assigned\n" );
   printf("SurfaceHeight ==> %f\n",InPckt->GetSurfaceHeight());
   printf("WaterTemp ==> %f\n",InPckt->GetWaterTemp());
   printf("Clarity ==> %f\n",InPckt->GetClarity());

}
