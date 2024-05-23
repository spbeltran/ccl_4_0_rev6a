// XMaritimeSurfaceCtrl.h: interface for the XMaritimeSurfaceCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XMaritimeSurfaceCtrl_INCLUDED_)
#define _PROC_XMaritimeSurfaceCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiMaritimeSurfaceCtrlV4.h"

class XMaritimeSurfaceCtrl : public CigiBaseEventProcessor
{
public:
   XMaritimeSurfaceCtrl();
   virtual ~XMaritimeSurfaceCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiMaritimeSurfaceCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiMaritimeSurfaceCtrlV4 *TPckt;

};

#endif // _PROC_XMaritimeSurfaceCtrl_INCLUDED_
