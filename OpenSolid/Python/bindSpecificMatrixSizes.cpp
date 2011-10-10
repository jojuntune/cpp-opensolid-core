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

#include <OpenSolid/Python/BoostPython.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Python/check.hpp>

using namespace boost::python;

namespace OpenSolid
{
    template <class MatrixType, class DynamicType>
    object newFixedSizeMatrix(tuple arguments, dict keyword_arguments) {
        checkSameSize(len(arguments) - 1, MatrixType::SizeAtCompileTime, __func__);
        int rows = MatrixType::RowsAtCompileTime;
        int cols = MatrixType::ColsAtCompileTime;
        DynamicType result(rows, cols);
        for (int i = 0; i < MatrixType::SizeAtCompileTime; ++i) {
            int row = i / MatrixType::ColsAtCompileTime;
            int col = i % MatrixType::ColsAtCompileTime;
            checkCompatiblePythonType<typename MatrixType::Scalar>(arguments[i + 1], __func__);
            result(row, col) = extract<typename MatrixType::Scalar>(arguments[i + 1]);
        }
        return object(result);
    }
    
    template <class MatrixType, class DynamicType>
    DynamicType* constantFixedSizeMatrix(typename MatrixType::Scalar value) {
        return new DynamicType(MatrixType::Constant(value));
    }
    
    template <class MatrixType, class DynamicType>
    DynamicType* onesFixedSizeMatrix() {return new DynamicType(MatrixType::Ones());}
    
    template <class MatrixType, class DynamicType>
    DynamicType* randomFixedSizeMatrix() {return new DynamicType(MatrixType::Random());}
    
    template <class MatrixType, class DynamicType>
    DynamicType* zeroFixedSizeMatrix() {return new DynamicType(MatrixType::Zero());}
    
    template <class MatrixType, class DynamicType>
    DynamicType* identityFixedSizeMatrix() {return new DynamicType(MatrixType::Identity());}
    
    template <class MatrixType>
    class FixedSizeMatrix {};
    
