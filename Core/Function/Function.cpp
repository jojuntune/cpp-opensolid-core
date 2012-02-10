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

#include <algorithm>

#include <OpenSolid/Core/Scalar/Comparison.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ArccosineFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ArcsineFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ComponentsFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/CompositionFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ConcatenationFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/CosineFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/CrossProductFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/DifferenceFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/DotProductFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/EllipticalFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ExponentialFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/LinearFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/LogarithmFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/NegationFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/NormFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/NormalizedFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ParametersFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/PowerFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ProductFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/QuotientFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/SineFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/SquaredNormFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/SquareRootFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/SumFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/TangentFunction.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>

namespace OpenSolid
{
    Function::Function() : _implementation(), _type(nullptr) {}
    
    Function::Function(const FunctionImplementation* implementation) :
        _implementation(implementation), _type(&typeid(implementation)) {}
    
    Function::Function(int value) {*this = Function(VectorXd::Constant(1, value));}

    Function::Function(double value) {*this = Function(VectorXd::Constant(1, value));}

    Function::Function(const VectorXd& vector) :
        _implementation(new ConstantFunction(vector)), _type(&typeid(ConstantFunction)) {}
    
    int Function::parameters() const {
        assert(implementation());
        return implementation()->parameters();
    }
    
    int Function::dimensions() const {
        assert(implementation());
        return implementation()->dimensions();
    }
    
    bool Function::isConstant() const {
        assert(implementation());
        assert(_type);
        return *_type == typeid(ConstantFunction);
    }

