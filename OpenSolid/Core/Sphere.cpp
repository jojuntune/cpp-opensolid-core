/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Sphere.hpp>

#include <cmath>

namespace opensolid
{
    namespace
    {
        inline
        double
        cubeRoot(double value) {
            if (value == Zero()) {
                return 0.0;
            } else if (value - 1.0 == Zero()) {
                return 1.0;
            } else if (value + 1.0 == Zero()) {
                return -1.0;
            } else {
                #ifdef _MSC_VER
                    #if (_MSC_VER >= 1800)
                        // std::cbrt() first implemented in Visual Studio 2013
                        return std::cbrt(value);
                    #else
                        // Fallback for previous versions of Visual Studio
                        return std::pow(value, 1.0 / 3.0);
                    #endif
                #else
                    return std::cbrt(value);
                #endif
            }
        }
    }

    Sphere3d
    TransformationFunction<Sphere3d, 3>::operator()(
        const Sphere3d& sphere,
        const Matrix3d& matrix
    ) const {
        double scale = abs(cubeRoot(matrix.determinant()));
        return Sphere3d(
            transformationFunction(sphere.centerPoint(), matrix),
            scale * sphere.radius()
        );
    }

    Sphere3d
    MorphingFunction<Sphere3d, 3>::operator()(
        const Sphere3d& sphere,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        double scale = abs(
            cubeRoot(morphingExpression.jacobian(sphere.centerPoint().components()).determinant())
        );
        return Sphere3d(
            morphingFunction(sphere.centerPoint(), morphingExpression),
            scale * sphere.radius()
        );
    }
}
