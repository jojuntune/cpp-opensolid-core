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

#include <OpenSolid/Core/FunctionImplementation/LinearFunction.hpp>

namespace opensolid
{
    int
    LinearFunction::numDimensionsImpl() const {
        return basisMatrix().rows();
    }

    int
    LinearFunction::numParametersImpl() const {
        return basisMatrix().cols();
    }
    
    void
    LinearFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = (basisMatrix() * parameterValues).colwise() + originPoint();
    }
    
    void
    LinearFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = (basisMatrix().cast<Interval>() * parameterBounds).colwise() +
            originPoint().cast<Interval>();
    }

    FunctionImplementationPtr
    LinearFunction::derivativeImpl(int parameterIndex) const {
        return new ConstantFunction(basisMatrix().col(parameterIndex), numParameters());
    }
    
    bool
    LinearFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        const LinearFunction* otherLinear = other->cast<LinearFunction>();

        return (this->originPoint() - otherLinear->originPoint()).isZero() &&
            (this->basisMatrix() - otherLinear->basisMatrix()).isZero();
    }

    FunctionImplementationPtr
    LinearFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }

    FunctionImplementationPtr
    LinearFunction::scalarMultiplicationImpl(double scale) const {
        return new LinearFunction(scale * originPoint(), scale * basisMatrix());
    }
    
    FunctionImplementationPtr
    LinearFunction::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return new LinearFunction(matrix * originPoint(), matrix * basisMatrix());
    }

    FunctionImplementationPtr
    LinearFunction::vectorAdditionImpl(const VectorXd& vector) const {
        return new LinearFunction(originPoint() + vector, basisMatrix());
    }
    
    void
    LinearFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "LinearFunction" << std::endl;
    }
    
    LinearFunction::LinearFunction(const VectorXd& originPoint, const MatrixXd& basisMatrix) :
        _originPoint(originPoint),
        _basisMatrix(basisMatrix) {
    }
}
