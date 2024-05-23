// XAnimationCtrl.h: interface for the XEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XAnimationCtrl_INCLUDED_)
#define _PROC_XAnimationCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiAnimationCtrlV4.h"

class XAnimationCtrl : public CigiBaseEventProcessor
{
public:
   XAnimationCtrl();
   virtual ~XAnimationCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiAnimationCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiAnimationCtrlV4 *TPckt;

};

#endif // _PROC_XAnimationCtrl_INCLUDED_
