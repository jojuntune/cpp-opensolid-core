/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <OpenSolid/Datum/Datum.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Python/BoostPython.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

#include "check.hpp"

using namespace boost::python;

namespace OpenSolid
{
    template <class ExpressionType>
    struct ExpressionConverter
    {
        static inline PyObject* convert(const ExpressionType& expression) {
            typedef Matrix<typename ExpressionType::Scalar, Dynamic, Dynamic> MatrixType;
            typedef typename manage_new_object::apply<MatrixType*>::type ConverterType;
            return ConverterType()(new MatrixType(expression));
        }
    };

    template <class ExpressionType>
    void registerExpressionConverter() {
        to_python_converter<ExpressionType, ExpressionConverter<ExpressionType>>();
    }

    template <class MatrixType>
    int rows(const MatrixType& argument) {return argument.rows();}
    
    template <class MatrixType>
    int cols(const MatrixType& argument) {return argument.cols();}
    
    template <class MatrixType>
    int size(const MatrixType& argument) {return argument.size();}
    
    template <class MatrixType>
    typename MatrixType::Scalar value(const MatrixType& argument) {return argument.value();}

    template <class MatrixType>
    typename MatrixType::Scalar xComponent(const MatrixType& argument) {
        checkVectorValue(argument, __func__);
        return argument(0, 0);
    }

    template <class MatrixType>
    typename MatrixType::Scalar yComponent(const MatrixType& argument) {
        checkVectorValue(argument, __func__);
        checkComponentIndexInRange(1, argument.size(), __func__);
        return argument(1, 0);
    }

    template <class MatrixType>
    typename MatrixType::Scalar zComponent(const MatrixType& argument) {
        checkVectorValue(argument, __func__);
        checkComponentIndexInRange(2, argument.size(), __func__);
        return argument(2, 0);
    }
        
    int positiveIndex(int index, int size) {
        checkComponentIndexInRange(index, size, __func__);
        return index >= 0 ? index : size + index;
    }
    
    void getComponentBlock(slice indices, int size, int& block_start, int& block_size) {
        checkNoMatrixIndexStep(indices, __func__);
        if (indices.start() == object()) {
            block_start = 0;
        } else {
            checkCompatiblePythonType<int>(indices.start(), __func__);
            block_start = extract<int>(indices.start());
        }
        if (indices.stop() == object()) {
            block_size = block_start < 0 ? -block_start : size - block_start;
        } else {
            checkCompatiblePythonType<int>(indices.stop(), __func__);
            block_size = extract<int>(indices.stop());
        }
        checkComponentBlockInRange(block_start, block_size, size, __func__);
        if (block_start < 0) {block_start += size;}
    }
    
    template <class MatrixType>
    typename MatrixType::Scalar getI(const MatrixType& matrix, int index) {
        checkVectorOrRowVectorValue(matrix, __func__);
        if (matrix.cols() == 1) {
            return matrix(positiveIndex(index, matrix.rows()), 0);
        } else {
            return matrix(0, positiveIndex(index, matrix.cols()));
        }
    }
    
    template <class MatrixType>
    MatrixType* getS(const MatrixType& matrix, slice indices) {
        checkVectorOrRowVectorValue(matrix, __func__);
        int block_start;
        int block_size;
        if (matrix.cols() == 1) {
            getComponentBlock(indices, matrix.rows(), block_start, block_size);
            return new MatrixType(matrix.block(block_start, 0, block_size, 1));
        } else {
            getComponentBlock(indices, matrix.cols(), block_start, block_size);
            return new MatrixType(matrix.block(0, block_start, 1, block_size));
        }
    }
    
    template <class MatrixType>
    typename MatrixType::Scalar getII(const MatrixType& matrix, int row, int col) {
        return matrix(positiveIndex(row, matrix.rows()), positiveIndex(col, matrix.cols()));
    }
    
    template <class MatrixType>
    MatrixType* getSI(const MatrixType& matrix, slice rows, int col) {
        int block_start;
        int block_size;
        getComponentBlock(rows, matrix.rows(), block_start, block_size);
        return new MatrixType(
            matrix.block(
                block_start,
                positiveIndex(col, matrix.cols()),
                block_size,
                1
            )
        );
    }
    
    template <class MatrixType>
    MatrixType* getIS(const MatrixType& matrix, int row, slice cols) {
        int block_start;
        int block_size;
        getComponentBlock(cols, matrix.cols(), block_start, block_size);
        return new MatrixType(
            matrix.block(
                positiveIndex(row, matrix.rows()),
                block_start,
                1,
                block_size
            )
        );
    }
    
