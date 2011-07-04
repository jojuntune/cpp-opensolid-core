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

#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
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
    
    std::pair<Function, Function> mergedFunctions(
        const Function& first_operand,
        const Function& second_operand
    ) {
        if (first_operand.isA<ConstantFunction>() || second_operand.isA<ConstantFunction>()) {
            return std::pair<Function, Function>(first_operand, second_operand);
        }
        int first_parameters = first_operand.parameters();
        int second_parameters = second_operand.parameters();
        int total = first_parameters + second_parameters;
        return std::pair<Function, Function>(
            first_operand(Function::Parameters(total, 0, first_parameters)),
            second_operand(Function::Parameters(total, first_parameters, second_parameters))
        );
    }
    
    Geometry Geometry::concatenate(const Geometry& other) const {
        std::pair<Function, Function> functions = mergedFunctions(function(), other.function());
        return Geometry(
            functions.first.concatenate(functions.second),
            domain().concatenate(other.domain())
        );
    }
    
    Geometry Geometry::dot(const Geometry& other) const {
        std::pair<Function, Function> functions = mergedFunctions(function(), other.function());
        return Geometry(
            functions.first.dot(functions.second),
            domain().concatenate(other.domain())
        );
    }
    
    Geometry Geometry::cross(const Geometry& other) const {
        std::pair<Function, Function> functions = mergedFunctions(function(), other.function());
        return Geometry(
            functions.first.cross(functions.second),
            domain().concatenate(other.domain())
        );
    }
    
    Geometry Geometry::tangent() const {return Geometry(function().tangent(), domain());}
    
    Geometry Geometry::curvature() const {return Geometry(function().curvature(), domain());}
    
    Geometry Geometry::normal() const {return Geometry(function().normal(), domain());}
    
    Geometry Geometry::binormal() const {return Geometry(function().binormal(), domain());}
    
    Geometry Geometry::Line(const VectorXD& start, const VectorXD& end) {
        return Geometry(start + Function::t * (end - start), Interval(0, 1));
    }
    
    Geometry Geometry::Arc(Double radius, const Interval& angle) {
        Vector2D x_vector = radius * Vector2D::UnitX();
        Vector2D y_vector = radius * Vector2D::UnitY();
        return Geometry(cos(Function::t) * x_vector + sin(Function::t) * y_vector, angle);
    }
    
    Geometry Geometry::Arc(
        const Vector2D& center,
        const Vector2D& start,
        const Vector2D& end,
        bool counterclockwise
    ) {
        Vector2D start_radial = start - center;
        Double radius = start_radial.norm();
        Vector2D end_radial = end - center;
        assert(end_radial.norm().isEqualTo(radius));
        Vector2D perpendicular = start_radial.unitOrthogonal() * radius;
        if (!counterclockwise) {perpendicular = -perpendicular;}
        Double angle = atan2(end_radial.dot(perpendicular), end_radial.dot(start_radial));
        if (angle.isLessThanOrEqualTo(0.0)) {angle += 2 * M_PI;}
        return Geometry(
            center + cos(Function::t) * start_radial + sin(Function::t) * perpendicular,
            Interval(0, angle)
        );
    }
    
    Geometry Geometry::Arc(
        const Axis3D& axis,
        const Vector3D& start,
        const Vector3D& end
    ) {
        Vector3D center = (start / axis) * axis;
        Vector3D start_radial = start - center;
        Vector3D end_radial = end - center;
        assert(end_radial.isOrthogonal(axis.vector()));
        Double radius = start_radial.norm();
        assert(end_radial.norm().isEqualTo(radius));
        Vector3D perpendicular = axis.vector().cross(start_radial).normalized() * radius;
        Double angle = atan2(end_radial.dot(perpendicular), end_radial.dot(start_radial));
        if (angle.isLessThanOrEqualTo(0.0)) {angle += 2 * M_PI;}
        return Geometry(
            center + cos(Function::t) * start_radial + sin(Function::t) * perpendicular,
            Interval(0, angle)
        );
    }
    
    Geometry Geometry::Circle(Double radius) {
        Interval angle(0, 2 * M_PI);
        Function theta = Function::Parameter(1, 0);
        return Geometry(Function(radius * cos(theta), radius * sin(theta)), angle);
    }
    
    Geometry Geometry::Helix(Double radius, Double pitch, const Interval& angle) {
        Function theta = Function::Parameter(1, 0);
        return Geometry(
            Function(radius * cos(theta), radius * sin(theta), theta * (pitch / (2 * M_PI))),
            angle
        );
    }

    inline Geometry operator-(const Geometry& argument) {
        return Geometry(-argument.function(), argument.domain());
    }
    
    inline Geometry operator+(const Geometry& first_operand, const Geometry& second_operand) {
        std::pair<Function, Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first + functions.second,
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    inline Geometry operator-(const Geometry& first_operand, const Geometry& second_operand) {
        std::pair<Function, Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first - functions.second,
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    Geometry operator*(const Geometry& first_operand, const Geometry& second_operand) {
        std::pair<Function, Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first * functions.second,
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    Geometry operator/(const Geometry& first_operand, const Geometry& second_operand) {
        std::pair<Function, Function> functions = mergedFunctions(
            first_operand.function(),
            second_operand.function()
        );
        return Geometry(
            functions.first / functions.second,
            first_operand.domain().concatenate(second_operand.domain())
        );
    }
    
    Geometry operator*(const Geometry& geometry, const DatumXD& datum) {
        return Geometry(geometry.function() * datum, geometry.domain());
    }
    
    Geometry operator/(const Geometry& geometry, const DatumXD& datum) {
        return Geometry(geometry.function() / datum, geometry.domain());
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
