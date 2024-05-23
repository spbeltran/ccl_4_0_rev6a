// XIGCtrl.h: interface for the XIGCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XIGCtrl_INCLUDED_)
#define _PROC_XIGCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiIGCtrlV4.h"

class XIGCtrl : public CigiBaseEventProcessor
{
public:
   XIGCtrl();
   virtual ~XIGCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiIGCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiIGCtrlV4 *TPckt;

};

#endif // _PROC_XIGCtrl_INCLUDED_
