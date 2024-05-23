// XWaveCtrl.h: interface for the XWaveCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XWaveCtrl_INCLUDED_)
#define _PROC_XWaveCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiWaveCtrlV4.h"

class XWaveCtrl : public CigiBaseEventProcessor
{
public:
   XWaveCtrl();
   virtual ~XWaveCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiWaveCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiWaveCtrlV4 *TPckt;

};

#endif // _PROC_XWaveCtrl_INCLUDED_
