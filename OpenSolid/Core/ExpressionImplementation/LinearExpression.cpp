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
************************************************************************************/

#include <OpenSolid/Core/ExpressionImplementation/LinearExpression.hpp>

#include <OpenSolid/Core/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    LinearExpression::numDimensionsImpl() const {
        return basisMatrix().rows();
    }

    int
    LinearExpression::numParametersImpl() const {
        return basisMatrix().cols();
    }
    
    void
    LinearExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = (basisMatrix() * parameterValues).colwise() + originPoint();
    }
    
    void
    LinearExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = (basisMatrix().cast<Interval>() * parameterBounds).colwise() +
            originPoint().cast<Interval>();
    }

    void
    LinearExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = basisMatrix();
    }
    
    void
    LinearExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = basisMatrix().cast<Interval>();
    }

    ExpressionImplementationPtr
    LinearExpression::derivativeImpl(int parameterIndex) const {
        return new ConstantExpression(basisMatrix().col(parameterIndex), numParameters());
    }
    
    bool
    LinearExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        const LinearExpression* otherLinearPtr = other->cast<LinearExpression>();

        return (this->originPoint() - otherLinearPtr->originPoint()).isZero() &&
            (this->basisMatrix() - otherLinearPtr->basisMatrix()).isZero();
    }

    ExpressionImplementationPtr
    LinearExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }

    ExpressionImplementationPtr
    LinearExpression::scalarMultiplicationImpl(double scale) const {
        return new LinearExpression(scale * originPoint(), scale * basisMatrix());
    }
    
    ExpressionImplementationPtr
    LinearExpression::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return new LinearExpression(matrix * originPoint(), matrix * basisMatrix());
    }

    ExpressionImplementationPtr
    LinearExpression::vectorAdditionImpl(const VectorXd& vector) const {
        return new LinearExpression(originPoint() + vector, basisMatrix());
    }
    
    void
    LinearExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "LinearExpression" << std::endl;
    }
    
    LinearExpression::LinearExpression(const VectorXd& originPoint, const MatrixXd& basisMatrix) :
        _originPoint(originPoint),
        _basisMatrix(basisMatrix) {
    }
}
