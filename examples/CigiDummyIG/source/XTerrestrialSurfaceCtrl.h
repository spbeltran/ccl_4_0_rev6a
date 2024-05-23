// XTerrestrialSurfaceCtrl.h: interface for the XTerrestrialSurfaceCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XTerrestrialSurfaceCtrl_INCLUDED_)
#define _PROC_XTerrestrialSurfaceCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiTerrestrialSurfaceCtrlV4.h"

class XTerrestrialSurfaceCtrl : public CigiBaseEventProcessor
{
public:
   XTerrestrialSurfaceCtrl();
   virtual ~XTerrestrialSurfaceCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiTerrestrialSurfaceCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiTerrestrialSurfaceCtrlV4 *TPckt;

};

#endif // _PROC_XTerrestrialSurfaceCtrl_INCLUDED_
