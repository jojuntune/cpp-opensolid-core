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

#include <OpenSolid/Core/ParametricExpression/Bytecode/Bytecode.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        class Bytecode
        {
        public:
            enum Instruction
            {
                DBL_ADD_DBL,
                VEC2_ADD_VEC2,
                VEC3_ADD_VEC3,
                INT_ADD_INT,
                BOX2_ADD_BOX2,
                BOX3_ADD_BOX3,
                INT_ADD_DBL,
                BOX2_ADD_VEC2,
                BOX3_ADD_VEC3,

                DBL_SUB_DBL,
                VEC2_SUB_VEC2,
                VEC3_SUB_VEC3,
                INT_SUB_INT,
                BOX2_SUB_BOX2,
                BOX3_SUB_BOX3,
                INT_SUB_DBL,
                BOX2_SUB_VEC2,
                BOX3_SUB_VEC3,

                DBL_MUL_DBL,
                VEC2_MUL_DBL,
                VEC3_MUL_DBL,
                INT_MUL_INT,
                BOX2_MUL_INT,
                BOX3_MUL_INT,
                INT_MUL_DBL,
                BOX2_MUL_DBL,
                BOX3_MUL_DBL,

                DBL_DIV_DBL,
                VEC2_DIV_DBL,
                VEC3_DIV_DBL,
                INT_DIV_INT,
                BOX2_DIV_INT,
                BOX3_DIV_INT,
                INT_DIV_DBL,
                BOX2_DIV_DBL,
                BOX3_DIV_DBL,

                VEC2_NORMALIZE,
                VEC3_NORMALIZE,
                BOX2_NORMALIZE,
                BOX3_NORMALIZE

                DBL_EQ_DBL,
                VEC2_EQ_VEC2,
                VEC3_EQ_VEC3,
                INT_EQ_INT,
                BOX2_EQ_BOX2,
                BOX3_EQ_BOX3,
                INT_EQ_DBL,
                BOX2_EQ_VEC2,
                BOX3_EQ_VEC3,

                INT_EQ_DBL_SUB_INT,
                BOX2_EQ_VEC2_SUB_BOX2,
                BOX3_EQ_VEC3_SUB_BOX3,

                INT_EQ_DBL_MUL_INT,
                BOX2_EQ_VEC2_MUL_INT,
                BOX3_EQ_VEC3_MUL_INT,

                INT_EQ_DBL_DIV_INT,
                BOX2_EQ_VEC2_DIV_INT,
                BOX3_EQ_VEC3_DIV_INT,

                DBL_EQ_VEC2_DOT_VEC2,
                DBL_EQ_VEC3_DOT_VEC3,
                INT_EQ_BOX2_DOT_BOX2,
                INT_EQ_BOX3_DOT_BOX3,
                INT_EQ_VEC2_DOT_BOX2,
                INT_EQ_VEC3_DOT_BOX3,
                INT_EQ_BOX2_DOT_VEC2,
                INT_EQ_BOX3_DOT_VEC3,

                VEC3_EQ_VEC3_CROSS_VEC3,
                BOX3_EQ_BOX3_CROSS_BOX3,
                BOX3_EQ_VEC3_CROSS_BOX3,
                BOX3_EQ_BOX3_CROSS_VEC3,

                DBL_EQ_VEC2_SQUARED_NORM,
                DBL_EQ_VEC3_SQUARED_NORM,
                INT_EQ_BOX2_SQUARED_NORM,
                INT_EQ_BOX3_SQUARED_NORM,
                DBL_EQ_VEC2_NORM,
                DBL_EQ_VEC3_NORM,
                INT_EQ_BOX2_NORM,
                INT_EQ_BOX3_NORM
            };
        };   
    }
}
