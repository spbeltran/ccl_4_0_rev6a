/** <pre>
 *  The SDK is used to create and format CIGI compliant messages.
 *  Copyright (c) 2001-2005 The Boeing Company
 *  
 *  This library is free software; you can redistribute it and/or modify it 
 *  under the terms of the GNU Lesser General Public License as published by 
 *  the Free Software Foundation; either version 2.1 of the License, or (at 
 *  your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser Public License for more 
 *  details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License 
 *  along with this library; if not, write to the Free Software Foundation, 
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *  
 *  FILENAME:   CigiBaseSignalProcessing.h
 *  LANGUAGE:   C++
 *  CLASS:      UNCLASSIFIED
 *  PROJECT:    Common Image Generator Interface (CIGI) SDK
 *  
 *  PROGRAM DESCRIPTION: 
 *  ...
 *  
 *  MODIFICATION NOTES:
 *  DATE     NAME                                SCR NUMBER
 *  DESCRIPTION OF CHANGE........................
 *  
 *  09/17/2003 Greg Basler                       CIGI_CR_DR_1
 *  Initial Release.
 *  
 *  01/21/2005 Greg Basler                       Version 1.5
 *  Added the CIGI_SPEC modifier to the class declaration for exporting the 
 *  class in a Windows DLL.
 *  
 *  04/03/2008 Greg Basler                       Version 2.1.0
 *  Fixed the signals and added symbol signals
 *
 *  07/29/2015 Chas Whitley                      Version 4.0.0
 *  Initial Release for CIGI 4.0 compatibility.
 *  OnVelocityCtrl, OnAccelerationCtrl, OnSymbolPolygonDef,
 *  OnSymbolTexturedCircleDef, OnSymbolTexturedPolygonDef,
 *  OnAnimationControl
 *
 *  07/25/2019 Chas Whitley                      Version 4.0.2
 *  Added OnEntityPositionCtrl
 *
 * </pre>
 *  Author: The Boeing Company
 *
 */

#if !defined(_CIGI_BASE_SIGNAL_PROCESSING_INCLUDED_)
#define _CIGI_BASE_SIGNAL_PROCESSING_INCLUDED_

#include "CigiBasePacket.h"


//=========================================================
//! The base class for processing incoming packets using a 
//!   signal processing class.
//!
class CIGI_SPEC CigiBaseSignalProcessing  
{
public:

   //==> Management

   //=========================================================
   //! General Constructor
   //!
   CigiBaseSignalProcessing() { };

   //=========================================================
   //! General Destructor
   //!
   virtual ~CigiBaseSignalProcessing() { };



   //==> Incoming Packet Processing Functions

   //==+> Host to IG

