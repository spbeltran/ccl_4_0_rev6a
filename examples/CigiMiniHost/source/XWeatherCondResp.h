// XWeatherCondResp.h: interface for the XWeatherCondResp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XWeatherCondResp_INCLUDED_)
#define _PROC_XWeatherCondResp_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiWeatherCondRespV4.h"

class XWeatherCondResp : public CigiBaseEventProcessor
{
public:
   XWeatherCondResp();
   virtual ~XWeatherCondResp();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiWeatherCondRespV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiWeatherCondRespV4 *TPckt;

};

#endif // _PROC_XWeatherCondResp_INCLUDED_
