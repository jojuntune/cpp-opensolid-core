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

#include <OpenSolid/Core/FunctionImplementation/EllipticalFunction.hpp>

namespace opensolid
{
    int
    EllipticalFunction::numDimensionsImpl() const {
        return basisMatrix().rows();
    }

    int
    EllipticalFunction::numParametersImpl() const {
        return basisMatrix().cols() - 1;
    }
    
    void
    EllipticalFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MatrixXd localCoordinates = MatrixXd::Ones(basisMatrix().cols(), parameterValues.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                localCoordinates.row(i).array() *= cos(parameterValues.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    sin(parameterValues.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                localCoordinates.row(i).array() *= sin(parameterValues.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    cos(parameterValues.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = (basisMatrix() * localCoordinates).colwise() + originPoint();
    }
    
    void
    EllipticalFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MatrixXI localCoordinates = MatrixXI::Ones(basisMatrix().cols(), parameterBounds.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                localCoordinates.row(i).array() *= cos(parameterBounds.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    sin(parameterBounds.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                localCoordinates.row(i).array() *= sin(parameterBounds.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    cos(parameterBounds.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = (basisMatrix().template cast<Interval>() * localCoordinates).colwise() +
            originPoint().template cast<Interval>();
    }

    FunctionImplementationPtr
    EllipticalFunction::derivativeImpl(int parameterIndex) const {
        MatrixXd derivativeBasisMatrix = basisMatrix();
        RowVectorXb derivativeConvention = convention();

        derivativeConvention(parameterIndex) = !derivativeConvention(parameterIndex);

        if (convention()(parameterIndex)) {
            derivativeBasisMatrix.col(parameterIndex) *= -1;
        } else {
            int numFlipped = numParameters() - parameterIndex;
            derivativeBasisMatrix.rightCols(numFlipped) *= -1;
        }
        return new EllipticalFunction(
            VectorXd::Zero(numDimensions()),
            derivativeBasisMatrix,
            derivativeConvention
        );
    }
    
    bool
    EllipticalFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        const EllipticalFunction* otherElliptical = other->cast<EllipticalFunction>();

        return (this->originPoint() - otherElliptical->originPoint()).isZero() &&
            (this->basisMatrix() - otherElliptical->basisMatrix()).isZero() &&
            this->convention() == otherElliptical->convention();
    }

    FunctionImplementationPtr
    EllipticalFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }
    
    FunctionImplementationPtr
    EllipticalFunction::scalarMultiplicationImpl(double scale) const {
        return new EllipticalFunction(scale * originPoint(), scale * basisMatrix(), convention());
    }
    
    FunctionImplementationPtr
    EllipticalFunction::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return new EllipticalFunction(matrix * originPoint(), matrix * basisMatrix(), convention());
    }
    
    FunctionImplementationPtr
    EllipticalFunction::vectorAdditionImpl(const VectorXd& vector) const {
        return new EllipticalFunction(originPoint() + vector, basisMatrix(), convention());
    }
    
    void
    EllipticalFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "EllipticalFunction" << std::endl;
    }

    EllipticalFunction::EllipticalFunction(
        const VectorXd& originPoint,
        const MatrixXd& basisMatrix,
        const RowVectorXb& convention
    ) : _originPoint(originPoint),
        _basisMatrix(basisMatrix),
        _convention(convention) {
    }
}
