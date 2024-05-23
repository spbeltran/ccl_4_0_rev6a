// XEntityPositionCtrl.h: interface for the XEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XEntityPositionCtrl_INCLUDED_)
#define _PROC_XEntityPositionCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiEntityPositionCtrlV4.h"

class XEntityPositionCtrl : public CigiBaseEventProcessor
{
public:
   XEntityPositionCtrl();
   virtual ~XEntityPositionCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiEntityPositionCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiEntityPositionCtrlV4 *TPckt;

};

#endif // _PROC_XEntityPositionCtrl_INCLUDED_
