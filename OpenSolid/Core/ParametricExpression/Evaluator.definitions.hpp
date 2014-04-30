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

#include <OpenSolid/Core/ParametricExpression/Evaluator.declarations.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.definitions.hpp>

#include <unordered_map>

namespace opensolid
{
    class Evaluator
    {
    private:
        typedef std::pair<const ExpressionImplementation*, const double*> Key;
        typedef std::pair<const ExpressionImplementation*, const Interval*> IntervalKey;
        
        struct KeyHash
        {
            template <class TScalar>
            std::size_t
            operator()(const std::pair<const ExpressionImplementation*, const TScalar*>& key) const;
        };

        typedef std::unordered_map<Key, MatrixXd, Evaluator::KeyHash> Cache;

        typedef std::unordered_map<
            IntervalKey,
            IntervalMatrixXd,
            Evaluator::KeyHash
        > IntervalCache;

        Cache _valuesCache;
        Cache _jacobianValuesCache;
        IntervalCache _boundsCache;
        IntervalCache _jacobianBoundsCache;

        template <class TScalar>
        struct Types;

        template <class TScalar>
        friend struct Types;

        template <class TScalar>
        typename Types<TScalar>::ConstView
        evaluate(
            const ExpressionImplementationPtr& functionImplementation,
            const typename Types<TScalar>::ConstView& parameterView,
            typename Types<TScalar>::Cache& cache
        );

        template <class TScalar>
        typename Types<TScalar>::ConstView
        evaluateJacobian(
            const ExpressionImplementationPtr& functionImplementation,
            const typename Types<TScalar>::ConstView& parameterView,
            typename Types<TScalar>::Cache& cache
        );
    public:
        OPENSOLID_CORE_EXPORT
        ConstMatrixViewXd
        evaluate(
            const ExpressionImplementationPtr& functionImplementation,
            const ConstMatrixViewXd& parameterView
        );
        
        OPENSOLID_CORE_EXPORT
        ConstMatrixViewXd
        evaluateJacobian(
            const ExpressionImplementationPtr& functionImplementation,
            const ConstMatrixViewXd& parameterView
        );

        OPENSOLID_CORE_EXPORT
        ConstIntervalMatrixViewXd
        evaluate(
            const ExpressionImplementationPtr& functionImplementation,
            const ConstIntervalMatrixViewXd& parameterView
        );
        
        OPENSOLID_CORE_EXPORT
        ConstIntervalMatrixViewXd
        evaluateJacobian(
            const ExpressionImplementationPtr& functionImplementation,
            const ConstIntervalMatrixViewXd& parameterView
        );
    };
}
