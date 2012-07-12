// Copyright 2004 Scott Lanham.
// ----------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef CAMERA_H
#define CAMERA_H

#include <qgl.h>

#include <stk/vector3.h>
using namespace stk;

//! Base class of all cameras.

class camera
{
    public:

        virtual ~camera();
    
        camera();
        
        virtual void viewSetup(); //!< Setup cameras view into 3D space.

        typedef enum
        {
            BASE_CAMERA, //!< No specific camera has been specified.
            FIRST_PERSON, //!< Camera is based on a first person view.
            MODELVIEW  //!< Camera is model view centric.
            
        } cameraType;

        int type();

        enum
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        void viewType ( int type );

        void zoom ( double delta ); //!< Change focal distance by delta.

        int viewPortWidth(); //!< Get view port width.
        void viewPortWidth ( int width ); //!< Set view port width.
        
        int viewPortHeight(); //!< Get view port height.
        void viewPortHeight ( int height ); //!< Set view port height.

        double dotPitch(); //!< Get dot pitch.
        void dotPitch ( double size ); //!< Set dot pitch.

        double focalLength(); //!< Get Focal Length.
        void focalLength ( double length );

        double nearClip(); //!< Get position of near clip plane.
        void nearClip ( double distFromEye ); //!< Set position of near clip plane.

        double farClip(); //!< Get position of far clip plane.
        void farClip ( double distFromEye ); //!< Set position of far clip plane.

    protected:

        //! Adjust vector2 to be orthogonal to vector1.
        void adjustOrthogonal ( vector3& vector1, vector3& vector2 );

        //! @par Notes All measurements are in metres unless otherwise specified.
        
        double      near_clip;  //!< Near clipping plane relative to the image plane.
        double      far_clip;  //!< Far clipping plane relative to the image plane.
        
        double      focalLen;  //!< Focal length. Length from eye to image plane.

        int         view_port_width; //!< Viewport width in pixels.
        int         view_port_height; //!< Viewport height in pixels.
        double      dot_pitch;

        int         camera_type;

        int         view_type;  // Ortho or projection.

    private:

        void init();
};

#endif
