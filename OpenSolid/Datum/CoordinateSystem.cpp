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

#include <OpenSolid/Datum/CoordinateSystem.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    inline CoordinateSystem<dimensions_, axes_>::CoordinateSystem(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, axes_>& basis
    ) : Datum<dimensions_, axes_>(origin, basis) {}

    template <int dimensions_, int axes_>
    inline CoordinateSystem<dimensions_, axes_>::CoordinateSystem(
        const Datum<dimensions_, axes_>& other
    ) : Datum<dimensions_, axes_>(other) {}

    template class CoordinateSystem<1, 1>;
    template class CoordinateSystem<1, Dynamic>;
    template class CoordinateSystem<2, 1>;
    template class CoordinateSystem<2, 2>;
    template class CoordinateSystem<2, Dynamic>;
    template class CoordinateSystem<3, 1>;
    template class CoordinateSystem<3, 2>;
    template class CoordinateSystem<3, 3>;
    template class CoordinateSystem<3, Dynamic>;
    template class CoordinateSystem<Dynamic, 1>;
    template class CoordinateSystem<Dynamic, 2>;
    template class CoordinateSystem<Dynamic, 3>;
    template class CoordinateSystem<Dynamic, Dynamic>;
}
