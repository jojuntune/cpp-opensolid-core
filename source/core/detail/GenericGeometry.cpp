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

#include <opensolid/detail/GenericGeometry.hpp>

#include <opensolid/Geometry.hpp>

namespace opensolid
{
    GenericGeometry::GenericGeometry(const Function& function, const Domain& domain) :
        _function(function), _domain(domain) {}

    Function GenericGeometry::function() const {return _function;}

    Domain GenericGeometry::domain() const {return _domain;}

    int GenericGeometry::parameters() const {return _function.parameters();}

    int GenericGeometry::dimensions() const {return _function.dimensions();}

    void GenericGeometry::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        _function.evaluate(parameter_values, results);
    }

    void GenericGeometry::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        _function.evaluate(parameter_bounds, results);
    }
}
