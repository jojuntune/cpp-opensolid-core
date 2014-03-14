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

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.definitions.hpp>

namespace opensolid
{
    class ConstantExpression :
        public ExpressionImplementation
    {
    private:
        ColumnMatrixXd _columnMatrixXd;
        ColumnMatrixXI _columnMatrixXI;
        int _numParameters;

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
            const MapXcI& parameterValues,
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
            const MapXcI& parameterValues,
            MapXI& results,
            Evaluator& evaluator
        ) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        derivativeImpl(int index) const override;
        
        OPENSOLID_CORE_EXPORT
        bool
        isDuplicateOfImpl(const ExpressionImplementationPtr& other) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        composedImpl(const ExpressionImplementationPtr& innerExpression) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        componentsImpl(int startIndex, int numComponents) const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        scalingImpl(double scale) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        translationImpl(const ColumnMatrixXd& columnMatrixXd) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        transformationImpl(const MatrixXd& matrixXd) const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        normImpl() const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        normalizedImpl() const override;
        
        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        squaredNormImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        sqrtImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        sinImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        cosImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        tanImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        acosImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        asinImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        expImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        logImpl() const override;
        
        OPENSOLID_CORE_EXPORT
        void
        debugImpl(std::ostream& stream, int indent) const override;
    public:
        OPENSOLID_CORE_EXPORT
        ConstantExpression(const ColumnMatrixXd& columnMatrixXd, int numParameters);

        OPENSOLID_CORE_EXPORT
        ConstantExpression(double value, int numParameters);
        
        const ColumnMatrixXd&
        columnMatrixXd() const;

        double
        value() const;
        
        const ColumnMatrixXI&
        columnMatrixXI() const;

        bool
        isZero(double tolerance = 1e-12) const;
    };
}

namespace opensolid
{
    inline
    const ColumnMatrixXd&
    ConstantExpression::columnMatrixXd() const {
        return _columnMatrixXd;
    }

    inline
    double
    ConstantExpression::value() const {
        return columnMatrixXd().value();
    }

    inline
    const ColumnMatrixXI&
    ConstantExpression::columnMatrixXI() const {
        return _columnMatrixXI;
    }

    inline
    bool
    ConstantExpression::isZero(double tolerance) const {
        return columnMatrixXd().isZero(tolerance);
    }
}
