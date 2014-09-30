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

#include <OpenSolid/Core/ParametricExpression/EvaluationContext.declarations.hpp>

#include <OpenSolid/Core/MatrixView.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/MatrixID.declarations.hpp>

#include <vector>
#include <cstdint>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        class EvaluationContext
        {
        private:
            MatrixView<const TScalar, -1, -1, -1> _parameterView;
            std::vector<MatrixView<TScalar, -1, -1, -1>> _mutableViews;
            std::vector<TScalar> _memory;
            TScalar* _stackEnd;
            TScalar* _heapStart;
            TScalar* _heapEnd;
        public:
            EvaluationContext(
                const MatrixView<const TScalar, -1, -1, -1>& parameterView,
                MatrixView<TScalar, -1, -1, -1>& resultView,
                int stackSize,
                int heapSize,
                int numTemporaryMatrices
            );

            int
            numColumns() const;

            void
            stackAllocate(int viewIndex, int numRows, int numColumns);

            void
            stackDeallocate(int viewIndex);

            void
            heapAllocate(int viewIndex, int numRows, int numColumns);

            MatrixView<TScalar, -1, -1, -1>
            matrixView(const MatrixID<TScalar>& matrixID);

            MatrixView<const TScalar, -1, -1, -1>
            matrixView(const MatrixID<const TScalar>& matrixID) const;
        };
    }
}
