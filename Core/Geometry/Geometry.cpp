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

#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Scalar/Comparison.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Geometry/SerializedGeometry.pb.h>
#include <OpenSolid/Core/Geometry/GeometryImplementation/GeometryImplementation.hpp>
#include <OpenSolid/Core/Geometry/GeometryImplementation/ConstantGeometry.hpp>
#include <OpenSolid/Core/Geometry/GeometryImplementation/GenericGeometry.hpp>
#include <OpenSolid/Core/Geometry/GeometryImplementation/SimplexGeometry.hpp>

namespace OpenSolid
{
    Geometry::Geometry() : _implementation(), _type(nullptr) {}

    Geometry::Geometry(const GeometryImplementation* implementation) :
        _implementation(implementation), _type(&typeid(implementation)) {}
    
    Geometry::Geometry(const Function& function, const Domain& domain) :
        _implementation(new GenericGeometry(function, domain)), _type(&typeid(GenericGeometry)) {
        assert(function.isConstant() || domain.dimensions() == function.parameters());
    }
    
    Geometry::Geometry(int value) :
        _implementation(new ConstantGeometry(VectorXd::Constant(1, value))),
        _type(&typeid(ConstantGeometry)) {}
    
    Geometry::Geometry(double value) :
        _implementation(new ConstantGeometry(VectorXd::Constant(1, value))),
        _type(&typeid(ConstantGeometry)) {}
    
    Geometry::Geometry(const VectorXd& vector) :
        _implementation(new ConstantGeometry(vector)), _type(&typeid(ConstantGeometry)) {}
    
    Geometry::Geometry(const SimplexXd& simplex) :
        _implementation(new SimplexGeometry(simplex)), _type(&typeid(SimplexGeometry)) {}

    const GeometryImplementation* Geometry::implementation() const {return _implementation.get();}
    
    Function Geometry::function() const {return implementation()->function();}
    
    Domain Geometry::domain() const {return implementation()->domain();}

    void Geometry::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        implementation()->evaluate(parameter_values, results);
    }

    void Geometry::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        implementation()->evaluate(parameter_bounds, results);
    }
    
    int Geometry::parameters() const {return implementation()->parameters();}
    
    int Geometry::dimensions() const {return implementation()->dimensions();}
    
    bool Geometry::isConstant() const {return implementation()->isConstant();}
    
    VectorXI Geometry::bounds() const {return implementation()->bounds();}
    
    Set<Geometry> Geometry::boundaries() const {return implementation()->boundaries();}

    Geometry Geometry::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return implementation()->transformed(matrix, vector);
    }

    Geometry Geometry::reversed() const {return implementation()->reversed();}

    VectorXI Bounds<Geometry>::operator()(const Geometry& argument) const {
        return argument.bounds();
    }
    
    double Conversion<Geometry, double>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 1);
        return argument.function().as<double>();
    }
    
    Vector2d Conversion<Geometry, Vector2d>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 2);
        return argument.function().as<Vector2d>();
    }
    
    Vector3d Conversion<Geometry, Vector3d>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 3);
        return argument.function().as<Vector3d>();
    }
    
    VectorXd Conversion<Geometry, VectorXd>::operator()(const Geometry& argument) const {
        assert(argument.isConstant());
        return argument.function().as<VectorXd>();
    }

    std::string TypeName<Geometry>::operator()() const {return "Geometry";}

    std::string Serialization<Geometry>::operator()(const Geometry& argument) const {
        throw NotImplementedError(__FILE__, __LINE__);
    }

    Geometry Deserialization<Geometry>::operator()(const std::string& argument) const {
        throw NotImplementedError(__FILE__, __LINE__);
    }
}
