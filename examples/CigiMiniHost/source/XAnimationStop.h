// XAnimationStop.h: interface for the XAnimationStop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XAnimationStop_INCLUDED_)
#define _PROC_XAnimationStop_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiAnimationStopV4.h"

class XAnimationStop : public CigiBaseEventProcessor
{
public:
   XAnimationStop();
   virtual ~XAnimationStop();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiAnimationStopV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiAnimationStopV4 *TPckt;

};

#endif // _PROC_XAnimationStop_INCLUDED_
