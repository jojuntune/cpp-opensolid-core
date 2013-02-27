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

#include <OpenSolid/Core/Function/LinearTransformationFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    LinearTransformationFunction::LinearTransformationFunction(
        const MatrixXd& transformationMatrix,
        const Function& operand
    ) : UnaryOperation(operand),
        _transformationMatrix(transformationMatrix) {

        assert(transformationMatrix.cols() == operand.numDimensions());
    }

    int LinearTransformationFunction::numDimensions() const {
        return transformationMatrix().rows();
    }

    bool LinearTransformationFunction::isDuplicate(const Function& function) const {
        const LinearTransformationFunction* other =
            dynamic_cast<const LinearTransformationFunction*>(function.implementation());
        if (other) {
            return this->transformationMatrix().rows() == other->transformationMatrix().rows() &&
                this->transformationMatrix().cols() == other->transformationMatrix().cols() &&
                (this->transformationMatrix() - other->transformationMatrix()).isZero() &&
                this->operand().isDuplicate(other->operand());
        } else {
            return false;
        }
    }

    Function LinearTransformationFunction::deduplicated(std::vector<Function>& others) const {
        return new LinearTransformationFunction(
            transformationMatrix(),
            operand().deduplicated(others)
        );
    }
    
    void LinearTransformationFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results
    ) const {
        results = transformationMatrix() * operand()(parameterValues);
    }
    
    void LinearTransformationFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results
    ) const {
        results = transformationMatrix().cast<Interval>() * operand()(parameterBounds);
    }
    
    Function LinearTransformationFunction::derivative(int index) const {
        return transformationMatrix() * operand().derivative(index);
    }
    
    Function LinearTransformationFunction::compose(const Function& innerFunction) const {
        return transformationMatrix() * operand()(innerFunction);
    }

    Function LinearTransformationFunction::scaled(double value) const {
        return (value * transformationMatrix()) * operand();
    }

    Function LinearTransformationFunction::transformed(const MatrixXd& transformationMatrix) const {
        return (transformationMatrix * this->transformationMatrix()) * operand();
    }
    
    void LinearTransformationFunction::debug(std::ostream& stream, int indent) const {
        stream << "LinearTransformationFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
