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

#ifndef OPENSOLID__COORDINATESYSTEM_HPP
#define OPENSOLID__COORDINATESYSTEM_HPP

#include <functional>

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    class CoordinateSystem : public Datum<dimensions_, axes_>
    {
    public:
        typedef Eigen::Matrix<double, dimensions_, 1> Vector;
        typedef Eigen::Matrix<double, dimensions_, axes_> Matrix;
        
        template <class DerivedType>
        CoordinateSystem(const Vector& origin, const EigenBase<DerivedType>& vectors);
    };
    
    typedef CoordinateSystem<2, 2> CoordinateSystem2d;
    typedef CoordinateSystem<3, 3> CoordinateSystem3d;
    typedef CoordinateSystem<4, 4> CoordinateSystem4d;
    typedef CoordinateSystem<Dynamic, Dynamic> CoordinateSystemXd;
}

namespace std
{
    template <int dimensions_, int axes_>
    struct hash<OpenSolid::CoordinateSystem<dimensions_, axes_>>
    {
        std::size_t operator()(
            const OpenSolid::CoordinateSystem<dimensions_, axes_>& argument
        ) const;
    };

    template <int dimensions_, int axes_>
    struct equal_to<OpenSolid::CoordinateSystem<dimensions_, axes_>>
    {
        bool operator()(
            const OpenSolid::CoordinateSystem<dimensions_, axes_>& first_argument,
            const OpenSolid::CoordinateSystem<dimensions_, axes_>& second_argument
        ) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_, int axes_> template <class DerivedType>
    inline CoordinateSystem<dimensions_, axes_>::CoordinateSystem(
        const Vector& origin,
        const EigenBase<DerivedType>& vectors
    ) {initialize(origin, vectors, false);}
}

namespace std
{
    template <int dimensions_, int axes_>
    inline size_t hash<OpenSolid::CoordinateSystem<dimensions_, axes_>>::operator()(
        const OpenSolid::CoordinateSystem<dimensions_, axes_>& argument
    ) const {return hash<OpenSolid::Datum<dimensions_, axes_>>()(argument);}

    template <int dimensions_, int axes_>
    inline bool equal_to<OpenSolid::CoordinateSystem<dimensions_, axes_>>::operator()(
        const OpenSolid::CoordinateSystem<dimensions_, axes_>& first_argument,
        const OpenSolid::CoordinateSystem<dimensions_, axes_>& second_argument
    ) const {
        return equal_to<OpenSolid::Datum<dimensions_, axes_>>()(first_argument, second_argument);
    }
}


#endif
