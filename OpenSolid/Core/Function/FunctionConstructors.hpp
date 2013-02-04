/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

// Public headers
#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    class Function;

    class FunctionConstructors
    {
    public:
        OPENSOLID_CORE_EXPORT static Function Identity(int numDimensions = 1);

        OPENSOLID_CORE_EXPORT static Function Parameter();

        OPENSOLID_CORE_EXPORT static Function Parameter(int totalNumParameters, int index);

        OPENSOLID_CORE_EXPORT static Function Parameters(int totalNumParameters);

        OPENSOLID_CORE_EXPORT static Function Parameters(
            int totalNumParameters,
            int startIndex,
            int numParameters
        );

        OPENSOLID_CORE_EXPORT static Function Components(
            const Function& xFunction,
            const Function& yFunction
        );

        OPENSOLID_CORE_EXPORT static Function Components(
            const Function& xFunction,
            const Function& yFunction,
            const Function& zFunction
        );
        
        OPENSOLID_CORE_EXPORT static Function Linear(const Axis2d& axis);
        OPENSOLID_CORE_EXPORT static Function Linear(const Frame2d& frame);
        OPENSOLID_CORE_EXPORT static Function Linear(const Axis3d& axis);
        OPENSOLID_CORE_EXPORT static Function Linear(const Plane3d& plane);
        OPENSOLID_CORE_EXPORT static Function Linear(const Frame3d& frame);
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(const Frame2d& frame);
        OPENSOLID_CORE_EXPORT static Function Elliptical(const Plane3d& plane);
        OPENSOLID_CORE_EXPORT static Function Elliptical(const Frame3d& frame);
    };
}
