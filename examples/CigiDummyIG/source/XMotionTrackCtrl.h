// XMotionTrackCtrl.h: interface for the XMotionTrackCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XMotionTrackCtrl_INCLUDED_)
#define _PROC_XMotionTrackCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiMotionTrackCtrlV4.h"

class XMotionTrackCtrl : public CigiBaseEventProcessor
{
public:
   XMotionTrackCtrl();
   virtual ~XMotionTrackCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiMotionTrackCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiMotionTrackCtrlV4 *TPckt;

};

#endif // _PROC_XMotionTrackCtrl_INCLUDED_
