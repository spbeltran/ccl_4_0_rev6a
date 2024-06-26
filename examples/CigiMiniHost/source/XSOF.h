// XSOF.h: interface for the XSOF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROC_XSOF_INCLUDED_)
#define _PROC_XSOF_INCLUDED_

#include "CigiBaseEventProcessor.h"
#include "CigiSOFV4.h"

class XSOF : public CigiBaseEventProcessor
{
public:
   XSOF();
   virtual ~XSOF();

   virtual void OnPacketReceived(CigiBasePacket *Packet);

   void SetOrigPckt(CigiSOFV4 *TPcktIn) { TPckt = TPcktIn; }

protected:
   CigiSOFV4 *TPckt;

};

#endif // _PROC_XSOF_INCLUDED_
