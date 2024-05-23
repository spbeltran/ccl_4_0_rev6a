// XSymbolCircleDefV3_3.h: interface for the XSymbolCircleDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolCircleDefV4_INCLUDED_)
#define _PROC_XSymbolCircleDefV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolCircleDefV4.h"

class XSymbolCircleDefV4 : public CigiBaseEventProcessor
{
public:
   XSymbolCircleDefV4();
   virtual ~XSymbolCircleDefV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolCircleDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolCircleDefV4 *TPckt;

};

#endif // _PROC_XSymbolCircleDefV4_INCLUDED_
