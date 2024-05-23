// XSensorXResp.h: interface for the XSensorXResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSensorXResp_INCLUDED_)
#define _PROC_XSensorXResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSensorXRespV4.h"

class XSensorXResp : public CigiBaseEventProcessor
{
public:
   XSensorXResp();
   virtual ~XSensorXResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSensorXRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSensorXRespV4 *TPckt;

};

#endif // _PROC_XSensorXResp_INCLUDED_
