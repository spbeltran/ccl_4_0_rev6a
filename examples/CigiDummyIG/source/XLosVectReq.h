// XLosVectReq.h: interface for the XLosVectReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XLosVectReq_INCLUDED_)
#define _PROC_XLosVectReq_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiLosVectReqV4.h"

class XLosVectReq : public CigiBaseEventProcessor
{
public:
   XLosVectReq();
   virtual ~XLosVectReq();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiLosVectReqV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiLosVectReqV4 *TPckt;

};

#endif // _PROC_XLosVectReq_INCLUDED_
