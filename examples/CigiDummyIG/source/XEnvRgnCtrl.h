// XEnvRgnCtrl.h: interface for the XEnvRgnCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XEnvRgnCtrl_INCLUDED_)
#define _PROC_XEnvRgnCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiEnvRgnCtrlV4.h"

class XEnvRgnCtrl : public CigiBaseEventProcessor
{
public:
   XEnvRgnCtrl();
   virtual ~XEnvRgnCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiEnvRgnCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiEnvRgnCtrlV4 *TPckt;

};

#endif // _PROC_XEnvRgnCtrl_INCLUDED_
