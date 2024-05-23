// XEventNotification.h: interface for the XEventNotification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XEventNotification_INCLUDED_)
#define _PROC_XEventNotification_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiEventNotificationV4.h"

class XEventNotification : public CigiBaseEventProcessor
{
public:
   XEventNotification();
   virtual ~XEventNotification();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiEventNotificationV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiEventNotificationV4 *TPckt;

};

#endif // _PROC_XEventNotification_INCLUDED_
