// XTerrestrialSurfaceResp.h: interface for the XTerrestrialSurfaceResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XTerrestrialSurfaceResp_INCLUDED_)
#define _PROC_XTerrestrialSurfaceResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiTerrestrialSurfaceRespV4.h"

class XTerrestrialSurfaceResp : public CigiBaseEventProcessor
{
public:
   XTerrestrialSurfaceResp();
   virtual ~XTerrestrialSurfaceResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiTerrestrialSurfaceRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiTerrestrialSurfaceRespV4 *TPckt;

};

#endif // _PROC_XTerrestrialSurfaceResp_INCLUDED_
