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

#include <opensolid/value/Tolerance.hpp>
#include "Geometry.hpp"

namespace opensolid
{
    Geometry Geometry::derivative(int parameter_index) const {
        return Geometry(function().derivative(parameter_index), domain());
    }
    
    Geometry Geometry::norm() const {return Geometry(function().norm(), domain());}
    
    Geometry Geometry::normalized() const {return Geometry(function().normalized(), domain());}
    
    Geometry Geometry::squaredNorm() const {return Geometry(function().squaredNorm(), domain());}
    
    Geometry Geometry::component(int index) const {
        return Geometry(function().component(index), domain());
    }
    
    Geometry Geometry::components(int index, int num) const {
        return Geometry(function().components(index, num), domain());
    }
    
    Pair<Function> mergedFunctions(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isA<ConstantFunction>() || second_operand.isA<ConstantFunction>()) {
            return Pair<Function>(first_operand, second_operand);
        }
        int first_parameters = first_operand.parameters();
        int second_parameters = second_operand.parameters();
        int total = first_parameters + second_parameters;
        return Pair<Function>(
            first_operand(Function::Parameters(total, 0, first_parameters)),
            second_operand(Function::Parameters(total, first_parameters, second_parameters))
        );
    }
    
    Geometry Geometry::concatenate(const Geometry& other) const {
        Pair<Function> functions = mergedFunctions(function(), other.function());
        return Geometry(
            functions.first().concatenate(functions.second()),
            domain().concatenate(other.domain())
        );
    }
    
    Geometry Geometry::dot(const Geometry& other) const {
        Pair<Function> functions = mergedFunctions(function(), other.function());
        return Geometry(
            functions.first().dot(functions.second()),
            domain().concatenate(other.domain())
        );
    }
    
    Geometry Geometry::cross(const Geometry& other) const {
        Pair<Function> functions = mergedFunctions(function(), other.function());
        return Geometry(
            functions.first().cross(functions.second()),
            domain().concatenate(other.domain())
        );
    }
    
    Geometry Geometry::tangent() const {return Geometry(function().tangent(), domain());}
    
    Geometry Geometry::curvature() const {return Geometry(function().curvature(), domain());}
    
    Geometry Geometry::normal() const {return Geometry(function().normal(), domain());}
    
    Geometry Geometry::binormal() const {return Geometry(function().binormal(), domain());}
    
    Geometry Geometry::Line(const VectorXd& start, const VectorXd& end) {
        return Geometry(Function::Linear(start, end - start), Interval(0, 1));
    }
        
    Geometry Geometry::Arc2d(const Frame2d& frame, const Interval& angle) {
        
    }
    
    Geometry Geometry::Arc2d(const Vector2d& center, const Interval& angle) {
        
    }
    
    Geometry Geometry::Arc2d(
        const Vector2d& center,
        bool counterclockwise,
        const Vector2d& start,
        const Vector2d& end
    ) {
        
    }
    
    Geometry Geometry::Circle2d(const Vector2d& center);
    
    Geometry Geometry::Arc3d(const Plane3d& plane, const Interval& angle);
    
    Geometry Geometry::Arc3d(
        const Axis3d& axis,
        const Vector3d& start,
        const Vector3d& end
    ) {
        Vector3d start_radial = start - axis.origin();
        Vector3d end_radial = end - axis.origin();
        assert(start_radial.isOrthogonal(axis.unitVector(), Tolerance::roundoff()));
        assert(end_radial.isOrthogonal(axis.unitVector(), Tolerance::roundoff()));
        double radius = start_radial.norm();
        Matrix<double, 3, 2> radial_vectors;
        radial_vectors << start_radial, axis.unitVector().cross(start_radial).normalized() * radius;
        double angle = atan2(end_radial.dot(radial_vectors.col(1)), end_radial.dot(start_radial));
        if (angle < Tolerance::roundoff()) {angle += 2 * M_PI;}
        return Geometry(
            Function::Elliptical(
                center,
                radial_vectors,
                VectorXb::Constant(1, true)
            ),
            Interval(0, angle)
        );
    }
    
    Geometry Geometry::Circle3d(const Axis3d& axis);

    inline Geometry operator-(const Geometry& argument) {
        return Geometry(-argument.function(), argument.domain());
    }
    
    inline Geometry operator+(const Geometry& first_operand, const Geometry& second_operand) {
        Pair<Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first() + functions.second(),
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    inline Geometry operator-(const Geometry& first_operand, const Geometry& second_operand) {
        Pair<Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first() - functions.second(),
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    Geometry operator*(const Geometry& first_operand, const Geometry& second_operand) {
        Pair<Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first() * functions.second(),
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    Geometry operator/(const Geometry& first_operand, const Geometry& second_operand) {
        Pair<Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first() / functions.second(),
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    Geometry cos(const Geometry& argument) {
        return Geometry(cos(argument.function()), argument.domain());
    }
    
    Geometry sin(const Geometry& argument) {
        return Geometry(sin(argument.function()), argument.domain());
    }
    
    Geometry sqrt(const Geometry& argument) {
        return Geometry(sqrt(argument.function()), argument.domain());
    }
}
