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

namespace OpenSolid
{
    Set<Geometry, VectorXI> Domain::rectangularBoundaries(const VectorXI& bounds) {
        int dims = bounds.size();
        std::vector<Geometry> list;
        if (dims == 1) {
            list.push_back(bounds.lower());
            list.push_back(bounds.upper());
        } else {
            VectorXI geometry_domain_bounds = bounds.tail(dims - 1);
            MatrixXD geometry_domain_unit_vectors = MatrixXD::Zero(dims, dims - 1);
            geometry_domain_unit_vectors.diagonal(-1).setOnes();
            VectorXD geometry_domain_origin = VectorXD::Zero(dims, 0);
            geometry_domain_origin(0) = bounds(0).lower();
            list.push_back(
                Geometry(
                    Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                    geometry_domain_bounds
                )
            );
            geometry_domain_origin(0) = bounds(0).upper();
            list.push_back(
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
                list.push_back(
                    Geometry(
                        Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                        geometry_domain_bounds
                    )
                );
                geometry_domain_origin(i) = bounds(i).upper();
                list.push_back(
                    Geometry(
                        Function::Linear(geometry_domain_origin, geometry_domain_unit_vectors),
                        geometry_domain_bounds
                    )
                );
            }
        }
        return Set<Geometry>(list.begin(), list.end());
    }
    
    Domain Domain::concatenate(const Domain& other) const {
        if (empty()) {return other;}
        if (other.empty()) {return *this;}
        Set<Geometry, VectorXI> result_boundaries;
        for (auto i = boundaries().begin(); i != boundaries().end(); ++i) {
            result_boundaries.insert(
                i->concatenate(Function::Identity(other.dimensions())(other))
            );
        }
        for (auto i = other.boundaries().begin(); i != other.boundaries().end(); ++i) {
            result_boundaries.insert(
                Function::Identity(dimensions())(*this).concatenate(*i)
            );
        }
        return Domain(result_boundaries);
    }
}