    template <class MatrixType>
    MatrixType* getSS(const MatrixType& matrix, slice rows, slice cols) {
        int row_start;
        int row_size;
        getComponentBlock(rows, matrix.rows(), row_start, row_size);
        int col_start;
        int col_size;
        getComponentBlock(cols, matrix.cols(), col_start, col_size);
        return new MatrixType(matrix.block(row_start, col_start, row_size, col_size));
    }
    
    object getItem(tuple arguments, dict) {
        object self = arguments[0];
        object get = self.attr("get");
        extract<tuple> extracted(arguments[1]);
        if (extracted.check()) {
            tuple indices = extracted;
            object row = indices[0];
            object col = indices[1];
            return get(row, col);
        } else {
            object index = arguments[1];
            return get(index);
        }
    }
    
    template <class MatrixType>
    void setI(MatrixType& matrix, int index, typename MatrixType::Scalar argument) {
        checkVectorOrRowVectorValue(matrix, __func__);
        if (matrix.cols() == 1) {
            matrix(positiveIndex(index, matrix.rows()), 0) = argument;
        } else {
            matrix(0, positiveIndex(index, matrix.cols())) = argument;
        }
    }
    
    template <class MatrixType>
    void setS(MatrixType& matrix, slice indices, const MatrixType& argument) {
        checkVectorOrRowVectorValue(matrix, __func__);
        int block_start;
        int block_size;
        if (matrix.cols() == 1) {
            getComponentBlock(indices, matrix.rows(), block_start, block_size);
            checkSpecificMatrixSize(argument, block_size, 1, __func__);
            matrix.block(block_start, 0, block_size, 1) = argument;
        } else {
            getComponentBlock(indices, matrix.cols(), block_start, block_size);
            checkSpecificMatrixSize(argument, 1, block_size, __func__);
            matrix.block(0, block_start, 1, block_size) = argument;
        }
    }
    
    template <class MatrixType>
    void setII(MatrixType& matrix, int row, int col, typename MatrixType::Scalar argument) {
        matrix(positiveIndex(row, matrix.rows()), positiveIndex(col, matrix.cols())) = argument;
    }
    
    template <class MatrixType>
    void setSI(MatrixType& matrix, slice rows, int col, const MatrixType& argument) {
        int block_start;
        int block_size;
        getComponentBlock(rows, matrix.rows(), block_start, block_size);
        checkSpecificMatrixSize(argument, block_size, 1, __func__);
        matrix.block(block_start, positiveIndex(col, matrix.cols()), block_size, 1) = argument;
    }
    
    template <class MatrixType>
    void setIS(MatrixType& matrix, int row, slice cols, const MatrixType& argument) {
        int block_start;
        int block_size;
        getComponentBlock(cols, matrix.cols(), block_start, block_size);
        checkSpecificMatrixSize(argument, 1, block_size, __func__);
        matrix.block(positiveIndex(row, matrix.rows()), block_start, 1, block_size) = argument;
    }
    
    template <class MatrixType>
    void setSS(MatrixType& matrix, slice rows, slice cols, const MatrixType& argument) {
        int row_start;
        int row_size;
        getComponentBlock(rows, matrix.rows(), row_start, row_size);
        int col_start;
        int col_size;
        getComponentBlock(cols, matrix.cols(), col_start, col_size);
        checkSpecificMatrixSize(argument, row_size, col_size, __func__);
        matrix.block(row_start, col_start, row_size, col_size) = argument;
    }
    
    object setItem(tuple arguments, dict) {
        object self = arguments[0];
        object set = self.attr("set");
        extract<tuple> extracted(arguments[1]);
        object value = arguments[2];
        if (extracted.check()) {
            tuple indices = extracted;
            object row = indices[0];
            object col = indices[1];
            return set(row, col, value);
        } else {
            object index = arguments[1];
            return set(index, value);
        }
    }

    template <class MatrixType>
    ConstMatrixIterator<MatrixType> matrixBegin(const MatrixType& argument) {
        return begin(argument);
    }

    template <class MatrixType>
    ConstMatrixIterator<MatrixType> matrixEnd(const MatrixType& argument) {
        return end(argument);
    }
    
    double minCoeff(const MatrixXd& argument) {return argument.minCoeff();}
    
    double maxCoeff(const MatrixXd& argument) {return argument.maxCoeff();}

    template <class MatrixType>
    typename MatrixType::Scalar squaredNorm(const MatrixType& argument) {
        checkVectorValue(argument, __func__);
        return argument.col(0).squaredNorm();
    }
    
    template <class MatrixType>
    typename MatrixType::Scalar norm(const MatrixType& argument) {return argument.norm();}
    
    template <class MatrixType>
    MatrixType* normalized(const MatrixType& argument);
    
