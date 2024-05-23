// XShortArtPartCtrl.h: interface for the XShortArtPartCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XShortArtPartCtrl_INCLUDED_)
#define _PROC_XShortArtPartCtrl_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiShortArtPartCtrlV4.h"

class XShortArtPartCtrl : public CigiBaseEventProcessor
{
public:
   XShortArtPartCtrl();
   virtual ~XShortArtPartCtrl();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiShortArtPartCtrlV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiShortArtPartCtrlV4 *TPckt;

};

#endif // _PROC_XShortArtPartCtrl_INCLUDED_
