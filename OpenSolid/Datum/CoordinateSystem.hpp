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

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    class CoordinateSystem : public Datum<dimensions_, axes_>
    {
    public:
        typedef Eigen::Matrix<Double, dimensions_, 1> Vector;
        typedef Eigen::Matrix<Double, dimensions_, axes_> Matrix;
        
        template <class DerivedType>
        CoordinateSystem(const Vector& origin, const EigenBase<DerivedType>& vectors);
    };
    
    typedef CoordinateSystem<2, 2> CoordinateSystem2D;
    typedef CoordinateSystem<3, 3> CoordinateSystem3D;
    typedef CoordinateSystem<4, 4> CoordinateSystem4D;
    typedef CoordinateSystem<Dynamic, Dynamic> CoordinateSystemXD;
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


#endif
