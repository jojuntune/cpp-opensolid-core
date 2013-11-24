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

#include <OpenSolid/Core/ExpressionImplementation/Evaluator.declarations.hpp>

#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ExpressionImplementation.declarations.hpp>

#include <unordered_map>

namespace opensolid
{
    class Evaluator
    {
    private:
        typedef std::pair<const ExpressionImplementation*, const double*> KeyXd;
        typedef std::pair<const ExpressionImplementation*, const Interval*> KeyXI;
        
        struct KeyHash
        {
            template <class TScalar>
            std::size_t
            operator()(const std::pair<const ExpressionImplementation*, const TScalar*>& key) const;
        };

        typedef std::unordered_map<KeyXd, MatrixXd, Evaluator::KeyHash> CacheXd;
        typedef std::unordered_map<KeyXI, MatrixXI, Evaluator::KeyHash> CacheXI;

        CacheXd _valuesCache;
        CacheXd _jacobianValuesCache;
        CacheXI _boundsCache;
        CacheXI _jacobianBoundsCache;

        template <class TScalar>
        struct Types;

        template <class TScalar>
        friend struct Types;

        template <class TScalar>
        typename Types<TScalar>::ConstMap
        evaluate(
            const ExpressionImplementationPtr& functionImplementation,
            const typename Types<TScalar>::ConstMap& parameterMap,
            typename Types<TScalar>::Cache& cache
        );

        template <class TScalar>
        typename Types<TScalar>::ConstMap
        evaluateJacobian(
            const ExpressionImplementationPtr& functionImplementation,
            const typename Types<TScalar>::ConstMap& parameterMap,
            typename Types<TScalar>::Cache& cache
        );
    public:
        OPENSOLID_CORE_EXPORT
        MapXcd
        evaluate(
            const ExpressionImplementationPtr& functionImplementation,
            const MapXcd& parameterValues
        );
        
        OPENSOLID_CORE_EXPORT
        MapXcd
        evaluateJacobian(
            const ExpressionImplementationPtr& functionImplementation,
            const MapXcd& parameterValues
        );

        OPENSOLID_CORE_EXPORT
        MapXcI
        evaluate(
            const ExpressionImplementationPtr& functionImplementation,
            const MapXcI& parameterBounds
        );
        
        OPENSOLID_CORE_EXPORT
        MapXcI
        evaluateJacobian(
            const ExpressionImplementationPtr& functionImplementation,
            const MapXcI& parameterBounds
        );
    };
}
