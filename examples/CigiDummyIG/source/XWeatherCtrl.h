// XWeatherCtrl.h: interface for the XWeatherCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XWeatherCtrl_INCLUDED_)
#define _PROC_XWeatherCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiWeatherCtrlV4.h"

class XWeatherCtrl : public CigiBaseEventProcessor
{
public:
   XWeatherCtrl();
   virtual ~XWeatherCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiWeatherCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiWeatherCtrlV4 *TPckt;

};

#endif // _PROC_XWeatherCtrl_INCLUDED_
