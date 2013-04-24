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

#include <OpenSolid/Core/Rotation.declarations.hpp>

#include <OpenSolid/Core/Datum.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>

namespace opensolid
{
    template <>
    class Rotation<2>
    {
    private:
        Point2d _originPoint;
        Matrix2d _transformationMatrix;
    public:
        OPENSOLID_CORE_EXPORT
        Rotation(double angle, const Point2d& originPoint);

        const Point2d&
        originPoint() const;
        
        const Matrix2d&
        transformationMatrix() const;

        template <class TTransformable>
        TTransformable
        operator()(const TTransformable& transformable) const;
    };

    typedef Rotation<2> Rotation2d;

    template <>
    class Rotation<3>
    {
    private:
        Point3d _originPoint;
        Matrix3d _transformationMatrix;
    public:
        OPENSOLID_CORE_EXPORT
        Rotation(double angle, const Datum<3, 1>& axis);

        const Point3d&
        originPoint() const;
        
        const Matrix3d&
        transformationMatrix() const;

        template <class TTransformable>
        TTransformable
        operator()(const TTransformable& transformable) const;
    };

    typedef Rotation<3> Rotation3d;
}
