// XSymbolLineDefV4.h: interface for the XSymbolLineDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolPolygonDefV4_INCLUDED_)
#define _PROC_XSymbolPolygonDefV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolPolygonDefV4.h"

class XSymbolPolygonDefV4 : public CigiBaseEventProcessor
{
public:
   XSymbolPolygonDefV4();
   virtual ~XSymbolPolygonDefV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolPolygonDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolPolygonDefV4 *TPckt;

};

#endif // _PROC_XSymbolPolygonDefV4_INCLUDED_
