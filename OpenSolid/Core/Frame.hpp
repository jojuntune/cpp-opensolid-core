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

#include <OpenSolid/Core/Frame.definitions.hpp>

#include <OpenSolid/Core/Axis.definitions.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/FrameBase.hpp>
#include <OpenSolid/Core/Handedness.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Quaternion.definitions.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    inline
    Frame2d::Frame() :
        FrameBase<2, 2>(Point2d::ORIGIN(), Matrix2d::IDENTITY()),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Frame2d::Frame(const Point2d& originPoint) :
        FrameBase<2, 2>(originPoint, Matrix2d::IDENTITY()),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Frame2d::Frame(const Point2d& originPoint, const Matrix2d& basisMatrix) :
        FrameBase<2, 2>(originPoint, basisMatrix),
        _handedness(Handedness(Sign::of(basisMatrix.determinant()))) {
    }

    inline
    Frame2d::Frame(const Point2d& originPoint, const Quaternion2d& orientation) :
        FrameBase<2, 2>(originPoint, orientation.rotationMatrix()),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Frame2d::Frame(
        const Point2d& originPoint,
        const UnitVector2d& xDirectionVector,
        const UnitVector2d& yDirectionVector
    ) : FrameBase<2, 2>(
            originPoint,
            Matrix2d::fromColumns(xDirectionVector.components(), yDirectionVector.components())
        ),
        _handedness(
            Handedness(Sign::of(xDirectionVector.unitOrthogonal().dot(yDirectionVector)))
        ) {
    }

    inline
    Frame2d::Frame(
        const Point2d& originPoint,
        const UnitVector2d& xDirectionVector,
        const UnitVector2d& yDirectionVector,
        Handedness handedness
    ) : FrameBase<2, 2>(
            originPoint,
            Matrix2d::fromColumns(xDirectionVector.components(), yDirectionVector.components())
        ),
        _handedness(handedness) {
        assert(
            handedness ==
            Handedness(Sign::of(xDirectionVector.unitOrthogonal().dot(yDirectionVector)))
        );
    }

    inline
    Handedness
    Frame2d::handedness() const {
        return _handedness;
    }

    inline
    UnitVector2d
    Frame2d::xDirectionVector() const {
        return UnitVector2d(basisMatrix().column(0));
    }
    
    inline
    UnitVector2d
    Frame2d::yDirectionVector() const {
        return UnitVector2d(basisMatrix().column(1));
    }
    
    inline
    Axis2d
    Frame2d::xAxis() const {
        return Axis2d(originPoint(), xDirectionVector(), handedness());
    }
    
    inline
    Axis2d
    Frame2d::yAxis() const {
        return Axis2d(originPoint(), yDirectionVector(), handedness());
    }

    template <class TTransformation>
    inline
    Frame2d
    Frame2d::transformedBy(const TTransformation& transformation) const {
        return Frame2d(
            originPoint().transformedBy(transformation),
            xDirectionVector().transformedBy(transformation),
            yDirectionVector().transformedBy(transformation),
            handedness().transformedBy(transformation)
        );
    }

    inline
    Plane3d
    Frame2d::placedOnto(const Plane3d& plane) const {
        return Plane3d(
            originPoint().placedOnto(plane),
            xDirectionVector().placedOnto(plane),
            yDirectionVector().placedOnto(plane),
            handedness()
        );
    }

    inline
    Frame2d
    Frame2d::XY() {
        return Frame2d(Point2d::ORIGIN(), UnitVector2d::X(), UnitVector2d::Y());
    }

    inline
    Frame3d::Frame() :
        FrameBase<3, 3>(Point3d::ORIGIN(), Matrix3d::IDENTITY()),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Frame3d::Frame(const Point3d& originPoint) :
        FrameBase<3, 3>(originPoint, Matrix3d::IDENTITY()),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Frame3d::Frame(const Point3d& originPoint, const Matrix3d& basisMatrix) :
        FrameBase<3, 3>(originPoint, basisMatrix),
        _handedness(Handedness(Sign::of(basisMatrix.determinant()))) {
    }

    inline
    Frame3d::Frame(const Point3d& originPoint, const Quaternion3d& orientation) :
        FrameBase<3, 3>(originPoint, orientation.rotationMatrix()),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Frame3d::Frame(
        const Point3d& originPoint,
        const UnitVector3d& xDirectionVector,
        const UnitVector3d& yDirectionVector,
        const UnitVector3d& zDirectionVector
    ) : FrameBase<3, 3>(
            originPoint,
            Matrix3d::fromColumns(
                xDirectionVector.components(),
                yDirectionVector.components(),
                zDirectionVector.components()
            )
        ),
        _handedness(
            Handedness(Sign::of(xDirectionVector.cross(yDirectionVector).dot(zDirectionVector)))
        ) {
    }

    inline
    Frame3d::Frame(
        const Point3d& originPoint,
        const UnitVector3d& xDirectionVector,
        const UnitVector3d& yDirectionVector,
        const UnitVector3d& zDirectionVector,
        Handedness handedness
    ) : FrameBase<3, 3>(
            originPoint,
            Matrix3d::fromColumns(
                xDirectionVector.components(),
                yDirectionVector.components(),
                zDirectionVector.components()
            )
        ),
        _handedness(handedness) {

        assert(
            handedness ==
            Handedness(Sign::of(xDirectionVector.cross(yDirectionVector).dot(zDirectionVector)))
        );
    }

    inline
    Handedness
    Frame3d::handedness() const {
        return _handedness;
    }

    inline
    UnitVector3d
    Frame3d::xDirectionVector() const {
        return UnitVector3d(basisMatrix().column(0));
    }
    
    inline
    UnitVector3d
    Frame3d::yDirectionVector() const {
        return UnitVector3d(basisMatrix().column(1));
    }
    
    inline
    UnitVector3d
    Frame3d::zDirectionVector() const {
        return UnitVector3d(basisMatrix().column(2));
    }
    
    inline
    Axis3d
    Frame3d::xAxis() const {
        return Axis3d(originPoint(), xDirectionVector());
    }
    
    inline
    Axis3d
    Frame3d::yAxis() const {
        return Axis3d(originPoint(), yDirectionVector());
    }
    
    inline
    Axis3d
    Frame3d::zAxis() const {
        return Axis3d(originPoint(), zDirectionVector());
    }

    inline
    Plane3d
    Frame3d::xyPlane() const {
        return Plane3d(
            originPoint(),
            xDirectionVector(),
            yDirectionVector(),
            zDirectionVector(),
            handedness()
        );
    }
    
    inline
    Plane3d
    Frame3d::xzPlane() const {
        return Plane3d(
            originPoint(),
            xDirectionVector(),
            zDirectionVector(),
            -yDirectionVector(),
            handedness()
        );
    }
    
    inline
    Plane3d
    Frame3d::yxPlane() const {
        return Plane3d(
            originPoint(),
            yDirectionVector(),
            xDirectionVector(),
            -zDirectionVector(),
            handedness()
        );
    }
    
    inline
    Plane3d
    Frame3d::yzPlane() const {
        return Plane3d(
            originPoint(),
            yDirectionVector(),
            zDirectionVector(),
            xDirectionVector(),
            handedness()
        );
    }
    
    inline
    Plane3d
    Frame3d::zxPlane() const {
        return Plane3d(
            originPoint(),
            zDirectionVector(),
            xDirectionVector(),
            yDirectionVector(),
            handedness()
        );
    }
    
    inline
    Plane3d
    Frame3d::zyPlane() const {
        return Plane3d(
            originPoint(),
            zDirectionVector(),
            yDirectionVector(),
            -xDirectionVector(),
            handedness()
        );
    }

    template <class TTransformation>
    inline
    Frame3d
    Frame3d::transformedBy(const TTransformation& transformation) const {
        return Frame3d(
            originPoint().transformedBy(transformation),
            xDirectionVector().transformedBy(transformation),
            yDirectionVector().transformedBy(transformation),
            zDirectionVector().transformedBy(transformation),
            handedness().transformedBy(transformation)
        );
    }

    inline
    Frame3d
    Frame3d::XYZ() {
        return Frame3d(
            Point3d::ORIGIN(),
            UnitVector3d::X(),
            UnitVector3d::Y(),
            UnitVector3d::Z(),
            Handedness::RIGHT_HANDED()
        );
    }
}
