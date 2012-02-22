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

#ifndef OPENSOLID__PLANE_HPP
#define OPENSOLID__PLANE_HPP

#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Common/TypeName.hpp>

namespace OpenSolid
{
    class Plane3d : public Datum<3, 2>
    {
    public:
        Plane3d();
        Plane3d(const Vector3d& origin, const Vector3d& normal);
        Plane3d(const Vector3d& origin, const Vector3d& x_direction, const Vector3d& y_direction);

        template <int dimensions_, int axes_>
        Plane3d(const Datum<dimensions_, axes_>& datum);
    };
}

////////// Specializations //////////

namespace OpenSolid
{
    template <>
    struct TypeName<Plane3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Plane3d::Plane3d() {initialize(Vector3d::Zero(), Matrix<double, 3, 2>::Identity());}

    inline Plane3d::Plane3d(const Vector3d& origin, const Vector3d& normal) {
        Matrix<double, 3, 2> basis;
        basis.col(0) = normal.unitOrthogonal();
        basis.col(1) = normal.cross(basis.col(0)).normalized();
        initialize(origin, basis);
    }

    inline Plane3d::Plane3d(
        const Vector3d& origin,
        const Vector3d& x_direction,
        const Vector3d& y_direction
    ) {
        Matrix<double, 3, 2> basis;
        basis.col(0) = x_direction.normalized();
        basis.col(1) = (y_direction - y_direction.dot(basis.col(0)) * basis.col(0)).normalized();
        initialize(origin, basis);
    }

    template <int dimensions_, int axes_>
    inline Plane3d::Plane3d(const Datum<dimensions_, axes_>& datum) {
        assertCompatible<dimensions_, 3>();
        assert(datum.dimensions() == 3);
        assertCompatible<axes_, 2>();
        assert(datum.axes() == 2);
        assert(datum.basis().isUnitary());
        initialize(datum);
    }
}

#endif
