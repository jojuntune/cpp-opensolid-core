/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
 *  ian.e.mackenzie@gmail.com                                                        *
 *                                                                                   *
 *  This library is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU Lesser General Public                       *
 *  License as published by the Free Software Foundation; either                     *
 *  version 2.1 of the License, or (at your option) any later version.               *
 *                                                                                   *
 *  This library is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
 *  Lesser General Public License for more details.                                  *
 *                                                                                   *
 *  You should have received a copy of the GNU Lesser General Public                 *
 *  License along with this library; if not, write to the Free Software              *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
 *                                                                                   *
 *************************************************************************************/

#include <OpenSolid/Core/DomainImplementation.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    DomainImplementation::~DomainImplementation() {
    }

    bool DomainImplementation::isEmpty() const {
        return boundaries().isEmpty();
    }

    int DomainImplementation::numDimensions() const {
        return bounds().size();
    }

    VectorXI DomainImplementation::bounds() const {
        return boundaries().bounds();
    }

    Domain DomainImplementation::transformed(
        const MatrixXd& matrix,
        const VectorXd& vector
    ) const {
        assertValidTransform<Dynamic>(numDimensions(), matrix, vector);
        Set<Geometry> transformed_boundaries;
        boundaries().transform(
            [&matrix, &vector] (const Geometry& boundary) {
                return matrix * boundary + vector;
            },
            transformed_boundaries.inserter()
        );
        return Domain(transformed_boundaries);
    }
}
