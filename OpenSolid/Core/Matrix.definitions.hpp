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

#include <OpenSolid/Core/Matrix.declarations.hpp>

#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

#include <array>
#include <vector>

namespace opensolid
{
    template <class TScalar, int iNumRows, int iNumColumns>
    class Matrix :
        public detail::MatrixInterface<Matrix<TScalar, iNumRows, iNumColumns>>
    {
    private:
        std::array<TScalar, iNumRows * iNumColumns>  _data;

        template <class TOtherScalar, int iOtherNumRows, int iOtherNumColumns> friend class Matrix;

        explicit
        Matrix(bool);
    public:
        static_assert(iNumRows > 0, "Matrices must have at least one row");
        static_assert(iNumColumns > 0, "Matrices must have at least one column");

        Matrix();

        Matrix(const std::pair<int, int>& dimensions);

        Matrix(const Matrix<TScalar, iNumRows, iNumColumns>& other);

        Matrix(const Matrix<TScalar, -1, iNumColumns>& other);

        Matrix(const Matrix<TScalar, iNumRows, -1>& other);

        Matrix(const Matrix<TScalar, -1, -1>& other);
       
        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);
        
        Matrix(
            TScalar firstComponent,
            TScalar secondComponent
        );
        
        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent
        );
        
        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent,
            TScalar fourthComponent
        );
        
        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent,
            TScalar fourthComponent,
            TScalar fifthComponent
        );
        
        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent,
            TScalar fourthComponent,
            TScalar fifthComponent,
            TScalar sixthComponent
        );

        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent,
            TScalar fourthComponent,
            TScalar fifthComponent,
            TScalar sixthComponent,
            TScalar seventhComponent
        );
        
        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent,
            TScalar fourthComponent,
            TScalar fifthComponent,
            TScalar sixthComponent,
            TScalar seventhComponent,
            TScalar eighthComponent
        );
        
        Matrix(
            TScalar firstComponent, 
            TScalar secondComponent, 
            TScalar thirdComponent,
            TScalar fourthComponent,
            TScalar fifthComponent,
            TScalar sixthComponent,
            TScalar seventhComponent,
            TScalar eighthComponent,
            TScalar ninthComponent
        );

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        numRows() const;

        int
        numColumns() const;

        int
        numComponents() const;

        int
        columnStrideInBytes() const;

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        static Matrix<TScalar, iNumRows, iNumColumns>
        constant(TScalar value);

        static Matrix<TScalar, iNumRows, iNumColumns>
        ZERO();

        static Matrix<TScalar, iNumRows, iNumColumns>
        ONES();

        static Matrix<TScalar, iNumRows, iNumColumns>
        IDENTITY();

        static Matrix<TScalar, iNumRows, iNumColumns>
        random();

        template <class TFirstDerived, class TSecondDerived>
        static Matrix<TScalar, iNumRows, iNumColumns>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn
        );

        template <class TFirstDerived, class TSecondDerived, class TThirdDerived>
        static Matrix<TScalar, iNumRows, iNumColumns>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn,
            const detail::MatrixInterface<TThirdDerived>& thirdColumn
        );
    };

    typedef Matrix<double, 2, 1> ColumnMatrix2d;
    typedef Matrix<double, 3, 1> ColumnMatrix3d;
    typedef Matrix<double, 1, 2> RowMatrix2d;
    typedef Matrix<double, 2, 2> Matrix2d;
    typedef Matrix<double, 3, 2> Matrix3x2;
    typedef Matrix<double, 1, 3> RowMatrix3d;
    typedef Matrix<double, 2, 3> Matrix2x3;
    typedef Matrix<double, 3, 3> Matrix3d;

    typedef Matrix<Interval, 2, 1> IntervalColumnMatrix2d;
    typedef Matrix<Interval, 3, 1> IntervalColumnMatrix3d;
    typedef Matrix<Interval, 1, 2> IntervalRowMatrix2d;
    typedef Matrix<Interval, 2, 2> IntervalMatrix2d;
    typedef Matrix<Interval, 3, 2> IntervalMatrix3x2;
    typedef Matrix<Interval, 1, 3> IntervalRowMatrix3d;
    typedef Matrix<Interval, 2, 3> IntervalMatrix2x3;
    typedef Matrix<Interval, 3, 3> IntervalMatrix3d;

    template <class TScalar>
    class Matrix<TScalar, 1, 1> :
        public detail::MatrixInterface<Matrix<TScalar, 1, 1>>
    {
    private:
        TScalar _value;
    public:
        Matrix();

        Matrix(const std::pair<int, int>& dimensions);

        Matrix(TScalar value);
       
        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        numRows() const;

        int
        numColumns() const;

        int
        numComponents() const;

        int
        columnStrideInBytes() const;

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        operator TScalar() const;

        static Matrix<TScalar, 1, 1>
        constant(TScalar value);

        static Matrix<TScalar, 1, 1>
        ZERO();

        static Matrix<TScalar, 1, 1>
        ONES();

        static Matrix<TScalar, 1, 1>
        IDENTITY();

        static Matrix<TScalar, 1, 1>
        random();
    };

    typedef Matrix<double, 1, 1> Matrix1d;
    typedef Matrix<Interval, 1, 1> IntervalMatrix1d;

    template <class TScalar, int iNumColumns>
    class Matrix<TScalar, -1, iNumColumns> :
        public detail::MatrixInterface<Matrix<TScalar, -1, iNumColumns>>
    {
    private:
        std::vector<TScalar> _data;
        int _numRows;

        template <class TOtherScalar, int iOtherNumRows, int iOtherNumColumns> friend class Matrix;
    public:
        static_assert(iNumColumns > 0, "Matrices must have at least one column");

        explicit
        Matrix(int numRows);

        explicit
        Matrix(const std::pair<int, int>& dimensions);
       
        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);
        
        Matrix(const Matrix<TScalar, -1, iNumColumns>& other);

        Matrix(Matrix<TScalar, -1, iNumColumns>&& other);

        Matrix(Matrix<TScalar, -1, -1>&& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        numRows() const;

        int
        numColumns() const;

        int
        numComponents() const;

        int
        columnStrideInBytes() const;

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        static Matrix<TScalar, -1, iNumColumns>
        constant(int numRows, TScalar value);

        static Matrix<TScalar, -1, iNumColumns>
        zero(int numRows);

        static Matrix<TScalar, -1, iNumColumns>
        ones(int numRows);

        static Matrix<TScalar, -1, iNumColumns>
        identity(int numRows);

        static Matrix<TScalar, -1, iNumColumns>
        random(int numRows);

        template <class TFirstDerived, class TSecondDerived>
        static Matrix<TScalar, -1, iNumColumns>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn
        );

        template <class TFirstDerived, class TSecondDerived, class TThirdDerived>
        static Matrix<TScalar, -1, iNumColumns>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn,
            const detail::MatrixInterface<TThirdDerived>& thirdColumn
        );
    };

    typedef Matrix<double, -1, 1> ColumnMatrixXd;
    typedef Matrix<double, -1, 2> MatrixXx2;
    typedef Matrix<double, -1, 3> MatrixXx3;

    typedef Matrix<Interval, -1, 1> IntervalColumnMatrixXd;
    typedef Matrix<Interval, -1, 2> IntervalMatrixXx2;
    typedef Matrix<Interval, -1, 3> IntervalMatrixXx3;

    template <class TScalar, int iNumRows>
    class Matrix<TScalar, iNumRows, -1> :
        public detail::MatrixInterface<Matrix<TScalar, iNumRows, -1>>
    {
    private:
        std::vector<TScalar> _data;
        int _numColumns;

        template <class TOtherScalar, int iOtherNumRows, int iOtherNumColumns> friend class Matrix;
    public:
        static_assert(iNumRows > 0, "Matrices must have at least one row");

        explicit
        Matrix(int numColumns);

        explicit
        Matrix(const std::pair<int, int>& dimensions);
       
        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);
        
        Matrix(const Matrix<TScalar, iNumRows, -1>& other);

        Matrix(Matrix<TScalar, iNumRows, -1>&& other);

        Matrix(Matrix<TScalar, -1, -1>&& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        numRows() const;

        int
        numColumns() const;

        int
        numComponents() const;

        int
        columnStrideInBytes() const;

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        static Matrix<TScalar, iNumRows, -1>
        constant(int numColumns, TScalar value);

        static Matrix<TScalar, iNumRows, -1>
        zero(int numColumns);

        static Matrix<TScalar, iNumRows, -1>
        ones(int numColumns);

        static Matrix<TScalar, iNumRows, -1>
        identity(int numColumns);

        static Matrix<TScalar, iNumRows, -1>
        random(int numColumns);

        template <class TFirstDerived, class TSecondDerived>
        static Matrix<TScalar, iNumRows, -1>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn
        );

        template <class TFirstDerived, class TSecondDerived, class TThirdDerived>
        static Matrix<TScalar, iNumRows, -1>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn,
            const detail::MatrixInterface<TThirdDerived>& thirdColumn
        );
    };

    typedef Matrix<double, 1, -1> RowMatrixXd;
    typedef Matrix<double, 2, -1> Matrix2xX;
    typedef Matrix<double, 3, -1> Matrix3xX;

    typedef Matrix<Interval, 1, -1> IntervalRowMatrixXd;
    typedef Matrix<Interval, 2, -1> IntervalMatrix2xX;
    typedef Matrix<Interval, 3, -1> IntervalMatrix3xX;

    template <class TScalar>
    class Matrix<TScalar, -1, -1> :
        public detail::MatrixInterface<Matrix<TScalar, -1, -1>>
    {
    private:
        std::vector<TScalar> _data;
        int _numRows;
        int _numColumns;

        template <class TOtherScalar, int iOtherNumRows, int iOtherNumColumns> friend class Matrix;
    public:
        Matrix(int numRows, int numColumns);

        Matrix(const std::pair<int, int>& dimensions);

        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);
        
        Matrix(const Matrix<TScalar, -1, -1>& other);

        Matrix(Matrix<TScalar, -1, -1>&& other);

        template <int iNumRows>
        Matrix(Matrix<TScalar, iNumRows, -1>&& other);

        template <int iNumColumns>
        Matrix(Matrix<TScalar, -1, iNumColumns>&& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        numRows() const;

        int
        numColumns() const;

        int
        numComponents() const;

        int
        columnStrideInBytes() const;

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        static Matrix<TScalar, -1, -1>
        constant(int numRows, int numColumns, TScalar value);

        static Matrix<TScalar, -1, -1>
        zero(int numRows, int numColumns);

        static Matrix<TScalar, -1, -1>
        ones(int numRows, int numColumns);

        static Matrix<TScalar, -1, -1>
        identity(int numRows, int numColumns);

        static Matrix<TScalar, -1, -1>
        random(int numRows, int numColumns);

        template <class TFirstDerived, class TSecondDerived>
        static Matrix<TScalar, -1, -1>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn
        );

        template <class TFirstDerived, class TSecondDerived, class TThirdDerived>
        static Matrix<TScalar, -1, -1>
        fromColumns(
            const detail::MatrixInterface<TFirstDerived>& firstColumn,
            const detail::MatrixInterface<TSecondDerived>& secondColumn,
            const detail::MatrixInterface<TThirdDerived>& thirdColumn
        );
    };

    typedef Matrix<double, -1, -1> MatrixXd;
    typedef Matrix<Interval, -1, -1> IntervalMatrixXd;

    template <class TScalar, int iNumRows, int iNumColumns>
    struct MatrixTraits<Matrix<TScalar, iNumRows, iNumColumns>>
    {
        typedef TScalar Scalar;
        typedef typename std::remove_const<TScalar>::type PlainScalar;
        typedef const PlainScalar ConstScalar;
        static const int NumRows = iNumRows;
        static const int NumColumns = iNumColumns;
        static const int ColumnStrideInBytes = (
            iNumRows == -1 ?
            -1 :
            iNumRows * int(sizeof(TScalar))
        );
    };

    template <class TScalar, int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iNumRows, iNumColumns>& matrix);
}
