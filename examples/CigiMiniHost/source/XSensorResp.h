// XSensorResp.h: interface for the XSensorResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSensorResp_INCLUDED_)
#define _PROC_XSensorResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSensorRespV4.h"

class XSensorResp : public CigiBaseEventProcessor
{
public:
   XSensorResp();
   virtual ~XSensorResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSensorRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSensorRespV4 *TPckt;

};

#endif // _PROC_XSensorResp_INCLUDED_
