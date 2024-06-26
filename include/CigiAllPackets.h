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
 *  FILENAME:   CigiAllPackets.h
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
 *  11/27/2007 Greg Basler                       Version 2.0.0
 *  Created to contain all the Cigi packet classes
 *  
 *  04/03/2007 Greg Basler                       Version 2.1.0
 *  Added CigiSymbolCloneV3_3
 *  
 *  05/14/2008 Greg Basler                       Version 2.2.0
 *  Added CigiIGCtrlV3_3 and CigiEntityCtrlV3_3
 *
 *  07/29/2015 Chas Whitley                      Version 4.0.0
 *  Initial Release for CIGI 4.0 compatibility.
 *
 * </pre>
 *  Author: The Boeing Company
 *
 */

#if !defined(_CIGI_ALL_PACKETS_INCLUDED_)
#define _CIGI_ALL_PACKETS_INCLUDED_


// IG control
#include "CigiIGCtrlV1.h"
#include "CigiIGCtrlV2.h"
#include "CigiIGCtrlV3.h"
#include "CigiIGCtrlV3_2.h"
#include "CigiIGCtrlV3_3.h"
#include "CigiIGCtrlV4.h"

// Entity control
#include "CigiEntityCtrlV1.h"
#include "CigiEntityCtrlV2.h"
#include "CigiEntityCtrlV3.h"
#include "CigiEntityCtrlV3_3.h"
#include "CigiEntityCtrlV4.h"

// View Definition
#include "CigiViewDefV1.h"
#include "CigiViewDefV2.h"
#include "CigiViewDefV3.h"
#include "CigiViewDefV4.h"

// View Control
#include "CigiViewCtrlV1.h"
#include "CigiViewCtrlV2.h"
#include "CigiViewCtrlV3.h"
#include "CigiViewCtrlV4.h"

// Rate Control
#include "CigiRateCtrlV1.h"
#include "CigiRateCtrlV2.h"
#include "CigiRateCtrlV3.h"
#include "CigiRateCtrlV3_2.h"

// Velocity Control
#include "CigiVelocityCtrlV4.h"

// Sensor Control
#include "CigiSensorCtrlV1.h"
#include "CigiSensorCtrlV2.h"
#include "CigiSensorCtrlV3.h"
#include "CigiSensorCtrlV4.h"

// Trajectory Definition
#include "CigiTrajectoryDefV1.h"
#include "CigiTrajectoryDefV2.h"
#include "CigiTrajectoryDefV3.h"

//Acceleration Control
#include "CigiAccelerationCtrlV4.h"

// Weather Control
#include "CigiWeatherCtrlV1.h"
#include "CigiWeatherCtrlV2.h"
#include "CigiWeatherCtrlV3.h"
#include "CigiWeatherCtrlV4.h"

// Collision Detection Segment Definition
#include "CigiCollDetSegDefV1.h"
#include "CigiCollDetSegDefV2.h"
#include "CigiCollDetSegDefV3.h"
#include "CigiCollDetSegDefV4.h"

// LOS Segment Request
#include "CigiLosSegReqV1.h"
#include "CigiLosSegReqV2.h"
#include "CigiLosSegReqV3.h"
#include "CigiLosSegReqV3_2.h"
#include "CigiLosSegReqV4.h"

// LOS Vector Request
#include "CigiLosVectReqV1.h"
#include "CigiLosVectReqV2.h"
#include "CigiLosVectReqV3.h"
#include "CigiLosVectReqV3_2.h"
#include "CigiLosVectReqV4.h"

// Hat Hot Request
#include "CigiHatReqV1.h"
#include "CigiHatReqV2.h"
#include "CigiHotReqV2.h"
#include "CigiHatHotReqV3.h"
#include "CigiHatHotReqV3_2.h"
#include "CigiHatHotReqV4.h"

// Environmental Control
#include "CigiEnvCtrlV1.h"
#include "CigiEnvCtrlV2.h"
#include "CigiAtmosCtrl.h"
#include "CigiAtmosCtrlV4.h"
#include "CigiCelestialCtrl.h"
#include "CigiCelestialCtrlV4.h"

// Special Effect Definision
#include "CigiSpecEffDefV1.h"
#include "CigiSpecEffDefV2.h"

// Articulated Part Control
#include "CigiArtPartCtrlV1.h"
#include "CigiArtPartCtrlV2.h"
#include "CigiArtPartCtrlV3.h"
#include "CigiArtPartCtrlV4.h"

// Collision Detection Volume Definition
#include "CigiCollDetVolDefV2.h"
#include "CigiCollDetVolDefV3.h"
#include "CigiCollDetVolDefV4.h"

// Short Articulated Part Control
#include "CigiShortArtPartCtrlV3.h"
#include "CigiShortArtPartCtrlV4.h"

// Conformal Clamped Entity Control
#include "CigiConfClampEntityCtrlV3.h"
#include "CigiConfClampEntityCtrlV4.h"

// Maritime Surface Conditions Control
#include "CigiMaritimeSurfaceCtrlV3.h"
#include "CigiMaritimeSurfaceCtrlV4.h"

// Environmental Region Control
#include "CigiEnvRgnCtrlV3.h"
#include "CigiEnvRgnCtrlV4.h"

