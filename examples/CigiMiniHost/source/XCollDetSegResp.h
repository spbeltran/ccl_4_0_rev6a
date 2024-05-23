// XCollDetSegResp.h: interface for the XCollDetSegResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XCollDetSegResp_INCLUDED_)
#define _PROC_XCollDetSegResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiCollDetSegRespV4.h"

class XCollDetSegResp : public CigiBaseEventProcessor
{
public:
   XCollDetSegResp();
   virtual ~XCollDetSegResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiCollDetSegRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiCollDetSegRespV4 *TPckt;

};

#endif // _PROC_XCollDetSegResp_INCLUDED_
