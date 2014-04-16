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

#include <OpenSolid/Core/ParametricExpression/Evaluator.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>
#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

#include <unordered_map>

namespace opensolid
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
        typedef MatrixViewXxX ViewType;
        typedef ConstMatrixViewXxX ConstViewType;
        typedef MatrixXxX MatrixType;
        typedef Evaluator::Key KeyType;
        typedef Evaluator::Cache CacheType;
    };

    template <>
    struct Evaluator::Types<Interval>
    {
        typedef IntervalMatrixViewXxX ViewType;
        typedef ConstIntervalMatrixViewXxX ConstViewType;
        typedef IntervalMatrixXxX MatrixType;
        typedef Evaluator::IntervalKey KeyType;
        typedef Evaluator::IntervalCache CacheType;
    };
    
    namespace
    {
        template <class TScalar>
        const TScalar*
        dataPointer(const ConstantExpression* constantExpression);

        template <>
        const double*
        dataPointer<double>(const ConstantExpression* constantExpression) {
            return constantExpression->colMatrix().data();
        }

        template <>
        const Interval*
        dataPointer<Interval>(const ConstantExpression* constantExpression) {
            return constantExpression->intervalColMatrix().data();
        }
    }

    template <class TScalar>
    inline
    typename Evaluator::Types<TScalar>::ConstViewType
    Evaluator::evaluate(
        const ExpressionImplementationPtr& expressionImplementation,
        const typename Types<TScalar>::ConstViewType& parameterView,
        typename Types<TScalar>::CacheType& cache
    ) {
        typedef typename Types<TScalar>::ViewType ViewType;
        typedef typename Types<TScalar>::ConstViewType ConstViewType;
        typedef typename Types<TScalar>::MatrixType MatrixType;
        typedef typename Types<TScalar>::KeyType KeyType;
        typedef typename Types<TScalar>::CacheType CacheType;

        if (expressionImplementation->isIdentityExpression()) {
            // Identity expression: simply return parameter values map as-is
            return parameterView;
        } else if (expressionImplementation->isParameterExpression()) {
            // Parameter expression: return view pointing to a single row of data within the given
            // parameter values
            return parameterView.row(parameterIndex);
        } else if (expressionImplementation->isConstantExpression()) {
            // Constant expression: build map pointing to constant data (using a stride of  zero
            // allows the single column of data within the ConstantExpression to be used to
            // represent a matrix of arbitrary number of columns)
            return ConstViewType(
                dataPointer<TScalar>(expressionImplementation->cast<ConstantExpression>()),
                expressionImplementation->numDimensions(),
                parameterView.cols(),
                0
            );
        } else {
            // Generic expression: return map to cached data, generating data if necessary
            KeyType key(expressionImplementation.get(), parameterView.data());
            auto iterator = cache.find(key);
            if (iterator == cache.end()) {
                // Cached results not found - insert new empty entry into cache
                MatrixType newMatrix(
                    expressionImplementation->numDimensions(),
                    parameterView.cols()
                );
                iterator = cache.insert(
                    std::pair<const KeyType, MatrixType>(key, std::move(newMatrix))
                ).first;
                MatrixType& resultMatrix = iterator->second;

                // Construct map pointing to newly allocated results matrix
                ViewType resultView(
                    resultMatrix.data(),
                    resultMatrix.rows(),
                    resultMatrix.cols(),
                    resultMatrix.colStride()
                );

                // Evaluate expression into results matrix using map
                expressionImplementation->evaluate(parameterView, resultView, *this);
            }

            // Get reference to cached matrix
            const Matrix& resultMatrix = iterator->second;

            // Return map pointing to cached matrix
            return ConstViewType(
                resultMatrix.data(),
                resultMatrix.rows(),
                resultMatrix.cols(),
                Eigen::Stride<Eigen::Dynamic, 1>(resultMatrix.rows(), 1)
            );
        }
    }

    template <class TScalar>
    inline
    typename Evaluator::Types<TScalar>::ConstViewType
    Evaluator::evaluateJacobian(
        const ExpressionImplementationPtr& expressionImplementation,
        const typename Types<TScalar>::ConstViewType& parameterView,
        typename Types<TScalar>::CacheType& cache
    ) {
        typedef typename Types<TScalar>::ViewType ViewType;
        typedef typename Types<TScalar>::ConstViewType ConstViewType;
        typedef typename Types<TScalar>::MatrixType MatrixType;
        typedef typename Types<TScalar>::KeyType KeyType;
        typedef typename Types<TScalar>::CacheType CacheType;

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
            Matrix& resultMatrix = iterator->second;

            // Construct map pointing to newly allocated results matrix
            ViewType resultView(
                resultMatrix.data(),
                resultMatrix.rows(),
                resultMatrix.cols(),
                resultMatrix.colStride()
            );

            // Evaluate expression into results matrix using map
            expressionImplementation->evaluateJacobian(parameterView, resultView, *this);
        }

        // Get reference to cached matrix
        const MatrixType& resultMatrix = iterator->second;

        // Return map pointing to cached matrix
        return ConstViewType(
            resultMatrix.data(),
            resultMatrix.rows(),
            resultMatrix.cols(),
            resultMatrix.colStride()
        );
    }

    ConstMatrixViewXxX
    Evaluator::evaluate(
        const ExpressionImplementationPtr& expressionImplementation,
        const ConstMatrixViewXxX& parameterView
    ) {
        return evaluate<double>(expressionImplementation, parameterView, _valuesCache);
    }

    ConstMatrixViewXxX
    Evaluator::evaluateJacobian(
        const ExpressionImplementationPtr& expressionImplementation,
        const ConstMatrixViewXxX& parameterView
    ) {
        return evaluateJacobian<double>(
            expressionImplementation,
            parameterView,
            _jacobianValuesCache
        );
    }

    ConstIntervalMatrixViewXxX
    Evaluator::evaluate(
        const ExpressionImplementationPtr& expressionImplementation,
        const ConstIntervalMatrixViewXxX& parameterView
    ) {
        return evaluate<Interval>(expressionImplementation, parameterView, _boundsCache);
    }

    ConstIntervalMatrixViewXxX
    Evaluator::evaluateJacobian(
        const ExpressionImplementationPtr& expressionImplementation,
        const ConstIntervalMatrixViewXxX& parameterView
    ) {
        return evaluateJacobian<Interval>(
            expressionImplementation,
            parameterView,
            _jacobianBoundsCache
        );
    }
}
