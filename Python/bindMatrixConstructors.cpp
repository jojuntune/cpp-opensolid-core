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

#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    struct Vector2dConstructors
    {
        static MatrixXd* components(object, double x, double y) {
            return new MatrixXd(Vector2d(x, y));
        }

        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 2 || matrix.cols() != 1) {
                throw Vector2dCopyConstructionError(matrix);
            }
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(double value) {
            return new MatrixXd(Vector2d::Constant(value));
        }

        static MatrixXd* LinSpaced(const Interval& range) {
            return new MatrixXd(Vector2d::LinSpaced(range));
        }

        static MatrixXd* Ones() {return new MatrixXd(Vector2d::Ones());}

        static MatrixXd* Random() {return new MatrixXd(Vector2d::Random());}

        static MatrixXd* Zero() {return new MatrixXd(Vector2d::Zero());}

        static MatrixXd* UnitX() {return new MatrixXd(Vector2d::UnitX());}

        static MatrixXd* UnitY() {return new MatrixXd(Vector2d::UnitY());}

        static MatrixXd* Unit(int index) {
            if (index < 0 || index > 1) {throw UnitVector2dConstructionError(index);}
            return new MatrixXd(Vector2d::Unit(index));
        }
    };

    struct Vector3dConstructors
    {
        static MatrixXd* components(object, double x, double y, double z) {
            return new MatrixXd(Vector3d(x, y, z));
        }

        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 3 || matrix.cols() != 1) {
                throw Vector3dCopyConstructionError(matrix);
            }
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(double value) {
            return new MatrixXd(Vector3d::Constant(value));
        }

        static MatrixXd* LinSpaced(const Interval& range) {
            return new MatrixXd(Vector3d::LinSpaced(range));
        }

        static MatrixXd* Ones() {return new MatrixXd(Vector3d::Ones());}

        static MatrixXd* Random() {return new MatrixXd(Vector3d::Random());}

        static MatrixXd* Zero() {return new MatrixXd(Vector3d::Zero());}

        static MatrixXd* UnitX() {return new MatrixXd(Vector3d::UnitX());}

        static MatrixXd* UnitY() {return new MatrixXd(Vector3d::UnitY());}

        static MatrixXd* UnitZ() {return new MatrixXd(Vector3d::UnitZ());}

        static MatrixXd* Unit(int index) {
            if (index < 0 || index > 2) {throw UnitVector3dConstructionError(index);}
            return new MatrixXd(Vector3d::Unit(index));
        }
    };

    struct VectorXdConstructors
    {
        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.cols() != 1) {throw VectorXdCopyConstructionError(matrix);}
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(int size, double value) {
            return new MatrixXd(VectorXd::Constant(size, value));
        }

        static MatrixXd* LinSpaced(int size, const Interval& range) {
            return new MatrixXd(VectorXd::LinSpaced(size, range));
        }

        static MatrixXd* Ones(int size) {return new MatrixXd(VectorXd::Ones(size));}

        static MatrixXd* Random(int size) {return new MatrixXd(VectorXd::Random(size));}

        static MatrixXd* Zero(int size) {return new MatrixXd(VectorXd::Zero(size));}

        static MatrixXd* Unit(int size, int index) {
            if (size <= 0 || index < 0 || index >= size) {
                throw UnitVectorXdConstructionError(size, index);
            }
            return new MatrixXd(VectorXd::Unit(size, index));
        }
    };

    struct RowVector2dConstructors
    {
        static MatrixXd* components(object, double x, double y) {
            return new MatrixXd(RowVector2d(x, y));
        }

        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 1 || matrix.cols() != 2) {
                throw RowVector2dCopyConstructionError(matrix);
            }
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(double value) {
            return new MatrixXd(RowVector2d::Constant(value));
        }

        static MatrixXd* LinSpaced(const Interval& range) {
            return new MatrixXd(RowVector2d::LinSpaced(range));
        }

        static MatrixXd* Ones() {return new MatrixXd(RowVector2d::Ones());}

        static MatrixXd* Random() {return new MatrixXd(RowVector2d::Random());}

        static MatrixXd* Zero() {return new MatrixXd(RowVector2d::Zero());}

        static MatrixXd* UnitX() {return new MatrixXd(RowVector2d::UnitX());}

        static MatrixXd* UnitY() {return new MatrixXd(RowVector2d::UnitY());}

        static MatrixXd* Unit(int index) {
            if (index < 0 || index > 1) {throw UnitRowVector2dConstructionError(index);}
            return new MatrixXd(RowVector2d::Unit(index));
        }
    };

    struct RowVector3dConstructors
    {
        static MatrixXd* components(object, double x, double y, double z) {
            return new MatrixXd(RowVector3d(x, y, z));
        }

        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 1 || matrix.cols() != 3) {
                throw RowVector3dCopyConstructionError(matrix);
            }
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(double value) {
            return new MatrixXd(RowVector3d::Constant(value));
        }

        static MatrixXd* LinSpaced(const Interval& range) {
            return new MatrixXd(RowVector3d::LinSpaced(range));
        }

        static MatrixXd* Ones() {return new MatrixXd(RowVector3d::Ones());}

        static MatrixXd* Random() {return new MatrixXd(RowVector3d::Random());}

        static MatrixXd* Zero() {return new MatrixXd(RowVector3d::Zero());}

        static MatrixXd* UnitX() {return new MatrixXd(RowVector3d::UnitX());}

        static MatrixXd* UnitY() {return new MatrixXd(RowVector3d::UnitY());}

        static MatrixXd* UnitZ() {return new MatrixXd(RowVector3d::UnitZ());}

        static MatrixXd* Unit(int index) {
            if (index < 0 || index > 2) {throw UnitRowVector3dConstructionError(index);}
            return new MatrixXd(RowVector3d::Unit(index));
        }
    };

    struct RowVectorXdConstructors
    {
        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 1) {throw RowVectorXdCopyConstructionError(matrix);}
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(int size, double value) {
            return new MatrixXd(RowVectorXd::Constant(size, value));
        }

        static MatrixXd* LinSpaced(int size, const Interval& range) {
            return new MatrixXd(RowVectorXd::LinSpaced(size, range));
        }

        static MatrixXd* Ones(int size) {return new MatrixXd(RowVectorXd::Ones(size));}

        static MatrixXd* Random(int size) {return new MatrixXd(RowVectorXd::Random(size));}

        static MatrixXd* Zero(int size) {return new MatrixXd(RowVectorXd::Zero(size));}

        static MatrixXd* Unit(int size, int index) {
            if (size <= 0 || index < 0 || index >= size) {
                throw UnitRowVectorXdConstructionError(size, index);
            }
            return new MatrixXd(RowVectorXd::Unit(size, index));
        }
    };
    
    struct Vector2IConstructors
    {
        static MatrixXI* components(object, const Interval& x, const Interval& y) {
            return new MatrixXI(Vector2I(x, y));
        }

        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 2 || matrix.cols() != 1) {
                throw Vector2ICopyConstructionError(matrix);
            }
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(const Interval& value) {
            return new MatrixXI(Vector2I::Constant(value));
        }

        static MatrixXI* LinSpaced(const Interval& range) {
            return new MatrixXI(Vector2I::LinSpaced(range));
        }

        static MatrixXI* Ones() {return new MatrixXI(Vector2I::Ones());}

        static MatrixXI* Random() {return new MatrixXI(Vector2I::Random());}

        static MatrixXI* Zero() {return new MatrixXI(Vector2I::Zero());}

        static MatrixXI* UnitX() {return new MatrixXI(Vector2I::UnitX());}

        static MatrixXI* UnitY() {return new MatrixXI(Vector2I::UnitY());}

        static MatrixXI* Unit(int index) {
            if (index < 0 || index > 1) {throw UnitVector2IConstructionError(index);}
            return new MatrixXI(Vector2I::Unit(index));
        }
    };

    struct Vector3IConstructors
    {
        static MatrixXI* components(object, const Interval& x, const Interval& y, const Interval& z) {
            return new MatrixXI(Vector3I(x, y, z));
        }

        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 3 || matrix.cols() != 1) {
                throw Vector3ICopyConstructionError(matrix);
            }
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(const Interval& value) {
            return new MatrixXI(Vector3I::Constant(value));
        }

        static MatrixXI* LinSpaced(const Interval& range) {
            return new MatrixXI(Vector3I::LinSpaced(range));
        }

        static MatrixXI* Ones() {return new MatrixXI(Vector3I::Ones());}

        static MatrixXI* Random() {return new MatrixXI(Vector3I::Random());}

        static MatrixXI* Zero() {return new MatrixXI(Vector3I::Zero());}

        static MatrixXI* UnitX() {return new MatrixXI(Vector3I::UnitX());}

        static MatrixXI* UnitY() {return new MatrixXI(Vector3I::UnitY());}

        static MatrixXI* UnitZ() {return new MatrixXI(Vector3I::UnitZ());}

        static MatrixXI* Unit(int index) {
            if (index < 0 || index > 2) {throw UnitVector3IConstructionError(index);}
            return new MatrixXI(Vector3I::Unit(index));
        }
    };

    struct VectorXIConstructors
    {
        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.cols() != 1) {throw VectorXICopyConstructionError(matrix);}
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(int size, const Interval& value) {
            return new MatrixXI(VectorXI::Constant(size, value));
        }

        static MatrixXI* LinSpaced(int size, const Interval& range) {
            return new MatrixXI(VectorXI::LinSpaced(size, range));
        }

        static MatrixXI* Ones(int size) {return new MatrixXI(VectorXI::Ones(size));}

        static MatrixXI* Random(int size) {return new MatrixXI(VectorXI::Random(size));}

        static MatrixXI* Zero(int size) {return new MatrixXI(VectorXI::Zero(size));}

        static MatrixXI* Unit(int size, int index) {
            if (size <= 0 || index < 0 || index >= size) {
                throw UnitVectorXIConstructionError(size, index);
            }
            return new MatrixXI(VectorXI::Unit(size, index));
        }
    };
    
    struct RowVector2IConstructors
    {
        static MatrixXI* components(object, const Interval& x, const Interval& y) {
            return new MatrixXI(RowVector2I(x, y));
        }

        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 1 || matrix.cols() != 2) {
                throw RowVector2ICopyConstructionError(matrix);
            }
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(const Interval& value) {
            return new MatrixXI(RowVector2I::Constant(value));
        }

        static MatrixXI* LinSpaced(const Interval& range) {
            return new MatrixXI(RowVector2I::LinSpaced(range));
        }

        static MatrixXI* Ones() {return new MatrixXI(RowVector2I::Ones());}

        static MatrixXI* Random() {return new MatrixXI(RowVector2I::Random());}

        static MatrixXI* Zero() {return new MatrixXI(RowVector2I::Zero());}

        static MatrixXI* UnitX() {return new MatrixXI(RowVector2I::UnitX());}

        static MatrixXI* UnitY() {return new MatrixXI(RowVector2I::UnitY());}

        static MatrixXI* Unit(int index) {
            if (index < 0 || index > 1) {throw UnitRowVector2IConstructionError(index);}
            return new MatrixXI(RowVector2I::Unit(index));
        }
    };

    struct RowVector3IConstructors
    {
        static MatrixXI* components(object, const Interval& x, const Interval& y, const Interval& z) {
            return new MatrixXI(RowVector3I(x, y, z));
        }

        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 1 || matrix.cols() != 3) {
                throw RowVector2ICopyConstructionError(matrix);
            }
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(const Interval& value) {
            return new MatrixXI(RowVector3I::Constant(value));
        }

        static MatrixXI* LinSpaced(const Interval& range) {
            return new MatrixXI(RowVector3I::LinSpaced(range));
        }

        static MatrixXI* Ones() {return new MatrixXI(RowVector3I::Ones());}

        static MatrixXI* Random() {return new MatrixXI(RowVector3I::Random());}

        static MatrixXI* Zero() {return new MatrixXI(RowVector3I::Zero());}

        static MatrixXI* UnitX() {return new MatrixXI(RowVector3I::UnitX());}

        static MatrixXI* UnitY() {return new MatrixXI(RowVector3I::UnitY());}

        static MatrixXI* UnitZ() {return new MatrixXI(RowVector3I::UnitZ());}

        static MatrixXI* Unit(int index) {
            if (index < 0 || index > 1) {throw UnitRowVector3IConstructionError(index);}
            return new MatrixXI(RowVector3I::Unit(index));
        }
    };

    struct RowVectorXIConstructors
    {
        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 1) {throw RowVectorXICopyConstructionError(matrix);}
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(int size, const Interval& value) {
            return new MatrixXI(RowVectorXI::Constant(size, value));
        }

        static MatrixXI* LinSpaced(int size, const Interval& range) {
            return new MatrixXI(RowVectorXI::LinSpaced(size, range));
        }

        static MatrixXI* Ones(int size) {return new MatrixXI(RowVectorXI::Ones(size));}

        static MatrixXI* Random(int size) {return new MatrixXI(RowVectorXI::Random(size));}

        static MatrixXI* Zero(int size) {return new MatrixXI(RowVectorXI::Zero(size));}

        static MatrixXI* Unit(int size, int index) {
            if (size <= 0 || index < 0 || index >= size) {
                throw UnitRowVectorXIConstructionError(size, index);
            }
            return new MatrixXI(RowVectorXI::Unit(size, index));
        }
    };

    struct Matrix2dConstructors
    {
        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 2 || matrix.cols() != 2) {
                throw Matrix2dCopyConstructionError(matrix);
            }
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(double value) {return new MatrixXd(Matrix2d::Constant(value));}

        static MatrixXd* Identity() {return new MatrixXd(Matrix2d::Identity());}

        static MatrixXd* Ones() {return new MatrixXd(Matrix2d::Ones());}

        static MatrixXd* Random() {return new MatrixXd(Matrix2d::Random());}

        static MatrixXd* Zero() {return new MatrixXd(Matrix2d::Zero());}
    };

    struct Matrix3dConstructors
    {
        static MatrixXd* copy(object, const MatrixXd& matrix) {
            if (matrix.rows() != 3 || matrix.cols() != 3) {
                throw Matrix3dCopyConstructionError(matrix);
            }
            return new MatrixXd(matrix);
        }

        static MatrixXd* Constant(double value) {return new MatrixXd(Matrix3d::Constant(value));}

        static MatrixXd* Identity() {return new MatrixXd(Matrix3d::Identity());}

        static MatrixXd* Ones() {return new MatrixXd(Matrix3d::Ones());}

        static MatrixXd* Random() {return new MatrixXd(Matrix3d::Random());}

        static MatrixXd* Zero() {return new MatrixXd(Matrix3d::Zero());}
    };

    struct MatrixXdConstructors
    {
        static MatrixXd* copy(const MatrixXd& matrix) {return new MatrixXd(matrix);}

        static MatrixXd* Constant(int rows, int cols, double value) {
            if (rows <= 0 || cols <= 0) {
                throw ConstantMatrixConstructionError<MatrixXd>(rows, cols, value);
            }
            return new MatrixXd(MatrixXd::Constant(rows, cols, value));
        }

        static MatrixXd* Identity(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw IdentityMatrixConstructionError<MatrixXd>(rows, cols);
            }
            return new MatrixXd(MatrixXd::Identity(rows, cols));
        }

        static MatrixXd* Ones(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw OnesMatrixConstructionError<MatrixXd>(rows, cols);
            }
            return new MatrixXd(MatrixXd::Ones(rows, cols));
        }

        static MatrixXd* Random(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw RandomMatrixConstructionError<MatrixXd>(rows, cols);
            }
            return new MatrixXd(MatrixXd::Random(rows, cols));
        }

        static MatrixXd* Zero(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw ZeroMatrixConstructionError<MatrixXd>(rows, cols);
            }
            return new MatrixXd(MatrixXd::Zero(rows, cols));
        }
    };

    struct Matrix2IConstructors
    {
        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 2 || matrix.cols() != 2) {
                throw Matrix2ICopyConstructionError(matrix);
            }
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(const Interval& value) {
            return new MatrixXI(Matrix2I::Constant(value));
        }

        static MatrixXI* Identity() {return new MatrixXI(Matrix2I::Identity());}

        static MatrixXI* Ones() {return new MatrixXI(Matrix2I::Ones());}

        static MatrixXI* Random() {return new MatrixXI(Matrix2I::Random());}

        static MatrixXI* Zero() {return new MatrixXI(Matrix2I::Zero());}
    };

    struct Matrix3IConstructors
    {
        static MatrixXI* copy(object, const MatrixXI& matrix) {
            if (matrix.rows() != 3 || matrix.cols() != 3) {
                throw Matrix3ICopyConstructionError(matrix);
            }
            return new MatrixXI(matrix);
        }

        static MatrixXI* Constant(const Interval& value) {
            return new MatrixXI(Matrix3I::Constant(value));
        }

        static MatrixXI* Identity() {return new MatrixXI(Matrix3I::Identity());}

        static MatrixXI* Ones() {return new MatrixXI(Matrix3I::Ones());}

        static MatrixXI* Random() {return new MatrixXI(Matrix3I::Random());}

        static MatrixXI* Zero() {return new MatrixXI(Matrix3I::Zero());}
    };

    struct MatrixXIConstructors
    {
        static MatrixXI* copy(const MatrixXI& matrix) {return new MatrixXI(matrix);}

        static MatrixXI* Constant(int rows, int cols, const Interval& value) {
            if (rows <= 0 || cols <= 0) {
                throw ConstantMatrixConstructionError<MatrixXI>(rows, cols, value);
            }
            return new MatrixXI(MatrixXI::Constant(rows, cols, value));
        }

        static MatrixXI* Identity(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw IdentityMatrixConstructionError<MatrixXI>(rows, cols);
            }
            return new MatrixXI(MatrixXI::Identity(rows, cols));
        }

        static MatrixXI* Ones(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw OnesMatrixConstructionError<MatrixXI>(rows, cols);
            }
            return new MatrixXI(MatrixXI::Ones(rows, cols));
        }

        static MatrixXI* Random(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw RandomMatrixConstructionError<MatrixXd>(rows, cols);
            }
            return new MatrixXI(MatrixXI::Random(rows, cols));
        }

        static MatrixXI* Zero(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw ZeroMatrixConstructionError<MatrixXd>(rows, cols);
            }
            return new MatrixXI(MatrixXI::Zero(rows, cols));
        }
    };

    template <class VectorType>
    Matrix<typename VectorType::Scalar, Dynamic, Dynamic>* vectorFromList(object, list components) {
        typedef Matrix<typename VectorType::Scalar, Dynamic, Dynamic> ResultType;
        int size = len(components);
        int rows = VectorType::RowsAtCompileTime == 1 ? 1 : size;
        int cols = VectorType::ColsAtCompileTime == 1 ? 1 : size;
        ResultType* result = new ResultType(rows, cols);
        for (int i = 0; i < size; ++i) {
            (*result)(i) = extract<typename VectorType::Scalar>(components[i]);
        }
        return result;
    }

    template <class MatrixType>
    Matrix<typename MatrixType::Scalar, Dynamic, Dynamic>* initMatrixFromList(list components) {
        typedef Matrix<typename MatrixType::Scalar, Dynamic, Dynamic> ResultType;
        int cols = len(components);
        int rows = len(components[0]);
        ResultType* result = new ResultType(rows, cols);
        for (int j = 0; j < cols; ++j) {
            object column = components[j];
            for (int i = 0; i < rows; ++i) {
                (*result)(i, j) = extract<typename MatrixType::Scalar>(column[i]);
            }
        }
        return result;
    }
    
    template <class MatrixType>
    auto newMatrixFromList(object, list components) ->
        decltype(initMatrixFromList<MatrixType>(components)) {
        return initMatrixFromList<MatrixType>(components);
    }

    class_<MatrixXd>& pythonMatrixXd();
    class_<MatrixXI>& pythonMatrixXI();

    void bindMatrixConstructors() {
        return_value_policy<manage_new_object> manage_new_matrix;

        class_<Vector2dConstructors>("Vector2d", no_init)
            .def("__new__", &vectorFromList<Vector2d>, manage_new_matrix)
            .def("__new__", &Vector2dConstructors::components, manage_new_matrix)
            .def("__new__", &Vector2dConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Vector2dConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &Vector2dConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &Vector2dConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Vector2dConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Vector2dConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &Vector2dConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &Vector2dConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("Unit", &Vector2dConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXd, Vector2d>();

        class_<Vector3dConstructors>("Vector3d", no_init)
            .def("__new__", &vectorFromList<Vector3d>, manage_new_matrix)
            .def("__new__", &Vector3dConstructors::components, manage_new_matrix)
            .def("__new__", &Vector3dConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Vector3dConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &Vector3dConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &Vector3dConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Vector3dConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Vector3dConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &Vector3dConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &Vector3dConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("UnitZ", &Vector3dConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitZ")
            .def("Unit", &Vector3dConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXd, Vector3d>();

        class_<VectorXdConstructors>("VectorXd", no_init)
            .def("__new__", &vectorFromList<VectorXd>, manage_new_matrix)
            .def("__new__", &VectorXdConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &VectorXdConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &VectorXdConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &VectorXdConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &VectorXdConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &VectorXdConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("Unit", &VectorXdConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXd, VectorXd>();

        class_<RowVector2dConstructors>("RowVector2d", no_init)
            .def("__new__", &vectorFromList<RowVector2d>, manage_new_matrix)
            .def("__new__", &RowVector2dConstructors::components, manage_new_matrix)
            .def("__new__", &RowVector2dConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &RowVector2dConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &RowVector2dConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &RowVector2dConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &RowVector2dConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &RowVector2dConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &RowVector2dConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &RowVector2dConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("Unit", &RowVector2dConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXd, RowVector2d>();

        class_<RowVector3dConstructors>("RowVector3d", no_init)
            .def("__new__", &vectorFromList<RowVector3d>, manage_new_matrix)
            .def("__new__", &RowVector3dConstructors::components, manage_new_matrix)
            .def("__new__", &RowVector3dConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &RowVector3dConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &RowVector3dConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &RowVector3dConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &RowVector3dConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &RowVector3dConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &RowVector3dConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &RowVector3dConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("UnitZ", &RowVector3dConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitZ")
            .def("Unit", &RowVector3dConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXd, RowVector3d>();

        class_<RowVectorXdConstructors>("RowVectorXd", no_init)
            .def("__new__", &vectorFromList<RowVectorXd>, manage_new_matrix)
            .def("__new__", &RowVectorXdConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &RowVectorXdConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &RowVectorXdConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &RowVectorXdConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &RowVectorXdConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &RowVectorXdConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("Unit", &RowVectorXdConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXd, RowVectorXd>();

        class_<Vector2IConstructors>("Vector2I", no_init)
            .def("__new__", &vectorFromList<Vector2I>, manage_new_matrix)
            .def("__new__", &Vector2IConstructors::components, manage_new_matrix)
            .def("__new__", &Vector2IConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Vector2IConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &Vector2IConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &Vector2IConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Vector2IConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Vector2IConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &Vector2IConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &Vector2IConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("Unit", &Vector2IConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXI, Vector2I>();

        class_<Vector3IConstructors>("Vector3I", no_init)
            .def("__new__", &vectorFromList<Vector3I>, manage_new_matrix)
            .def("__new__", &Vector3IConstructors::components, manage_new_matrix)
            .def("__new__", &Vector3IConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Vector3IConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &Vector3IConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &Vector3IConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Vector3IConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Vector3IConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &Vector3IConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &Vector3IConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("UnitZ", &Vector3IConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitZ")
            .def("Unit", &Vector3IConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXI, Vector3I>();

        class_<VectorXIConstructors>("VectorXI", no_init)
            .def("__new__", &vectorFromList<VectorXI>, manage_new_matrix)
            .def("__new__", &VectorXIConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &VectorXIConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &VectorXIConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &VectorXIConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &VectorXIConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &VectorXIConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("Unit", &VectorXIConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXI, VectorXI>();

        class_<RowVector2IConstructors>("RowVector2I", no_init)
            .def("__new__", &vectorFromList<RowVector2I>, manage_new_matrix)
            .def("__new__", &RowVector2IConstructors::components, manage_new_matrix)
            .def("__new__", &RowVector2IConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &RowVector2IConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &RowVector2IConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &RowVector2IConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &RowVector2IConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &RowVector2IConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &RowVector2IConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &RowVector2IConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("Unit", &RowVector2IConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXI, RowVector2I>();

        class_<RowVector3IConstructors>("RowVector3I", no_init)
            .def("__new__", &vectorFromList<RowVector3I>, manage_new_matrix)
            .def("__new__", &RowVector3IConstructors::components, manage_new_matrix)
            .def("__new__", &RowVector3IConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &RowVector3IConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &RowVector3IConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &RowVector3IConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &RowVector3IConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &RowVector3IConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("UnitX", &RowVector3IConstructors::UnitX, manage_new_matrix)
                .staticmethod("UnitX")
            .def("UnitY", &RowVector3IConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitY")
            .def("UnitZ", &RowVector3IConstructors::UnitY, manage_new_matrix)
                .staticmethod("UnitZ")
            .def("Unit", &RowVector3IConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXI, RowVector3I>();

        class_<RowVectorXIConstructors>("RowVectorXI", no_init)
            .def("__new__", &vectorFromList<RowVectorXI>, manage_new_matrix)
            .def("__new__", &RowVectorXIConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &RowVectorXIConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("LinSpaced", &RowVectorXIConstructors::LinSpaced, manage_new_matrix)
                .staticmethod("LinSpaced")
            .def("Ones", &RowVectorXIConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &RowVectorXIConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &RowVectorXIConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero")
            .def("Unit", &RowVectorXIConstructors::Unit, manage_new_matrix)
                .staticmethod("Unit");

        implicitly_convertible<MatrixXI, RowVectorXI>();

        class_<Matrix2dConstructors>("Matrix2d", no_init)
            .def("__new__", &newMatrixFromList<Matrix2d>, manage_new_matrix)
            .def("__new__", &Matrix2dConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Matrix2dConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("Identity", &Matrix2dConstructors::Identity, manage_new_matrix)
                .staticmethod("Identity")
            .def("Ones", &Matrix2dConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Matrix2dConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Matrix2dConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero");

        implicitly_convertible<MatrixXd, Matrix2d>();

        class_<Matrix3dConstructors>("Matrix3d", no_init)
            .def("__new__", &newMatrixFromList<Matrix3d>, manage_new_matrix)
            .def("__new__", &Matrix3dConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Matrix3dConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("Identity", &Matrix3dConstructors::Identity, manage_new_matrix)
                .staticmethod("Identity")
            .def("Ones", &Matrix3dConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Matrix3dConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Matrix3dConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero");

        implicitly_convertible<MatrixXd, Matrix3d>();

        pythonMatrixXd()
            .def("__init__", make_constructor(&initMatrixFromList<MatrixXd>))
            .def("__init__", make_constructor(&MatrixXdConstructors::copy))
            .def("Constant", &MatrixXdConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("Identity", &MatrixXdConstructors::Identity, manage_new_matrix)
                .staticmethod("Identity")
            .def("Ones", &MatrixXdConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &MatrixXdConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &MatrixXdConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero");

        class_<Matrix2IConstructors>("Matrix2I", no_init)
            .def("__new__", &newMatrixFromList<Matrix2I>, manage_new_matrix)
            .def("__new__", &Matrix2IConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Matrix2IConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("Identity", &Matrix2IConstructors::Identity, manage_new_matrix)
                .staticmethod("Identity")
            .def("Ones", &Matrix2IConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Matrix2IConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Matrix2IConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero");

        implicitly_convertible<MatrixXI, Matrix2I>();

        class_<Matrix3IConstructors>("Matrix3I", no_init)
            .def("__new__", &newMatrixFromList<Matrix3I>, manage_new_matrix)
            .def("__new__", &Matrix3IConstructors::copy, manage_new_matrix)
                .staticmethod("__new__")
            .def("Constant", &Matrix3IConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("Identity", &Matrix3IConstructors::Identity, manage_new_matrix)
                .staticmethod("Identity")
            .def("Ones", &Matrix3IConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &Matrix3IConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &Matrix3IConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero");

        implicitly_convertible<MatrixXI, Matrix3I>();

        pythonMatrixXI()
            .def("__init__", make_constructor(&initMatrixFromList<MatrixXI>))
            .def("__init__", make_constructor(&MatrixXIConstructors::copy))
            .def("Constant", &MatrixXIConstructors::Constant, manage_new_matrix)
                .staticmethod("Constant")
            .def("Identity", &MatrixXIConstructors::Identity, manage_new_matrix)
                .staticmethod("Identity")
            .def("Ones", &MatrixXIConstructors::Ones, manage_new_matrix)
                .staticmethod("Ones")
            .def("Random", &MatrixXIConstructors::Random, manage_new_matrix)
                .staticmethod("Random")
            .def("Zero", &MatrixXIConstructors::Zero, manage_new_matrix)
                .staticmethod("Zero");
    }
}