   //=========================================================
   //! OnIGCtrl<br>
   //! A base function to process incoming IG control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnIGCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnArtPartCtrl<br>
   //! A base function to process incoming Articulated Part Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnArtPartCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnAtmosCtrl<br>
   //! A base function to process incoming Atmosphere Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnAtmosCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnCelestialCtrl<br>
   //! A base function to process incoming Celestial Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnCelestialCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnCollDetSegDef<br>
   //! A base function to process incoming Collision Detection Segment Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnCollDetSegDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnCollDetVolDef<br>
   //! A base function to process incoming Collision Detection Volume Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnCollDetVolDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnCompCtrl<br>
   //! A base function to process incoming Component Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnCompCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnConfClampEntityCtrl<br>
   //! A base function to process incoming Conformal Clamped Entity Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnConfClampEntityCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEarthModelDef<br>
   //! A base function to process incoming Earth Model Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEarthModelDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEntityCtrl<br>
   //! A base function to process incoming Entity control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEntityCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEnvCondReq<br>
   //! A base function to process incoming Environmental Conditions Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEnvCondReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEnvCtrl<br>
   //! A base function to process incoming Environmental Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEnvCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEnvRgnCtrl<br>
   //! A base function to process incoming Environmental Region Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEnvRgnCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHatReq<br>
   //! A base function to process incoming Hat only Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHatReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHatHotReq<br>
   //! A base function to process incoming Hat Hot Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHatHotReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHatHotXReq<br>
   //! A base function to process incoming Hat Hot Extended Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHatHotXReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHotReq<br>
   //! A base function to process incoming Hot only Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHotReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnLosSegReq<br>
   //! A base function to process incoming LOS Segment Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnLosSegReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnLosVectReq<br>
   //! A base function to process incoming LOS Vector Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnLosVectReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnMaritimeSurfaceCtrl<br>
   //! A base function to process incoming Maritime Surface Conditions Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnMaritimeSurfaceCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnMotionTrackCtrl<br>
   //! A base function to process incoming Motion Tracker control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnMotionTrackCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnPostionReq<br>
   //! A base function to process incoming Positon Request packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnPostionReq(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnRateCtrl<br>
   //! A base function to process incoming Rate Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnRateCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSensorCtrl<br>
   //! A base function to process incoming Sensor Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSensorCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnShortArtPartCtrl<br>
   //! A base function to process incoming Short Articulated Part Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnShortArtPartCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnIGMsg<br>
   //! A base function to process incoming Short Component Control packets.<br>
   //!   Segment Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnShortCompCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnShortSymbolCtrl<br>
   //! A base function to process incoming Short Symbol Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnShortSymbolCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSpecEffDef<br>
   //! A base function to process incoming Special Effect Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSpecEffDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolCircleDef<br>
   //! A base function to process incoming Symbol Circle Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolCircleDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolClone<br>
   //! A base function to process incoming Symbol Clone packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolClone(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolCtrl<br>
   //! A base function to process incoming Symbol Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolLineDef<br>
   //! A base function to process incoming Symbol Line Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolLineDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolTextDef<br>
   //! A base function to process incoming Symbol Text Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolTextDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolSurfaceDef<br>
   //! A base function to process incoming Symbol Surface Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolSurfaceDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnTerrestrialSurfaceCtrl<br>
   //! A base function to process incoming Terrestrial Surface Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnTerrestrialSurfaceCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnTrajectory<br>
   //! A base function to process incoming Trajectory Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnTrajectory(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnViewCtrl<br>
   //! A base function to process incoming View Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnViewCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnViewDef<br>
   //! A base function to process incoming View Definition packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnViewDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnWaveCtrl<br>
   //! A base function to process incoming Wave Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnWaveCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnWeatherCtrl<br>
   //! A base function to process incoming Weather Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnWeatherCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnVelocityCtrl<br>
   //! A base function to process incoming velocity Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnVelocityCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnAccelerationCtrl<br>
   //! A base function to process incoming acceleration Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnAccelerationCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolPolygonDef<br>
   //! A base function to process incoming Symbol Polygon 
   //! Definition Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolPolygonDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolTexturedCircleDef<br>
   //! A base function to process incoming Symbol Textured Circle 
   //! Definition Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolTexturedCircleDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSymbolTexturedPolygonDef<br>
   //! A base function to process incoming Symbol Textured
   //! Polygon Definition Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSymbolTexturedPolygonDef(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEntityPositionCtrl<br>
   //! A base function to process incoming Animation Control 
   //! packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEntityPositionCtrl(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnAnimationControl<br>
   //! A base function to process incoming Symbol Textured
   //! Polygon Definition Control packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnAnimationControl(CigiBasePacket *Packet) {Packet;};


   //==+> IG to Host

   //=========================================================
   //! OnSOF<br>
   //! A base function to process incoming Start Of Frame packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSOF(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnAerosolResp<br>
   //! A base function to process incoming Aerosol Resp packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnAerosolResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnAnimationStop<br>
   //! A base function to process incoming Animation Stop Notification packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnAnimationStop(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnCollDetSegResp<br>
   //! A base function to process incoming Collision Detection Segment Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnCollDetSegResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnCollDetVolResp<br>
   //! A base function to process incoming Collision Detection Volume Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnCollDetVolResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnEventNotification<br>
   //! A base function to process incoming Event Notification packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnEventNotification(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHatResp<br>
   //! A base function to process incoming Hat only Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHatResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHatHotResp<br>
   //! A base function to process incoming Hat Hot Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHatHotResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHatHotXResp<br>
   //! A base function to process incoming Hat Hot Extended Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHatHotXResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnHotResp<br>
   //! A base function to process incoming Hot only Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnHotResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnIGMsg<br>
   //! A base function to process incoming IG Message packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnIGMsg(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnLosResp<br>
   //! A base function to process incoming Los Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnLosResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnLosXResp<br>
   //! A base function to process incoming Los Extended Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnLosXResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnMaritimeSurfaceResp<br>
   //! A base function to process incoming Maritime Surface Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnMaritimeSurfaceResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnPositionResp<br>
   //! A base function to process incoming Position Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnPositionResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSensorResp<br>
   //! A base function to process incoming Sensor Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSensorResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnSensorXResp<br>
   //! A base function to process incoming Sensor Extended Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnSensorXResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnTerrestrialSurfaceResp<br>
   //! A base function to process incoming Terrestrial Surface Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnTerrestrialSurfaceResp(CigiBasePacket *Packet) {Packet;};

   //=========================================================
   //! OnWeatherCondResp<br>
   //! A base function to process incoming Weather Condition Response packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnWeatherCondResp(CigiBasePacket *Packet) {Packet;};



   //==+> Unrecognized

   //=========================================================
   //! OnUnrecognized<br>
   //! A base function to process any incoming unrecognized packets.<br>
   //! This function does nothing in this base class.<br>
   //! If processing is required, the inheriting class must
   //!   implement this call.
   //!
   virtual void OnUnrecognized(CigiBasePacket *Packet) {Packet;};

};

#endif // !defined(_CIGI_BASE_SIGNAL_PROCESSING_INCLUDED_)
