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

#include <OpenSolid/Core/FunctionImplementation/JacobianEvaluator.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    namespace
    {
        template <class TScalar>
        struct Types;

        template <>
        struct Types<double>
        {
            typedef MapXd Map;
            typedef MapXcd ConstMap;
            typedef MatrixXd Matrix;
            typedef std::pair<const FunctionImplementation*, const double*> Key;
            typedef std::unordered_map<Key, Matrix> Cache;
        };

        template <>
        struct Types<Interval>
        {
            typedef MapXI Map;
            typedef MapXcI ConstMap;
            typedef MatrixXI Matrix;
            typedef std::pair<const FunctionImplementation*, const Interval*> Key;
            typedef std::unordered_map<Key, Matrix> Cache;
        };

        template <class TScalar>
        inline typename Types<TScalar>::ConstMap
        evaluateJacobian(
            const FunctionImplementationPtr& functionImplementation,
            const typename Types<TScalar>::ConstMap& parameterValues,
            const typename Types<TScalar>::Cache& cache
        ) {
            typedef typename Types<TScalar>::Map Map;
            typedef typename Types<TScalar>::ConstMap ConstMap;
            typedef typename Types<TScalar>::Matrix Matrix;
            typedef typename Types<TScalar>::Key Key;
            typedef typename Types<TScalar>::Cache Cache;

            // Attempt to find cached results for the given function/parameter pair
            Key key(functionImplementation.get(), parameterValues.data());
            auto iterator = cache.find(key);

            if (iterator == cache.end()) {
                // Cached results not found - insert new empty entry into cache and update iterator
                // to point to the new entry
                iterator = cache.insert(std::pair<const Key, Matrix>(key, Matrix())).first;

                // Resize inserted matrix to the correct size
                Matrix& resultMatrix = iterator->second;
                resultMatrix.resize(
                    functionImplementation->numDimensions(),
                    functionImplementation->numParameters()
                );

                // Construct map pointing to newly allocated results matrix
                Map resultMap(
                    resultMatrix.data(),
                    resultMatrix.rows(),
                    resultMatrix.cols(),
                    Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
                );

                // Evaluate function into results matrix using map
                functionImplementation->evaluateJacobian(parameterValues, resultMap, *this);
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

    MapXcd
    JacobianEvaluator::evaluateJacobian(
        const FunctionImplementationPtr& functionImplementation,
        const MapXcd& parameterValues
    ) {
        return evaluateJacobian<double>(functionImplementation, parameterValues, _cachedValues);
    }

    MapXcI
    JacobianEvaluator::evaluateJacobian(
        const FunctionImplementationPtr& functionImplementation,
        const MapXcI& parameterBounds
    ) {
        return evaluateJacobian<Interval>(functionImplementation, parameterBounds, _cachedBounds);
    }
}
