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

#include <OpenSolid/Core/Geometry/GenericGeometry.hpp>

// Public headers
#include <OpenSolid/Core/Geometry.hpp>

// Internal headers
#include <OpenSolid/Core/Function/ResultCache.hpp>

namespace opensolid
{
    GenericGeometry::GenericGeometry(const Function& function, const Domain& domain) :
        _function(function),
        _domain(domain) {
    }

    Function GenericGeometry::function() const {
        return _function;
    }

    Domain GenericGeometry::domain() const {
        return _domain;
    }

    int GenericGeometry::numParameters() const {
        return _function.numParameters();
    }

    int GenericGeometry::numDimensions() const {
        return _function.numDimensions();
    }

    void GenericGeometry::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        if (!_function.isValid()) {
            assert(false);
            return;
        }
        _function.implementation()->evaluate(parameterValues, results, cache);
    }

    void GenericGeometry::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        if (!_function.isValid()) {
            assert(false);
            return;
        }
        _function.implementation()->evaluate(parameterBounds, results, cache);
    }
}
