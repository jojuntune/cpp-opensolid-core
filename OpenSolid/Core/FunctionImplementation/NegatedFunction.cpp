/************************************************************************************
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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/FunctionImplementation/NegatedFunction.hpp>

namespace opensolid
{
    int
    NegatedFunction::numDimensionsImpl() const {
        return operand().numDimensions();
    }

    void
    NegatedFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = -evaluator.evaluate(operand(), parameterValues);
    }

    void
    NegatedFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = -evaluator.evaluate(operand(), parameterBounds);
    }

    FunctionImplementationPtr
    NegatedFunction::derivativeImpl(int parameterIndex) const {
        return -operand()->derivative(parameterIndex);
    }

    bool
    NegatedFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return UnaryOperation::isDuplicateOfImpl(other);
    }
 
    FunctionImplementationPtr
    NegatedFunction::componentsImpl(int startIndex, int numComponents) const {
        return -operand()->components(startIndex, numComponents);
    }

    FunctionImplementationPtr
    NegatedFunction::scaledImpl(double scale) const {
        return operand()->scaled(-scale);
    }

    FunctionImplementationPtr
    NegatedFunction::transformedImpl(const MatrixXd& transformationMatrix) const {
        return operand()->transformed(-transformationMatrix);
    }

    FunctionImplementationPtr
    NegatedFunction::normImpl() const {
        return operand()->norm();
    }

    FunctionImplementationPtr
    NegatedFunction::normalizedImpl() const {
        return -operand()->normalized();
    }

    FunctionImplementationPtr
    NegatedFunction::squaredNormImpl() const {
        return operand()->squaredNorm();
    }

    FunctionImplementationPtr
    NegatedFunction::negatedImpl() const {
        return operand();
    }

    FunctionImplementationPtr
    NegatedFunction::sinImpl() const {
        return -sin(operand());
    }

    FunctionImplementationPtr
    NegatedFunction::cosImpl() const {
        return cos(operand());
    }

    FunctionImplementationPtr
    NegatedFunction::tanImpl() const {
        return -tan(operand());
    }

    FunctionImplementationPtr
    NegatedFunction::acosImpl() const {
        return M_PI - acos(operand());
    }

    FunctionImplementationPtr
    NegatedFunction::asinImpl() const {
        return -asin(operand());
    }

    void
    NegatedFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "NegatedFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    NegatedFunction::withNewOperand(const FunctionImplementationPtr& newOperand) const {
        return new NegatedFunction(newOperand);
    }

    NegatedFunction::NegatedFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
}
