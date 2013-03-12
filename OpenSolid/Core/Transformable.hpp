/*************************************************************************************
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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>

#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Transformation/declarations.hpp>

////////// Implementation //////////

namespace opensolid
{
    template <class TDerived>
    class Transformable
    {
    public:
        const TDerived& derived() const;

        template <class TPoint>
        TDerived scaled(double scale, const EigenBase<TPoint>& originPoint) const;

        template <int iNumDimensions>
        TDerived translated(double coordinateValue, const Datum<iNumDimensions, 1>& axis) const;

        TDerived rotated(double angle) const;

        TDerived rotated(double angle, const Vector2d& originPoint) const;

        TDerived rotated(const Rotation2d& rotation) const;

        TDerived rotated(const Rotation2d& rotation, LinearTag) const;

        TDerived rotated(double angle, const Datum<3, 1>& axis) const;

        TDerived rotated(double angle, const Datum<3, 1>& axis, LinearTag) const;

        TDerived rotated(const Rotation3d& rotation) const;

        TDerived rotated(const Rotation3d& rotation, LinearTag) const;

        template <int iNumDimensions>
        TDerived mirrored(const Datum<iNumDimensions, iNumDimensions - 1>& datum) const;

        template <int iNumDimensions>
        TDerived mirrored(const Datum<iNumDimensions, iNumDimensions - 1>& datum, LinearTag) const;

        template <int iNumDimensions>
        TDerived mirrored(const Mirror<iNumDimensions>& mirror) const;

        template <int iNumDimensions>
        TDerived mirrored(const Mirror<iNumDimensions>& mirror, LinearTag) const;

        template <int iNumDimensions, int iNumAxes>
        TDerived projected(const Datum<iNumDimensions, iNumAxes>& datum) const;

        template <int iNumDimensions, int iNumAxes>
        TDerived projected(const Datum<iNumDimensions, iNumAxes>& datum, LinearTag) const;

        template <int iNumDimensions>
        TDerived projected(const Projection<iNumDimensions>& projection) const;

        template <int iNumDimensions>
        TDerived projected(const Projection<iNumDimensions>& projection, LinearTag) const;

        template <int iNumSourceDimensions, int iNumDestinationDimensions, int iNumAxes>
        typename Transformed<TDerived, iNumDestinationDimensions>::Type transformed(
            const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
        ) const;

        template <int iNumSourceDimensions, int iNumDestinationDimensions, int iNumAxes>
        typename Transformed<TDerived, iNumDestinationDimensions>::Type transformed(
            const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum,
            LinearTag
        ) const;

        template <int iNumSourceDimensions, int iNumDestinationDimensions>
        typename Transformed<TDerived, iNumDestinationDimensions>::Type transformed(
            const Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation
        ) const;

        template <int iNumSourceDimensions, int iNumDestinationDimensions>
        typename Transformed<TDerived, iNumDestinationDimensions>::Type transformed(
            const Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation,
            LinearTag
        ) const;
    };

    template <class TDerived>
    TDerived operator-(const Transformable<TDerived>& transformable);

    template <class TDerived>
    TDerived operator*(const Transformable<TDerived>& transformable, double scale);

    template <class TDerived>
    TDerived operator/(const Transformable<TDerived>& transformable, double divisor);

    template <class TDerived, class TVector>
    TDerived operator-(
        const Transformable<TDerived>& transformable,
        const EigenBase<TVector>& vector
    );

    template <class TDerived, class TVector>
    TDerived operator+(
        const EigenBase<TVector>& vector,
        const Transformable<TDerived>& transformable
    );

    template <class TDerived, class TVector>
    TDerived operator-(
        const EigenBase<TVector>& vector,
        const Transformable<TDerived>& transformable
    );
}

////////// Implementation //////////

namespace opensolid
{
    template <class TDerived>
    inline const TDerived& Transformable<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived> template <class TPoint>
    inline TDerived Transformable<TDerived>::scaled(
        double scale,
        const EigenBase<TPoint>& originPoint
    ) const {
        return scale * (derived() - originPoint.derived()) + originPoint.derived();
    }

    template <class TDerived>
    inline TDerived Transformable<TDerived>::rotated(double angle) const {
        return Matrix2d(Rotation2Dd(angle)) * derived();
    }

    template <class TDerived>
    inline TDerived Transformable<TDerived>::rotated(
        double angle,
        const Vector2d& originPoint
    ) const {
        return rotated(Rotation2d(angle, originPoint));
    }

    template <class TDerived>
    TDerived Transformable<TDerived>::rotated(const Rotation2d& rotation) const {
        return rotation.transformationMatrix() * (derived() - rotation.originPoint()) +
            rotation.originPoint();
    }

    template <class TDerived>
    TDerived Transformable<TDerived>::rotated(const Rotation2d& rotation, LinearTag) const {
        return rotation.transformationMatrix() * derived();
    }

    template <class TDerived>
    TDerived Transformable<TDerived>::rotated(const Rotation3d& rotation) const {
        return rotation.transformationMatrix() * (derived() - rotation.originPoint()) +
            rotation.originPoint();
    }

    template <class TDerived>
    TDerived Transformable<TDerived>::rotated(const Rotation3d& rotation, LinearTag) const {
        return rotation.transformationMatrix() * derived();
    }

    template <class TDerived> template <int iNumDimensions>
    TDerived Transformable<TDerived>::mirrored(const Mirror<iNumDimensions>& mirror) const {
        return mirror.transformationMatrix() * (derived() - mirror.originPoint()) +
            mirror.originPoint();
    }

    template <class TDerived> template <int iNumDimensions>
    TDerived Transformable<TDerived>::mirrored(
        const Mirror<iNumDimensions>& mirror,
        LinearTag
    ) const {
        return mirror.transformationMatrix() * derived();
    }

    template <class TDerived> template <int iNumDimensions>
    TDerived Transformable<TDerived>::projected(
        const Projection<iNumDimensions>& projection
    ) const {
        return projection.transformationMatrix() * (derived() - projection.originPoint()) +
            projection.originPoint();
    }

    template <class TDerived> template <int iNumDimensions>
    TDerived Transformable<TDerived>::projected(
        const Projection<iNumDimensions>& projection,
        LinearTag
    ) const {
        return projection.transformationMatrix() * derived();
    }

    template <class TDerived> template <int iNumSourceDimensions, int iNumDestinationDimensions>
    typename Transformed<TDerived, iNumDestinationDimensions>::Type
    Transformable<TDerived>::transformed(
        const Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation
    ) const {
        return transformation.transformationMatrix() *
            (derived() - transformation.sourceOriginPoint()) +
            transformation.destinationOriginPoint();
    }

    template <class TDerived> template <int iNumSourceDimensions, int iNumDestinationDimensions>
    typename Transformed<TDerived, iNumDestinationDimensions>::Type
    Transformable<TDerived>::transformed(
        const Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation,
        LinearTag
    ) const {
        return transformation.transformationMatrix() * derived();
    }

    template <class TDerived>
    inline TDerived operator-(const Transformable<TDerived>& transformable) {
        return -1.0 * transformable.derived();
    }

    template <class TDerived>
    inline TDerived operator*(const Transformable<TDerived>& transformable, double scale) {
        return scale * transformable.derived();
    }

    template <class TDerived>
    inline TDerived operator/(const Transformable<TDerived>& transformable, double divisor) {
        assert(divisor != Zero());
        return (1.0 / divisor) * transformable.derived();
    }

    template <class TDerived, class TVector>
    inline TDerived operator-(
        const Transformable<TDerived>& transformable,
        const EigenBase<TVector>& vector
    ) {
        return transformable.derived() + (-vector.derived());
    }

    template <class TDerived, class TVector>
    inline TDerived operator+(
        const EigenBase<TVector>& vector,
        const Transformable<TDerived>& transformable
    ) {
        return transformable.derived() + vector.derived();
    }

    template <class TDerived, class TVector>
    inline TDerived operator-(
        const EigenBase<TVector>& vector,
        const Transformable<TDerived>& transformable
    ) {
        return -transformable.derived() + vector.derived();
    }
}
