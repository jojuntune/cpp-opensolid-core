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

#include <boost/python.hpp>
#include <boost/python/slice.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/raw_function.hpp>

#include <OpenSolid/Interval/Tolerance.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

#include "check.hpp"

using namespace boost::python;

namespace OpenSolid
{
    template <class MatrixType>
    int rows(const MatrixType& argument) {return argument.rows();}
    
    template <class MatrixType>
    int cols(const MatrixType& argument) {return argument.cols();}
    
    template <class MatrixType>
    int size(const MatrixType& argument) {return argument.size();}
    
    template <class MatrixType>
    typename MatrixType::Scalar scalar(const MatrixType& argument) {
        checkScalarValue(argument, __func__);
        return argument.scalar();
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
    typename MatrixType::Scalar squaredNorm(const MatrixType& argument) {
        checkVectorValue(argument, __func__);
        return argument.col(0).squaredNorm();
    }
    
    template <class MatrixType>
    typename MatrixType::Scalar norm(const MatrixType& argument) {
        checkVectorValue(argument, __func__);
        return argument.col(0).norm();
    }
    
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
    MatrixType* transpose(const MatrixType& argument) {
        return new MatrixType(argument.transpose());
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
    
    bool overlap(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return first_argument.overlap(second_argument);
    }
    
    bool containXIXd(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        return first_argument.contain(second_argument.cast<Interval>());
    }
    
    bool containXIXI(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        return first_argument.contain(second_argument);
    }
    
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
    
    bool operator==(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.operator==(second_argument);
    }
    
    bool operator==(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.operator==(second_argument);
    }
    
    bool operator==(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.cast<Interval>().eval() == second_argument;
    }
    
    bool operator==(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument == second_argument.cast<Interval>().eval();
    }
    
    bool operator!=(const MatrixXd& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.operator!=(second_argument);
    }
    
    bool operator!=(const MatrixXI& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.operator!=(second_argument);
    }
    
    bool operator!=(const MatrixXd& first_argument, const MatrixXI& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument.cast<Interval>().eval() != second_argument;
    }
    
    bool operator!=(const MatrixXI& first_argument, const MatrixXd& second_argument) {
        checkSameSizeMatrices(first_argument, second_argument, __func__);
        return first_argument != second_argument.cast<Interval>().eval();
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
    
    void bindMatrix() {         
        class_<MatrixXd>("MatrixXd", init<int, int>())
            .def("rows", &rows<MatrixXd>)
            .def("cols", &cols<MatrixXd>)
            .def("size", &size<MatrixXd>)
            .def("scalar", &scalar<MatrixXd>)
            .def("get", &getI<MatrixXd>)
            .def("get", &getS<MatrixXd>, return_value_policy<manage_new_object>())
            .def("get", &getII<MatrixXd>)
            .def("get", &getIS<MatrixXd>, return_value_policy<manage_new_object>())
            .def("get", &getSI<MatrixXd>, return_value_policy<manage_new_object>())
            .def("get", &getSS<MatrixXd>, return_value_policy<manage_new_object>())
            .def("__getitem__", raw_function(&getItem))
            .def("set", &setI<MatrixXd>)
            .def("set", &setS<MatrixXd>)
            .def("set", &setII<MatrixXd>)
            .def("set", &setIS<MatrixXd>)
            .def("set", &setSI<MatrixXd>)
            .def("set", &setSS<MatrixXd>)
            .def("__setitem__", raw_function(&setItem))
            .def("squaredNorm", &squaredNorm<MatrixXd>)
            .def("norm", &norm<MatrixXd>)
            .def("normalized", &normalized<MatrixXd>, return_value_policy<manage_new_object>())
            .def("determinant", &determinant<MatrixXd>)
            .def("trace", &trace<MatrixXd>)
            .def("transpose", &transpose<MatrixXd>, return_value_policy<manage_new_object>())
            .def("dot", &dotXdXI)
            .def("dot", &dotXdXd)
            .def("cross", &crossXdXI, return_value_policy<manage_new_object>())
            .def("cross", &crossXdXd, return_value_policy<manage_new_object>())
            .def("hull", &hullXdXI, return_value_policy<manage_new_object>())
            .def("hull", &hullXdXd, return_value_policy<manage_new_object>())
            .def("Constant", &constant<MatrixXd>, return_value_policy<manage_new_object>())
            .staticmethod("Constant")
            .def("Zero", &zero<MatrixXd>, return_value_policy<manage_new_object>())
            .staticmethod("Zero")
            .def("Ones", &ones<MatrixXd>, return_value_policy<manage_new_object>())
            .staticmethod("Ones")
            .def("Random", &random<MatrixXd>, return_value_policy<manage_new_object>())
            .staticmethod("Random")
            .def(self == MatrixXI())
            .def(self == self)
            .def(self != MatrixXI())
            .def(self != self)
            .def("__neg__", &negXd, return_value_policy<manage_new_object>())
            .def("__add__", &addXdXI, return_value_policy<manage_new_object>())
            .def("__add__", &addXdXd, return_value_policy<manage_new_object>())
            .def("__sub__", &subXdXI, return_value_policy<manage_new_object>())
            .def("__sub__", &subXdXd, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXdI, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXdd, return_value_policy<manage_new_object>())
            .def("__rmul__", &rmulXdI, return_value_policy<manage_new_object>())
            .def("__rmul__", &rmulXdd, return_value_policy<manage_new_object>())
            .def("__div__", &divXdI, return_value_policy<manage_new_object>())
            .def("__div__", &divXdd, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXdXI, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXdXd, return_value_policy<manage_new_object>())
            .def(self_ns::str(self));
        
        class_<MatrixXI>("MatrixXI", init<int, int>())
            .def("rows", &rows<MatrixXI>)
            .def("cols", &cols<MatrixXI>)
            .def("size", &size<MatrixXI>)
            .def("scalar", &scalar<MatrixXI>)
            .def("get", &getI<MatrixXI>)
            .def("get", &getS<MatrixXI>, return_value_policy<manage_new_object>())
            .def("get", &getII<MatrixXI>)
            .def("get", &getIS<MatrixXI>, return_value_policy<manage_new_object>())
            .def("get", &getSI<MatrixXI>, return_value_policy<manage_new_object>())
            .def("get", &getSS<MatrixXI>, return_value_policy<manage_new_object>())
            .def("__getitem__", raw_function(&getItem))
            .def("set", &setI<MatrixXI>)
            .def("set", &setS<MatrixXI>)
            .def("set", &setII<MatrixXI>)
            .def("set", &setIS<MatrixXI>)
            .def("set", &setSI<MatrixXI>)
            .def("set", &setSS<MatrixXI>)
            .def("__setitem__", raw_function(&setItem))
            .def("squaredNorm", &squaredNorm<MatrixXI>)
            .def("norm", &norm<MatrixXI>)
            .def("normalized", &normalized<MatrixXI>, return_value_policy<manage_new_object>())
            .def("determinant", &determinant<MatrixXI>)
            .def("trace", &trace<MatrixXI>)
            .def("transpose", &transpose<MatrixXI>, return_value_policy<manage_new_object>())
            .def("dot", &dotXIXI)
            .def("dot", &dotXIXd)
            .def("cross", &crossXIXI, return_value_policy<manage_new_object>())
            .def("cross", &crossXIXd, return_value_policy<manage_new_object>())
            .def("overlap", &overlap)
            .def("contain", &containXIXI)
            .def("contain", &containXIXd)
            .def("cwiseLower", &cwiseLower, return_value_policy<manage_new_object>())
            .def("cwiseUpper", &cwiseUpper, return_value_policy<manage_new_object>())
            .def("cwiseMedian", &cwiseMedian, return_value_policy<manage_new_object>())
            .def("cwiseWidth", &cwiseWidth, return_value_policy<manage_new_object>())
            .def("hull", &hullXIXI, return_value_policy<manage_new_object>())
            .def("hull", &hullXIXd, return_value_policy<manage_new_object>())
            .def("intersection", &intersection, return_value_policy<manage_new_object>())
            .def("Constant", &constant<MatrixXI>, return_value_policy<manage_new_object>())
            .staticmethod("Constant")
            .def("Zero", &zero<MatrixXI>, return_value_policy<manage_new_object>())
            .staticmethod("Zero")
            .def("Ones", &ones<MatrixXI>, return_value_policy<manage_new_object>())
            .staticmethod("Ones")
            .def("Random", &random<MatrixXI>, return_value_policy<manage_new_object>())
            .staticmethod("Random")
            .def(self == self)
            .def(self == MatrixXd())
            .def(self != self)
            .def(self != MatrixXd())
            .def("__neg__", &negXI, return_value_policy<manage_new_object>())
            .def("__add__", &addXIXI, return_value_policy<manage_new_object>())
            .def("__add__", &addXIXd, return_value_policy<manage_new_object>())
            .def("__sub__", &subXIXI, return_value_policy<manage_new_object>())
            .def("__sub__", &subXIXd, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXII, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXId, return_value_policy<manage_new_object>())
            .def("__rmul__", &rmulXII, return_value_policy<manage_new_object>())
            .def("__rmul__", &rmulXId, return_value_policy<manage_new_object>())
            .def("__div__", &divXII, return_value_policy<manage_new_object>())
            .def("__div__", &divXId, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXIXI, return_value_policy<manage_new_object>())
            .def("__mul__", &mulXIXd, return_value_policy<manage_new_object>())
            .def(self_ns::str(self));
    }
}
