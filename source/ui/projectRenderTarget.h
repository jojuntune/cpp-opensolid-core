// Copyright 2008 Scott Lanham.
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

#ifndef OS_PROJECT_RENDERTARGET_H
#define OS_PROJECT_RENDERTARGET_H

#include <graph/project.h>

#include "renderTarget.h"

namespace opensolid
{

class projectRenderTarget : public renderTarget
{
    public:

        projectRenderTarget ( project::sptr projToRender );

        virtual void render();

    private:

        project::sptr proj; // Project to render.
};

}

#endif
