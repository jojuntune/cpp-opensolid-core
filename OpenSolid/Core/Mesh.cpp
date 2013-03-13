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

#include <OpenSolid/Core/Mesh.hpp>

#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    void getParameterValues(
        const Function& function,
        const Function& derivative,
        const Interval& domain,
        double linear_deviation,
        std::vector<double>& results
    ) {

    }

    Mesh::Mesh(const Geometry& geometry, double linear_deviation) {
        if (geometry.numParameters() != 1) {
            // Only supports curves for now
            throw FeatureNotImplemented();
        }
        std::vector<double> temp;
        Function function = geometry.function();
        Function derivative = function.derivative();
        Interval domain = geometry.domain().as<Interval>();
        getParameterValues(
            function,
            derivative,
            domain,
            linear_deviation,
            temp
        );
        temp.push_back(domain.upperBound());
        RowVectorXd parameter_values(1, temp.size());
        std::copy(temp.begin(), temp.end(), begin(parameter_values));
        _vertices = function(parameter_values);
    }
}
