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

#include <OpenSolid/Core/Function/NormalizedFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    NormalizedFunction::NormalizedFunction(const Function& operand) : UnaryOperation(operand) {
    }
    
    int NormalizedFunction::numDimensions() const {
        return operand().numDimensions();
    }

    void NormalizedFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        MatrixXd operandValues = operand()(parameterValues);
        VectorXd squaredNorms = operandValues.colwise().squaredNorm();
        results = operandValues * squaredNorms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void NormalizedFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        MatrixXI operandBounds = operand()(parameterBounds);
        VectorXI squaredNorms = operandBounds.colwise().squaredNorm();
        results = operandBounds * squaredNorms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void NormalizedFunction::getDerivative(int index, Function& result) const {
        Function operandDerivative = operand().derivative(index);
        Function operandNormalized = operand().normalized();
        result =
            (operandDerivative - operandDerivative.dot(operandNormalized) * operandNormalized) /
            operand().norm();
    }
    
    void NormalizedFunction::getNorm(Function& result) const {
        result = 1.0;
    }
    
    void NormalizedFunction::getNormalized(Function& result) const {
        result = this;
    }
    
    void NormalizedFunction::getSquaredNorm(Function& result) const {
        result = 1.0;
    }
    
    void NormalizedFunction::debug(std::ostream& stream, int indent) const {
        stream << "NormalizedFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
