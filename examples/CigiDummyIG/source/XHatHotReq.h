// XHatHotReq.h: interface for the XHatHotReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XHatHotReq_INCLUDED_)
#define _PROC_XHatHotReq_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiHatHotReqV4.h"

class XHatHotReq : public CigiBaseEventProcessor
{
public:
   XHatHotReq();
   virtual ~XHatHotReq();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiHatHotReqV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiHatHotReqV4 *TPckt;

};

#endif // _PROC_XHatHotReq_INCLUDED_
