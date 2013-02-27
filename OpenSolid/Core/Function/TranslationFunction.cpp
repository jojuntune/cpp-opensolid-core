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

#include <OpenSolid/Core/Function/TranslationFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TranslationFunction::TranslationFunction(const Function& operand, const VectorXd& vector) :
        UnaryOperation(operand),
        _vector(vector) {

        assert(vector.size() == operand.numDimensions());
    }
    
    int TranslationFunction::numDimensions() const {
        return operand().numDimensions();
    }

    Function TranslationFunction::deduplicated(std::vector<Function>& others) const {
        return operand().deduplicated(others) + vector();
    }
    
    void TranslationFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        MatrixXd operandValues = operand()(parameterValues);
        results = operandValues.colwise() + vector();
    }
    
    void TranslationFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        MatrixXI operandBounds = operand()(parameterBounds);
        results = operandBounds.colwise() + vector().cast<Interval>();
    }
    
    Function TranslationFunction::derivative(int index) const {
        return operand().derivative(index);
    }
    
    Function TranslationFunction::compose(const Function& innerFunction) const {
        return operand()(innerFunction) + vector();
    }

    Function TranslationFunction::translated(const VectorXd& vector) const {
        return operand() + (this->vector() + vector);
    }
    
    void TranslationFunction::debug(std::ostream& stream, int indent) const {
        stream << "TranslationFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
