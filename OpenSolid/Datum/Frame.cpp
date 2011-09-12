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

#include <OpenSolid/Datum/Frame.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    inline Matrix<double, dimensions_, 1> defaultOrigin() {
        Matrix<double, dimensions_, 1> result;
        if (dimensions_ != Dynamic) {result.setZero();}
        return result;
    }

    template <int dimensions_>
    inline Matrix<double, dimensions_, dimensions_> defaultBasis() {
        Matrix<double, dimensions_, dimensions_> result;
        if (dimensions_ != Dynamic) {result.setIdentity();}
        return result;
    }

    template <int dimensions_>
    Frame<dimensions_>::Frame() :
        Datum<dimensions_, dimensions_>(
            defaultOrigin<dimensions_>(),
            defaultBasis<dimensions_>()
        ) {}
    
    template <int dimensions_>
    Frame<dimensions_>::Frame(int size) :
        Datum<dimensions_, dimensions_>(
            Matrix<double, dimensions_, 1>::Zero(size),
            Matrix<double, dimensions_, dimensions_>::Identity(size, size)
        ) {assertCompatible<dimensions_>(size);}
        
    template <int dimensions_>
    Frame<dimensions_>::Frame(const Matrix<double, dimensions_, 1>& origin) :
        Datum<dimensions_, dimensions_>(
            origin,
            Matrix<double, dimensions_, dimensions_>::Identity(origin.size(), origin.size())
        ) {assertCompatible<dimensions_>(origin.size());}

    template <int dimensions_>
    Frame<dimensions_>::Frame(const Datum<dimensions_, dimensions_>& other) :
        Datum<dimensions_, dimensions_>(other) {
        assert(other.dimensions() == other.axes());
        assert(other.basis().isUnitary());
    }

    template <int dimensions_>
    Frame<dimensions_>& Frame<dimensions_>::operator=(
        const Datum<dimensions_, dimensions_>& other
    ) {
        assert(other.dimensions() == other.axes());
        assert(other.basis().isUnitary());
        Datum<dimensions_, dimensions_>::operator=(other);
        return *this;
    }
    
    template class Frame<1>;
    template class Frame<2>;
    template class Frame<3>;
    template class Frame<Dynamic>;
}
