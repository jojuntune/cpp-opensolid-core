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

#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>
#include <OpenSolid/Geometry/GeometryImplementation/GenericGeometry.hpp>

namespace OpenSolid
{
    Geometry::Geometry() : _implementation() {}

    Geometry::Geometry(const GeometryImplementation* implementation)
        : _implementation(implementation) {}
    
    Geometry::Geometry(const Function& function, const Domain& domain) :
        _implementation(new GenericGeometry(function, domain)), _type(&typeid(GenericGeometry)) {
        assert(function.isConstant() || domain.dimensions() == function.parameters());
    }
    
    Geometry::Geometry(double value) :
        _implementation(new ConstantGeometry(VectorXd::Constant(1, value))),
        _type(&typeid(ConstantGeometry)) {}
    
    Function Geometry::function() const {return implementation()->function();}
    
    Domain Geometry::domain() const {return implementation()->domain();}
    
    int Geometry::parameters() const {return implementation()->parameters();}
    
    int Geometry::dimensions() const {return implementation()->dimensions();}
    
    bool Geometry::isConstant() const {return implementation()->isConstant();}
    
    VectorXI Geometry::bounds() const {return implementation()->bounds();}
    
    Set<Geometry> Geometry::boundaries() const {return implementation()->boundaries();}

    Geometry Geometry::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return implementation()->transformed(matrix, vector);
    }

    Geometry Geometry::reversed() const {return implementation()->reversed();}
    
    double Conversion<Geometry, double>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 1);
        return argument.function().to<double>();
    }
    
    Vector2d Conversion<Geometry, Vector2d>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 2);
        return argument.function().to<Vector2d>();
    }
    
    Vector3d Conversion<Geometry, Vector3d>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 3);
        return argument.function().to<Vector3d>();
    }
    
    VectorXd Conversion<Geometry, VectorXd>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        return argument.function().to<VectorXd>();
    }
}
