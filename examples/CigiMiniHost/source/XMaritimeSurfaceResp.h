// XMaritimeSurfaceResp.h: interface for the XMaritimeSurfaceResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XMaritimeSurfaceResp_INCLUDED_)
#define _PROC_XMaritimeSurfaceResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiMaritimeSurfaceRespV4.h"

class XMaritimeSurfaceResp : public CigiBaseEventProcessor
{
public:
   XMaritimeSurfaceResp();
   virtual ~XMaritimeSurfaceResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiMaritimeSurfaceRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiMaritimeSurfaceRespV4 *TPckt;

};

#endif // _PROC_XMaritimeSurfaceResp_INCLUDED_
