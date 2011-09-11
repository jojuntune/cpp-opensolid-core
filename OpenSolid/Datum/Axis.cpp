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

#include <OpenSolid/Datum/Axis.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    Axis<dimensions_>::Axis() {}
    
    template <int dimensions_>
    Axis<dimensions_>::Axis(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, 1>& direction
    ) : Datum<dimensions_, 1>(origin, direction.normalized()) {}

    template <int dimensions_>
    Axis<dimensions_>::Axis(const Datum<dimensions_, 1>& other) :
        Datum<dimensions_, 1>(other) {assert(other.basis().squaredNorm() == One());}

    template <int dimensions_>
    Axis<dimensions_>& Axis<dimensions_>::operator=(const Datum<dimensions_, 1>& other) {
        assert(other.basis().squaredNorm() == One());
        Datum<dimensions_, 1>::operator=(other);
        return *this;
    }
    
    template class Axis<1>;
    template class Axis<2>;
    template class Axis<3>;
    template class Axis<Dynamic>;
}
