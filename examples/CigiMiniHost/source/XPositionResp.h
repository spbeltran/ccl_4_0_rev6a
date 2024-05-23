// XPositionResp.h: interface for the XPositionResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XPositionResp_INCLUDED_)
#define _PROC_XPositionResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiPositionRespV4.h"

class XPositionResp : public CigiBaseEventProcessor
{
public:
   XPositionResp();
   virtual ~XPositionResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiPositionRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiPositionRespV4 *TPckt;

};

#endif // _PROC_XPositionResp_INCLUDED_
