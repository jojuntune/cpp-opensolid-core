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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ExpressionImplementation.definitions.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    class LinearExpression :
        public ExpressionImplementation
    {
    private:
        VectorXd _originPoint;
        MatrixXd _basisMatrix;
        
        OPENSOLID_CORE_EXPORT
        int
        numDimensionsImpl() const override;
        
        OPENSOLID_CORE_EXPORT
        int
        numParametersImpl() const override;
        
        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const override;
        
        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const override;

        OPENSOLID_CORE_EXPORT
        void
        evaluateJacobianImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const override;
        
        OPENSOLID_CORE_EXPORT
        void
        evaluateJacobianImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        derivativeImpl(int parameterIndex) const override;

        OPENSOLID_CORE_EXPORT
        bool
        isDuplicateOfImpl(const ExpressionImplementationPtr& other) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        scalarMultiplicationImpl(double scale) const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        matrixMultiplicationImpl(const MatrixXd& matrix) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        vectorAdditionImpl(const VectorXd& vector) const override;
        
        OPENSOLID_CORE_EXPORT
        void
        debugImpl(std::ostream& stream, int indent) const override;
    public:
        OPENSOLID_CORE_EXPORT
        LinearExpression(const VectorXd& originPoint, const MatrixXd& basisMatrix);
        
        const VectorXd&
        originPoint() const;

        const MatrixXd&
        basisMatrix() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline
    const VectorXd&
    LinearExpression::originPoint() const {
        return _originPoint;
    }

    inline
    const MatrixXd&
    LinearExpression::basisMatrix() const {
        return _basisMatrix;
    }
}
