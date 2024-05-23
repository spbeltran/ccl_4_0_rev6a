// XEntityCtrl.cpp: Body of the XEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "XEntityCtrl.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XEntityCtrl::XEntityCtrl()
{

}

XEntityCtrl::~XEntityCtrl()
{

}


void XEntityCtrl::OnPacketReceived(CigiBasePacket *Packet)
{
   CigiEntityCtrlV4 *InPckt = (CigiEntityCtrlV4 *)Packet;

   bool ok = true;

   printf("===> EntityCtrl <===\n");

   printf("EntityID ==> %d\n",InPckt->GetEntityID());
   printf("EntityState = %d : ",InPckt->GetEntityState());
   switch(InPckt->GetEntityState())
   {
   case 0:
      printf("Inactive/Standby\n");
      break;
   case 1:
      printf("Active\n");
      break;
   case 2:
      printf("Destroyed\n");
      break;
   }
   printf("Collision Reporting = %d : ",InPckt->GetCollisionDetectEn());
   switch(InPckt->GetCollisionDetectEn())
   {
   case 0:
      printf("Disabled\n");
      break;
   case 1:
      printf("Enabled\n");
      break;
   }
   printf("Inherit Alpha = %d : ",InPckt->GetInheritAlpha());
   switch(InPckt->GetInheritAlpha())
   {
   case 0:
      printf("Disabled\n");
      break;
   case 1:
      printf("Enabled\n");
      break;
   }

   printf("Smoothing Enable= %d : ",InPckt->GetSmoothingEn());
   switch(InPckt->GetSmoothingEn())
   {
   case 0:
      printf("Disabled\n");
      break;
   case 1:
      printf("Enabled\n");
      break;
   }

   printf("Extended Entity Type = %d : ",InPckt->GetExtendedEntityType());
   switch(InPckt->GetExtendedEntityType())
   {
   case 0:
      printf("Short\n");
      break;
   case 1:
      printf("Extended\n");
      break;
   }

   printf("Alpha ==> %d\n",InPckt->GetAlpha());
   printf("EntityKind ==> %d\n",InPckt->GetEntityKind());
   printf("EntityDomain ==> %d\n",InPckt->GetEntityDomain());
   if( InPckt->GetExtendedEntityType() )
	printf("EntityCountry ==> %d\n",InPckt->GetEntityCountry());
   else
	printf("ShortEntityType ==> %d\n",InPckt->GetShortEntityType());


   printf("EntityCategory ==> %d\n",InPckt->GetEntityCategory());
   printf("EntitySubcategory ==> %d\n",InPckt->GetEntitySubcategory());
   printf("EntitySpecific ==> %d\n",InPckt->GetEntitySpecific());
   printf("EntityExtra ==> %d\n",InPckt->GetEntityExtra());

}
