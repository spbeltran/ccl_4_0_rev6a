// XEnvCondReq.h: interface for the XEnvCondReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XEnvCondReq_INCLUDED_)
#define _PROC_XEnvCondReq_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiEnvCondReqV4.h"

class XEnvCondReq : public CigiBaseEventProcessor
{
public:
   XEnvCondReq();
   virtual ~XEnvCondReq();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiEnvCondReqV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiEnvCondReqV4 *TPckt;

};

#endif // _PROC_XEnvCondReq_INCLUDED_
