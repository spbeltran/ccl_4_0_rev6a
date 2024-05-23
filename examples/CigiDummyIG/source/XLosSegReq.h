// XLosSegReq.h: interface for the XLosSegReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XLosSegReq_INCLUDED_)
#define _PROC_XLosSegReq_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiLosSegReqV4.h"

class XLosSegReq : public CigiBaseEventProcessor
{
public:
   XLosSegReq();
   virtual ~XLosSegReq();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiLosSegReqV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiLosSegReqV4 *TPckt;

};

#endif // _PROC_XLosSegReq_INCLUDED_
