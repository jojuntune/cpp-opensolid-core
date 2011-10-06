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

#include <OpenSolid/Geometry/Geometry.hpp>
#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Geometry/GeometryImplementation/GenericGeometry.hpp>
#include <OpenSolid/Geometry/GeometryImplementation/GeometryImplementation.hpp>

namespace OpenSolid
{
    GeometryImplementation::~GeometryImplementation() {}
        
    void GeometryImplementation::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        getValues(parameter_values, results);
    }
        
    void GeometryImplementation::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        getBounds(parameter_bounds, results);
    }
        
    int GeometryImplementation::parameters() const {return function().parameters();}

    int GeometryImplementation::dimensions() const {return function().dimensions();}
        
    void GeometryImplementation::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = function()(parameter_values);
    }
        
    void GeometryImplementation::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = function()(parameter_bounds);
    }

    bool GeometryImplementation::isConstant() const {return function().isConstant();}

    VectorXI GeometryImplementation::bounds() const {
        Function function = this->function();
        if (function.isConstant()) {
            return function.to<VectorXd>().cast<Interval>();
        } else {
            return function(domain().bounds());
        }
    }

    Set<Geometry> GeometryImplementation::boundaries() const {
        Set<Geometry> results;
        Function function = this->function();
        domain().boundaries().transform(
            [function] (const Geometry& domain_boundary) {
                return Geometry(
                    function(domain_boundary.function()),
                    domain_boundary.domain()
                );
            },
            results.inserter()
        );
        return results;
    }

    Geometry GeometryImplementation::transformed(
        const MatrixXd& matrix,
        const VectorXd& vector
    ) const {
        assertValidTransform<Dynamic>(dimensions(), matrix, vector);
        return new GenericGeometry(function().transformed(matrix, vector), domain());
    }

    Geometry GeometryImplementation::reversed() const {
        assert(parameters() == 1);
        Interval interval = domain().to<Interval>();
        Function reversed_parameter = interval.lower() + interval.upper() - Parameter();
        return new GenericGeometry(function()(reversed_parameter), domain());
    }
}
