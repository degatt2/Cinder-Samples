/*
 Copyright (c) 2010-2012, Paul Houx - All rights reserved.
 This code is intended for use with the Cinder C++ library: http://libcinder.org

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "cinder/Vector.h"
#include "cinder/Camera.h"
#include "cinder/Timeline.h"
#include "cinder/app/AppBasic.h"

#include <deque>

class Cam {
public:
	Cam();
	Cam( const ci::CameraStereo &aInitialCam ) { mInitialCam = mCurrentCam = aInitialCam; }

	void		setup();
	void		update(double elapsed);

	void		mouseDown( const ci::Vec2i &mousePos );
	void		mouseDrag( const ci::Vec2i &mousePos, bool leftDown, bool middleDown, bool rightDown );
	void		mouseUp( const ci::Vec2i &mousePos );

	void		resize( ci::app::ResizeEvent event );

	void		setCurrentCam( const ci::CameraStereo &aCurrentCam );

	const ci::CameraStereo&	getCamera();

	void		setDistanceTime(double time) { mTimeDistanceTarget = time; }

	void		setEyeSeparation( float distance ) { mCurrentCam.setEyeSeparation(distance); }
	void		setConvergence( float distance ) { mCurrentCam.setConvergence(distance); }

	void		enableStereoLeft() { mCurrentCam.enableStereoLeft(); }
	bool		isStereoLeftEnabled() const { return mCurrentCam.isStereoLeftEnabled(); }

	void		enableStereoRight() { mCurrentCam.enableStereoRight(); }
	bool		isStereoRightEnabled() const { return mCurrentCam.isStereoRightEnabled(); }

	void		disableStereo() { mCurrentCam.disableStereo(); }

	//! returns the position of the camera in world space
	ci::Vec3f	getPosition();
private:
	//!
	double		average(const std::deque<double> &v){
		double avg = 0.0;

		for(std::deque<double>::const_iterator itr=v.begin();itr!=v.end();++itr) 
			avg += (*itr / v.size());

		return avg;
	};

	//!
	ci::Vec3d	average(const std::deque<ci::Vec3d> &v){
		ci::Vec3d avg(0.0, 0.0, 0.0);

		for(std::deque<ci::Vec3d>::const_iterator itr=v.begin();itr!=v.end();++itr) 
			avg += (*itr / v.size());

		return avg;
	};
private:
	static const double		LATITUDE_LIMIT;
	static const double		LATITUDE_THRESHOLD;
	static const double		DISTANCE_MIN;
	static const double		DISTANCE_MAX;

	ci::CameraStereo		mCurrentCam;

	ci::Vec2i				mInitialMousePos;
	ci::CameraStereo		mInitialCam;

	double					mDeltaX;
	double					mDeltaY;
	double					mDeltaD;
	std::deque<ci::Vec3d>	mDeltas;

	bool					mIsMouseDown;

	double					mTimeMouse;
	double					mTimeOut;

	double					mTimeDistanceTarget;
	double					mTimeDistance;

	ci::Anim<double>		mLatitude;
	ci::Anim<double>		mLongitude;
	ci::Anim<double>		mDistance;
	ci::Anim<double>		mFov;
};