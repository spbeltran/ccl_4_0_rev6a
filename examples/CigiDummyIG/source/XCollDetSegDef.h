// XCollDetSegDef.h: interface for the XCollDetSegDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XCollDetSegDef_INCLUDED_)
#define _PROC_XCollDetSegDef_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiCollDetSegDefV4.h"

class XCollDetSegDef : public CigiBaseEventProcessor
{
public:
   XCollDetSegDef();
   virtual ~XCollDetSegDef();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiCollDetSegDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiCollDetSegDefV4 *TPckt;

};

#endif // _PROC_XCollDetSegDef_INCLUDED_
