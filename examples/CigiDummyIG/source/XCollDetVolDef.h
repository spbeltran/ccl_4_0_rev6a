// XCollDetVolDef.h: interface for the XCollDetVolDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XCollDetVolDef_INCLUDED_)
#define _PROC_XCollDetVolDef_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiCollDetVolDefV4.h"

class XCollDetVolDef : public CigiBaseEventProcessor
{
public:
   XCollDetVolDef();
   virtual ~XCollDetVolDef();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiCollDetVolDefV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiCollDetVolDefV4 *TPckt;

};

#endif // _PROC_XCollDetVolDef_INCLUDED_
