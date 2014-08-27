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

#include <OpenSolid/Core/ParametricExpression/MatrixID.declarations.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionCompiler.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationContext.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        class ConstantExpression;
        
        template <class TScalar>
        class MatrixID
        {
        private:
            int _matrixIndex;
        private:
            MatrixID();

            explicit
            MatrixID(int matrixIndex);

            template <class TOtherScalar>
            friend class MatrixID;
            
            template <class TOtherScalar>
            friend class ExpressionCompiler;

            template <class TOtherScalar>
            friend class EvaluationContext;
        };

        template <class TScalar>
        class MatrixID<const TScalar>
        {
        private:
            enum Type
            {
                INDEXED,
                CONSTANT
            };
        private:
            Type _type;
            int _matrixIndex;
            const ConstantExpression* _constantExpression;

            bool _isBlock;
            int _startRow;
            int _numRows;
        private:
            MatrixID(
                Type type,
                int matrixIndex,
                const ConstantExpression* constantExpression,
                bool isBlock,
                int startRow,
                int numRows
            );
        private:
            MatrixID(int matrixIndex);

            MatrixID(const ConstantExpression* constantExpression);

            template <class TOtherScalar>
            friend class ExpressionCompiler;

            template <class TOtherScalar>
            friend class EvaluationContext;
        public:
            MatrixID();

            MatrixID(MatrixID<TScalar> matrixID);

            MatrixID<const TScalar>
            block(int startRow, int numRows) const;

            bool
            operator<(const MatrixID<const TScalar>& other) const;
        };
    }
}
