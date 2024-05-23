// XHatHotResp.h: interface for the XHatHotResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XHatHotResp_INCLUDED_)
#define _PROC_XHatHotResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiHatHotRespV4.h"

class XHatHotResp : public CigiBaseEventProcessor
{
public:
   XHatHotResp();
   virtual ~XHatHotResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiHatHotRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiHatHotRespV4 *TPckt;

};

#endif // _PROC_XHatHotResp_INCLUDED_
