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

namespace opensolid
{
    void
    EigenDecomposition2d::compute(const Matrix2d& matrix) {
        assert((matrix - matrix.transpose()).isZero());

        double a00 = matrix(0, 0);
        double a10 = matrix(1, 0);
        double a01 = matrix(0, 1);
        double a11 = matrix(1, 1);
        double trace = a00 + a11;
        double discriminant = (a00 - a11) * (a00 - a11) + 4 * a10 * a01;
        double firstEigenvalue = 0.0;
        double secondEigenvalue = 0.0;

        // Compute eigenvalues

        if (discriminant > Zero()) {
            double sqrtDiscriminant = sqrt(discriminant);
            firstEigenvalue = 0.5 * (trace - sqrtDiscriminant);
            secondEigenvalue = 0.5 * (trace + sqrtDiscriminant);
        } else if (discriminant < Zero()) {
            assert(false);
            return;
        } else {
            firstEigenvalue = 0.5 * trace;
            secondEigenvalue = firstEigenvalue;
        }
        _eigenvalues(0) = firstEigenvalue;
        _eigenvalues(1) = secondEigenvalue;

        // Compute eigenvectors
        
        double a00squared = a00 * a00;
        double a11squared = a11 * a11;
        double a10a01 = a10 * a01;
        double x0 = 0.0;
        double y0 = 0.0;
        if (a00squared > a11squared) {
            double scale = -1.0 / sqrt(a00squared + a10a01);
            x0 = (a00 - secondEigenvalue) * scale;
            y0 = a10 * scale;
        } else {
            double scale = -1.0 / sqrt(a11squared + a10a01);
            x0 = a10 * scale;
            y0 = (a11 - secondEigenvalue) * scale;
        }
        _eigenvectors(0, 0) = x0;
        _eigenvectors(1, 0) = y0;
        _eigenvectors(0, 1) = -y0;
        _eigenvectors(1, 1) = x0;

        _exists = true;
    }

    void
    EigenDecomposition3d::compute(const Matrix3d& matrix) {
        assert((matrix - matrix.transpose()).isZero());
        // TODO
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
