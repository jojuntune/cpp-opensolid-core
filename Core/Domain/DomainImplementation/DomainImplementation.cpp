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

#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Domain/DomainImplementation/DomainImplementation.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>

namespace OpenSolid
{
    DomainImplementation::~DomainImplementation() {}

    bool DomainImplementation::isEmpty() const {return boundaries().isEmpty();}

    int DomainImplementation::dimensions() const {return bounds().size();}

    VectorXI DomainImplementation::bounds() const {return boundaries().bounds();}

    Domain DomainImplementation::transformed(
        const MatrixXd& matrix,
        const VectorXd& vector
    ) const {
        assertValidTransform<Dynamic>(dimensions(), matrix, vector);
        Set<Geometry> transformed_boundaries;
        boundaries().transform(
            [&matrix, &vector] (const Geometry& boundary) {
                return boundary.transformed(matrix, vector);
            },
            transformed_boundaries.inserter()
        );
        return Domain(transformed_boundaries);
    }
}
