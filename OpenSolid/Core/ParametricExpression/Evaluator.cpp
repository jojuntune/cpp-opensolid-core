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
        typedef MapXd Map;
        typedef MapXcd ConstMap;
        typedef MatrixXd Matrix;
        typedef Evaluator::KeyXd Key;
        typedef Evaluator::CacheXd Cache;
    };

    template <>
    struct Evaluator::Types<Interval>
    {
        typedef MapXI Map;
        typedef MapXcI ConstMap;
        typedef MatrixXI Matrix;
        typedef Evaluator::KeyXI Key;
        typedef Evaluator::CacheXI Cache;
    };
    
    namespace
    {
        template <class TScalar>
        const TScalar*
        dataPointer(const ConstantExpression* constantExpression);

        template <>
        const double*
        dataPointer<double>(const ConstantExpression* constantExpression) {
            return &constantExpression->vector().coeffRef(0);
        }

        template <>
        const Interval*
        dataPointer<Interval>(const ConstantExpression* constantExpression) {
            return &constantExpression->bounds().coeffRef(0);
        }
    }

    template <class TScalar>
    inline
    typename Evaluator::Types<TScalar>::ConstMap
    Evaluator::evaluate(
        const ExpressionImplementationPtr& expressionImplementation,
        const typename Types<TScalar>::ConstMap& parameterValues,
        typename Types<TScalar>::Cache& cache
    ) {
        typedef typename Types<TScalar>::Map Map;
        typedef typename Types<TScalar>::ConstMap ConstMap;
        typedef typename Types<TScalar>::Matrix Matrix;
        typedef typename Types<TScalar>::Key Key;
        typedef typename Types<TScalar>::Cache Cache;

        if (expressionImplementation->isIdentityExpression()) {
            // Identity expression: simply return parameter values map as-is
            return parameterValues;
        } else if (expressionImplementation->isParameterExpression()) {
            // Parameter expression: build map pointing to a single row of data within the given
            // parameter values
            int parameterIndex =
                expressionImplementation->cast<ParameterExpression>()->parameterIndex();
            Stride<Dynamic, Dynamic> stride(parameterValues.outerStride(), 1);
            const TScalar* dataPtr = &parameterValues.coeffRef(parameterIndex, 0);
            return ConstMap(dataPtr, 1, parameterValues.cols(), stride);
        } else if (expressionImplementation->isConstantExpression()) {
            // Constant expression: build map pointing to constant data (using an outer stride of
            // zero allows the single column of data within the ConstantExpression to be used to
            // represent a matrix of arbitrary number of columns)
            Stride<Dynamic, Dynamic> stride(0, 1);
            const TScalar* dataPtr = dataPointer<TScalar>(
                expressionImplementation->cast<ConstantExpression>()
            );
            return ConstMap(
                dataPtr,
                expressionImplementation->numDimensions(),
                parameterValues.cols(),
                stride
            );
        } else {
            // Generic expression: return map to cached data, generating data if necessary
            Key key(expressionImplementation.get(), parameterValues.data());
            auto iterator = cache.find(key);
            if (iterator == cache.end()) {
                // Cached results not found - insert new empty entry into cache
                iterator = cache.insert(std::pair<const Key, Matrix>(key, Matrix())).first;
                Matrix& resultMatrix = iterator->second;

                // Resize inserted matrix to the correct size
                resultMatrix.resize(
                    expressionImplementation->numDimensions(),
                    parameterValues.cols()
                );

                // Construct map pointing to newly allocated results matrix
                Map resultMap(
                    resultMatrix.data(),
                    resultMatrix.rows(),
                    resultMatrix.cols(),
                    Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
                );

                // Evaluate expression into results matrix using map
                expressionImplementation->evaluate(parameterValues, resultMap, *this);
            }

            // Get reference to cached matrix
            const Matrix& resultMatrix = iterator->second;

            // Return map pointing to cached matrix
            return ConstMap(
                resultMatrix.data(),
                resultMatrix.rows(),
                resultMatrix.cols(),
                Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
            );
        }
    }

    template <class TScalar>
    inline
    typename Evaluator::Types<TScalar>::ConstMap
    Evaluator::evaluateJacobian(
        const ExpressionImplementationPtr& expressionImplementation,
        const typename Types<TScalar>::ConstMap& parameterValues,
        typename Types<TScalar>::Cache& cache
    ) {
        typedef typename Types<TScalar>::Map Map;
        typedef typename Types<TScalar>::ConstMap ConstMap;
        typedef typename Types<TScalar>::Matrix Matrix;
        typedef typename Types<TScalar>::Key Key;
        typedef typename Types<TScalar>::Cache Cache;

        // Attempt to find cached results for the given expression/parameter pair
        Key key(expressionImplementation.get(), parameterValues.data());
        auto iterator = cache.find(key);

        if (iterator == cache.end()) {
            // Cached results not found - insert new empty entry into cache and update iterator
            // to point to the new entry
            iterator = cache.insert(std::pair<const Key, Matrix>(key, Matrix())).first;

            // Resize inserted matrix to the correct size
            Matrix& resultMatrix = iterator->second;
            resultMatrix.resize(
                expressionImplementation->numDimensions(),
                expressionImplementation->numParameters()
            );

            // Construct map pointing to newly allocated results matrix
            Map resultMap(
                resultMatrix.data(),
                resultMatrix.rows(),
                resultMatrix.cols(),
                Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
            );

            // Evaluate expression into results matrix using map
            expressionImplementation->evaluateJacobian(parameterValues, resultMap, *this);
        }

        // Get reference to cached matrix
        const Matrix& resultMatrix = iterator->second;

        // Return map pointing to cached matrix
        return ConstMap(
            resultMatrix.data(),
            resultMatrix.rows(),
            resultMatrix.cols(),
            Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
        );
    }

    MapXcd
    Evaluator::evaluate(
        const ExpressionImplementationPtr& expressionImplementation,
        const MapXcd& parameterValues
    ) {
        return evaluate<double>(expressionImplementation, parameterValues, _valuesCache);
    }

    MapXcd
    Evaluator::evaluateJacobian(
        const ExpressionImplementationPtr& expressionImplementation,
        const MapXcd& parameterValues
    ) {
        return evaluateJacobian<double>(
            expressionImplementation,
            parameterValues,
            _jacobianValuesCache
        );
    }

    MapXcI
    Evaluator::evaluate(
        const ExpressionImplementationPtr& expressionImplementation,
        const MapXcI& parameterBounds
    ) {
        return evaluate<Interval>(expressionImplementation, parameterBounds, _boundsCache);
    }

    MapXcI
    Evaluator::evaluateJacobian(
        const ExpressionImplementationPtr& expressionImplementation,
        const MapXcI& parameterBounds
    ) {
        return evaluateJacobian<Interval>(
            expressionImplementation,
            parameterBounds,
            _jacobianBoundsCache
        );
    }
}
