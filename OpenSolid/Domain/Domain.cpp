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
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    Set<Geometry> rectangularBoundaries(const VectorXI& bounds) {
        int dims = bounds.size();
        Set<Geometry> results;
        if (dims == 1) {
            results.insert(bounds.value().lower());
            results.insert(bounds.value().upper());
        } else {
            VectorXI geometry_domain_bounds = bounds.tail(dims - 1);
            MatrixXd geometry_domain_unit_vectors = MatrixXd::Zero(dims, dims - 1);
            geometry_domain_unit_vectors.diagonal(-1).setOnes();
            VectorXd geometry_domain_origin = VectorXd::Zero(dims, 0);
            geometry_domain_origin(0) = bounds(0).lower();
            results.insert(
                Geometry(
                    Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                    geometry_domain_bounds
                )
            );
            geometry_domain_origin(0) = bounds(0).upper();
            results.insert(
                Geometry(
                    Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                    geometry_domain_bounds
                )
            );
            for (int i = 1; i < dims; ++i) {
                geometry_domain_bounds(i - 1) = bounds(i - 1);
                geometry_domain_unit_vectors(i, i - 1) = 0;
                geometry_domain_unit_vectors(i - 1, i - 1) = 1;
                geometry_domain_origin(i - 1) = 0;
                geometry_domain_origin(i) = bounds(i).lower();
                results.insert(
                    Geometry(
                        Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                        geometry_domain_bounds
                    )
                );
                geometry_domain_origin(i) = bounds(i).upper();
                results.insert(
                    Geometry(
                        Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                        geometry_domain_bounds
                    )
                );
            }
        }
        return results;
    }
    
    Domain::Domain() : _boundaries() {}
    
    Domain::Domain(const Set<Geometry>& boundaries) : _boundaries(boundaries) {}
    
    Domain::Domain(const Interval& bounds) {
        _boundaries = rectangularBoundaries(VectorXI::Constant(1, bounds));
    }
    
    Domain::Domain(const VectorXI& bounds) {_boundaries = rectangularBoundaries(bounds);}
    
    const Set<Geometry>& Domain::boundaries() const {return _boundaries;}
    
    bool Domain::isEmpty() const {return boundaries().isEmpty();}
    
    int Domain::dimensions() const {return bounds().size();}
    
    VectorXI Domain::bounds() const {
        assert(!isEmpty());
        return boundaries().bounds();
    }

    Domain Domain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
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
    
    Interval Conversion<Domain, Interval>::operator()(const Domain& argument) const {
        assert(!argument.isEmpty());
        assert(argument.dimensions() == 1);
        assert(argument.boundaries().size() == 2);
        return argument.bounds().value();
    }
}
