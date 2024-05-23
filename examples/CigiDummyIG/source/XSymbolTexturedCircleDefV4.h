// XSymbolTexturedCircleDefV4.h: interface for the XWeatherCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolTexturedCircleDefV4_INCLUDED_)
#define _PROC_XSymbolTexturedCircleDefV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolTexturedCircleDefV4.h"

class XSymbolTexturedCircleDefV4 : public CigiBaseEventProcessor
{
public:
   XSymbolTexturedCircleDefV4();
   virtual ~XSymbolTexturedCircleDefV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolTexturedCircleDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolTexturedCircleDefV4 *TPckt;

};

#endif // _PROC_XSymbolTexturedCircleDefV4_INCLUDED_
