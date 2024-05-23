// XShortSymbolCtrlV4.h: interface for the XShortSymbolCtrlV3_3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XShortSymbolCtrlV4INCLUDED_)
#define _PROC_XShortSymbolCtrlV4_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiShortSymbolCtrlV4.h"

class XShortSymbolCtrlV4 : public CigiBaseEventProcessor
{
public:
   XShortSymbolCtrlV4();
   virtual ~XShortSymbolCtrlV4();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiShortSymbolCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiShortSymbolCtrlV4 *TPckt;

};

#endif // _PROC_XShortSymbolCtrlV4_INCLUDED_
