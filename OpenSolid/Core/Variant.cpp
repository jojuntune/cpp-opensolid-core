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

    const Vector2d&
    Variant::toVector2d() const {
        return _valuePtr->toVector2d();
    }

    const Vector3d&
    Variant::toVector3d() const {
        return _valuePtr->toVector3d();
    }

    const VectorXd&
    Variant::toVectorXd() const {
        return _valuePtr->toVectorXd();
    }

    const Vector2I&
    Variant::toVector2I() const {
        return _valuePtr->toVector2I();
    }

    const Vector3I&
    Variant::toVector3I() const {
        return _valuePtr->toVector3I();
    }

    const VectorXI&
    Variant::toVectorXI() const {
        return _valuePtr->toVectorXI();
    }

    const RowVector2d&
    Variant::toRowVector2d() const {
        return _valuePtr->toRowVector2d();
    }

    const RowVector3d&
    Variant::toRowVector3d() const {
        return _valuePtr->toRowVector3d();
    }

    const RowVectorXd&
    Variant::toRowVectorXd() const {
        return _valuePtr->toRowVectorXd();
    }

    const RowVector2I&
    Variant::toRowVector2I() const {
        return _valuePtr->toRowVector2I();
    }

    const RowVector3I&
    Variant::toRowVector3I() const {
        return _valuePtr->toRowVector3I();
    }

    const RowVectorXI&
    Variant::toRowVectorXI() const {
        return _valuePtr->toRowVectorXI();
    }

    const Matrix2d&
    Variant::toMatrix2d() const {
        return _valuePtr->toMatrix2d();
    }

    const Matrix3d&
    Variant::toMatrix3d() const {
        return _valuePtr->toMatrix3d();
    }

    const Matrix2Xd&
    Variant::toMatrix2Xd() const {
        return _valuePtr->toMatrix2Xd();
    }

    const Matrix3Xd&
    Variant::toMatrix3Xd() const {
        return _valuePtr->toMatrix3Xd();
    }

    const MatrixXd&
    Variant::toMatrixXd() const {
        return _valuePtr->toMatrixXd();
    }

    const Matrix2I&
    Variant::toMatrix2I() const {
        return _valuePtr->toMatrix2I();
    }

    const Matrix3I&
    Variant::toMatrix3I() const {
        return _valuePtr->toMatrix3I();
    }

    const Matrix2XI&
    Variant::toMatrix2XI() const {
        return _valuePtr->toMatrix2XI();
    }

    const Matrix3XI&
    Variant::toMatrix3XI() const {
        return _valuePtr->toMatrix3XI();
    }

    const MatrixXI&
    Variant::toMatrixXI() const {
        return _valuePtr->toMatrixXI();
    }

    const Point<2>&
    Variant::toPoint2d() const {
        return _valuePtr->toPoint2d();
    }

    const Point<3>&
    Variant::toPoint3d() const {
        return _valuePtr->toPoint3d();
    }

    const Box<2>&
    Variant::toBox2d() const {
        return _valuePtr->toBox2d();
    }

    const Box<3>&
    Variant::toBox3d() const {
        return _valuePtr->toBox3d();
    }

    const Axis<2>&
    Variant::toAxis2d() const {
        return _valuePtr->toAxis2d();
    }

    const Axis<3>&
    Variant::toAxis3d() const {
        return _valuePtr->toAxis3d();
    }

    const Plane3d&
    Variant::toPlane3d() const {
        return _valuePtr->toPlane3d();
    }

    const CoordinateSystem<2, 1>&
    Variant::toAxialCoordinateSystem2d() const {
        return _valuePtr->toAxialCoordinateSystem2d();
    }

    const CoordinateSystem<3, 1>&
    Variant::toAxialCoordinateSystem3d() const {
        return _valuePtr->toAxialCoordinateSystem3d();
    }

    const CoordinateSystem<3, 2>&
    Variant::toPlanarCoordinateSystem3d() const {
        return _valuePtr->toPlanarCoordinateSystem3d();
    }

    const CoordinateSystem<2, 2>&
    Variant::toCoordinateSystem2d() const {
        return _valuePtr->toCoordinateSystem2d();
    }

    const CoordinateSystem<3, 3>&
    Variant::toCoordinateSystem3d() const {
        return _valuePtr->toCoordinateSystem3d();
    }

    const LineSegment<2>&
    Variant::toLineSegment2d() const {
        return _valuePtr->toLineSegment2d();
    }

    const LineSegment<3>&
    Variant::toLineSegment3d() const {
        return _valuePtr->toLineSegment3d();
    }

    const Triangle<2>&
    Variant::toTriangle2d() const {
        return _valuePtr->toTriangle2d();
    }

    const Triangle<3>&
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
