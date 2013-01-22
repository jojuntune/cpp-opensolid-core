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
 
#include "ConstantGeometry.hpp"

#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    ConstantGeometry::ConstantGeometry(const VectorXd& vector) : _vector(vector) {}

    Function ConstantGeometry::function() const {return _vector;}

    Domain ConstantGeometry::domain() const {return Domain();}
        
    int ConstantGeometry::parameters() const {return 0;}

    int ConstantGeometry::dimensions() const {return _vector.size();}

    void ConstantGeometry::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        results.colwise() = _vector;
    }

    void ConstantGeometry::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        results.colwise() = _vector.cast<Interval>();
    }

    bool ConstantGeometry::isConstant() const {return true;}

    VectorXI ConstantGeometry::bounds() const {return _vector.cast<Interval>();}

    Set<Geometry> ConstantGeometry::boundaries() const {return Set<Geometry>();}

    Geometry ConstantGeometry::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return new ConstantGeometry(matrix * _vector + vector);
    }

    Geometry ConstantGeometry::reversed() const {return this;}
}
