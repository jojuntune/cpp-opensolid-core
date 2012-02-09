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

#include <OpenSolid/Datum/CoordinateSystem.hpp>
#include <OpenSolid/Domain/DomainImplementation/VectorXIDomain.hpp>

namespace OpenSolid
{
    VectorXIDomain::VectorXIDomain(const VectorXI& bounds) : _bounds(bounds) {}

    Set<Geometry> VectorXIDomain::boundaries() const {
        Set<Geometry> results;
        if (_bounds.size() == 1) {
            results.insert(_bounds.value().lower());
            results.insert(_bounds.value().upper());
        } else {
            VectorXd origin;
            MatrixXd basis;
            for (int i = 0; i < _bounds.size(); ++i) {
                origin = _bounds.cwiseLower();

                origin = _bounds.cwiseUpper();
            }
        }
        return results;


        Set<Geometry> results;
        if (dims == 1) {
            results.insert(_bounds.value().lower());
            results.insert(_bounds.value().upper());
        } else {
            CoordinateSystemXd boundary_coordinate_system;
            VectorXI boundary_domain = _bounds.tail(dims - 1);
            MatrixXd boundary_basis = MatrixXd::Zero(dims, dims - 1);
            boundary_basis.diagonal(-1).setOnes();
            VectorXd boundary_origin = VectorXd::Zero(dims, 0);
            boundary_origin(0) = _bounds(0).lower();
            boundary_coordinate_system = CoordinateSystemXd(boundary_origin, boundary_basis);
            results.insert(Geometry(Function::Linear(boundary_coordinate_system), boundary_domain));
            boundary_origin(0) = _bounds(0).upper();
            boundary_coordinate_system = CoordinateSystemXd(boundary_origin, boundary_basis);
            results.insert(Geometry(Function::Linear(coordinate_system), geometry_domain_bounds));
            for (int i = 1; i < dims; ++i) {
                geometry_domain_bounds(i - 1) = _bounds(i - 1);
                geometry_basis(i, i - 1) = 0;
                geometry_basis(i - 1, i - 1) = 1;
                geometry_origin(i - 1) = 0;
                geometry_origin(i) = _bounds(i).lower();
                coordinate_system = CoordinateSystemXd(geometry_domain_origin, geometry_domain_basis);
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
