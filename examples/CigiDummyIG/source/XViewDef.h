// XViewDef.h: interface for the XViewDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XViewDef_INCLUDED_)
#define _PROC_XViewDef_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiViewDefV4.h"

class XViewDef : public CigiBaseEventProcessor
{
public:
   XViewDef();
   virtual ~XViewDef();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiViewDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiViewDefV4 *TPckt;

};

#endif // _PROC_XViewDef_INCLUDED_
