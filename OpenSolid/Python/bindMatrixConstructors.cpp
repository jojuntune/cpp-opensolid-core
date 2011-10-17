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

#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Python/BoostPython.hpp>

using namespace boost::python;

namespace OpenSolid
{
    object genericVector(list components, bool column) {
        bool all_convertible_to_double = true;
        bool all_convertible_to_interval = true;
        int size = len(components);
        for (int i = 0; i < size; ++i) {
            object component = components[i];
            all_convertible_to_double &= extract<double>(component).check();
            all_convertible_to_interval &= extract<Interval>(component).check();
        }
        if (all_convertible_to_double) {
            MatrixXd result;
            if (column) {
                result.resize(size, 1);
                for (int i = 0; i < size; ++i) {result(i, 0) = extract<double>(components[i]);}
            } else {
                result.resize(1, size);
                for (int i = 0; i < size; ++i) {result(0, i) = extract<double>(components[i]);}
            }
            return object(result);
        } else if (all_convertible_to_interval) {
            MatrixXI result;
            if (column) {
                result.resize(size, 1);
                for (int i = 0; i < size; ++i) {result(i, 0) = extract<Interval>(components[i]);}
            } else {
                result.resize(1, size);
                for (int i = 0; i < size; ++i) {result(0, i) = extract<Interval>(components[i]);}
            }
            return object(result);
        } else {
            // TODO: throw error
        }
    }

    ////////// Vector constructors //////////

    struct VectorConstructors
    {
    };

    object vectorFromList(object, list components) {return genericVector(components, true);}

    object vectorFromMatrixXd(object, const MatrixXd& matrix) {
        // TODO check dimensions
        return object(matrix);
    }

    object vectorFromMatrixXI(object, const MatrixXI& matrix) {
        // TODO check dimensions
        return object(matrix);
    }

    object constantVectorFromInterval(int size, const Interval& value) {
        return object(MatrixXI(VectorXI::Constant(size, value)));
    }

    object constantVectorFromDouble(int size, double value) {
        return object(MatrixXd(VectorXd::Constant(size, value)));
    }

    object linSpacedVector(int size, const Interval& range) {
        return object(MatrixXd(VectorXd::LinSpaced(size, range)));
    }

    object onesVector(int size) {return object(MatrixXd(VectorXd::Ones(size)));}

    object randomVector(int size) {return object(MatrixXd(VectorXd::Random(size)));}

    object zeroVector(int size) {return object(MatrixXd(VectorXd::Zero(size)));}

    ////////// RowVector constructors //////////

    struct RowVectorConstructors
    {
    };

    object rowVectorFromList(object, list components) {return genericVector(components, false);}

    object rowVectorFromMatrixXd(object, const MatrixXd& matrix) {
        // TODO check dimensions
        return object(matrix);
    }

    object rowVectorFromMatrixXI(object, const MatrixXI& matrix) {
        // TODO check dimensions
        return object(matrix);
    }

    object constantRowVectorFromInterval(int size, const Interval& value) {
        return object(MatrixXI(RowVectorXI::Constant(size, value)));
    }

    object constantRowVectorFromDouble(int size, double value) {
        return object(MatrixXd(RowVectorXd::Constant(size, value)));
    }

    object linSpacedRowVector(int size, const Interval& range) {
        return object(MatrixXd(RowVectorXd::LinSpaced(size, range)));
    }

    object onesRowVector(int size) {return object(MatrixXd(RowVectorXd::Ones(size)));}

    object randomRowVector(int size) {return object(MatrixXd(RowVectorXd::Random(size)));}

    object zeroRowVector(int size) {return object(MatrixXd(RowVectorXd::Zero(size)));}

    ////////// Matrix constructors //////////

    struct MatrixConstructors
    {
    };

    object matrixFromList(object, list columns) {
        object first_column = columns[0];
        int num_columns = len(columns);
        if (extract<list>(first_column).check()) {
            int num_rows = len(first_column);
            bool all_convertible_to_double = true;
            bool all_convertible_to_interval = true;
            for (int j = 0; j < num_columns; ++j) {
                object column = columns[j];
                if (len(column) != num_rows) {/*TODO: throw error*/}
                for (int i = 0; i < num_rows; ++i) {
                    object component = column[i];
                    all_convertible_to_double &= extract<double>(component).check();
                    all_convertible_to_interval &= extract<Interval>(component).check();
                }
            }
            if (all_convertible_to_double) {
                MatrixXd result(num_rows, num_columns);
                for (int j = 0; j < num_columns; ++j) {
                    object column = columns[j];
                    for (int i = 0; i < num_rows; ++i) {
                        result(i, j) = extract<double>(column[i]);
                    }
                }
                return object(result);
            } else if (all_convertible_to_interval) {
                MatrixXI result(num_rows, num_columns);
                for (int j = 0; j < num_columns; ++j) {
                    object column = columns[j];
                    for (int i = 0; i < num_rows; ++i) {
                        result(i, j) = extract<Interval>(column[i]);
                    }
                }
                return object(result);
            } else {
                // TOOD: throw error
            }
        } else if (extract<MatrixXd>(first_column).check()) {
            MatrixXd column = extract<MatrixXd>(first_column);
            int num_rows = column.rows();
            MatrixXd result(num_rows, num_columns);
            for (int j = 0; j < num_columns; ++j) {
                column = extract<MatrixXd>(columns[j]);
                // TODO check for 1 column, correct number of rows
                result.col(j) = column;
            }
            return object(result);
        } else if (extract<MatrixXI>(first_column).check()) {
            MatrixXI column = extract<MatrixXI>(first_column);
            int num_rows = column.rows();
            MatrixXI result(num_rows, num_columns);
            for (int j = 0; j < num_columns; ++j) {
                column = extract<MatrixXI>(columns[j]);
                // TODO check for 1 column, correct number of rows
                result.col(j) = column;
            }
            return object(result);
        } else {
            // TODO: throw error
        }
    }

