// XTrajectory.h: interface for the XTrajectory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XACCELERATION_CTRL_INCLUDED_)
#define _PROC_XACCELERATION_CTRL_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiAccelerationCtrlV4.h"

class XAccelerationCtrl : public CigiBaseEventProcessor
{
public:
   XAccelerationCtrl();
   virtual ~XAccelerationCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiAccelerationCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiAccelerationCtrlV4 *TPckt;

};

#endif // _PROC_XACCELERATION_CTRL_INCLUDED_
