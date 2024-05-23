// XSensorCtrl.h: interface for the XSensorCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSensorCtrl_INCLUDED_)
#define _PROC_XSensorCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSensorCtrlV4.h"

class XSensorCtrl : public CigiBaseEventProcessor
{
public:
   XSensorCtrl();
   virtual ~XSensorCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSensorCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSensorCtrlV4 *TPckt;

};

#endif // _PROC_XSensorCtrl_INCLUDED_
