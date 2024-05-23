// XAerosolResp.h: interface for the XAerosolResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XAerosolResp_INCLUDED_)
#define _PROC_XAerosolResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiAerosolRespV4.h"

class XAerosolResp : public CigiBaseEventProcessor
{
public:
   XAerosolResp();
   virtual ~XAerosolResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiAerosolRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiAerosolRespV4 *TPckt;

};

#endif // _PROC_XAerosolResp_INCLUDED_
