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
 
#include <OpenSolid/Geometry/GeometryImplementation/SimplexGeometry.hpp>

namespace OpenSolid
{
    SimplexGeometry::SimplexGeometry(const SimplexXd& simplex) : _simplex(simplex) {}

    Function SimplexGeometry::function() const {
        return Function::Linear(_simplex.coordinateSystem());
    }
    
    Domain SimplexGeometry::domain() const {
        MatrixXd unit_vertices(_simplex.size() - 1, _simplex.size());
        unit_vertices.col(0).setZero();
        unit_vertices.rightCols(_simplex.size() - 1).setIdentity();
        SimplexXd domain_simplex(unit_vertices);
        Set<Geometry> domain_boundaries;
        for (int i = 0; i < _simplex.size(); ++i) {
            domain_boundaries.insert(new SimplexGeometry(domain_simplex.face(i)));
        }
        return Domain(domain_boundaries);
    }
        
    int SimplexGeometry::parameters() const {return _simplex.size() - 1;}
    
    int SimplexGeometry::dimensions() const {return _simplex.dimensions();}
    
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
