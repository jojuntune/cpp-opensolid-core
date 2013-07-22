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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>

#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Axis
    {
    private:
        Point<iNumDimensions> _originPoint;
        Matrix<double, iNumDimensions, 1> _directionVector;
    public:
        Axis();

        Axis(
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumDimensions, 1>& directionVector
        );

        const Point<iNumDimensions>&
        originPoint() const;
        
        const Matrix<double, iNumDimensions, 1>&
        directionVector() const;

        Axis<iNumDimensions>
        flipped() const;

        CoordinateSystem<iNumDimensions, 1>
        coordinateSystem() const;
    };

    class Axis2d :
        public Axis<2>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Axis2d(const Point2d& originPoint, const Vector2d& directionVector);

        OPENSOLID_CORE_EXPORT
        Axis2d(const Axis<2>& other);

        OPENSOLID_CORE_EXPORT
        static Axis2d
        X();

        OPENSOLID_CORE_EXPORT
        static Axis2d
        Y();
    };

    class Axis3d :
        public Axis<3>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Axis3d(const Point3d& originPoint, const Vector3d& directionVector);

        OPENSOLID_CORE_EXPORT
        Axis3d(const Axis<3>& other);

        OPENSOLID_CORE_EXPORT
        static Axis3d
        X();

        OPENSOLID_CORE_EXPORT
        static Axis3d
        Y();

        OPENSOLID_CORE_EXPORT
        static Axis3d
        Z();

        OPENSOLID_CORE_EXPORT
        Plane3d
        normalPlane() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<Axis<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct ChangeDimensions<Axis<iNumDimensions>, iNumResultDimensions>
    {
        typedef Axis<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScalingFunction<Axis<iNumDimensions>>
    {
        Axis<iNumDimensions>
        operator()(const Axis<iNumDimensions>& axis, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Axis<iNumDimensions>>
    {
        template <class TVector>
        Axis<iNumDimensions>
        operator()(const Axis<iNumDimensions>& axis, const EigenBase<TVector>& vector) const;
    };

    template <int iNumDimensions, int iNumTransformedDimensions>
    struct TransformationFunction<Axis<iNumDimensions>, iNumTransformedDimensions>
    {
        template <class TMatrix>
        Axis<iNumTransformedDimensions>
        operator()(const Axis<iNumDimensions>& axis, const EigenBase<TMatrix>& matrix) const;
    };

    template <int iNumDimensions, int iNumDestinationDimensions>
    struct MorphingFunction<Axis<iNumDimensions>, iNumDestinationDimensions>
    {
        Axis<iNumDestinationDimensions>
        operator()(
            const Axis<iNumDimensions>& axis,
            const Function<iNumDestinationDimensions, iNumDimensions>& function
        ) const;
    };

    template <>
    struct NumDimensions<Axis2d> :
        public NumDimensions<Axis<2>>
    {
    };

    template <int iNumResultDimensions>
    struct ChangeDimensions<Axis2d, iNumResultDimensions> :
        public ChangeDimensions<Axis<2>, iNumResultDimensions>
    {
    };

    template <>
    struct ScalingFunction<Axis2d> :
        public ScalingFunction<Axis<2>>
    {
    };

    template <>
    struct TranslationFunction<Axis2d> :
        public TranslationFunction<Axis<2>>
    {
    };

    template <int iNumTransformedDimensions>
    struct TransformationFunction<Axis2d, iNumTransformedDimensions> :
        public TransformationFunction<Axis<2>, iNumTransformedDimensions>
    {
    };

    template <int iNumDestinationDimensions>
    struct MorphingFunction<Axis2d, iNumDestinationDimensions> :
        public MorphingFunction<Axis<2>, iNumDestinationDimensions>
    {
    };

    template <>
    struct NumDimensions<Axis3d> :
        public NumDimensions<Axis<3>>
    {
    };

    template <int iNumResultDimensions>
    struct ChangeDimensions<Axis3d, iNumResultDimensions> :
        public ChangeDimensions<Axis<3>, iNumResultDimensions>
    {
    };

    template <>
    struct ScalingFunction<Axis3d> :
        public ScalingFunction<Axis<3>>
    {
    };

    template <>
    struct TranslationFunction<Axis3d> :
        public TranslationFunction<Axis<3>>
    {
    };

    template <int iNumTransformedDimensions>
    struct TransformationFunction<Axis3d, iNumTransformedDimensions> :
        public TransformationFunction<Axis<3>, iNumTransformedDimensions>
    {
    };

    template <int iNumDestinationDimensions>
    struct MorphingFunction<Axis3d, iNumDestinationDimensions> :
        public MorphingFunction<Axis<3>, iNumDestinationDimensions>
    {
    };
}
