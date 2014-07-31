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

#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    typename ScaledType<TDerived>::Type
    Transformable<TDerived>::scaledAbout(
        const Point<NumDimensions<TDerived>::Value>& originPoint,
        double scale
    ) const {
        return ScalingFunction<TDerived>()(derived(), originPoint, scale);
    }

    template <class TDerived>
    inline
    typename TranslatedType<TDerived>::Type
    Transformable<TDerived>::translatedBy(
        const Vector<double, NumDimensions<TDerived>::Value>& vector
    ) const {
        return TranslationFunction<TDerived>()(derived(), vector);
    }
    
    template <class TDerived>
    inline
    typename TranslatedType<TDerived>::Type
    Transformable<TDerived>::translatedAlong(
        const Axis<NumDimensions<TDerived>::Value>& axis,
        double distance
    ) const {
        return TranslationFunction<TDerived>()(derived(), distance * axis.directionVector());
    }

    template <class TDerived>
    inline
    typename RotatedType<TDerived>::Type
    Transformable<TDerived>::rotatedAbout(const Point2d& originPoint, double angle) const {
        static_assert(
            NumDimensions<TDerived>::Value == 2,
            "Only 2D objects may be rotated around 2D points"
        );

        return RotationFunction<TDerived>()(
            derived(),
            originPoint,
            Quaternion2d(angle).rotationMatrix()
        );
    }

    template <class TDerived>
    inline
    typename RotatedType<TDerived>::Type
    Transformable<TDerived>::rotatedAbout(const Axis3d& axis, double angle) const {
        static_assert(
            NumDimensions<TDerived>::Value == 3,
            "Only 3D objects may be rotated around 3D points"
        );
        
        return RotationFunction<TDerived>()(
            derived(),
            axis.originPoint(),
            Quaternion3d(axis.directionVector(), angle).rotationMatrix()
        );
    }

    template <class TDerived>
    inline
    typename MirroredType<TDerived>::Type
    Transformable<TDerived>::mirroredAbout(const Axis2d& axis) const {
        static_assert(
            NumDimensions<TDerived>::Value == 2,
            "Only 2D objects may be mirrored around 2D axes"
        );
        
        return MirrorFunction<TDerived>()(derived(), axis.originPoint(), axis.normalVector());
    }

    template <class TDerived>
    inline
    typename MirroredType<TDerived>::Type
    Transformable<TDerived>::mirroredAbout(const Plane3d& plane) const {
        static_assert(
            NumDimensions<TDerived>::Value == 3,
            "Only 3D objects may be mirrored around 3D planes"
        );
        
        return MirrorFunction<TDerived>()(derived(), plane.originPoint(), plane.normalVector());
    }

    template <class TDerived>
    inline
    typename ProjectedType<TDerived, Axis<NumDimensions<TDerived>::Value>>::Type
    Transformable<TDerived>::projectedOnto(const Axis<NumDimensions<TDerived>::Value>& axis) const {
        return ProjectionFunction<TDerived, Axis<NumDimensions<TDerived>::Value>>()(
            derived(),
            axis
        );
    }

    template <class TDerived>
    inline
    typename ProjectedType<TDerived, Plane3d>::Type
    Transformable<TDerived>::projectedOnto(const Plane3d& plane) const {
        static_assert(
            NumDimensions<TDerived>::Value == 3,
            "Only 3D objects may be projected onto 3D planes"
        );
        
        return ProjectionFunction<TDerived, Plane3d>()(derived(), plane);
    }

    template <class TDerived> template <int iNumResultDimensions>
    inline
    typename TransformedType<TDerived, iNumResultDimensions>::Type
    Transformable<TDerived>::transformed(
        const Point<NumDimensions<TDerived>::Value>& originPoint,
        const Matrix<
            double,
            iNumResultDimensions,
            NumDimensions<TDerived>::Value
        >& transformationMatrix,
        const Point<iNumResultDimensions>& destinationPoint
    ) const {
        return TransformationFunction<TDerived, iNumResultDimensions>()(
            derived(),
            originPoint,
            transformationMatrix,
            destinationPoint
        );
    }

    template <class TDerived> template <int iNumResultDimensions>
    inline
    typename MorphedType<TDerived, iNumResultDimensions>::Type
    Transformable<TDerived>::morphedBy(
        const ParametricExpression<
            iNumResultDimensions,
            NumDimensions<TDerived>::Value
        >& morphingExpression
    ) const {
        return MorphingFunction<TDerived, iNumResultDimensions>()(derived(), morphingExpression);
    }

    template <class TTransformable>
    inline
    typename RotatedType<TTransformable>::Type
    RotationFunction<TTransformable>::operator()(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const Matrix<
            double,
            NumDimensions<TTransformable>::Value,
            NumDimensions<TTransformable>::Value
        >& rotationMatrix
    ) const {
        return transformed(
            transformable,
            originPoint,
            rotationMatrix,
            originPoint
        );
    }

    template <class TTransformable>
    inline
    typename MirroredType<TTransformable>::Type
    MirrorFunction<TTransformable>::operator()(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const UnitVector<NumDimensions<TTransformable>::Value>& normalVector
    ) const {
        return transformed(
            transformable,
            originPoint,
            Matrix<
                double,
                NumDimensions<TTransformable>::Value,
                NumDimensions<TTransformable>::Value
            >::identity() - 2 * normalVector.components() * normalVector.components().transpose(),
            originPoint
        );
    }

    template <class TTransformable>
    inline
    typename ProjectedType<TTransformable, Axis<NumDimensions<TTransformable>::Value>>::Type
    ProjectionFunction< TTransformable, Axis<NumDimensions<TTransformable>::Value>>::operator()(
        const TTransformable& transformable,
        const Axis<NumDimensions<TTransformable>::Value>& axis
    ) const {
        return transformed(
            transformable,
            axis.originPoint(),
            axis.directionVector().components() * axis.directionVector().components().transpose(),
            axis.originPoint()
        );
    }

    template <class TTransformable>
    inline
    typename ProjectedType<TTransformable, Plane3d>::Type
    ProjectionFunction<TTransformable, Plane3d>::operator()(
        const TTransformable& transformable,
        const Plane3d& plane
    ) const {
        return transformed(
            transformable,
            plane.originPoint(),
            Matrix3d::identity() - (
                plane.normalVector().components() * plane.normalVector().components().transpose()
            ),
            plane.originPoint()
        );
    }

    template <class TTransformable, class TCoordinateSystem>
    inline
    typename LocalizedType<TTransformable, TCoordinateSystem>::Type
    LocalizationFunction<TTransformable, TCoordinateSystem>::operator()(
        const TTransformable& transformable,
        const TCoordinateSystem& coordinateSystem
    ) const {
        return transformed(
            transformable,
            coordinateSystem.originPoint(),
            coordinateSystem.inverseMatrix(),
            Point<TCoordinateSystem::NumAxes>::origin()
        );
    }

    template <class TTransformable, class TCoordinateSystem>
    inline
    typename GlobalizedType<TTransformable, TCoordinateSystem>::Type
    GlobalizationFunction<TTransformable, TCoordinateSystem>::operator()(
        const TTransformable& transformable,
        const TCoordinateSystem& coordinateSystem
    ) const {
        return transformed(
            transformable,
            Point<TCoordinateSystem::NumAxes>::origin(),
            coordinateSystem.basisMatrix(),
            coordinateSystem.originPoint()
        );
    }

    template <class TTransformable>
    inline
    typename ScaledType<TTransformable>::Type
    scaled(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        double scale
    ) {
        return ScalingFunction<TTransformable>()(transformable, originPoint, scale);
    }

    template <class TTransformable>
    inline
    typename TranslatedType<TTransformable>::Type
    translated(
        const TTransformable& transformable,
        const Vector<double, NumDimensions<TTransformable>::Value>& vector
    ) {
        return TranslationFunction<TTransformable>()(transformable, vector);
    }

    template <class TTransformable, int iNumResultDimensions>
    inline
    typename TransformedType<TTransformable, iNumResultDimensions>::Type
    transformed(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const Matrix<
            double,
            iNumResultDimensions,
            NumDimensions<TTransformable>::Value
        >& transformationMatrix,
        const Point<iNumResultDimensions>& destinationPoint
    ) {
        return TransformationFunction<TTransformable, iNumResultDimensions>()(
            transformable,
            originPoint,
            transformationMatrix,
            destinationPoint
        );
    }

    template <class TTransformable, int iNumResultDimensions>
    inline
    typename MorphedType<TTransformable, iNumResultDimensions>::Type
    morphed(
        const TTransformable& transformable,
        const ParametricExpression<
            iNumResultDimensions,
            NumDimensions<TTransformable>::Value
        >& morphingExpression
    ) {
        return MorphingFunction<TTransformable, iNumResultDimensions>()(
            transformable,
            morphingExpression
        );
    }

    template <class TTransformable>
    inline
    typename RotatedType<TTransformable>::Type
    rotated(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const Matrix<
            double,
            NumDimensions<TTransformable>::Value,
            NumDimensions<TTransformable>::Value
        >& rotationMatrix
    ) {
        return RotationFunction<TTransformable>()(transformable, originPoint, rotationMatrix);
    }

    template <class TTransformable>
    inline
    typename MirroredType<TTransformable>::Type
    mirrored(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const UnitVector<NumDimensions<TTransformable>::Value>& normalVector
    ) {
        return MirrorFunction<TTransformable>()(transformable, originPoint, normalVector);
    }

    template <class TTransformable>
    inline
    typename ProjectedType<TTransformable, Axis<NumDimensions<TTransformable>::Value>>::Type
    projected(
        const TTransformable& transformable,
        const Axis<NumDimensions<TTransformable>::Value>& axis
    ) {
        return ProjectionFunction<TTransformable, Axis<NumDimensions<TTransformable>::Value>>(
            transformable,
            axis
        );
    }

    template <class TTransformable>
    inline
    typename ProjectedType<TTransformable, Plane3d>::Type
    projected(const TTransformable& transformable, const Plane3d& plane) {
        return ProjectionFunction<TTransformable, Plane3d>(transformable, plane);
    }

    template <class TTransformable, class TCoordinateSystem>
    inline
    typename LocalizedType<TTransformable, TCoordinateSystem>::Type
    localized(const TTransformable& transformable, const TCoordinateSystem& coordinateSystem) {
        return LocalizationFunction<TTransformable, TCoordinateSystem>()(
            transformable,
            coordinateSystem
        );
    }

    template <class TTransformable, class TCoordinateSystem>
    inline
    typename GlobalizedType<TTransformable, TCoordinateSystem>::Type
    globalized(const TTransformable& transformable, const TCoordinateSystem& coordinateSystem) {
        return GlobalizationFunction<TTransformable, TCoordinateSystem>()(
            transformable,
            coordinateSystem
        );
    }
}
