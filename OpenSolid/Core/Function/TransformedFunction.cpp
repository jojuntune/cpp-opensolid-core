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

#include <OpenSolid/Core/Function/TransformedFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TransformedFunction::TransformedFunction(
        const Function& operand,
        const MatrixXd& transformationMatrix,
        const VectorXd& translationVector
    ) : UnaryOperation(operand),
        _transformationMatrix(transformationMatrix),
        _translationVector(translationVector) {

        assert(operand.numDimensions() == transformationMatrix.cols());
        assert(translationVector.size() == transformationMatrix.rows());
    }
    
    int TransformedFunction::numDimensions() const {
        return transformationMatrix().rows();
    }
    
    void TransformedFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = (transformationMatrix() * operand()(parameterValues)).colwise() +
            translationVector();
    }
    
    void TransformedFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = (transformationMatrix().cast<Interval>() * operand()(parameterBounds)).colwise() +
            translationVector().cast<Interval>();
    }
    
    void TransformedFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index).transformed(
            transformationMatrix(),
            VectorXd::Zero(numDimensions())
        );
    }
    
    void TransformedFunction::getComposition(
        const Function& innerFunction,
        Function& result
    ) const {
        result = operand()(innerFunction).transformed(transformationMatrix(), translationVector());
    }
    
    void TransformedFunction::getTransformed(
        const MatrixXd& transformationMatrix,
        const VectorXd& translationVector,
        Function& result
    ) const {
        result = operand().transformed(
            transformationMatrix * this->transformationMatrix(),
            transformationMatrix * this->translationVector() + translationVector
        );
    }
    
    void TransformedFunction::debug(std::ostream& stream, int indent) const {
        stream << "TransformedFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
