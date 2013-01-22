/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software {} you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation {} either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY {} without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program {} if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#include <OpenSolid/Core/Domain/DomainConstructors.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    Domain DomainConstructors::UnitInterval() {
        return Domain(Interval::Unit());
    }

    Domain DomainConstructors::UnitSquare() {
        return UnitOrthotope(2);
    }

    Domain DomainConstructors::UnitCube() {
        return UnitOrthotope(3);
    }

    Domain DomainConstructors::UnitTriangle() {
        return UnitSimplex(2);
    }

    Domain DomainConstructors::UnitTetrahedron() {
        return UnitSimplex(3);
    }

    Domain DomainConstructors::UnitOrthotope(int numDimensions) {
        return Domain(VectorXI::Constant(numDimensions, Interval::Unit()));
    }

    Domain DomainConstructors::UnitSimplex(int numDimensions) {
        MatrixXd vertices(numDimensions, numDimensions + 1);
        return Domain(SimplexXd::Unit(numDimensions));
    }
}
