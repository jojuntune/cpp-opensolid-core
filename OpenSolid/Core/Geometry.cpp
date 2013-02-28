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

#include <OpenSolid/Core/Geometry.hpp>

// Public headers
#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Zero.hpp>

// Internal headers
#include <OpenSolid/Core/Geometry/ConstantGeometry.hpp>
#include <OpenSolid/Core/Geometry/GenericGeometry.hpp>
#include <OpenSolid/Core/Geometry/GeometryImplementation.hpp>
#include <OpenSolid/Core/Geometry/SimplexGeometry.hpp>

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

        assert(domain.numDimensions() == function.numParameters());
    }
    
    Geometry::Geometry(double value, int numParameters) :
        _implementation(new ConstantGeometry(VectorXd::Constant(1, value), numParameters)),
        _type(&typeid(ConstantGeometry)) {
    }
    
    Geometry::Geometry(const VectorXd& vector, int numParameters) :
        _implementation(new ConstantGeometry(vector, numParameters)),
        _type(&typeid(ConstantGeometry)) {
    }

    Geometry::Geometry(const LineSegment2d& lineSegment) :
        _implementation(new SimplexGeometry<2, 2>(lineSegment)) ,
        _type(&typeid(SimplexGeometry<2, 2>)) {
    }

    Geometry::Geometry(const Triangle2d& triangle) :
        _implementation(new SimplexGeometry<2, 3>(triangle)) ,
        _type(&typeid(SimplexGeometry<2, 3>)) {
    }

    Geometry::Geometry(const LineSegment3d& lineSegment) :
        _implementation(new SimplexGeometry<3, 2>(lineSegment)) ,
        _type(&typeid(SimplexGeometry<3, 2>)) {
    }

    Geometry::Geometry(const Triangle3d& triangle) :
        _implementation(new SimplexGeometry<3, 3>(triangle)) ,
        _type(&typeid(SimplexGeometry<3, 3>)) {
    }

    Geometry::Geometry(const Tetrahedron3d& tetrahedron) :
        _implementation(new SimplexGeometry<3, 4>(tetrahedron)) ,
        _type(&typeid(SimplexGeometry<3, 4>)) {
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

    void Geometry::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        implementation()->evaluate(parameterValues, results, cache);
    }

    void Geometry::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        implementation()->evaluate(parameterBounds, results, cache);
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
