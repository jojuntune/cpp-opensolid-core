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

#include <OpenSolid/Core/Variant/VariantValue.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Component.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Variant.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    VariantValue::~VariantValue() {
    }

    std::int64_t
    VariantValue::toInt() const {
        throw PlaceholderError();
    }

    double
    VariantValue::toDouble() const {
        throw PlaceholderError();
    }

    const std::string&
    VariantValue::toString() const {
        throw PlaceholderError();
    }

    Interval
    VariantValue::toInterval() const {
        throw PlaceholderError();
    }

    const Matrix2d&
    VariantValue::toMatrix2d() const {
        throw PlaceholderError();
    }

    const IntervalMatrix2d&
    VariantValue::toIntervalMatrix2d() const {
        throw PlaceholderError();
    }

    const Matrix3d&
    VariantValue::toMatrix3d() const {
        throw PlaceholderError();
    }

    const IntervalMatrix3d&
    VariantValue::toIntervalMatrix3d() const {
        throw PlaceholderError();
    }

    const RowMatrix2d&
    VariantValue::toRowMatrix2d() const {
        throw PlaceholderError();
    }

    const IntervalRowMatrix2d&
    VariantValue::toIntervalRowMatrix2d() const {
        throw PlaceholderError();
    }

    const ColumnMatrix2d&
    VariantValue::toColumnMatrix2d() const {
        throw PlaceholderError();
    }

    const IntervalColumnMatrix2d&
    VariantValue::toIntervalColumnMatrix2d() const {
        throw PlaceholderError();
    }

    const RowMatrix3d&
    VariantValue::toRowMatrix3d() const {
        throw PlaceholderError();
    }

    const IntervalRowMatrix3d&
    VariantValue::toIntervalRowMatrix3d() const {
        throw PlaceholderError();
    }

    const ColumnMatrix3d&
    VariantValue::toColumnMatrix3d() const {
        throw PlaceholderError();
    }

    const IntervalColumnMatrix3d&
    VariantValue::toIntervalColumnMatrix3d() const {
        throw PlaceholderError();
    }

    const Vector2d&
    VariantValue::toVector2d() const {
        throw PlaceholderError();
    }

    const Vector3d&
    VariantValue::toVector3d() const {
        throw PlaceholderError();
    }

    const IntervalVector2d&
    VariantValue::toIntervalVector2d() const {
        throw PlaceholderError();
    }

    const IntervalVector3d&
    VariantValue::toIntervalVector3d() const {
        throw PlaceholderError();
    }

    const Point2d&
    VariantValue::toPoint2d() const {
        throw PlaceholderError();
    }

    const Point3d&
    VariantValue::toPoint3d() const {
        throw PlaceholderError();
    }

    const Box2d&
    VariantValue::toBox2d() const {
        throw PlaceholderError();
    }

    const Box3d&
    VariantValue::toBox3d() const {
        throw PlaceholderError();
    }

    const Axis2d&
    VariantValue::toAxis2d() const {
        throw PlaceholderError();
    }

    const Axis3d&
    VariantValue::toAxis3d() const {
        throw PlaceholderError();
    }

    const Plane3d&
    VariantValue::toPlane3d() const {
        throw PlaceholderError();
    }

    const LineSegment2d&
    VariantValue::toLineSegment2d() const {
        throw PlaceholderError();
    }

    const LineSegment3d&
    VariantValue::toLineSegment3d() const {
        throw PlaceholderError();
    }

    const Triangle2d&
    VariantValue::toTriangle2d() const {
        throw PlaceholderError();
    }

    const Triangle3d&
    VariantValue::toTriangle3d() const {
        throw PlaceholderError();
    }

    const Tetrahedron3d&
    VariantValue::toTetrahedron3d() const {
        throw PlaceholderError();
    }

    const Component&
    VariantValue::toComponent() const {
        throw PlaceholderError();
    }
}
