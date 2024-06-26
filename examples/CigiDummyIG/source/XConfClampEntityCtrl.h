// XConfClampEntityCtrl.h: interface for the XConfClampEntityCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XConfClampEntityCtrl_INCLUDED_)
#define _PROC_XConfClampEntityCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiConfClampEntityCtrlV4.h"

class XConfClampEntityCtrl : public CigiBaseEventProcessor
{
public:
   XConfClampEntityCtrl();
   virtual ~XConfClampEntityCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiConfClampEntityCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiConfClampEntityCtrlV4 *TPckt;

};

#endif // _PROC_XConfClampEntityCtrl_INCLUDED_
