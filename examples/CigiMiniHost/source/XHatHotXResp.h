// XHatHotXResp.h: interface for the XHatHotXResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XHatHotXResp_INCLUDED_)
#define _PROC_XHatHotXResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiHatHotXRespV4.h"

class XHatHotXResp : public CigiBaseEventProcessor
{
public:
   XHatHotXResp();
   virtual ~XHatHotXResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiHatHotXRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiHatHotXRespV4 *TPckt;

};

#endif // _PROC_XHatHotXResp_INCLUDED_
