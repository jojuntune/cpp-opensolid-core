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

#include <OpenSolid/Core/FunctionImplementation/TempTransformationFunction.hpp>

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TempTransformationFunction::TempTransformationFunction(
        const MatrixXd& transformationMatrix,
        const Function& operand
    ) : UnaryOperation(operand),
        _transformationMatrix(transformationMatrix) {

        assert(transformationMatrix.cols() == operand.numDimensions());
    }

    int TempTransformationFunction::numDimensions() const {
        return transformationMatrix().rows();
    }

    bool TempTransformationFunction::isDuplicate(const Function& function) const {
        const TempTransformationFunction* other =
            dynamic_cast<const TempTransformationFunction*>(function.implementation());
        if (other) {
            return this->transformationMatrix().rows() == other->transformationMatrix().rows() &&
                this->transformationMatrix().cols() == other->transformationMatrix().cols() &&
                (this->transformationMatrix() - other->transformationMatrix()).isZero() &&
                this->operand().isDuplicate(other->operand());
        } else {
            return false;
        }
    }

    Function TempTransformationFunction::deduplicated(std::vector<Function>& others) const {
        return new TempTransformationFunction(
            transformationMatrix(),
            operand().deduplicated(others)
        );
    }
    
    void TempTransformationFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>& cache
    ) const {
        results = transformationMatrix() *
            cache.results(operand(), parameterValues);
    }
    
    void TempTransformationFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>& cache
    ) const {
        results = transformationMatrix().cast<Interval>() *
            cache.results(operand(), parameterBounds);
    }
    
    Function TempTransformationFunction::derivative(int index) const {
        return transformationMatrix() * operand().derivative(index);
    }
    
    Function TempTransformationFunction::compose(const Function& innerFunction) const {
        return transformationMatrix() * operand().compose(innerFunction);
    }

    Function TempTransformationFunction::scaled(double value) const {
        return (value * transformationMatrix()) * operand();
    }

    Function TempTransformationFunction::transformed(const MatrixXd& transformationMatrix) const {
        return (transformationMatrix * this->transformationMatrix()) * operand();
    }
    
    void TempTransformationFunction::debug(std::ostream& stream, int indent) const {
        stream << "TempTransformationFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
