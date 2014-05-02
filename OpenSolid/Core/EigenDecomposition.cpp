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

#include <OpenSolid/Core/EigenDecomposition.hpp>

#include <OpenSolid/Core/Quaternion.hpp>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

#include <limits>

namespace opensolid
{
    void
    EigenDecomposition2d::compute(const Matrix2d& matrix) {
        assert((matrix - matrix.transpose()).isZero());
        Eigen::Matrix2d eigenMatrix = Eigen::Matrix2d::Map(matrix.data());
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> eigenSolver(eigenMatrix);
        if (eigenSolver.info() == Eigen::Success) {
            Eigen::Matrix2d eigenvectors = eigenSolver.eigenvectors();
            Eigen::Vector2d eigenvalues = eigenSolver.eigenvalues();
            _eigenvectors = MatrixView<const double, 2, 2, 2>(eigenvectors.data());
            _eigenvalues = MatrixView<const double, 2, 1, 2>(eigenvalues.data());
            _exists = true;
        }
    }

    void
    EigenDecomposition3d::compute(const Matrix3d& matrix) {
        assert((matrix - matrix.transpose()).isZero());
        Eigen::Matrix3d eigenMatrix = Eigen::Matrix3d::Map(matrix.data());
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigenSolver(eigenMatrix);
        if (eigenSolver.info() == Eigen::Success) {
            Eigen::Matrix3d eigenvectors = eigenSolver.eigenvectors();
            Eigen::Vector3d eigenvalues = eigenSolver.eigenvalues();
            _eigenvectors = MatrixView<const double, 3, 3, 3>(eigenvectors.data());
            _eigenvalues = MatrixView<const double, 3, 1, 3>(eigenvalues.data());
            _exists = true;
        }
    }

    void
    EigenDecompositionXd::compute(const MatrixXd& matrix) {
        if (matrix.numRows() == 1 && matrix.numColumns() == 1) {
            EigenDecomposition1d decomposition(matrix);
            if (decomposition.exists()) {
                _eigenvalues = decomposition.eigenvalues();
                _eigenvectors = decomposition.eigenvectors();
                _exists = true;
            }
        } else if (matrix.numRows() == 2 && matrix.numColumns() == 2) {
            EigenDecomposition2d decomposition(matrix);
            if (decomposition.exists()) {
                _eigenvalues = decomposition.eigenvalues();
                _eigenvectors = decomposition.eigenvectors();
                _exists = true;
            }
        } else if (matrix.numRows() == 3 && matrix.numColumns() == 3) {
            EigenDecomposition3d decomposition(matrix);
            if (decomposition.exists()) {
                _eigenvalues = decomposition.eigenvalues();
                _eigenvectors = decomposition.eigenvectors();
                _exists = true;
            }
        }
    }

}
