/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__MATRIX_HPP
#define OPENSOLID__MATRIX_HPP

#include <type_traits>

#include <OpenSolid/Common/config.hpp>
#include <OpenSolid/Value/Double.hpp>
#include <OpenSolid/Value/Interval.hpp>

namespace Eigen
{
    namespace internal
    {
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;
        
        inline OpenSolid::Double conj(OpenSolid::Double argument) {return argument;}
        
        inline OpenSolid::Double real(OpenSolid::Double argument) {return argument;}
        
        inline OpenSolid::Double imag(OpenSolid::Double) {return 0.0;}
        
        inline OpenSolid::Double abs2(OpenSolid::Double argument) {
            return argument.squaredNorm();
        }
        
        inline int significant_decimals_default_impl<OpenSolid::Double, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
        
        inline const OpenSolid::Interval& conj(const OpenSolid::Interval& argument) {
            return argument;
        }
        
        inline const OpenSolid::Interval& real(const OpenSolid::Interval& argument) {
            return argument;
        }
        
        inline OpenSolid::Interval imag(const OpenSolid::Interval&) {return 0.0;}
        
        inline OpenSolid::Interval abs2(const OpenSolid::Interval& argument) {
            return argument.squaredNorm();
        }
        
        inline int significant_decimals_default_impl<OpenSolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
    }
    
    template <class ScalarType>
    struct NumTraits;

    inline OpenSolid::Double NumTraits<OpenSolid::Double>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::dummy_precision() {
        return OPENSOLID_PRECISION;
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::highest() {
        return std::numeric_limits<double>::max();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::dummy_precision() {
        return OPENSOLID_PRECISION;
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::highest() {
        return std::numeric_limits<double>::max();
    }
}

namespace OpenSolid
{   
    template <class ScalarType, int rows_ = 0, int cols_ = 0>
    class Matrix
    {
    private:
        Eigen::Matrix<ScalarType, rows_, cols_> _matrix;
    public:
        typedef ScalarType Scalar;
        typedef Matrix<Interval, rows_, cols_> Bounds;
        
        Matrix();
        Matrix(ScalarType argument);
        Matrix(ScalarType first_argument, ScalarType second_argument);
        Matrix(ScalarType first_argument, ScalarType second_argument, ScalarType third_argument);
        Matrix(const Matrix<ScalarType, rows_, cols_>& other);
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix(const Matrix<ScalarType, argument_rows_, argument_cols_>& argument);
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix(Matrix<ScalarType, argument_rows_, argument_cols_>&& argument);
        
        Matrix<ScalarType, rows_, cols_>& operator=(
            const Matrix<ScalarType, rows_, cols_>& argument
        );
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix<ScalarType, rows_, cols_> operator=(
            const Matrix<ScalarType, argument_rows_, argument_cols_>& argument
        );
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix<ScalarType, rows_, cols_>::operator=(
            Matrix<ScalarType, argument_rows_, argument_cols_>&& argument
        );
        
        int rows() const;
        int cols() const;
        int size() const;
        
        ScalarType operator()(int index) const;
        ScalarType operator()(int row, int col) const;
        ScalarType& operator()(int index);
        ScalarType& operator()(int row, int col);
        
        const ScalarType* begin() const;
        const ScalarType* end() const;
        ScalarType* begin();
        ScalarType* end();
        
        ScalarType minCoeff() const;
        ScalarType minCoeff(int* index) const;
        ScalarType minCoeff(int* row, int* col) const;
        ScalarType maxCoeff() const;
        ScalarType maxCoeff(int* index) const;
        ScalarType maxCoeff(int* row, int* col) const;Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        Matrix<Double, rows_, cols_> cwiseLower() const;
        Matrix<Double, rows_, cols_> cwiseUpper() const;
        Matrix<Double, rows_, cols_> cwiseMedian() const;
        Matrix<Double, rows_, cols_> cwiseWidth() const;
        
        template <class Type>
        auto cwiseProduct(const Type& argument) const -> Matrix<decltype(ScalarType() * argument(0, 0)), row
        
        template <class FunctionType>
        auto unaryExpr(FunctionType function = FunctionType()) const ->
            decltype(function(Double()));
        
        template <class FunctionType>
        auto binaryExpr(
            Double argument,
            FunctionType function = FunctionType()
        ) const -> decltype(function(Double(), Double()));
        
        Double dot(Double argument) const;
        
        Double inverse() const;
        Double determinant() const;

        Double norm() const;
        Double squaredNorm() const;
        Double normalized() const;
        
        Double transpose() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        Interval hull(Double argument) const;
        Interval intersection(Double argument) const;
        
        bool isZero(double precision = OPENSOLID_PRECISION) const;
        bool isEqualTo(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThan(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThan(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThanOrEqualTo(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThanOrEqualTo(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool overlaps(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isSubsetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSubsetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isSupersetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSupersetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        
        Double& operator+=(Double argument);
        Double& operator-=(Double argument);
        Double& operator*=(Double argument);
        Double& operator/=(Double argument);
        
        static Matrix<ScalarType, rows_, cols_> Zero();
        static Matrix<ScalarType, rows_, cols_> Zero(int size);
        static Matrix<ScalarType, rows_, cols_> Zero(int rows, int cols);
        
        static Matrix<ScalarType, rows_, cols_> Ones();
        static Matrix<ScalarType, rows_, cols_> Ones(int size);
        static Matrix<ScalarType, rows_, cols_> Ones(int rows, int cols);
        
        static Matrix<ScalarType, rows_, cols_> Identity();
        static Matrix<ScalarType, rows_, cols_> Identity(int size);
        
        static Matrix<ScalarType, rows_, cols_> UnitX();
        static Matrix<ScalarType, rows_, cols_> UnitY();
        static Matrix<ScalarType, rows_, cols_> UnitZ();
        static Matrix<ScalarType, rows_, cols_> Unit(int index);
        
        static Matrix<ScalarType, rows_, cols_> LinSpaced(const Interval& range);
        static Matrix<ScalarType, rows_, cols_> LinSpaced(int size, const Interval& range);
    }
    
    class MatrixXD : public Matrix
}

////////// Implementation //////////

namespace OpenSolid
{
}

#endif
