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

#include <opensolid/Core/Mesh/Mesh.hpp>

#include <opensolid/Core/Common/Error.hpp>

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
        if (geometry.parameters() != 1) {
            // Only supports curves for now
            throw NotImplementedError("Mesh.cpp", __LINE__);
        }
        std::vector<double> temp;
        Function function = geometry.function();
        Function derivative = function.derivative();
        Interval domain = geometry.domain().convertTo<Interval>();
        getParameterValues(
            function,
            derivative,
            domain,
            linear_deviation,
            temp
        );
        temp.push_back(domain.upper());
        RowVectorXd parameter_values(1, temp.size());
        std::copy(temp.begin(), temp.end(), begin(parameter_values));
        _vertices = function(parameter_values);
    }
}
