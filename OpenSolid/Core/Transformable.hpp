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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformation.hpp>

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class Datum;

    template <class TInput, int iTransformedDimensions>
    struct Transformed
    {
        typedef TInput Type;
    };

    template <class TDerived>
    class Transformable
    {
    private:
        const TDerived& derived() const;
    public:
        template <class TPoint>
        typename Transformed<TDerived, TPoint::SizeAtCompileTime>::Type scaled(
            double scale,
            const EigenBase<TPoint>& point
        ) const;

        template <class TVector>
        typename Transformed<TDerived, TVector::SizeAtCompileTime>::Type translated(
            const EigenBase<TVector>& vector
        ) const;

        template <int iNumDimensions, int iNumAxes>
        typename Transformed<TDerived, iNumDimensions>::Type translated(
            double distance,
            const Datum<iNumDimensions, iNumAxes>& axis
        ) const;

        typename Transformed<TDerived, 2>::Type rotated(
            double angle,
            const Vector2d& point
        ) const;

        template <int iNumDimensions, int iNumAxes>
        typename Transformed<TDerived, 3>::Type rotated(
            double angle,
            const Datum<iNumDimensions, iNumAxes>& axis
        ) const;

        template <int iNumDimensions, int iNumAxes>
        typename Transformed<TDerived, iNumDimensions>::Type mirrored(
            const Datum<iNumDimensions, iNumAxes>& datum
        ) const;

        template <int iNumDimensions, int iNumAxes>
        typename Transformed<TDerived, iNumDimensions>::Type projected(
            const Datum<iNumDimensions, iNumAxes>& datum
        ) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class TDerived>
    inline const TDerived& Transformable<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived> template <class TPoint>
    inline typename Transformed<TDerived, TPoint::SizeAtCompileTime>::Type
    Transformable<TDerived>::scaled(
        double scale,
        const EigenBase<TPoint>& point
    ) const {
        return derived().transformed(
            Transformation<TPoint::SizeAtCompileTime>(
                Matrix<double, TPoint::SizeAtCompileTime, TPoint::SizeAtCompileTime>::Identity(
                    point.size()
                ) * scale,
                point.derived() - scale * point.derived()
            )
        );
    }

    template <class TDerived> template <class TVector>
    inline typename Transformed<TDerived, TVector::SizeAtCompileTime>::Type
    Transformable<TDerived, TResult>::translated(
        const EigenBase<TVector>& vector
    ) const {
        return derived().transformed(
            Transformation<TVector::SizeAtCompileTime>(
                Matrix<double, TVector::SizeAtCompileTime, TVector::SizeAtCompileTime>::Identity(
                    vector.size()
                ),
                vector.derived()
            )
        );
    }

    template <class TDerived>
    inline typename Transformed<TDerived, 2>::Type Transformable<TDerived>::rotated(
        double angle,
        const Vector2d& point
    ) const {
        return derived().transformed(
            Transformation<2>(Matrix2d(Rotation2Dd(angle)), point - matrix * point)
        );
    }
}
