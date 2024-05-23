// XLosResp.h: interface for the XLosResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XLosResp_INCLUDED_)
#define _PROC_XLosResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiLosRespV4.h"

class XLosResp : public CigiBaseEventProcessor
{
public:
   XLosResp();
   virtual ~XLosResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiLosRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiLosRespV4 *TPckt;

};

#endif // _PROC_XLosResp_INCLUDED_
