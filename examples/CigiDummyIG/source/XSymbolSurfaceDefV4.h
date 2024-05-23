// XSymbolSurfaceDef.h: interface for the XSymbolSurfaceDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolSurfaceDefV4_INCLUDED_)
#define _PROC_XSymbolSurfaceDefV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolSurfaceDefV4.h"

class XSymbolSurfaceDefV4 : public CigiBaseEventProcessor
{
public:
   XSymbolSurfaceDefV4();
   virtual ~XSymbolSurfaceDefV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolSurfaceDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolSurfaceDefV4 *TPckt;

};

#endif // _PROC_XSymbolSurfaceDefV4_INCLUDED_
