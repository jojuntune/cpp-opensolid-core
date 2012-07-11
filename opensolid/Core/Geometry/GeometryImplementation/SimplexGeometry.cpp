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
 
#include <OpenSolid/Core/Geometry/GeometryImplementation/SimplexGeometry.hpp>

#include <OpenSolid/Core/Geometry/Geometry.hpp>

namespace opensolid
{
    SimplexGeometry::SimplexGeometry(const SimplexXd& simplex) : _simplex(simplex) {}

    Function SimplexGeometry::function() const {
        return Function::Linear(_simplex.coordinateSystem());
    }
    
    Domain SimplexGeometry::domain() const {return Domain::UnitSimplex(parameters());}
        
    int SimplexGeometry::parameters() const {return _simplex.size() - 1;}
    
    int SimplexGeometry::dimensions() const {return _simplex.dimensions();}

    void SimplexGeometry::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        results = parameter_values * _simplex.coordinateSystem();
    }

    void SimplexGeometry::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        results = parameter_bounds * _simplex.coordinateSystem();
    }
    
    bool SimplexGeometry::isConstant() const {return false;}
    
    VectorXI SimplexGeometry::bounds() const {return _simplex.bounds();}
    
    Set<Geometry> SimplexGeometry::boundaries() const {
        Set<Geometry> results;
        for (int i = 0; i < _simplex.size(); ++i) {
            results.insert(new SimplexGeometry(_simplex.face(i)));
        }
        return results;
    }

    Geometry SimplexGeometry::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return new SimplexGeometry(_simplex.transformed(matrix, vector));
    }

    Geometry SimplexGeometry::reversed() const {
        return new SimplexGeometry(SimplexXd(_simplex.vertex(1), _simplex.vertex(0)));
    }
}
