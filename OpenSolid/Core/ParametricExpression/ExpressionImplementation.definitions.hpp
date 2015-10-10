/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.declarations.hpp>

#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/MatrixView.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/DeduplicationCache.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionCompiler.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/MatrixID.declarations.hpp>

#include <vector>
#include <memory>

namespace opensolid
{
    namespace detail
    {
        class ExpressionImplementation :
            public std::enable_shared_from_this<ExpressionImplementation>
        {
        private:
            OPENSOLID_CORE_EXPORT
            virtual int
            numDimensionsImpl() const = 0;

            OPENSOLID_CORE_EXPORT
            virtual int
            numParametersImpl() const = 0;

            OPENSOLID_CORE_EXPORT
            virtual void
            evaluateImpl(
                const MatrixID<const double>& parameterID,
                const MatrixID<double>& resultView,
                ExpressionCompiler<double>& expressionCompiler
            ) const = 0;
            
            OPENSOLID_CORE_EXPORT
            virtual void
            evaluateImpl(
                const MatrixID<const Interval>& parameterID,
                const MatrixID<Interval>& resultView,
                ExpressionCompiler<Interval>& expressionCompiler
            ) const = 0;

            OPENSOLID_CORE_EXPORT
            virtual void
            evaluateJacobianImpl(
                const MatrixID<const double>& parameterID,
                const MatrixID<double>& resultView,
                ExpressionCompiler<double>& expressionCompiler
            ) const = 0;
            
            OPENSOLID_CORE_EXPORT
            virtual void
            evaluateJacobianImpl(
                const MatrixID<const Interval>& parameterID,
                const MatrixID<Interval>& resultView,
                ExpressionCompiler<Interval>& expressionCompiler
            ) const = 0;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            derivativeImpl(int parameterIndex) const = 0;

            OPENSOLID_CORE_EXPORT
            virtual bool
            isDuplicateOfImpl(const ExpressionImplementationPtr& other) const = 0;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            deduplicatedImpl(DeduplicationCache& deduplicationCache) const = 0;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            composedImpl(const ExpressionImplementationPtr& innerExpression) const;

            OPENSOLID_CORE_EXPORT 
            virtual ExpressionImplementationPtr
            componentsImpl(int startIndex, int numComponents) const;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            scalingImpl(double scale) const;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            translationImpl(const ColumnMatrixXd& columnMatrix) const;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            transformationImpl(const MatrixXd& matrix) const;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            normImpl() const;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            normalizedImpl() const;
            
            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            squaredNormImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            negatedImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            sqrtImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            sinImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            cosImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            tanImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            acosImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            asinImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            expImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual ExpressionImplementationPtr
            logImpl() const;

            OPENSOLID_CORE_EXPORT
            virtual void
            debugImpl(std::ostream& stream, int indent) const = 0;

            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr operator-(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr operator+(const ExpressionImplementationPtr&, const ColumnMatrixXd&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr operator*(double, const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr operator*(const MatrixXd&, const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr sqrt(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr sin(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr cos(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr tan(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr acos(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr asin(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr exp(const ExpressionImplementationPtr&);
            friend OPENSOLID_CORE_EXPORT ExpressionImplementationPtr log(const ExpressionImplementationPtr&);
        protected:
            ExpressionImplementationPtr
            self() const;
        public:
            OPENSOLID_CORE_EXPORT
            virtual
            ~ExpressionImplementation();

            bool
            isConstantExpression() const;
            
            bool
            isIdentityExpression() const;
            
            bool
            isParameterExpression() const;

            bool
            isComponentsExpression() const;

            template <class TExpressionImplementation>
            const TExpressionImplementation*
            cast() const;

            int
            numDimensions() const;
            
            int
            numParameters() const;
            
            void
            evaluate(
                const MatrixID<const double>& parameterID,
                const MatrixID<double>& resultID,
                ExpressionCompiler<double>& expressionCompiler
            ) const;
            
            void
            evaluate(
                const MatrixID<const Interval>& parameterID,
                const MatrixID<Interval>& resultID,
                ExpressionCompiler<Interval>& expressionCompiler
            ) const;
            
            void
            evaluateJacobian(
                const MatrixID<const double>& parameterID,
                const MatrixID<double>& resultID,
                ExpressionCompiler<double>& expressionCompiler
            ) const;

            void
            evaluateJacobian(
                const MatrixID<const Interval>& parameterID,
                const MatrixID<Interval>& resultID,
                ExpressionCompiler<Interval>& expressionCompiler
            ) const;
            
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            derivative(int parameterIndex = 0) const;

            OPENSOLID_CORE_EXPORT
            bool
            isDuplicateOf(const ExpressionImplementationPtr& other) const;
            
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            deduplicated(DeduplicationCache& deduplicationCache) const;
            
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            composed(const ExpressionImplementationPtr& innerExpression) const;
             
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            components(int startIndex, int numComponents) const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            component(int index) const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            x() const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            y() const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            z() const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            concatenated(const ExpressionImplementationPtr& other) const;
            
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            norm() const;
            
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            normalized() const;
            
            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            squaredNorm() const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            dot(const ExpressionImplementationPtr& other) const;

            OPENSOLID_CORE_EXPORT
            ExpressionImplementationPtr
            cross(const ExpressionImplementationPtr& other) const;

            OPENSOLID_CORE_EXPORT
            void
            debug(std::ostream& stream, int indent) const;
        };

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator-(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator+(
            const ExpressionImplementationPtr& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator+(
            const ExpressionImplementationPtr& argument,
            const ColumnMatrixXd& columnMatrix
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator+(
            const ColumnMatrixXd& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator+(
            const ExpressionImplementationPtr& firstArgument,
            double secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator+(
            double firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator-(
            const ExpressionImplementationPtr& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator-(
            const ExpressionImplementationPtr& firstArgument,
            const ColumnMatrixXd& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator-(
            const ColumnMatrixXd& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator-(
            const ExpressionImplementationPtr& firstArgument,
            double secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator-(
            double firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator*(
            const ExpressionImplementationPtr& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator*(
            const ExpressionImplementationPtr& firstArgument,
            const ColumnMatrixXd& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator*(
            const MatrixXd& matrix,
            const ExpressionImplementationPtr& argument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator*(
            const ExpressionImplementationPtr& firstArgument,
            double secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator*(
            double scale,
            const ExpressionImplementationPtr& argument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator/(
            const ExpressionImplementationPtr& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator/(
            const ColumnMatrixXd& firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator/(
            const ExpressionImplementationPtr& firstArgument,
            double secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        operator/(
            double firstArgument,
            const ExpressionImplementationPtr& secondArgument
        );

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        sqrt(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        sin(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        cos(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        tan(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        acos(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        asin(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        exp(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        log(const ExpressionImplementationPtr& argument);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        pow(double base, const ExpressionImplementationPtr& exponent);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        pow(const ExpressionImplementationPtr& base, double exponent);

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        pow(const ExpressionImplementationPtr& base, const ExpressionImplementationPtr& exponent);
    }
}
