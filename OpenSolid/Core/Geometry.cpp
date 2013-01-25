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

#include "Geometry.hpp"

#include "Geometry/GeometryImplementation.hpp"
#include "Geometry/ConstantGeometry.hpp"
#include "Geometry/GenericGeometry.hpp"
#include "Geometry/SimplexGeometry.hpp"

#include <OpenSolid/Utils/Zero.hpp>
#include <OpenSolid/Core/Domain.hpp>

namespace opensolid
{
    Geometry::Geometry() :
        _implementation(),
        _type(nullptr) {
    }

    Geometry::Geometry(const GeometryImplementation* implementation) :
        _implementation(implementation),
        _type(&typeid(implementation)) {
    }
    
    Geometry::Geometry(const Function& function, const Domain& domain) :
        _implementation(new GenericGeometry(function, domain)),
        _type(&typeid(GenericGeometry)) {

        assert(function.isConstant() || domain.numDimensions() == function.numParameters());
    }
    
    Geometry::Geometry(int value) :
        _implementation(new ConstantGeometry(VectorXd::Constant(1, value))),
        _type(&typeid(ConstantGeometry)) {
    }
    
    Geometry::Geometry(double value) :
        _implementation(new ConstantGeometry(VectorXd::Constant(1, value))),
        _type(&typeid(ConstantGeometry)) {
    }
    
    Geometry::Geometry(const VectorXd& vector) :
        _implementation(new ConstantGeometry(vector)),
        _type(&typeid(ConstantGeometry)) {
    }
    
    Geometry::Geometry(const SimplexXd& simplex) :
        _implementation(new SimplexGeometry(simplex)),
        _type(&typeid(SimplexGeometry)) {
    }

    const GeometryImplementation* Geometry::implementation() const {
        return _implementation.get();
    }
    
    Function Geometry::function() const {
        return implementation()->function();
    }
    
    Domain Geometry::domain() const {
        return implementation()->domain();
    }

    void Geometry::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        implementation()->evaluate(parameterValues, results);
    }

    void Geometry::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        implementation()->evaluate(parameterBounds, results);
    }
    
    int Geometry::numParameters() const {
        return implementation()->numParameters();
    }
    
    int Geometry::numDimensions() const {
        return implementation()->numDimensions();
    }
    
    bool Geometry::isConstant() const {
        return implementation()->isConstant();
    }
    
    VectorXI Geometry::bounds() const {
        return implementation()->bounds();
    }
    
    Set<Geometry> Geometry::boundaries() const {
        return implementation()->boundaries();
    }

    Geometry Geometry::transformed(
        const MatrixXd& transformMatrix,
        const VectorXd& transformVector
    ) const {
        return implementation()->transformed(transformMatrix, transformVector);
    }

    Geometry Geometry::reversed() const {
        return implementation()->reversed();
    }

    Geometry operator*(double multiplier, const Geometry& geometry) {
        return geometry.transformed(
            multiplier * MatrixXd::Identity(geometry.numDimensions(), geometry.numDimensions()),
            VectorXd::Zero(geometry.numDimensions())
        );
    }

    VectorXI Bounds<Geometry>::operator()(const Geometry& geometry) const {
        return geometry.bounds();
    }
    
    double Conversion<Geometry, double>::operator()(const Geometry& geometry) const {
        assert(geometry.isConstant());
        assert(geometry.numDimensions() == 1);
        return geometry.function().as<double>();
    }
    
    Vector2d Conversion<Geometry, Vector2d>::operator()(const Geometry& geometry) const {
        assert(geometry.isConstant());
        assert(geometry.numDimensions() == 2);
        return geometry.function().as<Vector2d>();
    }
    
    Vector3d Conversion<Geometry, Vector3d>::operator()(const Geometry& geometry) const {
        assert(geometry.isConstant());
        assert(geometry.numDimensions() == 3);
        return geometry.function().as<Vector3d>();
    }
    
    VectorXd Conversion<Geometry, VectorXd>::operator()(const Geometry& geometry) const {
        assert(geometry.isConstant());
        return geometry.function().as<VectorXd>();
    }
}
