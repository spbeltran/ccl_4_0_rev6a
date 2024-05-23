// XCompCtrl.h: interface for the XCompCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XCompCtrl_INCLUDED_)
#define _PROC_XCompCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiCompCtrlV4.h"

class XCompCtrl : public CigiBaseEventProcessor
{
public:
   XCompCtrl();
   virtual ~XCompCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiCompCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiCompCtrlV4 *TPckt;

};

#endif // _PROC_XCompCtrl_INCLUDED_
