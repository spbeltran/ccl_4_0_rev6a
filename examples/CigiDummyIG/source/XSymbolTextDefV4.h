// XSymbolTextDefV3_3.h: interface for the XSymbolTextDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolTextDefV4_INCLUDED_)
#define _PROC_XSymbolTextDefV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolTextDefV4.h"

class XSymbolTextDefV4 : public CigiBaseEventProcessor
{
public:
   XSymbolTextDefV4();
   virtual ~XSymbolTextDefV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolTextDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolTextDefV4 *TPckt;

};

#endif // _PROC_XSymbolTextDefV4_INCLUDED_
