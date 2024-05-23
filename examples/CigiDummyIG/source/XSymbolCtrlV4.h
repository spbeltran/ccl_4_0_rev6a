// XSymbolCtrlV4.h: interface for the XSymbolCtrlV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSymbolCtrlV4_INCLUDED_)
#define _PROC_XSymbolCtrlV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSymbolCtrlV4.h"

class XSymbolCtrlV4 : public CigiBaseEventProcessor
{
public:
   XSymbolCtrlV4();
   virtual ~XSymbolCtrlV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSymbolCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSymbolCtrlV4 *TPckt;

};

#endif // _PROC_XSymbolCtrlV4_INCLUDED_
