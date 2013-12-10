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

#include <OpenSolid/Core/Variant/VariantValue.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Interval.hpp>

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

    const Vector2d&
    VariantValue::toVector2d() const {
        throw PlaceholderError();
    }

    const Vector3d&
    VariantValue::toVector3d() const {
        throw PlaceholderError();
    }

    const VectorXd&
    VariantValue::toVectorXd() const {
        throw PlaceholderError();
    }

    const Vector2I&
    VariantValue::toVector2I() const {
        throw PlaceholderError();
    }

    const Vector3I&
    VariantValue::toVector3I() const {
        throw PlaceholderError();
    }

    const VectorXI&
    VariantValue::toVectorXI() const {
        throw PlaceholderError();
    }

    const RowVector2d&
    VariantValue::toRowVector2d() const {
        throw PlaceholderError();
    }

    const RowVector3d&
    VariantValue::toRowVector3d() const {
        throw PlaceholderError();
    }

    const RowVectorXd&
    VariantValue::toRowVectorXd() const {
        throw PlaceholderError();
    }

    const RowVector2I&
    VariantValue::toRowVector2I() const {
        throw PlaceholderError();
    }

    const RowVector3I&
    VariantValue::toRowVector3I() const {
        throw PlaceholderError();
    }

    const RowVectorXI&
    VariantValue::toRowVectorXI() const {
        throw PlaceholderError();
    }

    const Matrix2d&
    VariantValue::toMatrix2d() const {
        throw PlaceholderError();
    }

    const Matrix3d&
    VariantValue::toMatrix3d() const {
        throw PlaceholderError();
    }

    const Matrix2Xd&
    VariantValue::toMatrix2Xd() const {
        throw PlaceholderError();
    }

    const Matrix3Xd&
    VariantValue::toMatrix3Xd() const {
        throw PlaceholderError();
    }

    const MatrixXd&
    VariantValue::toMatrixXd() const {
        throw PlaceholderError();
    }

    const Matrix2I&
    VariantValue::toMatrix2I() const {
        throw PlaceholderError();
    }

    const Matrix3I&
    VariantValue::toMatrix3I() const {
        throw PlaceholderError();
    }

    const Matrix2XI&
    VariantValue::toMatrix2XI() const {
        throw PlaceholderError();
    }

    const Matrix3XI&
    VariantValue::toMatrix3XI() const {
        throw PlaceholderError();
    }

    const MatrixXI&
    VariantValue::toMatrixXI() const {
        throw PlaceholderError();
    }

    const Point<2>&
    VariantValue::toPoint2d() const {
        throw PlaceholderError();
    }

    const Point<3>&
    VariantValue::toPoint3d() const {
        throw PlaceholderError();
    }

    const Box<2>&
    VariantValue::toBox2d() const {
        throw PlaceholderError();
    }

    const Box<3>&
    VariantValue::toBox3d() const {
        throw PlaceholderError();
    }

    const Axis<2>&
    VariantValue::toAxis2d() const {
        throw PlaceholderError();
    }

    const Axis<3>&
    VariantValue::toAxis3d() const {
        throw PlaceholderError();
    }

    const Plane3d&
    VariantValue::toPlane3d() const {
        throw PlaceholderError();
    }

    const CoordinateSystem<2, 1>&
    VariantValue::toAxialCoordinateSystem2d() const {
        throw PlaceholderError();
    }

    const CoordinateSystem<3, 1>&
    VariantValue::toAxialCoordinateSystem3d() const {
        throw PlaceholderError();
    }

    const CoordinateSystem<3, 2>&
    VariantValue::toPlanarCoordinateSystem3d() const {
        throw PlaceholderError();
    }

    const CoordinateSystem<2, 2>&
    VariantValue::toCoordinateSystem2d() const {
        throw PlaceholderError();
    }

    const CoordinateSystem<3, 3>&
    VariantValue::toCoordinateSystem3d() const {
        throw PlaceholderError();
    }

    const LineSegment<2>&
    VariantValue::toLineSegment2d() const {
        throw PlaceholderError();
    }

    const LineSegment<3>&
    VariantValue::toLineSegment3d() const {
        throw PlaceholderError();
    }

    const Triangle<2>&
    VariantValue::toTriangle2d() const {
        throw PlaceholderError();
    }

    const Triangle<3>&
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
