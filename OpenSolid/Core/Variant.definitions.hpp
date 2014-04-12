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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Variant.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Component.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Tetrahedron.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/Variant/VariantValue.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace opensolid
{
    class Variant
    {
    private:
        VariantValuePtr _valuePtr;
    public:
        enum Type
        {
            NONE,
            INT,
            DOUBLE,
            STRING,
            INTERVAL,
            MATRIX2D,
            INTERVALMATRIX2D,
            MATRIX3D,
            INTERVALMATRIX3D,
            ROWMATRIX2D,
            INTERVALROWMATRIX2D,
            COLUMNMATRIX2D,
            INTERVALCOLUMNMATRIX2D,
            ROWMATRIX3D,
            INTERVALROWMATRIX3D,
            COLUMNMATRIX3D,
            INTERVALCOLUMNMATRIX3D,
            VECTOR2D,
            VECTOR3D,
            INTERVALVECTOR2D,
            INTERVALVECTOR3D,
            POINT2D,
            POINT3D,
            BOX2D,
            BOX3D,
            AXIS2D,
            AXIS3D,
            PLANE3D,
            AXIALCOORDINATESYSTEM2D,
            AXIALCOORDINATESYSTEM3D,
            PLANARCOORDINATESYSTEM3D,
            COORDINATESYSTEM2D,
            COORDINATESYSTEM3D,
            LINESEGMENT2D,
            LINESEGMENT3D,
            TRIANGLE2D,
            TRIANGLE3D,
            TETRAHEDRON3D,
            COMPONENT,
            NUM_TYPES
        };

        OPENSOLID_CORE_EXPORT
        Variant();

        OPENSOLID_CORE_EXPORT
        Variant(VariantValue* valuePtr);

        OPENSOLID_CORE_EXPORT
        Variant(VariantValuePtr valuePtr);

        OPENSOLID_CORE_EXPORT
        Variant(std::int64_t value);

        OPENSOLID_CORE_EXPORT
        Variant(double value);

        OPENSOLID_CORE_EXPORT
        Variant(std::string value);

        OPENSOLID_CORE_EXPORT
        Variant(Interval value);

        OPENSOLID_CORE_EXPORT
        Variant(Component component);

        OPENSOLID_CORE_EXPORT
        Type
        type() const;

        OPENSOLID_CORE_EXPORT
        std::int64_t
        toInt() const;

        OPENSOLID_CORE_EXPORT
        double
        toDouble() const;

        OPENSOLID_CORE_EXPORT
        const std::string&
        toString() const;

        OPENSOLID_CORE_EXPORT
        Interval
        toInterval() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<double, 2, 2>&
        toMatrix2x2() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<Interval, 2, 2>&
        toIntervalMatrix2x2() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<double, 3, 3>&
        toMatrix3x3() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<Interval, 3, 3>&
        toIntervalMatrix3x3() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<double, 1, 2>&
        toRowMatrix1x2() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<Interval, 1, 2>&
        toIntervalRowMatrix1x2() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<double, 2, 1>&
        toColMatrix2x1() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<Interval, 2, 1>&
        toIntervalColMatrix2x1() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<double, 1, 3>&
        toRowMatrix1x3() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<Interval, 1, 3>&
        toIntervalRowMatrix1x3() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<double, 3, 1>&
        toColMatrix3x1() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<Interval, 3, 1>&
        toIntervalColMatrix3x1() const;

        OPENSOLID_CORE_EXPORT
        const Vector<double, 2>&
        toVector2d() const;

        OPENSOLID_CORE_EXPORT
        const Vector<double, 3>&
        toVector3d() const;

        OPENSOLID_CORE_EXPORT
        const Vector<Interval, 2>&
        toIntervalVector2d() const;

        OPENSOLID_CORE_EXPORT
        const Vector<Interval, 3>&
        toIntervalVector3d() const;

        OPENSOLID_CORE_EXPORT
        const Point<2>&
        toPoint2d() const;

        OPENSOLID_CORE_EXPORT
        const Point<3>&
        toPoint3d() const;

        OPENSOLID_CORE_EXPORT
        const Box<2>&
        toBox2d() const;

        OPENSOLID_CORE_EXPORT
        const Box<3>&
        toBox3d() const;

        OPENSOLID_CORE_EXPORT
        const Axis<2>&
        toAxis2d() const;

        OPENSOLID_CORE_EXPORT
        const Axis<3>&
        toAxis3d() const;

        OPENSOLID_CORE_EXPORT
        const Plane3d&
        toPlane3d() const;

        OPENSOLID_CORE_EXPORT
        const CoordinateSystem<2, 1>&
        toAxialCoordinateSystem2d() const;

        OPENSOLID_CORE_EXPORT
        const CoordinateSystem<3, 1>&
        toAxialCoordinateSystem3d() const;

        OPENSOLID_CORE_EXPORT
        const CoordinateSystem<3, 2>&
        toPlanarCoordinateSystem3d() const;

        OPENSOLID_CORE_EXPORT
        const CoordinateSystem<2, 2>&
        toCoordinateSystem2d() const;

        OPENSOLID_CORE_EXPORT
        const CoordinateSystem<3, 3>&
        toCoordinateSystem3d() const;

        OPENSOLID_CORE_EXPORT
        const LineSegment<2>&
        toLineSegment2d() const;

        OPENSOLID_CORE_EXPORT
        const LineSegment<3>&
        toLineSegment3d() const;

        OPENSOLID_CORE_EXPORT
        const Triangle<2>&
        toTriangle2d() const;

        OPENSOLID_CORE_EXPORT
        const Triangle<3>&
        toTriangle3d() const;

        OPENSOLID_CORE_EXPORT
        const Tetrahedron3d&
        toTetrahedron3d() const;

        OPENSOLID_CORE_EXPORT
        const Component&
        toComponent() const;
    };
}
