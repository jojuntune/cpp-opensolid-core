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

#include <OpenSolid/Geometry/Domain.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

#include "Function.hpp"
#include "implementations/ComponentsFunction.hpp"
#include "implementations/CompositionFunction.hpp"
#include "implementations/ConcatenationFunction.hpp"
#include "implementations/ConstantFunction.hpp"
#include "implementations/CosineFunction.hpp"
#include "implementations/CrossProductFunction.hpp"
#include "implementations/DifferenceFunction.hpp"
#include "implementations/DotProductFunction.hpp"
#include "implementations/EllipticalFunction.hpp"
#include "implementations/LinearFunction.hpp"
#include "implementations/NegationFunction.hpp"
#include "implementations/NormFunction.hpp"
#include "implementations/NormalizedFunction.hpp"
#include "implementations/ParametersFunction.hpp"
#include "implementations/ProductFunction.hpp"
#include "implementations/QuotientFunction.hpp"
#include "implementations/SineFunction.hpp"
#include "implementations/SquaredNormFunction.hpp"
#include "implementations/SquareRootFunction.hpp"
#include "implementations/SumFunction.hpp"
#include "implementations/TangentFunction.hpp"

namespace OpenSolid
{    
    Function Function::derivative(int index) const {
        Function result;
        implementation()->getDerivative(index, result);
        return result;
    }
    
    Function Function::norm() const {
        Function result;
        implementation()->getNorm(result);
        return result;
    }
    
    Function Function::normalized() const {
        Function result;
        implementation()->getNormalized(result);
        return result;
    }
    
    Function Function::squaredNorm() const {
        Function result;
        implementation()->getSquaredNorm(result);
        return result;
    }
    
    Function Function::component(int index) const {
        Function result;
        implementation()->getComponents(index, 1, result);
        return result;
    }
    
    Function Function::components(int index, int num) const {
        Function result;
        implementation()->getComponents(index, num, result);
        return result;
    }
    
    Function Function::concatenate(const Function& other) const {
        return new ConcatenationFunction(*this, other);
    }
    
    Function Function::dot(const Function& other) const {
        if (isA<ConstantFunction>() && other.isA<ConstantFunction>()) {
            return as<ConstantFunction>().value().dot(other.as<ConstantFunction>().value());
        } else if (
            (isA<ConstantFunction>() && as<ConstantFunction>().value().isZero()) ||
            (other.isA<ConstantFunction>() && other.as<ConstantFunction>().value().isZero())
        ) {
            return 0.0;
        } else {
            return new DotProductFunction(*this, other);
        }
    }
    
    Function Function::cross(const Function& other) const {
        assert(dimensions() == 3 && other.dimensions() == 3);
        if (isA<ConstantFunction>() && other.isA<ConstantFunction>()) {
            return as<ConstantFunction>().value().head<3>().cross(
                other.as<ConstantFunction>().value().head<3>()
            );
        }
        else if (
            (isA<ConstantFunction>() && as<ConstantFunction>().value().isZero()) ||
            (other.isA<ConstantFunction>() && other.as<ConstantFunction>().value().isZero())
        ) {
            return Vector3d::Zero();
        } else {
            return new CrossProductFunction(*this, other);
        }
    }
    
    Function Function::tangent() const {
        assert(parameters() == 1);
        Function result;
        implementation()->getTangent(result);
        return result;
    }
    
    Function Function::curvature() const {
        assert(parameters() == 1);
        Function result;
        implementation()->getCurvature(result);
        return result;
        
    }
    
    Function Function::normal() const {
        assert(parameters() == 1 || parameters() == 2);
        Function result;
        implementation()->getNormal(result);
        return result;
    }
    
    Function Function::binormal() const {
        assert(parameters() == 1);
        Function result;
        implementation()->getBinormal(result);
        return result;
    }
     
    Function Function::operator()(const Function& inner) const {
        assert(parameters() == inner.dimensions());
        if (inner.isA<ConstantFunction>()) {
            return operator()(inner.as<ConstantFunction>().value());
        }
        Function result;
        implementation()->getComposition(inner, result);
        return result;
    }
    
    Geometry Function::operator()(const Domain& domain) const {return Geometry(*this, domain);}
    
    Geometry Function::operator()(const Geometry& geometry) const {
        return Geometry(operator()(geometry.function()), geometry.domain());
    }
    
    std::ostream& operator<<(std::ostream& stream, const Function& function) {
        function.debug(stream);
        return stream;
    }
    
    void Function::debug(std::ostream& stream, int indent) const {
        for (int i = 0; i < indent; ++i) {stream << "  ";}
        stream << "R" << parameters() << " -> R" << dimensions() << " | ";
        stream << implementation().get() << " | ";
        implementation()->debug(stream, indent);
    }
         
    Function Function::t = new ParametersFunction(1, 0, 1);
    Function Function::u = new ParametersFunction(2, 0, 1);
    Function Function::v = new ParametersFunction(2, 1, 1);
    
    Function Function::CurveParameter() {return new ParametersFunction(1, 0, 1);}
    
    Function Function::SurfaceParameter(int index) {return new ParametersFunction(2, index, 1);}
    
