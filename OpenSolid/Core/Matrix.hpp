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

#include <OpenSolid/Core/Matrix.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.hpp>
#include <OpenSolid/Core/MatrixView.hpp>

#include <cassert>

// Disable warning C4351 (Visual Studio warning that _data array will in fact be value-initialized
// as specified in the C++ standard; previous versions of Visual Studio did not always
// value-initialize as required)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4351)
#endif

namespace opensolid
{
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(bool) {
        // Don't initialize _data - only used in static functions, which will
        // immediately assign to all components
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix() :
        _data() {
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(const std::pair<int, int>& dimensions) :
        _data() {

        assert(dimensions.first == iNumRows);
        assert(dimensions.second == iNumColumns);
    }
   
    template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherDerived>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        this->assign(other);
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(const TScalar firstComponent) {
        static_assert(iNumRows * iNumColumns == 1, "Incorrect matrix size");
        this->data()[0] = firstComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent
    ) {
        static_assert(iNumRows * iNumColumns == 2, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent
    ) {
        static_assert(iNumRows * iNumColumns == 3, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent,
        const TScalar fourthComponent        
    ) {
        static_assert(iNumRows * iNumColumns == 4, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
        this->data()[3] = fourthComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent,
        const TScalar fourthComponent,
        const TScalar fifthComponent
    ) {
        static_assert(iNumRows * iNumColumns == 5, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
        this->data()[3] = fourthComponent;
        this->data()[4] = fifthComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent,
        const TScalar fourthComponent,
        const TScalar fifthComponent,
        const TScalar sixthComponent
    ) {
        static_assert(iNumRows * iNumColumns == 6, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
        this->data()[3] = fourthComponent;
        this->data()[4] = fifthComponent;
        this->data()[5] = sixthComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent,
        const TScalar fourthComponent,
        const TScalar fifthComponent,
        const TScalar sixthComponent,
        const TScalar seventhComponent
    ) {
        static_assert(iNumRows * iNumColumns == 7, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
        this->data()[3] = fourthComponent;
        this->data()[4] = fifthComponent;
        this->data()[5] = sixthComponent;
        this->data()[6] = seventhComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent,
        const TScalar fourthComponent,
        const TScalar fifthComponent,
        const TScalar sixthComponent,
        const TScalar seventhComponent,
        const TScalar eighthComponent
    ) {
        static_assert(iNumRows * iNumColumns == 8, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
        this->data()[3] = fourthComponent;
        this->data()[4] = fifthComponent;
        this->data()[5] = sixthComponent;
        this->data()[6] = seventhComponent;
        this->data()[7] = eighthComponent;
    }
    
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar firstComponent, 
        const TScalar secondComponent,
        const TScalar thirdComponent,
        const TScalar fourthComponent,
        const TScalar fifthComponent,
        const TScalar sixthComponent,
        const TScalar seventhComponent,
        const TScalar eighthComponent,
        const TScalar ninthComponent
    ) {
        static_assert(iNumRows * iNumColumns == 9, "Incorrect matrix size");
        this->data()[0] = firstComponent;
        this->data()[1] = secondComponent;
        this->data()[2] = thirdComponent;
        this->data()[3] = fourthComponent;
        this->data()[4] = fifthComponent;
        this->data()[5] = sixthComponent;
        this->data()[6] = seventhComponent;
        this->data()[7] = eighthComponent;
        this->data()[8] = ninthComponent;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const TScalar*
    Matrix<TScalar, iNumRows, iNumColumns>::data() const {
        return _data;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    TScalar*
    Matrix<TScalar, iNumRows, iNumColumns>::data() {
        return _data;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    int
    Matrix<TScalar, iNumRows, iNumColumns>::numRows() const {
        return iNumRows;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    int
    Matrix<TScalar, iNumRows, iNumColumns>::numColumns() const {
        return iNumColumns;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    int
    Matrix<TScalar, iNumRows, iNumColumns>::numComponents() const {
        return iNumRows * iNumColumns;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    int
    Matrix<TScalar, iNumRows, iNumColumns>::columnStride() const {
        return iNumRows;
    }

    template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherDerived>
    inline
    void
    Matrix<TScalar, iNumRows, iNumColumns>::operator=(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        this->assign(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::constant(TScalar value) {
        Matrix<TScalar, iNumRows, iNumColumns> result(false);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::zero() {
        return Matrix<TScalar, iNumRows, iNumColumns>();
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::ones() {
        Matrix<TScalar, iNumRows, iNumColumns> result(false);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::identity() {
        Matrix<TScalar, iNumRows, iNumColumns> result(false);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::random() {
        Matrix<TScalar, iNumRows, iNumColumns> result(false);
        result.setRandom();
        return result;
    }

    template <class TScalar, int iNumColumns>
    inline
    Matrix<TScalar, -1, iNumColumns>::Matrix(int numRows) :
        _data(std::size_t(numRows * iNumColumns)),
        _numRows(numRows) {

        assert(numRows > 0);
    }

    template <class TScalar, int iNumColumns>
    inline
    Matrix<TScalar, -1, iNumColumns>::Matrix(const std::pair<int, int>& dimensions) :
        _data(std::size_t(dimensions.first * iNumColumns)),
        _numRows(dimensions.first) {

        assert(dimensions.first > 0);
        assert(dimensions.second == iNumColumns);
    }
   
    template <class TScalar, int iNumColumns> template <class TOtherDerived>
    inline
    Matrix<TScalar, -1, iNumColumns>::Matrix(const detail::MatrixInterface<TOtherDerived>& other) :
        _data(std::size_t(other.numRows() * iNumColumns)),
        _numRows(other.numRows()) {

        assert(other.numColumns() == iNumColumns);
        this->assign(other);
    }

    template <class TScalar, int iNumColumns>
    inline
    Matrix<TScalar, -1, iNumColumns>::Matrix(Matrix<TScalar, -1, iNumColumns>&& other) :
        _data(std::move(other._data)),
        _numRows(other.numRows()) {
    }

    template <class TScalar, int iNumColumns>
    inline
    Matrix<TScalar, -1, iNumColumns>::Matrix(Matrix<TScalar, -1, -1>&& other) :
        _data(std::move(other._data)),
        _numRows(other.numRows()) {
    
        assert(other.numColumns() == iNumColumns);
    }

    template <class TScalar, int iNumColumns>
    inline
    const TScalar*
    Matrix<TScalar, -1, iNumColumns>::data() const {
        return _data.data();
    }

    template <class TScalar, int iNumColumns>
    inline
    TScalar*
    Matrix<TScalar, -1, iNumColumns>::data() {
        return _data.data();
    }

    template <class TScalar, int iNumColumns>
    inline
    int
    Matrix<TScalar, -1, iNumColumns>::numRows() const {
        return _numRows;
    }

    template <class TScalar, int iNumColumns>
    inline
    int
    Matrix<TScalar, -1, iNumColumns>::numColumns() const {
        return iNumColumns;
    }

    template <class TScalar, int iNumColumns>
    inline
    int
    Matrix<TScalar, -1, iNumColumns>::numComponents() const {
        return int(_data.size());
    }

    template <class TScalar, int iNumColumns>
    inline
    int
    Matrix<TScalar, -1, iNumColumns>::columnStride() const {
        return _numRows;
    }

    template <class TScalar, int iNumColumns> template <class TOtherDerived>
    inline
    void
    Matrix<TScalar, -1, iNumColumns>::operator=(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        this->assign(other);
    }

    template <class TScalar, int iNumColumns>
    inline
    const Matrix<TScalar, -1, iNumColumns>
    Matrix<TScalar, -1, iNumColumns>::constant(int numRows, TScalar value) {
        Matrix<TScalar, -1, iNumColumns> result(numRows);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumColumns>
    inline
    const Matrix<TScalar, -1, iNumColumns>
    Matrix<TScalar, -1, iNumColumns>::zero(int numRows) {
        return Matrix<TScalar, -1, iNumColumns>(numRows);
    }

    template <class TScalar, int iNumColumns>
    inline
    const Matrix<TScalar, -1, iNumColumns>
    Matrix<TScalar, -1, iNumColumns>::ones(int numRows) {
        Matrix<TScalar, -1, iNumColumns> result(numRows);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumColumns>
    inline
    const Matrix<TScalar, -1, iNumColumns>
    Matrix<TScalar, -1, iNumColumns>::identity(int numRows) {
        Matrix<TScalar, -1, iNumColumns> result(numRows);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumColumns>
    inline
    const Matrix<TScalar, -1, iNumColumns>
    Matrix<TScalar, -1, iNumColumns>::random(int numRows) {
        Matrix<TScalar, -1, iNumColumns> result(numRows);
        result.setRandom();
        return result;
    }

    template <class TScalar, int iNumRows>
    inline
    Matrix<TScalar, iNumRows, -1>::Matrix(int numColumns) :
        _data(iNumRows * numColumns),
        _numColumns(numColumns) {

        assert(numColumns > 0);
    }

    template <class TScalar, int iNumRows>
    inline
    Matrix<TScalar, iNumRows, -1>::Matrix(const std::pair<int, int>& dimensions) :
        _data(iNumRows * dimensions.second),
        _numColumns(dimensions.second) {

        assert(dimensions.second > 0);
    }
   
    template <class TScalar, int iNumRows> template <class TOtherDerived>
    inline
    Matrix<TScalar, iNumRows, -1>::Matrix(const detail::MatrixInterface<TOtherDerived>& other) :
        _data(iNumRows * other.numColumns()),
        _numColumns(other.numColumns()) {

        assert(other.numRows() == iNumRows);
        this->assign(other);
    }

    template <class TScalar, int iNumRows>
    inline
    Matrix<TScalar, iNumRows, -1>::Matrix(Matrix<TScalar, iNumRows, -1>&& other) :
        _data(std::move(other._data)),
        _numColumns(other.numColumns()) {
    }

    template <class TScalar, int iNumRows>
    inline
    Matrix<TScalar, iNumRows, -1>::Matrix(Matrix<TScalar, -1, -1>&& other) :
        _data(std::move(other._data)),
        _numColumns(other.numColumns()) {
    
        assert(other.numRows() == iNumRows);
    }

    template <class TScalar, int iNumRows>
    inline
    const TScalar*
    Matrix<TScalar, iNumRows, -1>::data() const {
        return _data.data();
    }

    template <class TScalar, int iNumRows>
    inline
    TScalar*
    Matrix<TScalar, iNumRows, -1>::data() {
        return _data.data();
    }

    template <class TScalar, int iNumRows>
    inline
    int
    Matrix<TScalar, iNumRows, -1>::numRows() const {
        return iNumRows;
    }

    template <class TScalar, int iNumRows>
    inline
    int
    Matrix<TScalar, iNumRows, -1>::numColumns() const {
        return _numColumns;
    }

    template <class TScalar, int iNumRows>
    inline
    int
    Matrix<TScalar, iNumRows, -1>::numComponents() const {
        return int(_data.size());
    }

    template <class TScalar, int iNumRows>
    inline
    int
    Matrix<TScalar, iNumRows, -1>::columnStride() const {
        return iNumRows;
    }

    template <class TScalar, int iNumRows> template <class TOtherDerived>
    inline
    void
    Matrix<TScalar, iNumRows, -1>::operator=(const detail::MatrixInterface<TOtherDerived>& other) {
        this->assign(other);
    }

    template <class TScalar, int iNumRows>
    inline
    const Matrix<TScalar, iNumRows, -1>
    Matrix<TScalar, iNumRows, -1>::constant(int numColumns, TScalar value) {
        Matrix<TScalar, iNumRows, -1> result(numColumns);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows>
    inline
    const Matrix<TScalar, iNumRows, -1>
    Matrix<TScalar, iNumRows, -1>::zero(int numColumns) {
        return Matrix<TScalar, iNumRows, -1>(numColumns);
    }

    template <class TScalar, int iNumRows>
    inline
    const Matrix<TScalar, iNumRows, -1>
    Matrix<TScalar, iNumRows, -1>::ones(int numColumns) {
        Matrix<TScalar, iNumRows, -1> result(numColumns);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows>
    inline
    const Matrix<TScalar, iNumRows, -1>
    Matrix<TScalar, iNumRows, -1>::identity(int numColumns) {
        Matrix<TScalar, iNumRows, -1> result(numColumns);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows>
    inline
    const Matrix<TScalar, iNumRows, -1>
    Matrix<TScalar, iNumRows, -1>::random(int numColumns) {
        Matrix<TScalar, iNumRows, -1> result(numColumns);
        result.setRandom();
        return result;
    }

    template <class TScalar>
    inline
    Matrix<TScalar, -1, -1>::Matrix(int numRows, int numColumns) :
        _data(numRows * numColumns),
        _numRows(numRows),
        _numColumns(numColumns) {

        assert(numRows > 0);
        assert(numColumns > 0);
    }

    template <class TScalar>
    inline
    Matrix<TScalar, -1, -1>::Matrix(const std::pair<int, int>& dimensions) :
        _data(dimensions.first * dimensions.second),
        _numRows(dimensions.first),
        _numColumns(dimensions.second) {

        assert(dimensions.first > 0);
        assert(dimensions.second > 0);
    }

    template <class TScalar> template <class TOtherDerived>
    inline
    Matrix<TScalar, -1, -1>::Matrix(const detail::MatrixInterface<TOtherDerived>& other) :
        _data(other.numComponents()),
        _numRows(other.numRows()),
        _numColumns(other.numColumns()) {

        this->assign(other);
    }

    template <class TScalar>
    inline
    Matrix<TScalar, -1, -1>::Matrix(Matrix<TScalar, -1, -1>&& other) :
        _data(std::move(other._data)),
        _numRows(other.numRows()),
        _numColumns(other.numColumns()) {
    }

    template <class TScalar> template <int iNumRows>
    inline
    Matrix<TScalar, -1, -1>::Matrix(Matrix<TScalar, iNumRows, -1>&& other) :
        _data(std::move(other._data)),
        _numRows(iNumRows),
        _numColumns(other.numColumns()) {
    }

    template <class TScalar> template <int iNumColumns>
    inline
    Matrix<TScalar, -1, -1>::Matrix(Matrix<TScalar, -1, iNumColumns>&& other) :
        _data(std::move(other._data)),
        _numRows(other.numRows()),
        _numColumns(iNumColumns) {
    }

    template <class TScalar>
    inline
    const TScalar*
    Matrix<TScalar, -1, -1>::data() const {
        return _data.data();
    }

    template <class TScalar>
    inline
    TScalar*
    Matrix<TScalar, -1, -1>::data() {
        return _data.data();
    }

    template <class TScalar>
    inline
    int
    Matrix<TScalar, -1, -1>::numRows() const {
        return _numRows;
    }

    template <class TScalar>
    inline
    int
    Matrix<TScalar, -1, -1>::numColumns() const {
        return _numColumns;
    }

    template <class TScalar>
    inline
    int
    Matrix<TScalar, -1, -1>::numComponents() const {
        return int(_data.size());
    }

    template <class TScalar>
    inline
    int
    Matrix<TScalar, -1, -1>::columnStride() const {
        return _numRows;
    }

    template <class TScalar> template <class TOtherDerived>
    inline
    void
    Matrix<TScalar, -1, -1>::operator=(const detail::MatrixInterface<TOtherDerived>& other) {
        this->assign(other);
    }

    template <class TScalar>
    inline
    const Matrix<TScalar, -1, -1>
    Matrix<TScalar, -1, -1>::constant(int numRows, int numColumns, TScalar value) {
        Matrix<TScalar, -1, -1> result(numRows, numColumns);
        result.setConstant(value);
        return result;
    }

    template <class TScalar>
    inline
    const Matrix<TScalar, -1, -1>
    Matrix<TScalar, -1, -1>::zero(int numRows, int numColumns) {
        return Matrix<TScalar, -1, -1>(numRows, numColumns);
    }

    template <class TScalar>
    inline
    const Matrix<TScalar, -1, -1>
    Matrix<TScalar, -1, -1>::ones(int numRows, int numColumns) {
        Matrix<TScalar, -1, -1> result(numRows, numColumns);
        result.setOnes();
        return result;
    }

    template <class TScalar>
    inline
    const Matrix<TScalar, -1, -1>
    Matrix<TScalar, -1, -1>::identity(int numRows, int numColumns) {
        Matrix<TScalar, -1, -1> result(numRows, numColumns);
        result.setIdentity();
        return result;
    }

    template <class TScalar>
    inline
    const Matrix<TScalar, -1, -1>
    Matrix<TScalar, -1, -1>::random(int numRows, int numColumns) {
        Matrix<TScalar, -1, -1> result(numRows, numColumns);
        result.setRandom();
        return result;
    }

    namespace detail
    {
        template <class TScalar>
        inline
        void
        printMatrixTypePrefix(std::ostream& stream) {
        }

        template <>
        inline
        void
        printMatrixTypePrefix<Interval>(std::ostream& stream) {
            stream << "Interval";
        }
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iNumRows, iNumColumns>& matrix) {
        char numRowsCharacter = iNumRows == -1 ? 'X' : '0' + iNumRows;
        char numColumnsCharacter = iNumColumns == -1 ? 'X' : '0' + iNumColumns;

        // Print type name
        detail::printMatrixTypePrefix<TScalar>(stream);
        if (iNumRows == iNumColumns) {
            stream << "Matrix" << numRowsCharacter << "d";
        } else if (iNumRows == 1) {
            stream << "RowMatrix" << numColumnsCharacter << "d";
        } else if (iNumColumns == 1) {
            stream << "ColumnMatrix" << numRowsCharacter << "d";
        } else {
            stream << "Matrix" << numRowsCharacter << "x" << numColumnsCharacter;
        }

        // Print component arguments
        stream << "([";
        int numRows = matrix.numRows();
        int numColumns = matrix.numColumns();
        int numComponents = matrix.numComponents();
        if (numRows == 1 || numColumns == 1) {
            for (int index = 0; index < numComponents; ++index) {
                stream << matrix(index);
                if (index < numComponents - 1) {
                    stream << ", ";
                }
            }
        } else {
            for (int columnIndex = 0; columnIndex < numColumns; ++columnIndex) {
                stream << "[";
                for (int rowIndex = 0; rowIndex < numRows; ++rowIndex) {
                    stream << matrix(rowIndex, columnIndex);
                    if (rowIndex < numRows - 1) {
                        stream << ", ";
                    }
                }
                stream << "]";
                if (columnIndex < numColumns - 1) {
                    stream << ", ";
                }
            }
        }
        stream << "])";
        
        return stream;
    }
}
