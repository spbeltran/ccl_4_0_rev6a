// XCollDetVolResp.h: interface for the XCollDetVolResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XCollDetVolResp_INCLUDED_)
#define _PROC_XCollDetVolResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiCollDetVolRespV4.h"

class XCollDetVolResp : public CigiBaseEventProcessor
{
public:
   XCollDetVolResp();
   virtual ~XCollDetVolResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiCollDetVolRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiCollDetVolRespV4 *TPckt;

};

#endif // _PROC_XCollDetVolResp_INCLUDED_