    object matrixFromMatrixXd(object, const MatrixXd& matrix) {
        // TODO check dimensions
        return object(matrix);
    }

    object matrixFromMatrixXI(object, const MatrixXI& matrix) {
        // TODO check dimensions
        return object(matrix);
    }

    object constantMatrixFromInterval(int rows, int cols, const Interval& value) {
        return object(MatrixXI(MatrixXI::Constant(rows, cols, value)));
    }

    object constantSquareMatrixFromInterval(int size, const Interval& value) {
        return object(MatrixXI(MatrixXI::Constant(size, size, value)));
    }

    object constantMatrixFromDouble(int rows, int cols, double value) {
        return object(MatrixXd(MatrixXd::Constant(rows, cols, value)));
    }

    object constantSquareMatrixFromDouble(int size, double value) {
        return object(MatrixXd(MatrixXd::Constant(size, size, value)));
    }

    object onesMatrix(int rows, int cols) {return object(MatrixXd(MatrixXd::Ones(rows, cols)));}

    object onesSquareMatrix(int size) {return object(MatrixXd(MatrixXd::Ones(size, size)));}

    object randomMatrix(int rows, int cols) {return object(MatrixXd(MatrixXd::Random(rows, cols)));}

    object randomSquareMatrix(int size) {return object(MatrixXd(MatrixXd::Random(size, size)));}

    object zeroMatrix(int rows, int cols) {return object(MatrixXd(MatrixXd::Zero(rows, cols)));}

    object zeroSquareMatrix(int size) {return object(MatrixXd(MatrixXd::Zero(size, size)));}

    object identityMatrix(int rows, int cols) {
        return object(MatrixXd(MatrixXd::Identity(rows, cols)));
    }

    object identitySquareMatrix(int size) {
        return object(MatrixXd(MatrixXd::Identity(size, size)));
    }

    void bindMatrixConstructors() {
        class_<VectorConstructors>("Vector", no_init)
            .def("__new__", &vectorFromMatrixXI)
            .def("__new__", &vectorFromMatrixXd)
            .def("__new__", &vectorFromList)
                .staticmethod("__new__")
            .def("Constant", &constantVectorFromInterval)
            .def("Constant", &constantVectorFromDouble)
                .staticmethod("Constant")
            .def("LinSpaced", &linSpacedVector)
                .staticmethod("LinSpaced")
            .def("Ones", &onesVector)
                .staticmethod("Ones")
            .def("Random", &randomVector)
                .staticmethod("Random")
            .def("Zero", &zeroVector)
                .staticmethod("Zero");
        class_<RowVectorConstructors>("RowVector", no_init)
            .def("__new__", &rowVectorFromMatrixXI)
            .def("__new__", &rowVectorFromMatrixXd)
            .def("__new__", &rowVectorFromList)
                .staticmethod("__new__")
            .def("Constant", &constantRowVectorFromInterval)
            .def("Constant", &constantRowVectorFromDouble)
                .staticmethod("Constant")
            .def("LinSpaced", &linSpacedRowVector)
                .staticmethod("LinSpaced")
            .def("Ones", &onesRowVector)
                .staticmethod("Ones")
            .def("Random", &randomRowVector)
                .staticmethod("Random")
            .def("Zero", &zeroRowVector)
                .staticmethod("Zero");
        class_<MatrixConstructors>("Matrix", no_init)
            .def("__new__", &matrixFromMatrixXI)
            .def("__new__", &matrixFromMatrixXd)
            .def("__new__", &matrixFromList)
                .staticmethod("__new__")
            .def("Constant", &constantMatrixFromInterval)
            .def("Constant", &constantSquareMatrixFromInterval)
            .def("Constant", &constantMatrixFromDouble)
            .def("Constant", &constantSquareMatrixFromDouble)
                .staticmethod("Constant")
            .def("Ones", &onesMatrix)
            .def("Ones", &onesSquareMatrix)
                .staticmethod("Ones")
            .def("Random", &randomMatrix)
            .def("Random", &randomSquareMatrix)
                .staticmethod("Random")
            .def("Zero", &zeroMatrix)
            .def("Zero", &zeroSquareMatrix)
                .staticmethod("Zero")
            .def("Identity", &identityMatrix)
            .def("Identity", &identitySquareMatrix)
                .staticmethod("Identity");
    }
}
