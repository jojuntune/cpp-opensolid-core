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

#include <OpenSolid/Core/GeometryImplementation.hpp>

#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/Domain.hpp>

#include <OpenSolid/Core/GeometryImplementation/GenericGeometry.hpp>
#include <OpenSolid/Core/Function/ResultCache.hpp>

namespace opensolid
{
    GeometryImplementation::~GeometryImplementation() {
    }
        
    int GeometryImplementation::numParameters() const {
        return function().numParameters();
    }

    int GeometryImplementation::numDimensions() const {
        return function().numDimensions();
    }
        
    void GeometryImplementation::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        const FunctionImplementation* functionImplementation = function().implementation();
        if (!functionImplementation) {
            assert(false);
            return;
        }
        functionImplementation->evaluate(parameterValues, results, cache);
    }
        
    void GeometryImplementation::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        const FunctionImplementation* functionImplementation = function().implementation();
        if (!functionImplementation) {
            assert(false);
            return;
        }
        functionImplementation->evaluate(parameterBounds, results, cache);
    }

    bool GeometryImplementation::isConstant() const {
        return function().asConstant() != 0;
    }

    VectorXI GeometryImplementation::bounds() const {
        Function function = this->function();
        if (function.asConstant()) {
            return function.as<VectorXd>().cast<Interval>();
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
        assertValidTransform<Dynamic>(numDimensions(), matrix, vector);
        return new GenericGeometry(matrix * function() + vector, domain());
    }

    Geometry GeometryImplementation::reversed() const {
        assert(numParameters() == 1);
        Interval interval = domain().as<Interval>();
        Function reversedParameter = interval.lowerBound() + interval.upperBound() - Function::t();
        return new GenericGeometry(function()(reversedParameter), domain());
    }
}
