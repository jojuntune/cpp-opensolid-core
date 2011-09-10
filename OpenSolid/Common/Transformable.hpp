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

#ifndef OPENSOLID__TRANSFORMABLE_HPP
#define OPENSOLID__TRANSFORMABLE_HPP

#include <OpenSolid/Matrix/Matrix.hpp>

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    class Datum;

    template <class DerivedType>
    class Transformable
    {
    private:
        const DerivedType& derived() const;
    public:
        template <class PointType>
        DerivedType scaled(double scale, const EigenBase<PointType>& point) const;

        template <class VectorType>
        DerivedType translated(const EigenBase<VectorType>& vector) const;

        template <int dimensions_, int axes_>
        DerivedType translated(double distance, const Datum<dimensions_, axes_>& axis) const;

        DerivedType rotated(double angle, const Vector2d& point) const;

        template <int dimensions_, int axes_>
        DerivedType rotated(double angle, const Datum<dimensions_, axes_>& axis) const;

        template <int dimensions_, int axes_>
        DerivedType mirrored(const Datum<dimensions_, axes_>& datum) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class DerivedType>
    inline const DerivedType& Transformable<DerivedType>::derived() const {
        return static_cast<const DerivedType&>(*this);
    }

    template <class DerivedType> template <class PointType>
    inline DerivedType Transformable<DerivedType>::scaled(
        double scale,
        const EigenBase<PointType>& point
    ) const {
        static const int static_dimensions = PointType::SizeAtCompileTime;
        Matrix<double, static_dimensions, static_dimensions> identity(point.size(), point.size());
        identity.setIdentity();
        return derived().transformed(scale * identity, point - scale * point);
    }

    template <class DerivedType> template <class VectorType>
    inline DerivedType Transformable<DerivedType>::translated(
        const EigenBase<VectorType>& vector
    ) const {
        static const int dimensions = VectorType::SizeAtCompileTime;
        Matrix<double, dimensions, dimensions> identity(vector.size(), vector.size());
        identity.setIdentity();
        return derived().transformed(identity, vector.derived());
    }
}

#include <OpenSolid/Datum/Datum.hpp>

#endif