    Function Function::VolumeParameter(int index) {return new ParametersFunction(3, index, 1);}
    
    Function Function::HypervolumeParameter(int index) {return new ParametersFunction(4, index, 1);}
    
    Function Function::Parameter(int total, int index) {
        return new ParametersFunction(total, index, 1);
    }
    
    Function Function::Parameters(int total, int index, int num) {
        return new ParametersFunction(total, index, num);
    }
    
    Function Function::Identity(int dimensions) {
        return new ParametersFunction(dimensions, 0, dimensions);
    }
    
    Function Function::Linear(const VectorXd& point, const MatrixXd& vectors) {
        return new LinearFunction(point, vectors);
    }
    
    Function Function::Elliptical(
        const VectorXd& point,
        const MatrixXd& vectors
    ) {
        return new EllipticalFunction(
            point,
            vectors,
            VectorXb::Constant(vectors.cols() - 1, false)
        );
    }
    
    Function Function::Elliptical(
        const VectorXd& point,
        const MatrixXd& vectors,
        const VectorXb& convention
    ) {return new EllipticalFunction(point, vectors, convention);}
    
    Function operator-(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {return -operand.as<ConstantFunction>().value();}
        return new NegationFunction(operand);
    }
    
    Function operator+(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isA<ConstantFunction>() && second_operand.isA<ConstantFunction>()) {
            return first_operand.as<ConstantFunction>().value() +
                second_operand.as<ConstantFunction>().value();
        } else if (
            first_operand.isA<ConstantFunction>() &&
            first_operand.as<ConstantFunction>().value().isZero()
        ) {
            return second_operand;
        } else if (
            second_operand.isA<ConstantFunction>() &&
            second_operand.as<ConstantFunction>().value().isZero()
        ) {
            return first_operand;
        } else {
            return new SumFunction(first_operand, second_operand);
        }
    }
    
    Function operator-(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isA<ConstantFunction>() && second_operand.isA<ConstantFunction>()) {
            return first_operand.as<ConstantFunction>().value() -
                second_operand.as<ConstantFunction>().value();
        } else if (
            first_operand.isA<ConstantFunction>() &&
            first_operand.as<ConstantFunction>().value().isZero()
        ) {
            return -second_operand;
        } else if (
            second_operand.isA<ConstantFunction>() &&
            second_operand.as<ConstantFunction>().value().isZero()
        ) {
            return first_operand;
        } else {
            return new DifferenceFunction(first_operand, second_operand);
        }
    }
    
    Function operator*(const Function& first_operand, const Function& second_operand) {
        Function multiplicand;
        Function multiplier;
        if (second_operand.dimensions() == 1) {
            multiplicand = first_operand;
            multiplier = second_operand;
        } else {
            multiplicand = second_operand;
            multiplier = first_operand;
        }
        if (multiplicand.isA<ConstantFunction>() && multiplier.isA<ConstantFunction>()) {
            return multiplicand.as<ConstantFunction>().value() *
                multiplier.as<ConstantFunction>().value().scalar();
        } else if (
            multiplicand.isA<ConstantFunction>() &&
            multiplicand.as<ConstantFunction>().value().isZero()
        ) {
            return multiplicand;
        } else if (
            multiplier.isA<ConstantFunction>() &&
            multiplier.as<ConstantFunction>().value().isZero()
        ) {
            return VectorXd::Zero(multiplicand.dimensions());
        } else {
            return new ProductFunction(multiplicand, multiplier);
        }
    }
    
    Function operator/(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isA<ConstantFunction>() && second_operand.isA<ConstantFunction>()) {
            return first_operand.as<ConstantFunction>().value() /
                second_operand.as<ConstantFunction>().value().scalar();
        } else if (
            first_operand.isA<ConstantFunction>() &&
            first_operand.as<ConstantFunction>().value().isZero()
        ) {
            return first_operand;
        } else if (second_operand.isA<ConstantFunction>()) {
            return new ProductFunction(
                1 / second_operand.as<ConstantFunction>().value().scalar(),
                first_operand
            );
        } else {
            return new QuotientFunction(first_operand, second_operand);
        }
    }
    
    Function operator*(const Function& function, const DatumXd& datum) {
        assert(function.dimensions() == datum.axes());
        Function result;
        function.implementation()->getTransformed(datum, result);
        return result;
    }
    
    Function operator/(const Function& function, const DatumXd& datum) {
        assert(datum.axes() == datum.dimensions());
        assert(function.dimensions() == datum.dimensions());
        Function result;
        function.implementation()->getTransformed(datum.inverse(), result);
        return result;
    }
    
    Function sin(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {
            return sin(operand.as<ConstantFunction>().value().scalar());
        } else {
            return new SineFunction(operand);
        }
    }
    
    Function cos(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {
            return cos(operand.as<ConstantFunction>().value().scalar());
        } else {
            return new CosineFunction(operand);
        }
    }
    
    Function tan(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {
            return tan(operand.as<ConstantFunction>().value().scalar());
        } else {
            return new TangentFunction(operand);
        }   
    }
    
    Function sqrt(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {
            return sqrt(operand.as<ConstantFunction>().value().scalar());
        } else {
            return new SquareRootFunction(operand);
        }
    }
}
