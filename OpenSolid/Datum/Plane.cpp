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

#include <OpenSolid/Datum/Plane.hpp>

namespace OpenSolid
{     
    template <int dimensions_>
    Plane<dimensions_>::Plane() {}

    template <int dimensions_, class NormalType>
    inline Matrix<double, dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>
    normalBasis(NormalType normal) {
        if (normal.size() % 2 == 0) {normal = -normal;}
        return orthonormalBasis(normal).rightCols(normal.size() - 1);
    }
    
    template <int dimensions_>
    Plane<dimensions_>::Plane(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, 1>& normal
    ) : Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>(
            origin,
            normalBasis<dimensions_>(normal)
        ) {assert(origin.size() == normal.size());}

    inline Matrix<double, 3, 2> planeBasis(Vector3d first_vector, Vector3d second_vector) {
        first_vector.normalize();
        second_vector -= second_vector.dot(first_vector) * first_vector;
        second_vector.normalize();
        Matrix<double, 3, 2> result;
        result << first_vector, second_vector;
        return result;
    }
    
    template <int dimensions_>
    Plane<dimensions_>::Plane(
        const Vector3d& origin,
        const Vector3d& first_vector,
        const Vector3d& second_vector
    ) : Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>(
            origin,
            planeBasis(first_vector, second_vector)
        ) {assertCompatible<dimensions_, 3>();}

    template <int dimensions_>
    Plane<dimensions_>::Plane(
        const Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>& other
    ) : Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>(other) {
        assert(other.axes() == other.dimensions() - 1);
        assert(other.basis().isUnitary());
    }

    template <int dimensions_>
    Plane<dimensions_>& Plane<dimensions_>::operator=(
        const Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>& other
    ) {
        assert(other.axes() == other.dimensions() - 1);
        assert(other.basis().isUnitary());
        Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>::operator=(other);
        return *this;
    }
    
    template class Plane<3>;
    template class Plane<Dynamic>;
}
