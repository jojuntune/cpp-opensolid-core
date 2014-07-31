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

#include <OpenSolid/Core/ParametricExpression/Evaluator.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>
#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

#include <unordered_map>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        inline
        std::size_t
        Evaluator::KeyHash::operator()(
            const std::pair<const ExpressionImplementation*, const TScalar*>& key
        ) const {
            std::size_t expressionHash = std::hash<const ExpressionImplementation*>()(key.first);
            std::size_t parameterHash = std::hash<const TScalar*>()(key.second);
            return expressionHash ^ parameterHash;
        }
        
        template <>
        struct Evaluator::Types<double>
        {
            typedef MatrixViewXd View;
            typedef ConstMatrixViewXd ConstView;
            typedef MatrixXd Matrix;
            typedef Evaluator::Key Key;
            typedef Evaluator::Cache Cache;
        };

        template <>
        struct Evaluator::Types<Interval>
        {
            typedef IntervalMatrixViewXd View;
            typedef ConstIntervalMatrixViewXd ConstView;
            typedef IntervalMatrixXd Matrix;
            typedef Evaluator::IntervalKey Key;
            typedef Evaluator::IntervalCache Cache;
        };
        
        namespace
        {
            template <class TScalar>
            const TScalar*
            dataPointer(const ConstantExpression* constantExpression);

            template <>
            const double*
            dataPointer<double>(const ConstantExpression* constantExpression) {
                return constantExpression->columnMatrix().data();
            }

            template <>
            const Interval*
            dataPointer<Interval>(const ConstantExpression* constantExpression) {
                return constantExpression->intervalColumnMatrix().data();
            }
        }

        template <class TScalar>
        inline
        typename Evaluator::Types<TScalar>::ConstView
        Evaluator::evaluate(
            const ExpressionImplementationPtr& expressionImplementation,
            const typename Types<TScalar>::ConstView& parameterView,
            typename Types<TScalar>::Cache& cache
        ) {
            typedef typename Types<TScalar>::View ViewType;
            typedef typename Types<TScalar>::ConstView ConstViewType;
            typedef typename Types<TScalar>::Matrix MatrixType;
            typedef typename Types<TScalar>::Key KeyType;
            typedef typename Types<TScalar>::Cache CacheType;

            if (expressionImplementation->isIdentityExpression()) {
                // Identity expression: simply return parameter values view as-is
                return parameterView;
            } else if (expressionImplementation->isParameterExpression()) {
                // Parameter expression: return view pointing to a single row of data within the
                // given parameter values
                int parameterIndex =
                    expressionImplementation->cast<ParameterExpression>()->parameterIndex();
                return parameterView.row(parameterIndex);
            } else if (expressionImplementation->isConstantExpression()) {
                // Constant expression: build view pointing to constant data (using a stride of zero
                // allows the single column of data within the ConstantExpression to be used to
                // represent a matrix of arbitrary number of columns)
                return ConstViewType(
                    dataPointer<TScalar>(expressionImplementation->cast<ConstantExpression>()),
                    expressionImplementation->numDimensions(),
                    parameterView.numColumns(),
                    0
                );
            } else {
                // Generic expression: return view to cached data, generating data if necessary
                KeyType key(expressionImplementation.get(), parameterView.data());
                auto iterator = cache.find(key);
                if (iterator == cache.end()) {
                    // Cached results not found - insert new empty entry into cache
                    MatrixType newMatrix(
                        expressionImplementation->numDimensions(),
                        parameterView.numColumns()
                    );
                    iterator = cache.insert(
                        std::pair<const KeyType, MatrixType>(key, std::move(newMatrix))
                    ).first;
                    MatrixType& resultMatrix = iterator->second;
                    ViewType resultView = resultMatrix.view();

                    // Evaluate expression into results matrix using view
                    expressionImplementation->evaluate(parameterView, resultView, *this);
                }

                // Get reference to cached matrix
                const MatrixType& resultMatrix = iterator->second;

                // Return view pointing to cached matrix
                return resultMatrix.view();
            }
        }

        template <class TScalar>
        inline
        typename Evaluator::Types<TScalar>::ConstView
        Evaluator::evaluateJacobian(
            const ExpressionImplementationPtr& expressionImplementation,
            const typename Types<TScalar>::ConstView& parameterView,
            typename Types<TScalar>::Cache& cache
        ) {
            typedef typename Types<TScalar>::View ViewType;
            typedef typename Types<TScalar>::ConstView ConstViewType;
            typedef typename Types<TScalar>::Matrix MatrixType;
            typedef typename Types<TScalar>::Key KeyType;
            typedef typename Types<TScalar>::Cache CacheType;

            // Attempt to find cached results for the given expression/parameter pair
            KeyType key(expressionImplementation.get(), parameterView.data());
            auto iterator = cache.find(key);

            if (iterator == cache.end()) {
                // Cached results not found - insert new empty entry into cache and update iterator
                // to point to the new entry
                MatrixType newMatrix(
                    expressionImplementation->numDimensions(),
                    expressionImplementation->numParameters()
                );
                iterator = cache.insert(
                    std::pair<const KeyType, MatrixType>(key, std::move(newMatrix))
                ).first;
                MatrixType& resultMatrix = iterator->second;
                ViewType resultView = resultMatrix.view();

                // Evaluate expression into results matrix using view
                expressionImplementation->evaluateJacobian(parameterView, resultView, *this);
            }

            // Get reference to cached matrix
            const MatrixType& resultMatrix = iterator->second;

            // Return view pointing to cached matrix
            return resultMatrix.view();
        }

        ConstMatrixViewXd
        Evaluator::evaluate(
            const ExpressionImplementationPtr& expressionImplementation,
            const ConstMatrixViewXd& parameterView
        ) {
            return evaluate<double>(expressionImplementation, parameterView, _valuesCache);
        }

        ConstMatrixViewXd
        Evaluator::evaluateJacobian(
            const ExpressionImplementationPtr& expressionImplementation,
            const ConstMatrixViewXd& parameterView
        ) {
            return evaluateJacobian<double>(
                expressionImplementation,
                parameterView,
                _jacobianValuesCache
            );
        }

        ConstIntervalMatrixViewXd
        Evaluator::evaluate(
            const ExpressionImplementationPtr& expressionImplementation,
            const ConstIntervalMatrixViewXd& parameterView
        ) {
            return evaluate<Interval>(expressionImplementation, parameterView, _boundsCache);
        }

        ConstIntervalMatrixViewXd
        Evaluator::evaluateJacobian(
            const ExpressionImplementationPtr& expressionImplementation,
            const ConstIntervalMatrixViewXd& parameterView
        ) {
            return evaluateJacobian<Interval>(
                expressionImplementation,
                parameterView,
                _jacobianBoundsCache
            );
        }
    }
}
