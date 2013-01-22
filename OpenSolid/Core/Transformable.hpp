/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
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

        template <int iNumDimensions, int iNumAxes>
        TDerived translated(
            double coordinateValue,
            const Datum<iNumDimensions, iNumAxes>& axis
        ) const;

        TDerived rotated(double angle) const;

        TDerived rotated(double angle, const Vector2d& originPoint) const;

        TDerived rotated(const Rotation2d& rotation) const;

        TDerived rotated(const Rotation2d& rotation, LinearTag) const;

        template <int iNumDimensions, int iNumAxes>
        TDerived rotated(double angle, const Datum<iNumDimensions, iNumAxes>& axis) const;

        TDerived rotated(const Rotation3d& rotation) const;

        TDerived rotated(const Rotation3d& rotation, LinearTag) const;

        template <int iNumDimensions, int iNumAxes>
        TDerived mirrored(const Datum<iNumDimensions, iNumAxes>& datum) const;

        template <int iNumDimensions>
        TDerived mirrored(const Mirror<iNumDimensions>& mirror) const;

        template <int iNumDimensions>
        TDerived mirrored(const Mirror<iNumDimensions>& mirror, LinearTag) const;

        template <int iNumDimensions, int iNumAxes>
        TDerived projected(const Datum<iNumDimensions, iNumAxes>& datum) const;

        template <int iNumDimensions>
        TDerived projected(const Projection<iNumDimensions>& projection) const;

        template <int iNumDimensions>
        TDerived projected(const Projection<iNumDimensions>& projection, LinearTag) const;

        template <
            int iNumSourceDatumDimensions,
            int iNumSourceDatumAxes,
            int iNumDestinationDatumDimensions,
            int iNumDestinationDatumAxes
        >
        typename Transformed<TDerived, iNumDestinationDatumDimensions>::Type transformed(
            const Datum<iNumSourceDatumDimensions, iNumSourceDatumAxes>& sourceDatum,
            const Datum<iNumDestinationDatumDimensions, iNumDestinationDatumAxes>& destinationDatum
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
    TDerived operator*(const Transformable<TDerived>& transformable, double scaleFactor);

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

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline TDerived Transformable<TDerived>::translated(
        double coordinateValue,
        const Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        return derived() + coordinateValue * axis.basisVector();
    }

    template <class TDerived>
    inline TDerived Transformable<TDerived>::rotated(double angle) const {
        return rotated(Rotation2d(angle, Vector2d::Zero()), Linear);
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

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline TDerived Transformable<TDerived>::rotated(
        double angle,
        const Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        return rotated(Rotation3d(angle, axis));
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

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline TDerived Transformable<TDerived>::mirrored(
        const Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return mirrored(Mirror<iNumDimensions>(datum));
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

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    TDerived Transformable<TDerived>::projected(
        const Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return projected(Projection<iNumDimensions>(datum));
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

    template <class TDerived>
    template <
        int iNumSourceDatumDimensions,
        int iNumSourceDatumAxes,
        int iNumDestinationDatumDimensions,
        int iNumDestinationDatumAxes
    >
    typename Transformed<TDerived, iNumDestinationDatumDimensions>::Type
    Transformable<TDerived>::transformed(
        const Datum<iNumSourceDatumDimensions, iNumSourceDatumAxes>& sourceDatum,
        const Datum<iNumDestinationDatumDimensions, iNumDestinationDatumAxes>& destinationDatum
    ) const {
        return destinationDatum * (derived() / sourceDatum);
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
    inline TDerived operator*(const Transformable<TDerived>& transformable, double scaleFactor) {
        return scaleFactor * transformable.derived();
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
