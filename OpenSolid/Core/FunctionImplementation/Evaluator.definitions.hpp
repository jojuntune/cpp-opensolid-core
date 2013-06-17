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

#include <OpenSolid/Core/FunctionImplementation/Evaluator.declarations.hpp>

#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/FunctionImplementation.declarations.hpp>

#include <unordered_map>
#include <utility>

namespace opensolid
{
    class Evaluator
    {
    private:
        typedef std::pair<const FunctionImplementation*, const double*> KeyXd;
        typedef std::pair<const FunctionImplementation*, const Interval*> KeyXI;

        std::unordered_map<KeyXd, MatrixXd> _cachedValues;
        std::unordered_map<KeyXI, MatrixXI> _cachedBounds;
    public:
        OPENSOLID_CORE_EXPORT
        MapXcd
        evaluate(
            const FunctionImplementationPtr& functionImplementation,
            const MapXcd& parameterValues
        );

        OPENSOLID_CORE_EXPORT
        MapXcI
        evaluate(
            const FunctionImplementationPtr& functionImplementation,
            const MapXcI& parameterBounds
        );
    };
}
