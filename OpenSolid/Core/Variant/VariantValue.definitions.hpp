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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Variant/VariantValue.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Component.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Tetrahedron.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/Variant.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

#include <string>
#include <cstdint>

namespace opensolid
{
    class VariantValue
    {
    public:
        OPENSOLID_CORE_EXPORT
        virtual
        ~VariantValue();

        OPENSOLID_CORE_EXPORT
        virtual int
        type() const = 0;

        OPENSOLID_CORE_EXPORT
        virtual std::int64_t
        toInt() const;

        OPENSOLID_CORE_EXPORT
        virtual double
        toDouble() const;

        OPENSOLID_CORE_EXPORT
        virtual const std::string&
        toString() const;

        OPENSOLID_CORE_EXPORT
        virtual Interval
        toInterval() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<double, 2, 2>&
        toMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<Interval, 2, 2>&
        toIntervalMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<double, 3, 3>&
        toMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<Interval, 3, 3>&
        toIntervalMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<double, 1, 2>&
        toRowMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<Interval, 1, 2>&
        toIntervalRowMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<double, 2, 1>&
        toColumnMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<Interval, 2, 1>&
        toIntervalColumnMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<double, 1, 3>&
        toRowMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<Interval, 1, 3>&
        toIntervalRowMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<double, 3, 1>&
        toColumnMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix<Interval, 3, 1>&
        toIntervalColumnMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector<double, 2>&
        toVector2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector<double, 3>&
        toVector3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector<Interval, 2>&
        toIntervalVector2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector<Interval, 3>&
        toIntervalVector3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Point<2>&
        toPoint2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Point<3>&
        toPoint3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Box<2>&
        toBox2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Box<3>&
        toBox3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Axis<2>&
        toAxis2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Axis<3>&
        toAxis3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Plane3d&
        toPlane3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const LineSegment<2>&
        toLineSegment2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const LineSegment<3>&
        toLineSegment3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Triangle<2>&
        toTriangle2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Triangle<3>&
        toTriangle3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Tetrahedron3d&
        toTetrahedron3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Component&
        toComponent() const;
    };
}
