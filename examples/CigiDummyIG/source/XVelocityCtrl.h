// XRateCtrl.h: interface for the XRateCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XVelocityCtrl_INCLUDED_)
#define _PROC_XVelocityCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiVelocityCtrlV4.h"

class XVelocityCtrl : public CigiBaseEventProcessor
{
public:
   XVelocityCtrl();
   virtual ~XVelocityCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiVelocityCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiVelocityCtrlV4 *TPckt;

};

#endif // _PROC_XVelocityCtrl_INCLUDED_
