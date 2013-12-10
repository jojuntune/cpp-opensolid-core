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

#include <OpenSolid/Core/Variant/VariantValue.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Component.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/ReferenceCounted.hpp>
#include <OpenSolid/Core/Tetrahedron.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/Variant.declarations.hpp>

#include <string>

namespace opensolid
{
    class VariantValue :
        public ReferenceCounted
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
        virtual const Vector2d&
        toVector2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector3d&
        toVector3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const VectorXd&
        toVectorXd() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector2I&
        toVector2I() const;

        OPENSOLID_CORE_EXPORT
        virtual const Vector3I&
        toVector3I() const;

        OPENSOLID_CORE_EXPORT
        virtual const VectorXI&
        toVectorXI() const;

        OPENSOLID_CORE_EXPORT
        virtual const RowVector2d&
        toRowVector2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const RowVector3d&
        toRowVector3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const RowVectorXd&
        toRowVectorXd() const;

        OPENSOLID_CORE_EXPORT
        virtual const RowVector2I&
        toRowVector2I() const;

        OPENSOLID_CORE_EXPORT
        virtual const RowVector3I&
        toRowVector3I() const;

        OPENSOLID_CORE_EXPORT
        virtual const RowVectorXI&
        toRowVectorXI() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix2d&
        toMatrix2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix3d&
        toMatrix3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix2Xd&
        toMatrix2Xd() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix3Xd&
        toMatrix3Xd() const;

        OPENSOLID_CORE_EXPORT
        virtual const MatrixXd&
        toMatrixXd() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix2I&
        toMatrix2I() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix3I&
        toMatrix3I() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix2XI&
        toMatrix2XI() const;

        OPENSOLID_CORE_EXPORT
        virtual const Matrix3XI&
        toMatrix3XI() const;

        OPENSOLID_CORE_EXPORT
        virtual const MatrixXI&
        toMatrixXI() const;

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
        virtual const CoordinateSystem<2, 1>&
        toAxialCoordinateSystem2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const CoordinateSystem<3, 1>&
        toAxialCoordinateSystem3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const CoordinateSystem<3, 2>&
        toPlanarCoordinateSystem3d() const;

        OPENSOLID_CORE_EXPORT
        virtual const CoordinateSystem<2, 2>&
        toCoordinateSystem2d() const;

        OPENSOLID_CORE_EXPORT
        virtual const CoordinateSystem<3, 3>&
        toCoordinateSystem3d() const;

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
