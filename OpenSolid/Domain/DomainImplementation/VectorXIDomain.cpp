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

#include <OpenSolid/Domain/DomainImplementation/VectorXIDomain.hpp>

namespace OpenSolid
{
    VectorXIDomain::VectorXIDomain(const VectorXI& bounds) : _bounds(bounds) {}

    Set<Geometry> VectorXIDomain::boundaries() const {
        Set<Geometry> results;
        return results;
    }

    bool VectorXIDomain::isEmpty() const {return _bounds.isEmpty();}

    int VectorXIDomain::dimensions() const {return _bounds.size();}

    VectorXI VectorXIDomain::bounds() const {return _bounds;}

    Domain VectorXIDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        if (matrix.isDiagonal()) {
            VectorXI result(_bounds.size());
            for (int i = 0; i < _bounds.size(); ++i) {
                result(i) = matrix(i, i) * _bounds(i) + vector(i);
            }
            return new VectorXIDomain(result);
        } else {
            return DomainImplementation::transformed(matrix, vector);
        }
    }
}
