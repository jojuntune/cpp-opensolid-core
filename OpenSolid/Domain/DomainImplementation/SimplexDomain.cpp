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

#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Domain/DomainImplementation/SimplexDomain.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    SimplexDomain::SimplexDomain(const SimplexXd& simplex) : _simplex(simplex) {
        assert(simplex.dimensions() == simplex.size() - 1);
    }

    Set<Geometry> SimplexDomain::boundaries() const {
        Set<Geometry> results;
        for (int i = 0; i < _simplex.size(); ++i) {results.insert(_simplex.face(i));}
        return results;
    }

    bool SimplexDomain::isEmpty() const {return false;}

    int SimplexDomain::dimensions() const {return _simplex.dimensions();}

    VectorXI SimplexDomain::bounds() const {return _simplex.bounds();}

    Domain SimplexDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return new SimplexDomain(_simplex.transformed(matrix, vector));
    }
}
