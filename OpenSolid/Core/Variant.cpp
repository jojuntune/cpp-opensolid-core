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
************************************************************************************/

#include <OpenSolid/Core/Variant.hpp>

#include <OpenSolid/Core/Component.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Vector.hpp>
#include <OpenSolid/Core/Variant/ComponentValue.hpp>
#include <OpenSolid/Core/Variant/DoubleValue.hpp>
#include <OpenSolid/Core/Variant/IntValue.hpp>
#include <OpenSolid/Core/Variant/IntervalValue.hpp>
#include <OpenSolid/Core/Variant/StringValue.hpp>
#include <OpenSolid/Core/Variant/VariantValue.hpp>

namespace opensolid
{
    Variant::Variant() {
    }

    Variant::Variant(VariantValue* valuePtr) :
        _valuePtr(valuePtr) {
    }

    Variant::Variant(VariantValuePtr valuePtr) :
        _valuePtr(valuePtr) {
    }

    Variant::Variant(std::int64_t value) :
        _valuePtr(new IntValue(value)) {
    }

    Variant::Variant(double value) :
        _valuePtr(new DoubleValue(value)) {
    }

    Variant::Variant(std::string value) :
        _valuePtr(new StringValue(std::move(value))) {
    }

    Variant::Variant(Interval value) :
        _valuePtr(new IntervalValue(value)) {
    }

    Variant::Variant(Component value) :
        _valuePtr(new ComponentValue(std::move(value))) {
    }

    Variant::Type
    Variant::type() const {
        return Type(_valuePtr->type());
    }

    std::int64_t
    Variant::toInt() const {
        return _valuePtr->toInt();
    }

    double
    Variant::toDouble() const {
        return _valuePtr->toDouble();
    }

    const std::string&
    Variant::toString() const {
        return _valuePtr->toString();
    }

    Interval
    Variant::toInterval() const {
        return _valuePtr->toInterval();
    }

    const Matrix2x2&
    Variant::toMatrix2x2() const {
        return _valuePtr->toMatrix2x2();
    }

    const IntervalMatrix2x2&
    Variant::toIntervalMatrix2x2() const {
        return _valuePtr->toIntervalMatrix2x2();
    }

    const Matrix3x3&
    Variant::toMatrix3x3() const {
        return _valuePtr->toMatrix3x3();
    }

    const IntervalMatrix3x3&
    Variant::toIntervalMatrix3x3() const {
        return _valuePtr->toIntervalMatrix3x3();
    }

    const RowMatrix1x2&
    Variant::toRowMatrix1x2() const {
        return _valuePtr->toRowMatrix1x2();
    }

    const IntervalRowMatrix1x2&
    Variant::toIntervalRowMatrix1x2() const {
        return _valuePtr->toIntervalRowMatrix1x2();
    }

    const ColMatrix2x1&
    Variant::toColMatrix2x1() const {
        return _valuePtr->toColMatrix2x1();
    }

    const IntervalColMatrix2x1&
    Variant::toIntervalColMatrix2x1() const {
        return _valuePtr->toIntervalColMatrix2x1();
    }

    const RowMatrix1x3&
    Variant::toRowMatrix1x3() const {
        return _valuePtr->toRowMatrix1x3();
    }

    const IntervalRowMatrix1x3&
    Variant::toIntervalRowMatrix1x3() const {
        return _valuePtr->toIntervalRowMatrix1x3();
    }

    const ColMatrix3x1&
    Variant::toColMatrix3x1() const {
        return _valuePtr->toColMatrix3x1();
    }

    const IntervalColMatrix3x1&
    Variant::toIntervalColMatrix3x1() const {
        return _valuePtr->toIntervalColMatrix3x1();
    }

    const Vector2d&
    Variant::toVector2d() const {
        return _valuePtr->toVector2d();
    }

    const Vector3d&
    Variant::toVector3d() const {
        return _valuePtr->toVector3d();
    }

    const IntervalVector2d&
    Variant::toIntervalVector2d() const {
        return _valuePtr->toIntervalVector2d();
    }

    const IntervalVector3d&
    Variant::toIntervalVector3d() const {
        return _valuePtr->toIntervalVector3d();
    }

    const Point2d&
    Variant::toPoint2d() const {
        return _valuePtr->toPoint2d();
    }

    const Point3d&
    Variant::toPoint3d() const {
        return _valuePtr->toPoint3d();
    }

    const Box2d&
    Variant::toBox2d() const {
        return _valuePtr->toBox2d();
    }

    const Box3d&
    Variant::toBox3d() const {
        return _valuePtr->toBox3d();
    }

    const Axis2d&
    Variant::toAxis2d() const {
        return _valuePtr->toAxis2d();
    }

    const Axis3d&
    Variant::toAxis3d() const {
        return _valuePtr->toAxis3d();
    }

    const Plane3d&
    Variant::toPlane3d() const {
        return _valuePtr->toPlane3d();
    }

    const AxialCoordinateSystem2d&
    Variant::toAxialCoordinateSystem2d() const {
        return _valuePtr->toAxialCoordinateSystem2d();
    }

    const AxialCoordinateSystem3d&
    Variant::toAxialCoordinateSystem3d() const {
        return _valuePtr->toAxialCoordinateSystem3d();
    }

    const PlanarCoordinateSystem3d&
    Variant::toPlanarCoordinateSystem3d() const {
        return _valuePtr->toPlanarCoordinateSystem3d();
    }

    const CoordinateSystem2d&
    Variant::toCoordinateSystem2d() const {
        return _valuePtr->toCoordinateSystem2d();
    }

    const CoordinateSystem3d&
    Variant::toCoordinateSystem3d() const {
        return _valuePtr->toCoordinateSystem3d();
    }

    const LineSegment2d&
    Variant::toLineSegment2d() const {
        return _valuePtr->toLineSegment2d();
    }

    const LineSegment3d&
    Variant::toLineSegment3d() const {
        return _valuePtr->toLineSegment3d();
    }

    const Triangle2d&
    Variant::toTriangle2d() const {
        return _valuePtr->toTriangle2d();
    }

    const Triangle3d&
    Variant::toTriangle3d() const {
        return _valuePtr->toTriangle3d();
    }

    const Tetrahedron3d&
    Variant::toTetrahedron3d() const {
        return _valuePtr->toTetrahedron3d();
    }

    const Component&
    Variant::toComponent() const {
        return _valuePtr->toComponent();
    }
}
