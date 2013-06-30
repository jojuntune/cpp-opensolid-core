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

#include <OpenSolid/Core/FunctionImplementation/CrossProductFunction.hpp>

namespace opensolid
{   
    int
    CrossProductFunction::numDimensionsImpl() const {
        return 3;
    }
    
    void
    CrossProductFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterValues);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstValues.col(i).head<3>().cross(secondValues.col(i).head<3>());
        }
    }
    
    void
    CrossProductFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstBounds.col(i).head<3>().cross(secondBounds.col(i).head<3>());
        }
    }

    FunctionImplementationPtr
    CrossProductFunction::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex)->cross(secondOperand())
            + firstOperand()->cross(secondOperand()->derivative(parameterIndex));
    }

    bool
    CrossProductFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }
    
    void
    CrossProductFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "CrossProductFunction" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    CrossProductFunction::withNewOperandsImpl(
        const FunctionImplementationPtr& newFirstOperand,
        const FunctionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand->cross(newSecondOperand);
    }

    CrossProductFunction::CrossProductFunction(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand->numDimensions() == 3 && secondOperand->numDimensions() == 3);
    }
}
