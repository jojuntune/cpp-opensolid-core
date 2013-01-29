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

#include "SimplexDomain.hpp"

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/Geometry/SimplexGeometry.hpp>

namespace opensolid
{
    template <>
    Set<Geometry> SimplexDomain<1>::boundaries() const {
        Set<Geometry> results;
        results.insert(_simplex.vertex(0));
        results.insert(_simplex.vertex(1));
        return results;
    }

    template <>
    Set<Geometry> SimplexDomain<2>::boundaries() const {
        Set<Geometry> results;
        results.insert(new SimplexGeometry<2, 2>(_simplex.edge(1, 0)));
        results.insert(new SimplexGeometry<2, 2>(_simplex.edge(2, 1)));
        results.insert(new SimplexGeometry<2, 2>(_simplex.edge(0, 2)));
        return results;
    }

    template <>
    Set<Geometry> SimplexDomain<3>::boundaries() const {
        Set<Geometry> results;
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(0)));
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(1)));
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(2)));
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(3)));
        return results;
    }
}