    template <class MatrixType, class DynamicType>
    void bindFixedSizeMatrix(const char* name) {
        class_<FixedSizeMatrix<MatrixType>>(name, no_init)
            .def(
                "__new__",
                raw_function(&newFixedSizeMatrix<MatrixType, DynamicType>)
            )
            .staticmethod("__new__")
            .def(
                "Constant",
                &constantFixedSizeMatrix<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Constant")
            .def(
                "Ones",
                &onesFixedSizeMatrix<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Ones")
            .def(
                "Random",
                &randomFixedSizeMatrix<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Random")
            .def(
                "Zero",
                &zeroFixedSizeMatrix<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Zero")
            .def(
                "Identity",
                &identityFixedSizeMatrix<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Identity");
    }
    
    template <class MatrixType, class DynamicType>
    object newVector(tuple arguments, dict keyword_arguments) {
        int size = len(arguments) - 1;
        int rows = 1;
        int cols = 1;
        if (MatrixType::RowsAtCompileTime == Dynamic) {
            rows = size;
        } else {
            cols = size;
        }
        DynamicType result(rows, cols);
        for (int i = 0; i < size; ++i) {
            checkCompatiblePythonType<typename MatrixType::Scalar>(arguments[i + 1], __func__);
            if (MatrixType::RowsAtCompileTime == Dynamic) {
                result(i, 0) = extract<typename MatrixType::Scalar>(arguments[i + 1]);
            } else {
                result(0, i) = extract<typename MatrixType::Scalar>(arguments[i + 1]);
            }
        }
        return object(result);
    }

    template <class MatrixType, class DynamicType>
    DynamicType* constantVector(int size, typename MatrixType::Scalar value) {
        return new DynamicType(MatrixType::Constant(size, value));
    }

    template <class MatrixType, class DynamicType>
    DynamicType* linSpacedVector(int size, const Interval& range) {
        return new DynamicType(MatrixType::LinSpaced(size, range));
    }

    template <class MatrixType, class DynamicType>
    DynamicType* onesVector(int size) {return new DynamicType(MatrixType::Ones(size));}

    template <class MatrixType, class DynamicType>
    DynamicType* randomVector(int size) {return new DynamicType(MatrixType::Random(size));}

    template <class MatrixType, class DynamicType>
    DynamicType* zeroVector(int size) {return new DynamicType(MatrixType::Zero(size));}

    template <class MatrixType, class DynamicType>
    DynamicType* unitVector(int size, int index) {
        return new DynamicType(MatrixType::Unit(size, index));
    }
    
    template <class MatrixType>
    class Vector {};
    
    template <class MatrixType, class DynamicType>
    void bindVector(const char* name) {
        class_<Vector<MatrixType>>(name, no_init)
            .def(
                "__new__",
                raw_function(&newVector<MatrixType, DynamicType>)
            )
            .staticmethod("__new__")
            .def(
                "Constant",
                &constantVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Constant")
            .def(
                "LinSpaced",
                &linSpacedVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("LinSpaced")
            .def(
                "Ones",
                &onesVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Ones")
            .def(
                "Random",
                &randomVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Random")
            .def(
                "Zero",
                &zeroVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Zero")
            .def(
                "Unit",
                &unitVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Unit");
    }
    
    template <class MatrixType, class DynamicType>
    object newFixedSizeVector(tuple arguments, dict keyword_arguments) {
        checkSameSize(len(arguments) - 1, MatrixType::SizeAtCompileTime, __func__);
        int rows = MatrixType::RowsAtCompileTime;
        int cols = MatrixType::ColsAtCompileTime;
        DynamicType result(rows, cols);
        for (int i = 0; i < MatrixType::SizeAtCompileTime; ++i) {
            checkCompatiblePythonType<typename MatrixType::Scalar>(arguments[i + 1], __func__);
            if (MatrixType::ColsAtCompileTime == 1) {
                result(i, 0) = extract<typename MatrixType::Scalar>(arguments[i + 1]);
            } else {
                result(0, i) = extract<typename MatrixType::Scalar>(arguments[i + 1]);
            }
        }
        return object(result);
    }

    template <class MatrixType, class DynamicType>
    DynamicType* constantFixedSizeVector(typename MatrixType::Scalar value) {
        return new DynamicType(MatrixType::Constant(value));
    }

    template <class MatrixType, class DynamicType>
    DynamicType* linSpacedFixedSizeVector(const Interval& range) {
        return new DynamicType(MatrixType::LinSpaced(range));
    }

    template <class MatrixType, class DynamicType>
    DynamicType* onesFixedSizeVector() {return new DynamicType(MatrixType::Ones());}

    template <class MatrixType, class DynamicType>
    DynamicType* randomFixedSizeVector() {return new DynamicType(MatrixType::Random());}

    template <class MatrixType, class DynamicType>
    DynamicType* zeroFixedSizeVector() {return new DynamicType(MatrixType::Zero());}

    template <class MatrixType, class DynamicType>
    DynamicType* unitFixedSizeVector(int index) {return new DynamicType(MatrixType::Unit(index));}

    template <class MatrixType, class DynamicType>
    DynamicType* unitXFixedSizeVector() {return new DynamicType(MatrixType::UnitX());}

    template <class MatrixType, class DynamicType>
    DynamicType* unitYFixedSizeVector() {return new DynamicType(MatrixType::UnitY());}

    template <class MatrixType, class DynamicType>
    DynamicType* unitZFixedSizeVector() {return new DynamicType(MatrixType::UnitZ());}

    template <class MatrixType, class DynamicType>
    DynamicType* unitWFixedSizeVector() {return new DynamicType(MatrixType::UnitW());}
    
    template <class MatrixType>
    class FixedSizeVector {};
    
    template <class MatrixType, class DynamicType>
    void bindFixedSizeVector(const char* name) {
        class_<FixedSizeVector<MatrixType>> fixed_size_vector(name, no_init);
        fixed_size_vector
            .def(
                "__new__",
                raw_function(&newFixedSizeVector<MatrixType, DynamicType>)
            )
            .staticmethod("__new__")
            .def(
                "Constant",
                &constantFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Constant")
            .def(
                "LinSpaced",
                &linSpacedFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("LinSpaced")
            .def(
                "Ones",
                &onesFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Ones")
            .def(
                "Random",
                &randomFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Random")
            .def(
                "Zero",
                &zeroFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Zero")
            .def(
                "Unit",
                &unitFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("Unit")
            .def(
                "UnitX",
                &unitXFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("UnitX")
            .def(
                "UnitY",
                &unitYFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            )
            .staticmethod("UnitY");
        if (MatrixType::SizeAtCompileTime == 3) {
            fixed_size_vector.def(
                "UnitZ",
                &unitZFixedSizeVector<MatrixType, DynamicType>,
                return_value_policy<manage_new_object>()
            );
            fixed_size_vector.staticmethod("UnitZ");
        }
    }

    void bindSpecificMatrixSizes() {
        bindFixedSizeMatrix<Matrix2d, MatrixXd>("Matrix2d");
        bindFixedSizeMatrix<Matrix3d, MatrixXd>("Matrix3d");
        bindFixedSizeMatrix<Matrix2I, MatrixXI>("Matrix2I");
        bindFixedSizeMatrix<Matrix3I, MatrixXI>("Matrix3I");
        
        bindVector<VectorXd, MatrixXd>("VectorXd");
        bindVector<VectorXI, MatrixXI>("VectorXI");
        bindVector<RowVectorXd, MatrixXd>("RowVectorXd");
        bindVector<RowVectorXI, MatrixXI>("RowVectorXI");
        
        bindFixedSizeVector<Vector2d, MatrixXd>("Vector2d");
        bindFixedSizeVector<Vector3d, MatrixXd>("Vector3d");
        bindFixedSizeVector<Vector2I, MatrixXI>("Vector2I");
        bindFixedSizeVector<Vector3I, MatrixXI>("Vector3I");
        bindFixedSizeVector<RowVector2d, MatrixXd>("RowVector2d");
        bindFixedSizeVector<RowVector3d, MatrixXd>("RowVector3d");
        bindFixedSizeVector<RowVector2I, MatrixXI>("RowVector2I");
        bindFixedSizeVector<RowVector3I, MatrixXI>("RowVector3I");
    }
}
