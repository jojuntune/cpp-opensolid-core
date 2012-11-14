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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include "Handle.hpp"

#include <boost/python/slice.hpp>

namespace opensolid
{
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    class MatrixHandle;

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    class MatrixHandleIterator;

    class MatrixXdHandle;
    class MatrixXIHandle;

    class MatrixXdColwiseHandle;
    class MatrixXIColwiseHandle;

    class MatrixXdRowwiseHandle;
    class MatrixXIRowwiseHandle;

    class MatrixXdColwiseHandleIterator;
    class MatrixXIColwiseHandleIterator;

    class MatrixXdRowwiseHandleIterator;
    class MatrixXIRowwiseHandleIterator;

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    class MatrixHandle
    {
    private:
        const MatrixHandleType& derived() const;
        MatrixHandleType& derived();
    public:
        int rows() const;
        int cols() const;
        int size() const;

        ScalarType value() const;
        ScalarType x() const;
        ScalarType y() const;
        ScalarType z() const;

        ScalarType getItemI(int index) const;
        MatrixHandleType getItemS(boost::python::slice indices) const;
        ScalarType getItemII(int row, int col) const;
        MatrixHandleType getItemIS(int row, boost::python::slice cols) const;
        MatrixHandleType getItemSI(boost::python::slice rows, int col) const;
        MatrixHandleType getItemSS(boost::python::slice rows, boost::python::slice cols) const;

        void setItemI(int index, const ScalarType& argument);
        void setItemS(boost::python::slice indices, const MatrixHandleType& argument);
        void setItemII(int row, int col, const ScalarType& argument);
        void setItemIS(int row, boost::python::slice cols, const MatrixHandleType& argument);
        void setItemSI(boost::python::slice rows, int col, const MatrixHandleType& argument);
        void setItemSS(boost::python::slice rows, boost::python::slice cols, const MatrixHandleType& argument);

        MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType> begin() const;
        MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType> end() const;

        ScalarType squaredNorm() const;
        ScalarType norm() const;

        ScalarType determinant() const;
        ScalarType trace() const;

        MatrixHandleType transpose() const;
        MatrixHandleType replicate(int row_factor, int col_factor) const;

        bool isZero() const;
        bool isZeroP(double precision) const;

        MatrixHandleType transformed(const MatrixXdHandle& matrix, const MatrixXdHandle& vector) const;
        MatrixHandleType scaled(double scale, const MatrixXdHandle& point) const;
        MatrixHandleType translatedV(const MatrixXdHandle& vector) const;
        MatrixHandleType translatedD(double distance, const DatumXd& axis) const;
        MatrixHandleType rotatedP(double angle, const MatrixXdHandle& point);
        MatrixHandleType rotatedA(double angle, const DatumXd& axis);
        MatrixHandleType mirrored(const DatumXd& plane);

        static MatrixHandleType Constant(int rows, int cols, const ScalarType& value);
        static MatrixHandleType Zero(int rows, int cols);
        static MatrixHandleType Ones(int rows, int cols);
        static MatrixHandleType Random(int rows, int cols);
        static MatrixHandleType Identity(int rows, int cols);
    };

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    class MatrixHandleIterator
    {
    private:
        MatrixHandleType _matrix_handle;
        int _index;
    public:
        typedef ScalarType value_type;

        MatrixHandleIterator();
        MatrixHandleIterator(const MatrixHandleType& matrix_handle, int index);

        MatrixHandleIterator& operator++() const;
        ScalarType operator*() const;
        bool operator==(const MatrixHandleIterator& other) const;
        bool operator<(const MatrixHandleIterator& other) const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle :
        public Handle<MatrixXd>,
        public MatrixHandle<MatrixXdHandle, MatrixXd, double>
    {
    public:
        MatrixXdHandle();
        explicit MatrixXdHandle(MatrixXd* matrix);

        template <class Derived>
        MatrixXdHandle(const EigenBase<Derived>& expression);

        MatrixXdColwiseHandle colwise() const;
        MatrixXdRowwiseHandle rowwise() const;

        double minCoeff() const;
        double maxCoeff() const;

        MatrixXdHandle normalized() const;
        MatrixXdHandle inverse() const;

        double dotXd(const MatrixXdHandle& other) const;
        Interval dotXI(const MatrixXIHandle& other) const;

        MatrixXdHandle crossXd(const MatrixXdHandle& other) const;
        MatrixXIHandle crossXI(const MatrixXIHandle& other) const;

        MatrixXIHandle hullXd(const MatrixXdHandle& other) const;
        MatrixXIHandle hullXI(const MatrixXIHandle& other) const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle :
        public Handle<MatrixXI>,
        public MatrixHandle<MatrixXIHandle, MatrixXI, Interval>
    {
    public:
        MatrixXIHandle();
        explicit MatrixXIHandle(MatrixXI* matrix);

        template <class Derived>
        MatrixXIHandle(const EigenBase<Derived>& expression);

        MatrixXIColwiseHandle colwise() const;
        MatrixXIRowwiseHandle rowwise() const;

        MatrixXIHandle normalized() const;

        Interval dotXd(const MatrixXdHandle& other) const;
        Interval dotXI(const MatrixXIHandle& other) const;

        MatrixXIHandle crossXd(const MatrixXdHandle& other) const;
        MatrixXIHandle crossXI(const MatrixXIHandle& other) const;

        bool overlaps(const MatrixXIHandle& argument) const;
        bool overlapsP(const MatrixXIHandle& argument, double precision) const;
        bool strictlyOverlaps(const MatrixXIHandle& argument) const;
        bool strictlyOverlapsP(const MatrixXIHandle& argument, double precision) const;

        bool containsXd(const MatrixXdHandle& argument) const;
        bool containsXdP(const MatrixXdHandle& argument, double precision) const;
        bool containsXI(const MatrixXIHandle& argument) const;
        bool containsXIP(const MatrixXIHandle& argument, double precision) const;
        bool strictlyContainsXd(const MatrixXdHandle& argument) const;
        bool strictlyContainsXdP(const MatrixXdHandle& argument, double precision) const;
        bool strictlyContainsXI(const MatrixXIHandle& argument) const;
        bool strictlyContainsXIP(const MatrixXIHandle& argument, double precision) const;

        MatrixXdHandle cwiseLower() const;
        MatrixXdHandle cwiseUpper() const;
        MatrixXdHandle cwiseMedian() const;
        MatrixXdHandle cwiseRandom() const;
        MatrixXdHandle cwiseWidth() const;

        MatrixXIHandle hullXd(const MatrixXdHandle& other) const;
        MatrixXIHandle hullXI(const MatrixXIHandle& other) const;

        MatrixXIHandle intersection(const MatrixXIHandle& other) const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdColwiseHandle
    {
    private:
        MatrixXdHandle _matrix_handle;
    public:
        MatrixXdColwiseHandle();
        MatrixXdColwiseHandle(const MatrixXdHandle& matrix_handle);

        MatrixXdColwiseHandleIterator begin() const;
        MatrixXdColwiseHandleIterator end() const;

        MatrixXdHandle squaredNorm() const;
        MatrixXdHandle norm() const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIColwiseHandle
    {
    private:
        MatrixXIHandle _matrix_handle;
    public:
        MatrixXIColwiseHandle();
        MatrixXIColwiseHandle(const MatrixXIHandle& matrix_handle);

        MatrixXIColwiseHandleIterator begin() const;
        MatrixXIColwiseHandleIterator end() const;

        MatrixXIHandle squaredNorm() const;
        MatrixXIHandle norm() const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdRowwiseHandle
    {
    private:
        MatrixXdHandle _matrix_handle;
    public:
        MatrixXdRowwiseHandle(const MatrixXdHandle& matrix_handle);

        MatrixXdRowwiseHandleIterator begin() const;
        MatrixXdRowwiseHandleIterator end() const;

        MatrixXdHandle squaredNorm() const;
        MatrixXdHandle norm() const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIRowwiseHandle
    {
    private:
        MatrixXIHandle _matrix_handle;
    public:
        MatrixXIRowwiseHandle(const MatrixXIHandle& matrix_handle);

        MatrixXIRowwiseHandleIterator begin() const;
        MatrixXIRowwiseHandleIterator end() const;

        MatrixXIHandle squaredNorm() const;
        MatrixXIHandle norm() const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdColwiseHandleIterator
    {
    private:
        MatrixXdHandle _matrix_handle;
        int _index;
    public:
        typedef MatrixXdHandle value_type;

        MatrixXdColwiseHandleIterator();
        MatrixXdColwiseHandleIterator(const MatrixXdHandle& matrix_handle, int index);

        MatrixXdColwiseHandleIterator& operator++() const;
        MatrixXdHandle operator*() const;
        bool operator==(const MatrixXdColwiseHandleIterator& other) const;
        bool operator<(const MatrixXdColwiseHandleIterator& other) const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIColwiseHandleIterator
    {
    private:
        MatrixXIHandle _matrix_handle;
        int _index;
    public:
        typedef MatrixXIHandle value_type;

        MatrixXIColwiseHandleIterator();
        MatrixXIColwiseHandleIterator(const MatrixXIHandle& matrix_handle, int index);

        MatrixXIColwiseHandleIterator& operator++() const;
        MatrixXIHandle operator*() const;
        bool operator==(const MatrixXIColwiseHandleIterator& other) const;
        bool operator<(const MatrixXIColwiseHandleIterator& other) const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdRowwiseHandleIterator
    {
    private:
        MatrixXdHandle _matrix_handle;
        int _index;
    public:
        typedef MatrixXdHandle value_type;

        MatrixXdRowwiseHandleIterator();
        MatrixXdRowwiseHandleIterator(const MatrixXdHandle& matrix_handle, int index);

        MatrixXdRowwiseHandleIterator& operator++() const;
        MatrixXdHandle operator*() const;
        bool operator==(const MatrixXdRowwiseHandleIterator& other) const;
        bool operator<(const MatrixXdRowwiseHandleIterator& other) const;
    };

    class OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIRowwiseHandleIterator
    {
    private:
        MatrixXIHandle _matrix_handle;
        int _index;
    public:
        typedef MatrixXIHandle value_type;

        MatrixXIRowwiseHandleIterator();
        MatrixXIRowwiseHandleIterator(const MatrixXIHandle& matrix_handle, int index);

        MatrixXIRowwiseHandleIterator& operator++() const;
        MatrixXIHandle operator*() const;
        bool operator==(const MatrixXIRowwiseHandleIterator& other) const;
        bool operator<(const MatrixXIRowwiseHandleIterator& other) const;
    };

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator-(const MatrixXdHandle& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator-(const MatrixXIHandle& argument);

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator+(
        const MatrixXdHandle& first_argument,
        const MatrixXdHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator+(
        const MatrixXdHandle& first_argument,
        const MatrixXIHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator+(
        const MatrixXIHandle& first_argument,
        const MatrixXdHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator+(
        const MatrixXIHandle& first_argument,
        const MatrixXIHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator-(
        const MatrixXdHandle& first_argument,
        const MatrixXdHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator-(
        const MatrixXdHandle& first_argument,
        const MatrixXIHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator-(
        const MatrixXIHandle& first_argument,
        const MatrixXdHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator-(
        const MatrixXIHandle& first_argument,
        const MatrixXIHandle& second_argument
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator*(
        double value,
        const MatrixXdHandle& matrix
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        double value,
        const MatrixXIHandle& matrix
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const Interval& interval,
        const MatrixXdHandle& matrix
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const Interval& interval,
        const MatrixXIHandle& matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator*(
        const MatrixXdHandle& matrix,
        double value
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXIHandle& matrix,
        double value
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXdHandle& matrix,
        const Interval& interval
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXIHandle& matrix,
        const Interval& interval
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator/(
        const MatrixXdHandle& matrix,
        double value
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator/(
        const MatrixXdHandle& matrix,
        const Interval& interval
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator/(
        const MatrixXIHandle& matrix,
        double value
    );
    
    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator/(
        const MatrixXIHandle& matrix,
        const Interval& interval
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator*(
        const MatrixXdHandle& first_matrix,
        const MatrixXdHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXdHandle& first_matrix,
        const MatrixXIHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXIHandle& first_matrix,
        const MatrixXdHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXIHandle& first_matrix,
        const MatrixXIHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator==(
        const MatrixXdHandle& first_matrix,
        const MatrixXdHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator==(
        const MatrixXdHandle& first_matrix,
        const MatrixXIHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator==(
        const MatrixXIHandle& first_matrix,
        const MatrixXdHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator==(
        const MatrixXIHandle& first_matrix,
        const MatrixXIHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator!=(
        const MatrixXdHandle& first_matrix,
        const MatrixXdHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator!=(
        const MatrixXdHandle& first_matrix,
        const MatrixXIHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator!=(
        const MatrixXIHandle& first_matrix,
        const MatrixXdHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator!=(
        const MatrixXIHandle& first_matrix,
        const MatrixXIHandle& second_matrix
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator*(
        const MatrixXdHandle& matrix,
        const DatumXd& datum
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator*(
        const MatrixXIHandle& matrix,
        const DatumXd& datum
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator/(
        const MatrixXdHandle& matrix,
        const DatumXd& datum
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator/(
        const MatrixXIHandle& matrix,
        const DatumXd& datum
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdHandle operator%(
        const MatrixXdHandle& matrix,
        const DatumXd& datum
    );

    OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIHandle operator%(
        const MatrixXIHandle& matrix,
        const DatumXd& datum
    );
}
