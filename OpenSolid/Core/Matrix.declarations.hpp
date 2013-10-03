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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Convertible.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/LinearTransformation.declarations.hpp>
#include <OpenSolid/Core/Mirror.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Projection.declarations.hpp>
#include <OpenSolid/Core/Rotation.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>
#include <OpenSolid/Core/Transplant.declarations.hpp>

namespace Eigen
{
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

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE

#define EIGEN_DENSEBASE_PLUGIN "DenseBasePlugin.hpp"
#define EIGEN_MATRIXBASE_PLUGIN "MatrixBasePlugin.hpp"
#define EIGEN_MATRIX_PLUGIN "MatrixPlugin.hpp"

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include "../../External/Eigen/DenseBasePlugin.hpp"
#include "../../External/Eigen/MatrixBasePlugin.hpp"
#include "../../External/Eigen/MatrixPlugin.hpp"
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace Eigen
{   
    namespace internal
    {
        template <>
        struct significant_decimals_default_impl<opensolid::Interval, false>
        {
            static inline int
            run();
        };
        
        template <>
        struct is_arithmetic<opensolid::Interval>
        {
            static const bool value = true;
        };
    }
    
    template <>
    struct NumTraits<opensolid::Interval>
    {
        typedef opensolid::Interval Real;
        typedef opensolid::Interval NonInteger;
        typedef opensolid::Interval Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static opensolid::Interval
        epsilon();
        
        static opensolid::Interval
        dummy_precision();
        
        static opensolid::Interval
        lowest();
        
        static opensolid::Interval
        highest();  
    };

    typedef Matrix<int, 1, 1> Matrix1i;
    typedef Matrix<double, 1, 1> Matrix1d;
    typedef Matrix<opensolid::Interval, 1, 1> Matrix1I;
    typedef Matrix<bool, 1, 1> Matrix1b;

    typedef Matrix<opensolid::Interval, 2, 1> Vector2I;
    typedef Matrix<opensolid::Interval, 1, 2> RowVector2I;
    typedef Matrix<opensolid::Interval, 2, 2> Matrix2I;
    typedef Matrix<opensolid::Interval, 3, 1> Vector3I;
    typedef Matrix<opensolid::Interval, 1, 3> RowVector3I;
    typedef Matrix<opensolid::Interval, 3, 3> Matrix3I;
    typedef Matrix<opensolid::Interval, Dynamic, 1> VectorXI;
    typedef Matrix<opensolid::Interval, 1, Dynamic> RowVectorXI;
    typedef Matrix<opensolid::Interval, Dynamic, Dynamic> MatrixXI;
    typedef Matrix<opensolid::Interval, 2, Dynamic> Matrix2XI;
    typedef Matrix<opensolid::Interval, Dynamic, 2> MatrixX2I;
    typedef Matrix<opensolid::Interval, 3, Dynamic> Matrix3XI;
    typedef Matrix<opensolid::Interval, Dynamic, 3> MatrixX3I;
    
    typedef Matrix<bool, 2, 1> Vector2b;
    typedef Matrix<bool, 1, 2> RowVector2b;
    typedef Matrix<bool, 2, 2> Matrix2b;
    typedef Matrix<bool, 3, 1> Vector3b;
    typedef Matrix<bool, 1, 3> RowVector3b;
    typedef Matrix<bool, 3, 3> Matrix3b;
    typedef Matrix<bool, Dynamic, 1> VectorXb;
    typedef Matrix<bool, 1, Dynamic> RowVectorXb;
    typedef Matrix<bool, Dynamic, Dynamic> MatrixXb;
    typedef Matrix<bool, 2, Dynamic> Matrix2Xb;
    typedef Matrix<bool, Dynamic, 2> MatrixX2b;
    typedef Matrix<bool, 3, Dynamic> Matrix3Xb;
    typedef Matrix<bool, Dynamic, 3> MatrixX3b;
    
    typedef Map<MatrixXi, Unaligned, Stride<Dynamic, Dynamic>> MapXi;
    typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> MapXd;
    typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXI;
    typedef Map<MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXb;
    
    typedef Map<const MatrixXi, Unaligned, Stride<Dynamic, Dynamic>> MapXci;
    typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> MapXcd;
    typedef Map<const MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXcI;
    typedef Map<const MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXcb;
}

namespace opensolid
{
    using namespace Eigen;
}
