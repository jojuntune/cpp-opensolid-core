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

#include <opensolid/config.hpp>

#include <opensolid/TypeName.hpp>
#include <opensolid/Datum.hpp>

namespace opensolid
{
    class Frame2d : public Datum<2, 2>
    {
    public:
        Frame2d();
        explicit Frame2d(const Vector2d& origin);
        Frame2d(const Vector2d& origin, const Vector2d& x_direction);
        
        template <int dimensions_, int axes_>
        Frame2d(const Datum<dimensions_, axes_>& datum);
    };

    
    class Frame3d : public Datum<3, 3>
    {
    public:
        Frame3d();
        explicit Frame3d(const Vector3d& origin);
        Frame3d(const Vector3d& origin, const Vector3d& x_direction, const Vector3d& y_direction);
        
        template <int dimensions_, int axes_>
        Frame3d(const Datum<dimensions_, axes_>& datum);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Frame2d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
    
    template <>
    struct TypeName<Frame3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Frame2d::Frame2d() {initialize(Vector2d::Zero(), Matrix2d::Identity());}

    inline Frame2d::Frame2d(const Vector2d& origin) {initialize(origin, Matrix2d::Identity());}

    inline Frame2d::Frame2d(const Vector2d& origin, const Vector2d& x_direction) {
        Matrix2d basis;
        basis.col(0) = x_direction.normalized();
        basis.col(1) = x_direction.unitOrthogonal();
        initialize(origin, basis);
    }

    template <int dimensions_, int axes_>
    inline Frame2d::Frame2d(const Datum<dimensions_, axes_>& datum) {
        assertCompatible<2, dimensions_>();
        assert(datum.dimensions() == 2);
        assertCompatible<2, axes_>();
        assert(datum.axes() == 2);
        assert(datum.basis().isUnitary());
        initialize(datum);
    }

    inline Frame3d::Frame3d() {initialize(Vector3d::Zero(), Matrix3d::Identity());}

    inline Frame3d::Frame3d(const Vector3d& origin) {initialize(origin, Matrix3d::Identity());}

    inline Frame3d::Frame3d(
        const Vector3d& origin,
        const Vector3d& x_direction,
        const Vector3d& y_direction
    ) {
        Matrix3d basis;
        basis.col(0) = x_direction.normalized();
        basis.col(1) = (y_direction - y_direction.dot(basis.col(0)) * basis.col(0)).normalized();
        basis.col(2) = basis.col(0).cross(basis.col(1));
        initialize(origin, basis);
    }

    template <int dimensions_, int axes_>
    inline Frame3d::Frame3d(const Datum<dimensions_, axes_>& datum) {
        assertCompatible<3, dimensions_>();
        assert(datum.dimensions() == 3);
        assertCompatible<3, axes_>();
        assert(datum.axes() == 3);
        assert(datum.basis().isUnitary());
        initialize(datum);
    }
}
