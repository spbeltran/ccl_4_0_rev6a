// XViewCtrl.h: interface for the XViewCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XViewCtrl_INCLUDED_)
#define _PROC_XViewCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiViewCtrlV4.h"

class XViewCtrl : public CigiBaseEventProcessor
{
public:
   XViewCtrl();
   virtual ~XViewCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiViewCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiViewCtrlV4 *TPckt;

};

#endif // _PROC_XViewCtrl_INCLUDED_
