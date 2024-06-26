// XArtPartCtrl.h: interface for the XArtPartCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XArtPartCtrl_INCLUDED_)
#define _PROC_XArtPartCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiArtPartCtrlV4.h"

class XArtPartCtrl : public CigiBaseEventProcessor
{
public:
   XArtPartCtrl();
   virtual ~XArtPartCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiArtPartCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiArtPartCtrlV4 *TPckt;

};

#endif // _PROC_XArtPartCtrl_INCLUDED_
