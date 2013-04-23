/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>

namespace opensolid
{
    class FunctionConstructors
    {
    public:
        OPENSOLID_CORE_EXPORT static Function
        Zero(int numDimensions, int numParameters);

        OPENSOLID_CORE_EXPORT static Function
        Constant(double value, int numParameters);

        OPENSOLID_CORE_EXPORT static Function
        Constant(const VectorXd& vector, int numParameters);

        OPENSOLID_CORE_EXPORT static Function
        Identity(int numDimensions = 1);

        OPENSOLID_CORE_EXPORT static Function
        t();

        OPENSOLID_CORE_EXPORT static Function
        u();

        OPENSOLID_CORE_EXPORT static Function
        v();

        OPENSOLID_CORE_EXPORT static Function
        Parameter(int numParameters, int index);

        OPENSOLID_CORE_EXPORT static Function
        FromComponents(
            const Function& xFunction,
            const Function& yFunction
        );

        OPENSOLID_CORE_EXPORT static Function
        FromComponents(
            const Function& xFunction,
            const Function& yFunction,
            const Function& zFunction
        );
        
        OPENSOLID_CORE_EXPORT static Function
        Linear(const Axis<2>& axis);
        
        OPENSOLID_CORE_EXPORT static Function
        Linear(const Frame<2>& frame);
        
        OPENSOLID_CORE_EXPORT static Function
        Linear(const Axis<3>& axis);
        
        OPENSOLID_CORE_EXPORT static Function
        Linear(const Plane3d& plane);
        
        OPENSOLID_CORE_EXPORT static Function
        Linear(const Frame<3>& frame);
        
        OPENSOLID_CORE_EXPORT static Function
        Elliptical(const Frame<2>& frame);
        
        OPENSOLID_CORE_EXPORT static Function
        Elliptical(const Plane3d& plane);
        
        OPENSOLID_CORE_EXPORT static Function
        Elliptical(const Frame<3>& frame);
    };
}