// Terrestrial Surface Control
#include "CigiTerrestrialSurfaceCtrlV3.h"
#include "CigiTerrestrialSurfaceCtrlV4.h"

// Motion Tracker control
#include "CigiMotionTrackCtrlV3.h"
#include "CigiMotionTrackCtrlV4.h"

// Earth Model Definition
#include "CigiEarthModelDefV3.h"
#include "CigiEarthModelDefV4.h"

// Positon Request
#include "CigiPositionReqV3.h"
#include "CigiPositionReqV4.h"

// Environmental Conditions Request
#include "CigiEnvCondReqV3.h"
#include "CigiEnvCondReqV4.h"

// Wave Control
#include "CigiWaveCtrlV3.h"
#include "CigiWaveCtrlV4.h"

// Start Of Frame
#include "CigiSOFV1.h"
#include "CigiSOFV2.h"
#include "CigiSOFV3.h"
#include "CigiSOFV3_2.h"
#include "CigiSOFV4.h"

// Collision Detection Segment Response
#include "CigiCollDetSegRespV1.h"
#include "CigiCollDetSegRespV2.h"
#include "CigiCollDetSegRespV3.h"
#include "CigiCollDetSegRespV4.h"

// Collision Detection Volume Response
#include "CigiCollDetVolRespV2.h"
#include "CigiCollDetVolRespV3.h"
#include "CigiCollDetVolRespV4.h"

// Sensor Response
#include "CigiSensorRespV1.h"
#include "CigiSensorRespV2.h"
#include "CigiSensorRespV3.h"
#include "CigiSensorRespV4.h"

// Sensor Extended Response
#include "CigiSensorXRespV3.h"
#include "CigiSensorXRespV4.h"

// Los Response
#include "CigiLosRespV1.h"
#include "CigiLosRespV2.h"
#include "CigiLosRespV3.h"
#include "CigiLosRespV3_2.h"
#include "CigiLosRespV4.h"

// Los Extended Response
#include "CigiLosXRespV3.h"
#include "CigiLosXRespV3_2.h"
#include "CigiLosXRespV4.h"

// Hat Hot Response
#include "CigiHatRespV1.h"
#include "CigiHatRespV2.h"
#include "CigiHotRespV2.h"
#include "CigiHatHotRespV3.h"
#include "CigiHatHotRespV4.h"
#include "CigiHatHotXRespV3.h"
#include "CigiHatHotRespV3_2.h"
#include "CigiHatHotXRespV3_2.h"
#include "CigiHatHotXRespV4.h"

// Position Response
#include "CigiPositionRespV3.h"
#include "CigiPositionRespV4.h"

// Weather Condition Response
#include "CigiWeatherCondRespV3.h"
#include "CigiWeatherCondRespV4.h"

// Aerosol Resp
#include "CigiAerosolRespV3.h"
#include "CigiAerosolRespV4.h"

// Maritime Surface Response
#include "CigiMaritimeSurfaceRespV3.h"
#include "CigiMaritimeSurfaceRespV4.h"

// Terrestrial Surface Response
#include "CigiTerrestrialSurfaceRespV3.h"
#include "CigiTerrestrialSurfaceRespV4.h"

// Animation Stop Notification
#include "CigiAnimationStopV3.h"
#include "CigiAnimationStopV4.h"

// Event Notification
#include "CigiEventNotificationV3.h"
#include "CigiEventNotificationV4.h"

// IG Message
#include "CigiIGMsgV2.h"
#include "CigiIGMsgV3.h"
#include "CigiIGMsgV4.h"

// Component Control
#include "CigiCompCtrlV1.h"
#include "CigiCompCtrlV2.h"
#include "CigiCompCtrlV3.h"
#include "CigiCompCtrlV3_3.h"
#include "CigiCompCtrlV4.h"
#include "CigiShortCompCtrlV3.h"
#include "CigiShortCompCtrlV3_3.h"
#include "CigiShortCompCtrlV4.h"

// Symbol Surface Definition
#include "CigiSymbolSurfaceDefV3_3.h"
#include "CigiSymbolSurfaceDefV4.h"

// Symbol Control
#include "CigiSymbolCtrlV3_3.h"
#include "CigiSymbolCtrlV4.h"

// Short Symbol Control
#include "CigiShortSymbolCtrlV3_3.h"
#include "CigiShortSymbolCtrlV4.h"

// Symbol Text Definition
#include "CigiSymbolTextDefV3_3.h"
#include "CigiSymbolTextDefV4.h"

// Symbol Circle Definition
#include "CigiSymbolCircleDefV3_3.h"
#include "CigiSymbolCircleDefV4.h"

// Symbol Line Definition
#include "CigiSymbolLineDefV3_3.h"

// Symbol Polygon Definition
#include "CigiSymbolPolygonDefV4.h"

// Symbol Clone
#include "CigiSymbolCloneV3_3.h"
#include "CigiSymbolCloneV4.h"

// Symbol Textured Circle Def
#include "CigiSymbolTexturedCircleDefV4.h"

// Symbol Textured Polygon Def
#include "CigiSymbolTexturedPolygonDefV4.h"

// Entity Position Control
#include "CigiEntityPositionCtrlV4.h"

// Animation Control
#include "CigiAnimationCtrlV4.h"

#endif   //  _CIGI_ALL_PACKETS_INCLUDED_

