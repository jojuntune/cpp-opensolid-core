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

#include <OpenSolid/Geometry/Domain.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

#include "Function.hpp"
#include "implementations/ArccosineFunction.hpp"
#include "implementations/ArcsineFunction.hpp"
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
    
    double getZero(const List<Function>& derivatives, const Interval& domain_interval, int& order) {
        double x = domain_interval.median();
        double y = derivatives[order](x).scalar();
        double derivative_value = derivatives[order + 1](x).scalar();
        Interval derivative_bounds = derivatives[order + 1](domain_interval).scalar();
        Interval convergence_ratio = abs(1 - derivative_bounds / derivative_value);
        if (convergence_ratio < 1 - Tolerance::roundoff()) {
            double last_y = y;
            x = x - y / derivative_value;
            y = derivatives[order](x).scalar();
            while (abs(y) > 0 && abs(y) < abs(last_y)) {
                double new_derivative_value = derivatives[order + 1](x).scalar();
                convergence_ratio = abs(1 - derivative_bounds / new_derivative_value);
                if (convergence_ratio < 1 - Tolerance::roundoff()) {
                    derivative_value = new_derivative_value;
                }
                last_y = y;
                x = x - y / derivative_value;
                y = derivatives[order](x).scalar();
            }
            while (order > 0 && abs(derivatives[order - 1](x).scalar()) < Tolerance::roundoff()) {
                --order;
            }
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
        const List<Function>& derivatives,
        const Interval& domain_interval,
        int order,
        List<double>& results
    ) {
        RowVector2d endpoint_x(domain_interval.lower(), domain_interval.upper());
        RowVector2d endpoint_y = derivatives[order](endpoint_x);
        if ((endpoint_y(0) > 0) != (endpoint_y(1) > 0)) {
            double x = getZero(derivatives, domain_interval, order);
            if (order == 0) {
                results.append(x);
            } else {
                getZeros(derivatives, Interval(domain_interval.lower(), x), order - 1, results);
                getZeros(derivatives, Interval(x, domain_interval.upper()), order - 1, results);
            }
        } else if (order > 0) {
            getZeros(derivatives, domain_interval, order - 1, results);
        }
    }
    
    RowVectorXd Function::zeros(const Interval& domain, double tolerance) const {
        int order = 4;
        List<Function> derivatives(order + 1);
        derivatives[0] = *this;
        RowVectorXd derivative_values(order);
        for (int i = 1; i <= order; ++i) {
            derivatives[i] = derivatives[i - 1].derivative();
            derivative_values(i - 1) = derivatives[i](domain.median()).scalar();
        }
        if (derivative_values.isZero(Tolerance::roundoff())) {return RowVectorXd();}
        RowVectorXI domain_intervals(1);
        domain_intervals(0) = domain;
        List<double> results;
        while (domain_intervals.size() > 0) {
            MatrixXI bounds(derivatives.size(), domain_intervals.size());
            for (int i = 0; i < derivatives.size(); ++i) {
                bounds.row(i) = derivatives[i](domain_intervals);
            }
            MatrixXI bound_norms = bounds.cwiseAbs();
            List<Interval> bisected_intervals;
            for (int i = 0; i < domain_intervals.size(); ++i) {
                bool bisection_needed = true;
                for (int j = 0; j <= order; ++j) {
                    if (bound_norms(j, i) > Tolerance::roundoff()) {
                        bisection_needed = false;
                        if (j > 0) {getZeros(derivatives, domain_intervals[i], j - 1, results);}
                        break;
                    }
                }
                if (bisection_needed) {
                    Pair<Interval> bisected = domain_intervals[i].bisected();
                    bisected_intervals.append(bisected.first());
                    bisected_intervals.append(bisected.second());
                }
            }
            domain_intervals = bisected_intervals.empty() ? 
                RowVectorXI() : 
                bisected_intervals.matrix();
        }
        if (results.empty()) {
            return RowVectorXd();
        } else {
            std::sort(results.begin(), results.end());
            int index = 0;
            for (int i = 1; i < results.size(); ++i) {
                if (results[i] - results[index] > Tolerance::roundoff()) {
                    results[++index] = results[i];
                }
            }
            return results.matrix().leftCols(index + 1);
        }
    }
    
    std::ostream& operator<<(std::ostream& stream, const Function& function) {
        function.debug(stream);
        return stream;
    }
    
    void Function::debug(std::ostream& stream, int indent) const {
        for (int i = 0; i < indent; ++i) {stream << "  ";}
        stream << "R" << parameters() << " -> R" << dimensions() << " | ";
        stream << implementation() << " | ";
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
    
    Function asin(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {
            return asin(operand.as<ConstantFunction>().value().scalar());
        } else {
            return new ArcsineFunction(operand);
        }
    }
    
    Function acos(const Function& operand) {
        if (operand.isA<ConstantFunction>()) {
            return acos(operand.as<ConstantFunction>().value().scalar());
        } else {
            return new ArccosineFunction(operand);
        }
    }
}