    void Function::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        implementation()->evaluate(parameter_values, results);
    }

    void Function::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        implementation()->evaluate(parameter_bounds, results);
    }
    
    Function Function::derivative(int index) const {
        assert(implementation());
        Function result;
        implementation()->getDerivative(index, result);
        return result;
    }
    
    Function Function::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        assertValidTransform<Dynamic>(dimensions(), matrix, vector);
        assert(implementation());
        Function result;
        implementation()->getTransformed(matrix, vector, result);
        return result;
    }
    
    Function Function::norm() const {
        assert(implementation());
        Function result;
        implementation()->getNorm(result);
        return result;
    }
    
    Function Function::normalized() const {
        assert(implementation());
        Function result;
        implementation()->getNormalized(result);
        return result;
    }
    
    Function Function::squaredNorm() const {
        assert(implementation());
        Function result;
        implementation()->getSquaredNorm(result);
        return result;
    }

    Function Function::x() const {
        assert(implementation());
        return component(0);
    }

    Function Function::y() const {
        assert(implementation());
        return component(1);
    }

    Function Function::z() const {
        assert(implementation());
        return component(2);
    }
    
    Function Function::component(int index) const {
        assert(implementation());
        Function result;
        implementation()->getComponents(index, 1, result);
        return result;
    }
    
    Function Function::components(int index, int num) const {
        assert(implementation());
        Function result;
        implementation()->getComponents(index, num, result);
        return result;
    }
    
    Function Function::concatenate(const Function& other) const {
        assert(implementation());
        assert(other.implementation());
        if (isConstant() && other.isConstant()) {
            VectorXd result(dimensions() + other.dimensions());
            result.head(dimensions()) = this->as<VectorXd>();
            result.tail(other.dimensions()) = other.as<VectorXd>();
            return result;
        } else {
            return new ConcatenationFunction(*this, other);
        }
    }
    
    Function Function::dot(const Function& other) const {
        assert(implementation());
        assert(other.implementation());
        if (dimensions() == 1) {
            assert(other.dimensions() == 1);
            return (*this) * other;
        } else if (isConstant() && other.isConstant()) {
            return this->as<VectorXd>().dot(other.as<VectorXd>());
        } else if (
            (isConstant() && this->as<VectorXd>().isZero()) ||
            (other.isConstant() && other.as<VectorXd>().isZero())
        ) {
            return 0.0;
        } else {
            return new DotProductFunction(*this, other);
        }
    }
    
    Function Function::cross(const Function& other) const {
        assert(implementation());
        assert(other.implementation());
        assert(dimensions() == 3 && other.dimensions() == 3);
        if (isConstant() && other.isConstant()) {
            return this->as<Vector3d>().cross(other.as<Vector3d>());
        }
        else if (
            (isConstant() && this->as<Vector3d>().isZero()) ||
            (other.isConstant() && other.as<Vector3d>().isZero())
        ) {
            return Vector3d::Zero();
        } else {
            return new CrossProductFunction(*this, other);
        }
    }
    
    Function Function::tangent() const {
        assert(implementation());
        assert(parameters() == 1);
        Function result;
        implementation()->getTangent(result);
        return result;
    }
    
    Function Function::curvature() const {
        assert(implementation());
        assert(parameters() == 1);
        Function result;
        implementation()->getCurvature(result);
        return result;
        
    }
    
    Function Function::normal() const {
        assert(implementation());
        assert(parameters() == 1 || parameters() == 2);
        Function result;
        implementation()->getNormal(result);
        return result;
    }
    
    Function Function::binormal() const {
        assert(implementation());
        assert(parameters() == 1);
        Function result;
        implementation()->getBinormal(result);
        return result;
    }
     
    Function Function::operator()(const Function& inner) const {
        assert(implementation());
        assert(inner.implementation());
        if (isConstant()) {return *this;}
        assert(parameters() == inner.dimensions());
        if (inner.isConstant()) {return operator()(inner.as<VectorXd>());}
        Function result;
        implementation()->getComposition(inner, result);
        return result;
    }
    
    Geometry Function::operator()(const Domain& domain) const {
        assert(implementation());
        assert(isConstant() || !domain.isEmpty());
        return Geometry(*this, domain);
    }
    
    Geometry Function::operator()(const Geometry& geometry) const {
        assert(implementation());
        return Geometry(operator()(geometry.function()), geometry.domain());
    }
    
    double getZero(
        const std::vector<Function>& derivatives,
        const Interval& domain_interval,
        int& order
    ) {
        double x = domain_interval.median();
        double y = derivatives[order](x).value();
        double derivative_value = derivatives[order + 1](x).value();
        Interval derivative_bounds = derivatives[order + 1](domain_interval).value();
        Interval convergence_ratio = abs(1 - derivative_bounds / derivative_value);
        if (convergence_ratio < One()) {
            double last_y = y;
            x = x - y / derivative_value;
            y = derivatives[order](x).value();
            while (abs(y) > 0 && abs(y) < abs(last_y)) {
                double new_derivative_value = derivatives[order + 1](x).value();
                convergence_ratio = abs(1 - derivative_bounds / new_derivative_value);
                if (convergence_ratio < One()) {derivative_value = new_derivative_value;}
                last_y = y;
                x = x - y / derivative_value;
                y = derivatives[order](x).value();
            }
            while (order > 0 && derivatives[order - 1](x).isZero()) {--order;}
            return x;
        } else {
            if ((y > 0) == (derivative_value > 0)) {
                return getZero(derivatives, Interval(domain_interval.lower(), x), order);
            } else {
                return getZero(derivatives, Interval(x, domain_interval.upper()), order);
            }
        }
    }
    
    void getZeros(
        const std::vector<Function>& derivatives,
        const Interval& domain_interval,
        int order,
        std::vector<double>& results
    ) {
        RowVector2d endpoint_x(domain_interval.lower(), domain_interval.upper());
        RowVector2d endpoint_y = derivatives[order](endpoint_x);
        if ((endpoint_y(0) > 0) != (endpoint_y(1) > 0)) {
            double x = getZero(derivatives, domain_interval, order);
            if (order == 0) {
                results.push_back(x);
            } else {
                getZeros(derivatives, Interval(domain_interval.lower(), x), order - 1, results);
                getZeros(derivatives, Interval(x, domain_interval.upper()), order - 1, results);
            }
        } else if (order > 0) {
            getZeros(derivatives, domain_interval, order - 1, results);
        }
    }
    
    RowVectorXd Function::roots(const Interval& domain) const {
        assert(implementation());
        assert(parameters() == 1 || isConstant());
        assert(dimensions() == 1);
        int order = 4;
        std::vector<Function> derivatives(order + 1);
        derivatives[0] = *this;
        RowVectorXd derivative_values(order);
        for (int i = 1; i <= order; ++i) {
            derivatives[i] = derivatives[i - 1].derivative();
            derivative_values(i - 1) = derivatives[i](domain.median()).value();
        }
        if (derivative_values.isZero()) {return RowVectorXd();}
        RowVectorXI domain_intervals(1);
        domain_intervals(0) = domain;
        std::vector<double> results;
        while (domain_intervals.size() > 0) {
            MatrixXI bounds(derivatives.size(), domain_intervals.size());
            for (unsigned i = 0; i < derivatives.size(); ++i) {
                bounds.row(i) = derivatives[i](domain_intervals);
            }
            MatrixXI bound_norms = bounds.cwiseAbs();
            std::vector<Interval> bisected_intervals;
            for (int i = 0; i < domain_intervals.size(); ++i) {
                bool bisection_needed = true;
                for (int j = 0; j <= order; ++j) {
                    if (bound_norms(j, i) > Zero()) {
                        bisection_needed = false;
                        if (j > 0) {getZeros(derivatives, domain_intervals[i], j - 1, results);}
                        break;
                    }
                }
                if (bisection_needed) {
                    std::pair<Interval, Interval> bisected = domain_intervals[i].bisected();
                    bisected_intervals.push_back(bisected.first);
                    bisected_intervals.push_back(bisected.second);
                }
            }
            if (bisected_intervals.empty()) {
                domain_intervals = RowVectorXI();
            } else {
                domain_intervals.resize(bisected_intervals.size());
                std::copy(
                    bisected_intervals.begin(),
                    bisected_intervals.end(),
                    begin(domain_intervals)
                );
            }
        }
        if (results.empty()) {
            return RowVectorXd();
        } else {
            std::sort(results.begin(), results.end());
            int index = 0;
            for (unsigned i = 1; i < results.size(); ++i) {
                if (results[i] - results[index] > Zero()) {results[++index] = results[i];}
            }
            RowVectorXd final_results(index + 1);
            std::copy(results.begin(), results.begin() + index + 1, begin(final_results));
            return final_results;
        }
    }
    
    std::ostream& operator<<(std::ostream& stream, const Function& function) {
        assert(function.implementation());
        function.debug(stream);
        return stream;
    }
    
    void Function::debug(std::ostream& stream, int indent) const {
        assert(implementation());
        for (int i = 0; i < indent; ++i) {stream << "  ";}
        stream << "R" << parameters() << " -> R" << dimensions() << " | ";
        stream << implementation() << " | ";
        implementation()->debug(stream, indent);
    }
    
    Function operator-(const Function& operand) {
        if (operand.isConstant()) {return -operand.as<VectorXd>();}
        return new NegationFunction(operand);
    }
    
    double Conversion<Function, double>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 1);
        return argument.as<VectorXd>().value();
    }
    
    Vector2d Conversion<Function, Vector2d>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 2);
        return argument.as<VectorXd>();
    }
    
    Vector3d Conversion<Function, Vector3d>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        assert(argument.dimensions() == 3);
        return argument.as<VectorXd>();
    }
    
    const VectorXd& Conversion<Function, VectorXd>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        return static_cast<const ConstantFunction*>(argument.implementation())->vector();
    }
    
    Function operator+(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isConstant() && second_operand.isConstant()) {
            return first_operand.as<VectorXd>() + second_operand.as<VectorXd>();
        } else if (first_operand.isConstant() && first_operand.as<VectorXd>().isZero()) {
            return second_operand;
        } else if (second_operand.isConstant() && second_operand.as<VectorXd>().isZero()) {
            return first_operand;
        } else {
            return new SumFunction(first_operand, second_operand);
        }
    }
    
    Function operator-(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isConstant() && second_operand.isConstant()) {
            return first_operand.as<VectorXd>() - second_operand.as<VectorXd>();
        } else if (first_operand.isConstant() && first_operand.as<VectorXd>().isZero()) {
            return -second_operand;
        } else if (second_operand.isConstant() && second_operand.as<VectorXd>().isZero()) {
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
        if (multiplicand.isConstant() && multiplier.isConstant()) {
            double multiplier_value = multiplier.as<double>();
            return multiplicand.as<VectorXd>() * multiplier_value;
        } else if (multiplicand.isConstant() && multiplicand.as<VectorXd>().isZero()) {
            return multiplicand;
        } else if (multiplier.isConstant()) {
            double multiplier_value = multiplier.as<double>();
            if (multiplier_value == Zero()) {
                return VectorXd::Zero(multiplicand.dimensions());
            } else if (multiplier_value == One()) {
                return multiplicand;
            } else if (multiplier_value == -One()) {
                return -multiplicand;
            } else {
                return new ProductFunction(multiplicand, multiplier);
            }
        } else {
            return new ProductFunction(multiplicand, multiplier);
        }
    }
    
    Function operator/(const Function& first_operand, const Function& second_operand) {
        if (first_operand.isConstant() && second_operand.isConstant()) {
            double divisor_value = second_operand.as<double>();
            return first_operand.as<VectorXd>() / divisor_value;
        } else if (
            first_operand.isConstant() &&
            first_operand.as<VectorXd>().isZero()
        ) {
            return first_operand;
        } else if (second_operand.isConstant()) {
            double second_value = second_operand.as<double>();
            if (second_value == One()) {
                return first_operand;
            } else if (second_value == -One()) {
                return -first_operand;
            } else {
                return new ProductFunction(first_operand, 1 / second_value);
            }
        } else {
            return new QuotientFunction(first_operand, second_operand);
        }
    }
    
    Function sin(const Function& operand) {
        if (operand.isConstant()) {
            return sin(operand.as<double>());
        } else {
            return new SineFunction(operand);
        }
    }
    
    Function cos(const Function& operand) {
        if (operand.isConstant()) {
            return cos(operand.as<double>());
        } else {
            return new CosineFunction(operand);
        }
    }
    
    Function tan(const Function& operand) {
        if (operand.isConstant()) {
            return tan(operand.as<double>());
        } else {
            return new TangentFunction(operand);
        }
    }
    
    Function sqrt(const Function& operand) {
        if (operand.isConstant()) {
            return sqrt(operand.as<double>());
        } else {
            return new SquareRootFunction(operand);
        }
    }
    
    Function asin(const Function& operand) {
        if (operand.isConstant()) {
            return asin(operand.as<double>());
        } else {
            return new ArcsineFunction(operand);
        }
    }
    
    Function acos(const Function& operand) {
        if (operand.isConstant()) {
            return acos(operand.as<double>());
        } else {
            return new ArccosineFunction(operand);
        }
    }

    Function exp(const Function& argument) {
        if (argument.isConstant()) {
            return exp(argument.as<double>());
        } else {
            return new ExponentialFunction(argument);
        }
    }

    Function log(const Function& argument) {
        if (argument.isConstant()) {
            return log(argument.as<double>());
        } else {
            return new LogarithmFunction(argument);
        }
    }

    Function pow(const Function& base, const Function& exponent) {
        if (base.isConstant() && exponent.isConstant()) {
            return pow(base.as<double>(), exponent.as<double>());
        } else {
            return new PowerFunction(base, exponent);
        }
    }
}
