/*************************************************************************************
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

#pragma once

#include <OpenSolid/config.hpp>

namespace Eigen
{   
    namespace internal
    {
        template <class TScalar, bool bIsInteger>
        struct significant_decimals_default_impl;

        template<class TScalar>
        struct random_impl;
        
        template <class TScalar>
        struct is_arithmetic;
    }
    
    template <class TScalar>
    struct NumTraits;

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    class Matrix;

    template <class TDerived>
    struct EigenBase;

    template <class TDerived>
    class DenseBase;

    template <class TDerived>
    class MatrixBase;
    
    template <class TMatrix>
    class MatrixIterator;
    
    struct EmptyOperation;
    struct LowerOperation;
    struct UpperOperation;
    struct MedianOperation;
    struct RandomOperation;
    struct WidthOperation;
    struct HullOperation;
    struct IntersectionOperation;

    class OverlapOperation;
    class StrictOverlapOperation;
    class ContainOperation;
    class StrictContainOperation;
}
