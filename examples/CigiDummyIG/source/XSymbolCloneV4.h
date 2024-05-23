// XSymbolCloneV4.h: interface for the XSymbolCloneV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolCloneV4_INCLUDED_)
#define _PROC_XSymbolCloneV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolCloneV4.h"

class XSymbolCloneV4 : public CigiBaseEventProcessor
{
public:
   XSymbolCloneV4();
   virtual ~XSymbolCloneV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolCloneV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolCloneV4 *TPckt;

};

#endif // _PROC_XSymbolCloneV4_INCLUDED_