    template <>
    MatrixXd* normalized(const MatrixXd& argument) {
        checkVectorValue(argument, __func__);
        checkNonZeroValue(argument.squaredNorm(), __func__);
        return new MatrixXd(argument.col(0).normalized());
    }
    
    template <>
    MatrixXI* normalized(const MatrixXI& argument) {
        checkVectorValue(argument, __func__);
        checkNonZeroValue(argument.squaredNorm().lower(), __func__);
        return new MatrixXI(argument.col(0).normalized());
    }
    
    template <class MatrixType>
    typename MatrixType::Scalar determinant(const MatrixType& argument) {
        checkSquareMatrix(argument, __func__);
        return argument.determinant();
    }
    
    template <class MatrixType>
    typename MatrixType::Scalar trace(const MatrixType& argument) {return argument.trace();}
    
    template <class MatrixType>
    MatrixType* transpose(const MatrixType& argument) {return new MatrixType(argument.transpose());}

    MatrixXd* inverse(const MatrixXd& argument) {return new MatrixXd(argument.inverse());}
    
    template <class MatrixType>
    MatrixType* replicate(const MatrixType& argument, int row_factor, int col_factor) {
        return new MatrixType(argument.replicate(row_factor, col_factor));
    }
    
    double dotXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameDimensions(first_argument.rows(), second_argument.rows(), __func__);
        return first_argument.col(0).dot(second_argument.col(0));
    }
    
    Interval dotXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameDimensions(first_argument.rows(), second_argument.rows(), __func__);
        return first_argument.col(0).cast<Interval>().dot(second_argument.col(0));
    }
    
    Interval dotXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameDimensions(first_argument.rows(), second_argument.rows(), __func__);
        return first_argument.col(0).dot(second_argument.col(0).cast<Interval>());
    }
    
    Interval dotXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameDimensions(first_argument.rows(), second_argument.rows(), __func__);
        return first_argument.col(0).dot(second_argument.col(0));
    }
    
    MatrixXd* crossXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameSize(first_argument.rows(), 3, __func__);
        checkSameSize(second_argument.rows(), 3, __func__);
        return new MatrixXd(
            first_argument.block<3, 1>(0, 0).cross(second_argument.block<3, 1>(0, 0))
        );
    }
    
    MatrixXI* crossXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameSize(first_argument.rows(), 3, __func__);
        checkSameSize(second_argument.rows(), 3, __func__);
        return new MatrixXI(
            first_argument.block<3, 1>(0, 0).cast<Interval>().cross(
                second_argument.block<3, 1>(0, 0)
            )
        );
    }
    
    MatrixXI* crossXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameSize(first_argument.rows(), 3, __func__);
        checkSameSize(second_argument.rows(), 3, __func__);
        return new MatrixXI(
            first_argument.block<3, 1>(0, 0).cross(
                second_argument.block<3, 1>(0, 0).cast<Interval>()
            )
        );
    }
    
    MatrixXI* crossXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkVectorValue(first_argument, __func__);
        checkVectorValue(second_argument, __func__);
        checkSameSize(first_argument.rows(), 3, __func__);
        checkSameSize(second_argument.rows(), 3, __func__);
        return new MatrixXI(
            first_argument.block<3, 1>(0, 0).cross(second_argument.block<3, 1>(0, 0))
        );
    }
    
    template <class MatrixType>
    bool isZero(const MatrixType& argument) {return argument.isZero();}
    
    template <class MatrixType>
    bool isZeroP(const MatrixType& argument, double precision) {return argument.isZero(precision);}
    
    bool overlaps(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return first_argument.overlaps(second_argument);
    }
    
    bool overlapsP(
        const MatrixXI& first_argument,
        const MatrixXI& second_argument,
        double precision
    ) {return first_argument.overlaps(second_argument, precision);}
    
    bool strictlyOverlaps(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return first_argument.strictlyOverlaps(second_argument);
    }
    
    bool strictlyOverlapsP(
        const MatrixXI& first_argument,
        const MatrixXI& second_argument,
        double precision
    ) {return first_argument.strictlyOverlaps(second_argument, precision);}
    
    bool containsXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        return first_argument.contains(second_argument.cast<Interval>());
    }
    
    bool containsXdP(
        const MatrixXI& first_argument,
        const MatrixXd& second_argument,
        double precision
    ) {return first_argument.contains(second_argument.cast<Interval>(), precision);}
    
    bool containsXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return first_argument.contains(second_argument);
    }
    
    bool containsXIP(
        const MatrixXI& first_argument,
        const MatrixXI& second_argument,
        double precision
    ) {return first_argument.contains(second_argument, precision);}
    
    bool strictlyContainsXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        return first_argument.strictlyContains(second_argument.cast<Interval>());
    }
    
    bool strictlyContainsXdP(
        const MatrixXI& first_argument,
        const MatrixXd& second_argument,
        double precision
    ) {return first_argument.strictlyContains(second_argument.cast<Interval>(), precision);}
    
    bool strictlyContainsXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return first_argument.strictlyContains(second_argument);
    }
    
    bool strictlyContainsXIP(
        const MatrixXI& first_argument,
        const MatrixXI& second_argument,
        double precision
    ) {return first_argument.strictlyContains(second_argument, precision);}
    
    MatrixXd* cwiseLower(const MatrixXI& argument) {return new MatrixXd(argument.cwiseLower());}
    
    MatrixXd* cwiseUpper(const MatrixXI& argument) {return new MatrixXd(argument.cwiseUpper());}
    
    MatrixXd* cwiseMedian(const MatrixXI& argument) {return new MatrixXd(argument.cwiseMedian());}
    
    MatrixXd* cwiseWidth(const MatrixXI& argument) {return new MatrixXd(argument.cwiseWidth());}
    
    MatrixXI* hullXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        return new MatrixXI(first_argument.hull(second_argument));
    }
    
    MatrixXI* hullXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        return new MatrixXI(first_argument.cast<Interval>().hull(second_argument));
    }
    
    MatrixXI* hullXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        return new MatrixXI(first_argument.hull(second_argument.cast<Interval>()));
    }
    
    MatrixXI* hullXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return new MatrixXI(first_argument.hull(second_argument));
    }
    
    MatrixXI* intersection(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return new MatrixXI(first_argument.intersection(second_argument));
    }
    
    template <class MatrixType>
    MatrixType* constant(int rows, int cols, const typename MatrixType::Scalar& value) {
        return new MatrixType(MatrixType::Constant(rows, cols, value));
    }
    
    template <class MatrixType>
    MatrixType* zero(int rows, int cols) {return new MatrixType(MatrixType::Zero(rows, cols));}
    
    template <class MatrixType>
    MatrixType* ones(int rows, int cols) {return new MatrixType(MatrixType::Ones(rows, cols));}
    
    template <class MatrixType>
    MatrixType* random(int rows, int cols) {return new MatrixType(MatrixType::Random(rows, cols));}

    template <class MatrixType>
    MatrixType* identity(int rows, int cols) {
        return new MatrixType(MatrixType::Identity(rows, cols));
    }
    
    MatrixXd* negXd(const MatrixXd& argument) {return new MatrixXd(-argument);}
    
    MatrixXI* negXI(const MatrixXI& argument) {return new MatrixXI(-argument);}
    
    MatrixXd* addXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXd(first_argument + second_argument);
    }
    
    MatrixXI* addXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXI(first_argument.cast<Interval>() + second_argument);
    }
    
    MatrixXI* addXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXI(first_argument + second_argument.cast<Interval>());
    }
    
    MatrixXI* addXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXI(first_argument + second_argument);
    }
    
    MatrixXd* subXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXd(first_argument - second_argument);
    }
    
    MatrixXI* subXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXI(first_argument.cast<Interval>() - second_argument);
    }
    
    MatrixXI* subXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXI(first_argument - second_argument.cast<Interval>());
    }
    
    MatrixXI* subXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return new MatrixXI(first_argument - second_argument);
    }
    
    MatrixXd* rmulXdd(const MatrixXd& self, double argument) {
        return new MatrixXd(argument * self);
    }
    
    MatrixXI* rmulXId(const MatrixXI& self, double argument) {
        return new MatrixXI(Interval(argument) * self);
    }
    
    MatrixXI* rmulXdI(const MatrixXd& self, const Interval& argument) {
        return new MatrixXI(argument * self.cast<Interval>());
    }
    
    MatrixXI* rmulXII(const MatrixXI& self, const Interval& argument) {
        return new MatrixXI(argument * self);
    }
    
    MatrixXd* mulXdd(const MatrixXd& first_argument, double second_argument) {
        return new MatrixXd(first_argument * second_argument);
    }
    
    MatrixXI* mulXdI(const MatrixXd& first_argument, const Interval& second_argument) {
        return new MatrixXI(first_argument.cast<Interval>() * second_argument);
    }
    
    MatrixXI* mulXId(const MatrixXI& first_argument, double second_argument) {
        return new MatrixXI(first_argument * Interval(second_argument));
    }
    
    MatrixXI* mulXII(const MatrixXI& first_argument, const Interval& second_argument) {
        return new MatrixXI(first_argument * second_argument);
    }
    
    MatrixXd* divXdd(const MatrixXd& first_argument, double second_argument) {
        checkNonZeroValue(second_argument, __func__);
        return new MatrixXd(first_argument / second_argument);
    }
    
    MatrixXI* divXdI(const MatrixXd& first_argument, const Interval& second_argument) {
        checkNonZeroValue(abs(second_argument).lower(), __func__);
        return new MatrixXI(first_argument.cast<Interval>() / second_argument);
    }
    
    MatrixXI* divXId(const MatrixXI& first_argument, double second_argument) {
        checkNonZeroValue(second_argument, __func__);
        return new MatrixXI(first_argument / Interval(second_argument));
    }
    
    MatrixXI* divXII(const MatrixXI& first_argument, const Interval& second_argument) {
        checkNonZeroValue(abs(second_argument).lower(), __func__);
        return new MatrixXI(first_argument / second_argument);
    }
    
    MatrixXd* mulXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSize(first_argument.cols(), second_argument.rows(), __func__);
        return new MatrixXd(first_argument * second_argument);
    }
    
    MatrixXI* mulXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSize(first_argument.cols(), second_argument.rows(), __func__);
        return new MatrixXI(first_argument.cast<Interval>() * second_argument);
    }
    
    MatrixXI* mulXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSize(first_argument.cols(), second_argument.rows(), __func__);
        return new MatrixXI(first_argument * second_argument.cast<Interval>());
    }
    
    MatrixXI* mulXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSize(first_argument.cols(), second_argument.rows(), __func__);
        return new MatrixXI(first_argument * second_argument);
    }

    bool eqXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument == second_argument;
    }

    bool eqXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.cast<Interval>() == second_argument;
    }

    bool eqXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument == second_argument.cast<Interval>();
    }

    bool eqXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument == second_argument;
    }

    bool neXdXd(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument != second_argument;
    }

    bool neXdXI(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.cast<Interval>() != second_argument;
    }

    bool neXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument != second_argument.cast<Interval>();
    }

    bool neXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument != second_argument;
    }

    MatrixXd* mulXdDatum(const MatrixXd& matrix, const DatumXd& datum) {
        return new MatrixXd(matrix * datum);
    }

    MatrixXI* mulXIDatum(const MatrixXI& matrix, const DatumXd& datum) {
        return new MatrixXI(matrix * datum);
    }

    MatrixXd* divXdDatum(const MatrixXd& matrix, const DatumXd& datum) {
        return new MatrixXd(matrix / datum);
    }

    MatrixXI* divXIDatum(const MatrixXI& matrix, const DatumXd& datum) {
        return new MatrixXI(matrix / datum);
    }

    MatrixXd* modXdDatum(const MatrixXd& matrix, const DatumXd& datum) {
        return new MatrixXd(matrix % datum);
    }

    MatrixXI* modXIDatum(const MatrixXI& matrix, const DatumXd& datum) {
        return new MatrixXI(matrix % datum);
    }

    template <class MatrixType>
    struct Colwise
    {
        MatrixType* matrix;
    };

    template <class MatrixType>
    struct Rowwise
    {
        MatrixType* matrix;
    };

    template <class MatrixType>
    Colwise<MatrixType> colwise(MatrixType& matrix) {
        Colwise<MatrixType> result;
        result.matrix = &matrix;
        return result;
    }

    template <class MatrixType>
    Rowwise<MatrixType> rowwise(MatrixType& matrix) {
        Rowwise<MatrixType> result;
        result.matrix = &matrix;
        return result;
    }

    template <class MatrixType>
    ConstMatrixColIterator<MatrixType> colwiseBegin(const Colwise<MatrixType>& colwise) {
        return begin(colwise.matrix->colwise());
    }

    template <class MatrixType>
    ConstMatrixColIterator<MatrixType> colwiseEnd(const Colwise<MatrixType>& colwise) {
        return end(colwise.matrix->colwise());
    }

    template <class MatrixType>
    ConstMatrixRowIterator<MatrixType> rowwiseBegin(const Rowwise<MatrixType>& rowwise) {
        return begin(rowwise.matrix->rowwise());
    }

    template <class MatrixType>
    ConstMatrixRowIterator<MatrixType> rowwiseEnd(const Rowwise<MatrixType>& rowwise) {
        return end(rowwise.matrix->rowwise());
    }

    template <class MatrixType>
    MatrixType* colwiseSquaredNorm(const Colwise<MatrixType>& colwise) {
        return new MatrixType(colwise.matrix->colwise().squaredNorm());
    }

    template <class MatrixType>
    MatrixType* colwiseNorm(const Colwise<MatrixType>& colwise) {
        return new MatrixType(colwise.matrix->colwise().norm());
    }

    template <class MatrixType>
    MatrixType* rowwiseSquaredNorm(const Rowwise<MatrixType>& rowwise) {
        return new MatrixType(rowwise.matrix->rowwise().squaredNorm());
    }

    template <class MatrixType>
    MatrixType* rowwiseNorm(const Rowwise<MatrixType>& rowwise) {
        return new MatrixType(rowwise.matrix->rowwise().norm());
    }

    template <class MatrixType>
    std::string str(const MatrixType& argument) {
        std::stringstream stream;
        stream << argument;
        return stream.str();
    }

    template <class MatrixType>
    std::string repr(const MatrixType& argument) {
        std::stringstream stream;
        if (argument.cols() == 1) {
            stream << "Vector([";
            for (int i = 0; i < argument.rows(); ++i) {
                stream << argument(i, 0);
                if (i < argument.rows() - 1) {stream << ", ";}
            }
            stream << "])";
        } else if (argument.rows() == 1) {
            stream << "RowVector([";
            for (int i = 0; i < argument.cols(); ++i) {
                stream << argument(0, i);
                if (i < argument.cols() - 1) {stream << ", ";}
            }
            stream << "])";
        } else {
            stream << "Matrix([";
            for (int j = 0; j < argument.cols(); ++j) {
                stream << "[";
                for (int i = 0; i < argument.rows(); ++i) {
                    stream << argument(i, j);
                    if (i < argument.rows() - 1) {stream << ", ";}
                }
                stream << "]";
                if (j < argument.cols() - 1) {stream << ", ";}
            }
            stream << "])";
        }
        return stream.str();
    }

    template <class MatrixType>
    struct MatrixPickleSuite : public pickle_suite
    {
        static tuple getinitargs(const MatrixType&) {return tuple();}

        static tuple getstate(const MatrixType& argument) {
            list components;
            for (int j = 0; j < argument.cols(); ++j) {
                for (int i = 0; i < argument.rows(); ++i) {
                    components.append(argument(i, j));
                }
            }
            return make_tuple(argument.rows(), argument.cols(), components);
        }

        static void setstate(MatrixType& argument, tuple state) {
            argument.resize(extract<int>(state[0]), extract<int>(state[1]));
            object components = state[2];
            for (int j = 0; j < argument.cols(); ++j) {
                for (int i = 0; i < argument.rows(); ++i) {
                    argument(i, j) = extract<typename MatrixType::Scalar>(
                        components[j * argument.rows() + i]
                    );
                }
            }
        }
    };
    
    void bindMatrix() {
        registerExpressionConverter<MatrixXd::ConstColXpr>();
        registerExpressionConverter<MatrixXd::ConstRowXpr>();
        registerExpressionConverter<MatrixXI::ConstColXpr>();
        registerExpressionConverter<MatrixXI::ConstRowXpr>();

        return_value_policy<manage_new_object> manage_new_matrix;
        with_custodian_and_ward_postcall<0, 1> manage_matrix_expression;

        class_<MatrixXd>("MatrixXd")
            .def("rows", &rows<MatrixXd>)
            .def("cols", &cols<MatrixXd>)
            .def("size", &size<MatrixXd>)
            .def("value", &value<MatrixXd>)
            .def("x", &xComponent<MatrixXd>)
            .def("y", &yComponent<MatrixXd>)
            .def("z", &zComponent<MatrixXd>)
            .def("get", &getI<MatrixXd>)
            .def("get", &getS<MatrixXd>, manage_new_matrix)
            .def("get", &getII<MatrixXd>)
            .def("get", &getIS<MatrixXd>, manage_new_matrix)
            .def("get", &getSI<MatrixXd>, manage_new_matrix)
            .def("get", &getSS<MatrixXd>, manage_new_matrix)
            .def("__getitem__", raw_function(&getItem))
            .def("set", &setI<MatrixXd>)
            .def("set", &setS<MatrixXd>)
            .def("set", &setII<MatrixXd>)
            .def("set", &setIS<MatrixXd>)
            .def("set", &setSI<MatrixXd>)
            .def("set", &setSS<MatrixXd>)
            .def("__setitem__", raw_function(&setItem))
            .def("__iter__", range(&matrixBegin<MatrixXd>, &matrixEnd<MatrixXd>))
            .def("minCoeff", &minCoeff)
            .def("maxCoeff", &maxCoeff)
            .def("colwise", &colwise<MatrixXd>, manage_matrix_expression)
            .def("rowwise", &rowwise<MatrixXd>, manage_matrix_expression)
            .def("squaredNorm", &squaredNorm<MatrixXd>)
            .def("norm", &norm<MatrixXd>)
            .def("normalized", &normalized<MatrixXd>, manage_new_matrix)
            .def("determinant", &determinant<MatrixXd>)
            .def("trace", &trace<MatrixXd>)
            .def("transpose", &transpose<MatrixXd>, manage_new_matrix)
            .def("inverse", &inverse, manage_new_matrix)
            .def("replicate", &replicate<MatrixXd>, manage_new_matrix)
            .def("dot", &dotXdXI)
            .def("dot", &dotXdXd)
            .def("cross", &crossXdXI, manage_new_matrix)
            .def("cross", &crossXdXd, manage_new_matrix)
            .def("isZero", &isZero<MatrixXd>)
            .def("isZero", &isZeroP<MatrixXd>)
            .def("hull", &hullXdXI, manage_new_matrix)
            .def("hull", &hullXdXd, manage_new_matrix)
            .def("Constant", &constant<MatrixXd>, manage_new_matrix)
                .staticmethod("Constant")
            .def("Zero", &zero<MatrixXd>, manage_new_matrix)
                .staticmethod("Zero")
            .def("Ones", &ones<MatrixXd>, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &random<MatrixXd>, manage_new_matrix)
                .staticmethod("Random")
            .def("Identity", &identity<MatrixXd>, manage_new_matrix)
                .staticmethod("Identity")
            .def("__neg__", &negXd, manage_new_matrix) 
            .def("__add__", &addXdXI, manage_new_matrix)
            .def("__add__", &addXdXd, manage_new_matrix)
            .def("__sub__", &subXdXI, manage_new_matrix)
            .def("__sub__", &subXdXd, manage_new_matrix)
            .def("__mul__", &mulXdI, manage_new_matrix)
            .def("__mul__", &mulXdd, manage_new_matrix)
            .def("__rmul__", &rmulXdI, manage_new_matrix)
            .def("__rmul__", &rmulXdd, manage_new_matrix)
            .def("__div__", &divXdDatum, manage_new_matrix)
            .def("__div__", &divXdI, manage_new_matrix)
            .def("__div__", &divXdd, manage_new_matrix)
            .def("__mul__", &mulXdDatum, manage_new_matrix)
            .def("__mul__", &mulXdXI, manage_new_matrix)
            .def("__mul__", &mulXdXd, manage_new_matrix)
            .def("__mod__", &modXdDatum, manage_new_matrix)
            .def("__eq__", &eqXdXd)
            .def("__eq__", &eqXdXI)
            .def("__ne__", &neXdXd)
            .def("__ne__", &neXdXI)
            .def("__str__", &str<MatrixXd>)
            .def("__repr__", &repr<MatrixXd>)
            .def_pickle(MatrixPickleSuite<MatrixXd>());

        class_<Colwise<MatrixXd>>("ColwiseMatrixXd", no_init)
            .def("__iter__", range(&colwiseBegin<MatrixXd>, &colwiseEnd<MatrixXd>))
            .def("squaredNorm", &colwiseSquaredNorm<MatrixXd>, manage_new_matrix)
            .def("norm", &colwiseNorm<MatrixXd>, manage_new_matrix);

        class_<Rowwise<MatrixXd>>("RowwiseMatrixXd", no_init)
            .def("__iter__", range(&rowwiseBegin<MatrixXd>, &rowwiseEnd<MatrixXd>))
            .def("squaredNorm", &rowwiseSquaredNorm<MatrixXd>, manage_new_matrix)
            .def("norm", &rowwiseNorm<MatrixXd>, manage_new_matrix);

        class_<MatrixXI>("MatrixXI")
            .def("rows", &rows<MatrixXI>)
            .def("cols", &cols<MatrixXI>)
            .def("size", &size<MatrixXI>)
            .def("value", &value<MatrixXI>)
            .def("x", &xComponent<MatrixXI>)
            .def("y", &yComponent<MatrixXI>)
            .def("z", &zComponent<MatrixXI>)
            .def("get", &getI<MatrixXI>)
            .def("get", &getS<MatrixXI>, manage_new_matrix)
            .def("get", &getII<MatrixXI>)
            .def("get", &getIS<MatrixXI>, manage_new_matrix)
            .def("get", &getSI<MatrixXI>, manage_new_matrix)
            .def("get", &getSS<MatrixXI>, manage_new_matrix)
            .def("__getitem__", raw_function(&getItem))
            .def("set", &setI<MatrixXI>)
            .def("set", &setS<MatrixXI>)
            .def("set", &setII<MatrixXI>)
            .def("set", &setIS<MatrixXI>)
            .def("set", &setSI<MatrixXI>)
            .def("set", &setSS<MatrixXI>)
            .def("__setitem__", raw_function(&setItem))
            .def("__iter__", range(&matrixBegin<MatrixXI>, &matrixEnd<MatrixXI>))
            .def("colwise", &colwise<MatrixXI>, manage_matrix_expression)
            .def("rowwise", &rowwise<MatrixXI>, manage_matrix_expression)
            .def("squaredNorm", &squaredNorm<MatrixXI>)
            .def("norm", &norm<MatrixXI>)
            .def("normalized", &normalized<MatrixXI>, manage_new_matrix)
            .def("determinant", &determinant<MatrixXI>)
            .def("trace", &trace<MatrixXI>)
            .def("transpose", &transpose<MatrixXI>, manage_new_matrix)
            .def("replicate", &replicate<MatrixXI>, manage_new_matrix)
            .def("dot", &dotXIXI)
            .def("dot", &dotXIXd)
            .def("cross", &crossXIXI, manage_new_matrix)
            .def("cross", &crossXIXd, manage_new_matrix)
            .def("isZero", &isZero<MatrixXI>)
            .def("isZero", &isZeroP<MatrixXI>)
            .def("overlaps", &overlaps)
            .def("overlaps", &overlapsP)
            .def("strictlyOverlaps", &strictlyOverlaps)
            .def("strictlyOverlaps", &strictlyOverlapsP)
            .def("contains", &containsXI)
            .def("contains", &containsXIP)
            .def("contains", &containsXd)
            .def("contains", &containsXdP)
            .def("__contains__", &containsXI)
            .def("__contains__", &containsXd)
            .def("strictlyContains", &strictlyContainsXI)
            .def("strictlyContains", &strictlyContainsXIP)
            .def("strictlyContains", &strictlyContainsXd)
            .def("strictlyContains", &strictlyContainsXdP)
            .def("cwiseLower", &cwiseLower, manage_new_matrix)
            .def("cwiseUpper", &cwiseUpper, manage_new_matrix)
            .def("cwiseMedian", &cwiseMedian, manage_new_matrix)
            .def("cwiseWidth", &cwiseWidth, manage_new_matrix)
            .def("hull", &hullXIXI, manage_new_matrix)
            .def("hull", &hullXIXd, manage_new_matrix)
            .def("intersection", &intersection, manage_new_matrix)
            .def("Constant", &constant<MatrixXI>, manage_new_matrix)
                .staticmethod("Constant")
            .def("Zero", &zero<MatrixXI>, manage_new_matrix)
                .staticmethod("Zero")
            .def("Ones", &ones<MatrixXI>, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &random<MatrixXI>, manage_new_matrix)
                .staticmethod("Random")
            .def("Identity", &identity<MatrixXI>, manage_new_matrix)
                .staticmethod("Identity")
            .def("__neg__", &negXI, manage_new_matrix)
            .def("__add__", &addXIXI, manage_new_matrix)
            .def("__add__", &addXIXd, manage_new_matrix)
            .def("__sub__", &subXIXI, manage_new_matrix)
            .def("__sub__", &subXIXd, manage_new_matrix)
            .def("__mul__", &mulXII, manage_new_matrix)
            .def("__mul__", &mulXId, manage_new_matrix)
            .def("__rmul__", &rmulXII, manage_new_matrix)
            .def("__rmul__", &rmulXId, manage_new_matrix)
            .def("__div__", &divXIDatum, manage_new_matrix)
            .def("__div__", &divXII, manage_new_matrix)
            .def("__div__", &divXId, manage_new_matrix)
            .def("__mul__", &mulXIDatum, manage_new_matrix)
            .def("__mul__", &mulXIXI, manage_new_matrix)
            .def("__mul__", &mulXIXd, manage_new_matrix)
            .def("__mod__", &modXIDatum, manage_new_matrix)
            .def("__eq__", &eqXIXd)
            .def("__eq__", &eqXIXI)
            .def("__ne__", &neXIXd)
            .def("__ne__", &neXIXI)
            .def("__str__", &str<MatrixXI>)
            .def("__repr__", &repr<MatrixXI>)
            .def_pickle(MatrixPickleSuite<MatrixXI>());

        class_<Colwise<MatrixXI>>("ColwiseMatrixXI", no_init)
            .def("__iter__", range(&colwiseBegin<MatrixXI>, &colwiseEnd<MatrixXI>))
            .def("squaredNorm", &colwiseSquaredNorm<MatrixXI>, manage_new_matrix)
            .def("norm", &colwiseNorm<MatrixXI>, manage_new_matrix);

        class_<Rowwise<MatrixXI>>("RowwiseMatrixXI", no_init)
            .def("__iter__", range(&rowwiseBegin<MatrixXI>, &rowwiseEnd<MatrixXI>))
            .def("squaredNorm", &rowwiseSquaredNorm<MatrixXI>, manage_new_matrix)
            .def("norm", &rowwiseNorm<MatrixXI>, manage_new_matrix);
    }
}
