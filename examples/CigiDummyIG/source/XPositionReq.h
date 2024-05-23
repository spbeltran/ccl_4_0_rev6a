// XPostionReq.h: interface for the XPostionReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XPostionReq_INCLUDED_)
#define _PROC_XPostionReq_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiPositionReqV4.h"

class XPositionReq : public CigiBaseEventProcessor
{
public:
   XPositionReq();
   virtual ~XPositionReq();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiPositionReqV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiPositionReqV4 *TPckt;

};

#endif // _PROC_XPostionReq_INCLUDED_
