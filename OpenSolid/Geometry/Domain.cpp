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

#include "Domain.hpp"
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Collection/List.hpp>

namespace opensolid
{
    Set<Geometry> Domain::rectangularBoundaries(const VectorXI& bounds) {
        int dims = bounds.size();
        List<Geometry> list;
        if (dims == 1) {
            list.append(bounds.scalar().lower());
            list.append(bounds.scalar().upper());
        } else {
            VectorXI geometry_domain_bounds = bounds.tail(dims - 1);
            MatrixXd geometry_domain_unit_vectors = MatrixXd::Zero(dims, dims - 1);
            geometry_domain_unit_vectors.diagonal(-1).setOnes();
            VectorXd geometry_domain_origin = VectorXd::Zero(dims, 0);
            geometry_domain_origin(0) = bounds(0).lower();
            list.append(
                Geometry(
                    Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                    geometry_domain_bounds
                )
            );
            geometry_domain_origin(0) = bounds(0).upper();
            list.append(
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
                list.append(
                    Geometry(
                        Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                        geometry_domain_bounds
                    )
                );
                geometry_domain_origin(i) = bounds(i).upper();
                list.append(
                    Geometry(
                        Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                        geometry_domain_bounds
                    )
                );
            }
        }
        return Set<Geometry>(list);
    }
    
    Domain Domain::concatenate(const Domain& other) const {
        if (empty()) {return other;}
        if (other.empty()) {return *this;}
        List<Geometry> own_boundaries(boundaries());
        List<Geometry> other_boundaries(other.boundaries());
        List<Geometry> result_boundaries;
        result_boundaries.reserve(own_boundaries.size() + other_boundaries.size());
        List<Geometry>::Iterator i;
        for (i = own_boundaries.begin(); i != own_boundaries.end(); ++i) {
            result_boundaries.append(i->concatenate(Function::Identity(other.dimensions())(other)));
        }
        for (i = other_boundaries.begin(); i != other_boundaries.end(); ++i) {
            result_boundaries.append(Function::Identity(dimensions())(*this).concatenate(*i));
        }
        return Set<Geometry>(result_boundaries);
    }
}
