// XSymbolLineDefV4.h: interface for the XSymbolLineDefV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolTexturedPolygonDefV4_INCLUDED_)
#define _PROC_XSymbolTexturedPolygonDefV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolTexturedPolygonDefV4.h"

class XSymbolTexturedPolygonDefV4 : public CigiBaseEventProcessor
{
public:
   XSymbolTexturedPolygonDefV4();
   virtual ~XSymbolTexturedPolygonDefV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolTexturedPolygonDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolTexturedPolygonDefV4 *TPckt;

};

#endif // _PROC_XSymbolTexturedPolygonDefV4_INCLUDED_
