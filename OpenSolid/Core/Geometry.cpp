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

#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    Geometry::Geometry() {
    }
    
    Geometry::Geometry(const Function& function, const Domain& domain) :
        _function(function),
        _domain(domain),
        _bounds(function(domain.bounds())) {

        assert(function.numParameters() == domain.numDimensions());
    }

    Geometry::Geometry(const LineSegment2d& lineSegment) :
        _function(Function::Linear(lineSegment.datum())),
        _domain(Interval::Unit()),
        _bounds(lineSegment.bounds()) {
    }

    Geometry::Geometry(const Triangle2d& triangle) :
        _function(Function::Linear(triangle.datum())),
        _domain(Triangle2d::Unit()),
        _bounds(triangle.bounds()) {
    }

    Geometry::Geometry(const LineSegment3d& lineSegment) :
        _function(Function::Linear(lineSegment.datum())),
        _domain(Interval::Unit()),
        _bounds(lineSegment.bounds()) {
    }

    Geometry::Geometry(const Triangle3d& triangle) :
        _function(Function::Linear(triangle.datum())),
        _domain(Triangle2d::Unit()),
        _bounds(triangle.bounds()) {
    }

    Geometry::Geometry(const Tetrahedron3d& tetrahedron) :
        _function(Function::Linear(tetrahedron.datum())),
        _domain(Tetrahedron3d::Unit()),
        _bounds(tetrahedron.bounds()) {
    }
    
    int
    Geometry::numParameters() const {
        return function().numParameters();
    }
    
    int
    Geometry::numDimensions() const {
        return function().numDimensions();
    }
    
    Set<Geometry>
    Geometry::boundaries() const {
        Set<Geometry> results;
        domain().boundaries().transform(
            [this] (const Geometry& domainBoundary) {
                return Geometry(function()(domainBoundary.function()), domainBoundary.domain());
            },
            results.inserter()
        );
        return results;
    }

    Geometry Geometry::reversed() const {
        if (numParameters() == 1) {
            Interval interval = domain().as<Interval>();
            Function reversedParameter =
                interval.lowerBound() + interval.upperBound() - Function::t();
            return Geometry(function()(reversedParameter), domain());
        } else {
            assert(false);
            return Geometry();
        }
    }

    Geometry
    operator*(double multiplier, const Geometry& geometry) {
        return Geometry(multiplier * geometry.function(), geometry.domain());
    }

    Geometry
    operator*(const MatrixXd& matrix, const Geometry& geometry) {
        return Geometry(matrix * geometry.function(), geometry.domain());
    }

    Geometry
    operator+(const Geometry& geometry, const VectorXd& vector) {
        return Geometry(geometry.function() + vector, geometry.domain());
    }


    VectorXI Bounds<Geometry>::operator()(const Geometry& geometry) const {
        return geometry.bounds();
    }
    
    double Conversion<Geometry, double>::operator()(const Geometry& geometry) const {
        assert(geometry.function().asConstant());
        assert(geometry.numDimensions() == 1);
        return geometry.function().as<double>();
    }
    
    Vector2d Conversion<Geometry, Vector2d>::operator()(const Geometry& geometry) const {
        assert(geometry.function().asConstant());
        assert(geometry.numDimensions() == 2);
        return geometry.function().as<Vector2d>();
    }
    
    Vector3d Conversion<Geometry, Vector3d>::operator()(const Geometry& geometry) const {
        assert(geometry.function().asConstant());
        assert(geometry.numDimensions() == 3);
        return geometry.function().as<Vector3d>();
    }
    
    VectorXd Conversion<Geometry, VectorXd>::operator()(const Geometry& geometry) const {
        assert(geometry.function().asConstant());
        return geometry.function().as<VectorXd>();
    }
}
