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

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <vector>

namespace Eigen
{
    namespace internal
    {
        template <>
        struct significant_decimals_default_impl<opensolid::Interval, false>
        {
            static int
            run();
        };

        template <>
        struct random_impl<opensolid::Interval>
        {
            static opensolid::Interval
            run(
                const opensolid::Interval& lowerInterval,
                const opensolid::Interval& upperInterval
            );

            static opensolid::Interval
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
}

namespace opensolid
{
    typedef Eigen::Matrix<double, 1, Eigen::Dynamic> RowMatrixXd;
    typedef Eigen::Matrix<Interval, 1, Eigen::Dynamic> RowMatrixXI;

    typedef Eigen::Matrix<double, Eigen::Dynamic, 1> ColumnMatrixXd;
    typedef Eigen::Matrix<Interval, Eigen::Dynamic, 1> ColumnMatrixXI;

    typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
    typedef Eigen::Matrix<Interval, Eigen::Dynamic, Eigen::Dynamic> MatrixXI;

    typedef Eigen::Map<
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>,
        Eigen::Unaligned,
        Eigen::Stride<Eigen::Dynamic, 1>
    > MapXd;

    typedef Eigen::Map<
        Eigen::Matrix<Interval, Eigen::Dynamic, Eigen::Dynamic>,
        Eigen::Unaligned,
        Eigen::Stride<Eigen::Dynamic, 1>
    > MapXI;

    typedef Eigen::Map<
        const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>,
        Eigen::Unaligned,
        Eigen::Stride<Eigen::Dynamic, 1>
    > MapXcd;

    typedef Eigen::Map<
        const Eigen::Matrix<Interval, Eigen::Dynamic, Eigen::Dynamic>,
        Eigen::Unaligned,
        Eigen::Stride<Eigen::Dynamic, 1>
    > MapXcI;

    namespace detail
    {
        inline
        MapXcd
        constMap(const double& value);

        inline
        MapXcI
        constMap(const Interval& value);

        template <int iNumRows, int iNumColumns>
        inline
        MapXcd
        constMap(const Matrix<double, iNumRows, iNumColumns>& matrix);

        template <int iNumRows, int iNumColumns>
        inline
        MapXcI
        constMap(const Matrix<Interval, iNumRows, iNumColumns>& matrix);

        inline
        MapXcd
        constMap(const std::vector<double>& values);

        inline
        MapXcI
        constMap(const std::vector<Interval>& values);

        template <int iNumRows>
        inline
        MapXcd
        constMap(const std::vector<Matrix<double, iNumRows, 1>>& matrices);

        template <int iNumRows>
        inline
        MapXcI
        constMap(const std::vector<Matrix<Interval, iNumRows, 1>>& matrices);

        template <int iNumRows, int iNumColumns>
        inline
        MapXd
        mutableMap(Matrix<double, iNumRows, iNumColumns>& matrix);

        template <int iNumRows, int iNumColumns>
        inline
        MapXI
        mutableMap(Matrix<Interval, iNumRows, iNumColumns>& matrix);

        inline
        MapXd
        mutableMap(std::vector<double>& values);

        inline
        MapXI
        mutableMap(std::vector<Interval>& values);

        template <int iNumRows>
        inline
        MapXd
        mutableMap(std::vector<Matrix<double, iNumRows, 1>>& matrices);

        template <int iNumRows>
        inline
        MapXI
        mutableMap(std::vector<Matrix<Interval, iNumRows, 1>>& matrices);
    }
}

////////// Implementation //////////

namespace Eigen
{
    namespace internal
    {
        inline
        int
        significant_decimals_default_impl<opensolid::Interval, false>::run() {
            return 17;
        }

        inline
        opensolid::Interval
        random_impl<opensolid::Interval>::run(
            const opensolid::Interval& lowerInterval,
            const opensolid::Interval& upperInterval
        ) {
            opensolid::Interval interval(
                lowerInterval.lowerBound(),
                upperInterval.upperBound()
            );
            return interval.interpolated(opensolid::Interval::Random());
        }

        inline
        opensolid::Interval
        random_impl<opensolid::Interval>::run() {
            return opensolid::Interval::Random();
        }
    }

    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::dummy_precision() {
        return 1e-12;
    }
    
    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::highest() {
        return std::numeric_limits<double>::max();
    }
}

namespace opensolid
{
    namespace detail
    {
        inline
        MapXcd
        constMap(const double& value) {
            return MapXcd(&value, 1, 1, Eigen::Stride<Eigen::Dynamic, 1>(1, 1));
        }

        inline
        MapXcI
        constMap(const Interval& value) {
            return MapXcI(&value, 1, 1, Eigen::Stride<Eigen::Dynamic, 1>(1, 1));
        }

        template <int iNumRows, int iNumColumns>
        inline
        MapXcd
        constMap(const Matrix<double, iNumRows, iNumColumns>& matrix) {
            return MapXcd(
                matrix.data(),
                iNumRows,
                iNumColumns,
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        template <int iNumRows, int iNumColumns>
        inline
        MapXcI
        constMap(const Matrix<Interval, iNumRows, iNumColumns>& matrix) {
            return MapXcI(
                matrix.data(),
                iNumRows,
                iNumColumns,
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        inline
        MapXcd
        constMap(const std::vector<double>& values) {
            return MapXcd(
                &values.front(),
                1,
                values.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(1, 1)
            );
        }

        inline
        MapXcI
        constMap(const std::vector<Interval>& values) {
            return MapXcI(
                &values.front(),
                1,
                values.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(1, 1)
            );
        }

        template <int iNumRows>
        inline
        MapXcd
        constMap(const std::vector<Matrix<double, iNumRows, 1>>& matrices) {
            return MapXcd(
                matrices.front().data(),
                iNumRows,
                matrices.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        template <int iNumRows>
        inline
        MapXcI
        constMap(const std::vector<Matrix<Interval, iNumRows, 1>>& matrices) {
            return MapXcI(
                matrices.front().data(),
                iNumRows,
                matrices.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        template <int iNumRows, int iNumColumns>
        inline
        MapXd
        mutableMap(Matrix<double, iNumRows, iNumColumns>& matrix) {
            return MapXd(
                matrix.data(),
                iNumRows,
                iNumColumns,
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        template <int iNumRows, int iNumColumns>
        inline
        MapXI
        mutableMap(Matrix<Interval, iNumRows, iNumColumns>& matrix) {
            return MapXI(
                matrix.data(),
                iNumRows,
                iNumColumns,
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        inline
        MapXd
        mutableMap(std::vector<double>& values) {
            return MapXd(
                &values.front(),
                1,
                values.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(1, 1)
            );
        }

        inline
        MapXI
        mutableMap(std::vector<Interval>& values) {
            return MapXI(
                &values.front(),
                1,
                values.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(1, 1)
            );
        }

        template <int iNumRows>
        inline
        MapXd
        mutableMap(std::vector<Matrix<double, iNumRows, 1>>& matrices) {
            return MapXd(
                matrices.front().data(),
                iNumRows,
                matrices.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }

        template <int iNumRows>
        inline
        MapXI
        mutableMap(std::vector<Matrix<Interval, iNumRows, 1>>& matrices) {
            return MapXI(
                matrices.front().data(),
                iNumRows,
                matrices.size(),
                Eigen::Stride<Eigen::Dynamic, 1>(iNumRows, 1)
            );
        }
    }
}
