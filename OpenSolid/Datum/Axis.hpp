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

#ifndef OPENSOLID__AXIS_HPP
#define OPENSOLID__AXIS_HPP

#include <functional>

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    class Axis : public Datum<dimensions_, 1>
    {
    public:
        typedef Eigen::Matrix<double, dimensions_, 1> Vector;
        typedef Eigen::Matrix<double, dimensions_, 1> Matrix;
        
        Axis();
        Axis(const Vector& origin, const Vector& vector);
        
        template <int other_dimensions_, int other_axes_>
        Axis(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Axis<dimensions_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
    };
    
    typedef Axis<2> Axis2d;
    typedef Axis<3> Axis3d;
    typedef Axis<4> Axis4d;
    typedef Axis<Dynamic> AxisXd;
}

namespace std
{
    template <int dimensions_>
    struct hash<OpenSolid::Axis<dimensions_>>
    {
        std::size_t operator()(const OpenSolid::Axis<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Axis<dimensions_>>
    {
        bool operator()(
            const OpenSolid::Axis<dimensions_>& first_argument,
            const OpenSolid::Axis<dimensions_>& second_argument
        ) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_>
    inline Axis<dimensions_>::Axis() {}
    
    template <int dimensions_>
    inline Axis<dimensions_>::Axis(const Vector& origin, const Vector& vector) {
        initialize(origin, vector, true);
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Axis<dimensions_>::Axis(const Datum<other_dimensions_, other_axes_>& other) {
        assert(other._normalized);
        initialize(other);
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Axis<dimensions_>& Axis<dimensions_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(other._normalized);
        initialize(other);
        return *this;
    }
}

namespace std
{
    template <int dimensions_>
    inline size_t hash<OpenSolid::Axis<dimensions_>>::operator()(
        const OpenSolid::Axis<dimensions_>& argument
    ) const {return hash<OpenSolid::Datum<dimensions_, 1>>()(argument);}

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Axis<dimensions_>>::operator()(
        const OpenSolid::Axis<dimensions_>& first_argument,
        const OpenSolid::Axis<dimensions_>& second_argument
    ) const {return equal_to<OpenSolid::Datum<dimensions_, 1>>()(first_argument, second_argument);}
}

#endif
