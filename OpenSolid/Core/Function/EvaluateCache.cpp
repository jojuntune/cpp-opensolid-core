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

#include <OpenSolid/Core/Function/EvaluateCache.hpp>

#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>
#include <OpenSolid/Core/Matrix.hpp>

#include <unordered_map>

namespace opensolid
{
    namespace
    {
        template <class TScalar>
        const TScalar*
        dataPointer(const ConstantFunction* constantFunction);

        template <>
        const double*
        dataPointer<double>(const ConstantFunction* constantFunction) {
            return &constantFunction->vector().coeffRef(0);
        }

        template <>
        const Interval*
        dataPointer<Interval>(const ConstantFunction* constantFunction) {
            return &constantFunction->bounds().coeffRef(0);
        }
    }

    template <class TScalar>
    typename EvaluateCache<TScalar>::MapType
    EvaluateCache<TScalar>::results(
        const Function& function,
        const typename EvaluateCache<TScalar>::MapType& parameterValues
    ) {
        const FunctionImplementation* implementation = function.implementation();
        if (implementation->asIdentity()) {
            // Identity function: simply return parameter values map as-is
            return parameterValues;
        } else if (const ParameterFunction* parameterFunction = implementation->asParameter()) {
            // Parameter function: build map pointing to a single row of data within the given
            // parameter values
            int index = parameterFunction->index();
            Stride<Dynamic, Dynamic> stride(parameterValues.outerStride(), 1);
            const TScalar* data = &parameterValues.coeffRef(index, 0);
            return MapType(data, 1, parameterValues.cols(), stride);
        } else if (const ConstantFunction* constantFunction = implementation->asConstant()) {
            // Constant function: build map pointing to constant data (using an outer stride of
            // zero allows the single column of data within the ConstantFunction to be used to
            // represent a matrix of arbitrary number of columns)
            Stride<Dynamic, Dynamic> stride(0, 1);
            const TScalar* data = dataPointer<TScalar>(constantFunction);
            return MapType(data, constantFunction->numDimensions(), parameterValues.cols(), stride);
        } else {
            // Generic function: return map to cached data, generating data if necessary
            Key key(implementation, parameterValues.data());
            auto iterator = _cachedResults.find(key);
            if (iterator == _cachedResults.end()) {
                // Cached results not found - insert new empty entry into cache
                iterator = _cachedResults.insert(
                    std::pair<const Key, MatrixType>(key, MatrixType())
                ).first;
                MatrixType& resultMatrix = iterator->second;
                // Resize inserted matrix to the correct size
                resultMatrix.resize(implementation->numDimensions(), parameterValues.cols());
                // Construct map pointing to newly allocated results matrix
                Map<Matrix<TScalar, Dynamic, Dynamic>, Unaligned, Stride<Dynamic, Dynamic>> resultMap(
                    resultMatrix.data(),
                    resultMatrix.rows(),
                    resultMatrix.cols(),
                    Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
                );
                // Evaluate function into results matrix using map
                implementation->evaluate(parameterValues, resultMap, *this);
            }
            // Get reference to cached matrix
            const MatrixType& resultMatrix = iterator->second;
            // Return map pointing to cached matrix
            return MapType(
                resultMatrix.data(),
                resultMatrix.rows(),
                resultMatrix.cols(),
                Stride<Dynamic, Dynamic>(resultMatrix.rows(), 1)
            );
        }
    }

    template EvaluateCache<double>::MapType EvaluateCache<double>::results(const Function&, const MapXcd&);
    template EvaluateCache<Interval>::MapType EvaluateCache<Interval>::results(const Function&, const MapXcI&);
}
