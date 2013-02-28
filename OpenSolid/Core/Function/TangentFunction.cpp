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

#include <OpenSolid/Core/Function/TangentFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TangentFunction::TangentFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.numDimensions() == 1);
    }
    
    int TangentFunction::numDimensions() const {
        return 1;
    }

    bool TangentFunction::isDuplicate(const Function& function) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    Function TangentFunction::deduplicated(std::vector<Function>& others) const {
        return new TangentFunction(operand().deduplicated(others));
    }
    
    void TangentFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& resultCache
    ) const {
        MatrixXd operandValues = operand()(parameterValues);
        results = operandValues.array().sin() / operandValues.array().cos();
    }
    
    void TangentFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& resultCache
    ) const {
        MatrixXI operandBounds = operand()(parameterBounds);
        results = operandBounds.array().sin() / operandBounds.array().cos();
    }

    Function TangentFunction::derivative(int index) const {
        return (1 + Function(this).squaredNorm()) * operand().derivative(index);
    }
    
    void TangentFunction::debug(std::ostream& stream, int indent) const {
        stream << "TangentFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
