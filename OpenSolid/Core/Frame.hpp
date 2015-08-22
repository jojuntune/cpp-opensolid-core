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
        FrameBase<2, 2>(Point2d::origin(), Matrix2d::identity()) {
    }

    inline
    Frame2d::Frame(const Point2d& originPoint) :
        FrameBase<2, 2>(originPoint, Matrix2d::identity()) {
    }

    inline
    Frame2d::Frame(const Point2d& originPoint, const Matrix2d& basisMatrix) :
        FrameBase<2, 2>(originPoint, basisMatrix) {
    }

    inline
    Frame2d::Frame(const Point2d& originPoint, const Quaternion2d& orientation) :
        FrameBase<2, 2>(originPoint, orientation.rotationMatrix()) {

    }

    inline
    Frame2d::Frame(
        const Point2d& originPoint,
        const UnitVector2d& xDirectionVector,
        const UnitVector2d& yDirectionVector
    ) : FrameBase<2, 2>(
        originPoint,
        Matrix2d::fromColumns(xDirectionVector.components(), yDirectionVector.components())
    ) {
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
        return Axis2d(originPoint(), xDirectionVector());
    }
    
    inline
    Axis2d
    Frame2d::yAxis() const {
        return Axis2d(originPoint(), yDirectionVector());
    }

    inline
    Frame2d
    Frame2d::scaledAbout(const Point2d& point, double scale) const {
        return Frame2d(
            originPoint().scaledAbout(point, scale),
            basisMatrix()
        );
    }

    inline
    Frame2d
    Frame2d::rotatedAbout(const Point2d& point, const Matrix2d& rotationMatrix) const {
        return Frame2d(
            originPoint().rotatedAbout(point, rotationMatrix),
            rotationMatrix * basisMatrix()
        );
    }

    inline
    Frame2d
    Frame2d::translatedBy(const Vector2d& vector) const {
        return Frame2d(originPoint().translatedBy(vector), basisMatrix());
    }

    inline
    Frame2d
    Frame2d::toLocalIn(const Frame2d& frame) const {
        return Frame2d(
            originPoint().toLocalIn(frame),
            frame.basisMatrix().transposeProduct(basisMatrix())
        );
    }

    inline
    Frame2d
    Frame2d::toGlobalFrom(const Frame2d& frame) const {
        return Frame2d(
            originPoint().toGlobalFrom(frame),
            frame.basisMatrix() * basisMatrix()
        );
    }

    inline
    Frame2d
    Frame2d::mirroredAbout(const Point2d& point, const UnitVector2d& direction) const {
        return Frame2d(
            originPoint().mirroredAbout(point, direction),
            xDirectionVector().mirroredAlong(direction),
            yDirectionVector().mirroredAlong(direction)
        );
    }

    inline
    Frame3d::Frame() :
        FrameBase<3, 3>(Point3d::origin(), Matrix3d::identity()) {
    }

    inline
    Frame3d::Frame(const Point3d& originPoint) :
        FrameBase<3, 3>(originPoint, Matrix3d::identity()) {
    }

    inline
    Frame3d::Frame(const Point3d& originPoint, const Matrix3d& basisMatrix) :
        FrameBase<3, 3>(originPoint, basisMatrix) {
    }

    inline
    Frame3d::Frame(const Point3d& originPoint, const Quaternion3d& orientation) :
        FrameBase<3, 3>(originPoint, orientation.rotationMatrix()) {
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
    ) {
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
        return Plane3d(originPoint(), xDirectionVector(), yDirectionVector(), zDirectionVector());
    }
    
    inline
    Plane3d
    Frame3d::xzPlane() const {
        return Plane3d(originPoint(), xDirectionVector(), zDirectionVector(), -yDirectionVector());
    }
    
    inline
    Plane3d
    Frame3d::yxPlane() const {
        return Plane3d(originPoint(), yDirectionVector(), xDirectionVector(), -zDirectionVector());
    }
    
    inline
    Plane3d
    Frame3d::yzPlane() const {
        return Plane3d(originPoint(), yDirectionVector(), zDirectionVector(), xDirectionVector());
    }
    
    inline
    Plane3d
    Frame3d::zxPlane() const {
        return Plane3d(originPoint(), zDirectionVector(), xDirectionVector(), yDirectionVector());
    }
    
    inline
    Plane3d
    Frame3d::zyPlane() const {
        return Plane3d(originPoint(), zDirectionVector(), yDirectionVector(), -xDirectionVector());
    }

    inline
    Frame3d
    Frame3d::scaledAbout(const Point3d& point, double scale) const {
        return Frame3d(
            originPoint().scaledAbout(point, scale),
            basisMatrix()
        );
    }

    inline
    Frame3d
    Frame3d::rotatedAbout(const Point3d& point, const Matrix3d& rotationMatrix) const {
        return Frame3d(
            originPoint().rotatedAbout(point, rotationMatrix),
            rotationMatrix * basisMatrix()
        );
    }

    inline
    Frame3d
    Frame3d::translatedBy(const Vector3d& vector) const {
        return Frame3d(originPoint().translatedBy(vector), basisMatrix());
    }

    inline
    Frame3d
    Frame3d::toLocalIn(const Frame3d& other) const {
        return Frame3d(
            originPoint().toLocalIn(other),
            other.basisMatrix().transposeProduct(basisMatrix())
        );
    }

    inline
    Frame3d
    Frame3d::toGlobalFrom(const Frame3d& other) const {
        return Frame3d(
            originPoint().toGlobalFrom(other),
            other.basisMatrix() * basisMatrix()
        );
    }

    inline
    Frame3d
    Frame3d::mirroredAbout(const Point3d& point, const UnitVector3d& direction) const {
        return Frame3d(
            originPoint().mirroredAbout(point, direction),
            xDirectionVector().mirroredAlong(direction),
            yDirectionVector().mirroredAlong(direction),
            zDirectionVector().mirroredAlong(direction)
        );
    }
}
