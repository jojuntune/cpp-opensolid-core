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

namespace opensolid
{
    void
    EigenDecomposition2d::compute(const Matrix2d& matrix) {
        assert((matrix - matrix.transpose()).isZero());

        if (matrix.isZero()) {
            _eigenvectors.setIdentity();
            _exists = true;
            return;
        }

        double m00 = matrix(0, 0);
        double m11 = matrix(1, 1);
        double m10 = 0.5 * (matrix(1, 0) + matrix(0, 1));

        double trace = m00 + m11;
        double discriminant = (m00 - m11) * (m00 - m11) + 4 * m10 * m10;
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
        
        double m00squared = m00 * m00;
        double m11squared = m11 * m11;
        double m10squared = m10 * m10;
        double x0 = 0.0;
        double y0 = 0.0;
        if (m00squared > m11squared) {
            double scale = -1.0 / sqrt(m00squared + m10squared);
            x0 = (m00 - secondEigenvalue) * scale;
            y0 = m10 * scale;
        } else {
            double scale = -1.0 / sqrt(m11squared + m10squared);
            x0 = m10 * scale;
            y0 = (m11 - secondEigenvalue) * scale;
        }
        _eigenvectors(0, 0) = x0;
        _eigenvectors(1, 0) = y0;
        _eigenvectors(0, 1) = -y0;
        _eigenvectors(1, 1) = x0;

        _exists = true;
    }

    namespace
    {
        ColumnMatrix3d
        solveCubic(double a, double b, double c, double d) {
            // Set up useful constants
            static const double oneThird = 1.0 / 3.0;
            static const double oneThirdPi = oneThird * M_PI;
            static const Interval arccosineDomain = Interval(-1, 1);

            double aSquared = a * a;
            double aCubed = a * aSquared;
            double bSquared = b * b;
            double bCubed = b * bSquared;
            double ac = a * c;
            double abc = ac * b;

            // Compute coefficients of depressed cubic
            // (http://en.wikipedia.org/wiki/Cubic_function#Reduction_to_a_depressed_cubic)
            double p = (3 * ac - bSquared) / (3 * aSquared);
            double q = (2 * bCubed - 9 * abc + 27 * aSquared * d) / (27 * aCubed);

            // Three real roots exist only if p < 0
            // (http://en.wikipedia.org/wiki/Cubic_function#Trigonometric_.28and_hyperbolic.29_method)
            if (p >= Zero()) {
                assert(false);
                return ColumnMatrix3d();
            }

            // Compute roots of depressed cubic via trigonometric method
            // (http://en.wikipedia.org/wiki/Cubic_function#Trigonometric_.28and_hyperbolic.29_method)
            double squareRootTerm = 2 * sqrt(-oneThird * p);
            double arccosineArgument = 3 * q * 1.0 / (p * squareRootTerm);
            if (arccosineDomain.contains(arccosineArgument)) {
                arccosineArgument = arccosineDomain.clamp(arccosineArgument);
            } else {
                assert(false);
                return ColumnMatrix3d();
            }
            double arccosineTerm = oneThird * acos(arccosineArgument);
            double t0 = squareRootTerm * cos(arccosineTerm);
            double t1 = squareRootTerm * cos(arccosineTerm - 2 * oneThirdPi);
            double t2 = squareRootTerm * cos(arccosineTerm - 4 * oneThirdPi);
            assert(t0 >= t1);
            assert(t1 >= t2);

            // Convert back to roots of original cubic
            // (http://en.wikipedia.org/wiki/Cubic_function#Reduction_to_a_depressed_cubic)
            double offset = b / (3 * a);
            double x0 = t0 - offset;
            double x1 = t1 - offset;
            double x2 = t2 - offset;

            // Set up function to polish roots using Newton iteration
            auto polish = [a, b, c, d] (double x) -> double {
                double xSquared = x * x;
                double xCubed = x * xSquared;
                double y = a * xCubed + b * xSquared + c * x + d;
                double derivative = 3 * a * xSquared + 2 * b * x + c;

                double newX = x - y / derivative;
                double newXSquared = newX * newX;
                double newXCubed = newX * newXSquared;
                double newY = a * newXCubed + b * newXSquared + c * newX + d;

                while (newY < y) {
                    x = newX;
                    y = newY;
                    double derivative = 3 * a * xSquared + 2 * b * x + c;

                    newX = x - y / derivative;
                    newXSquared = newX * newX;
                    newXCubed = newX * newXSquared;
                    newY = a * newXCubed + b * newXSquared + c * newX + d;
                }

                return x;
            };

            // Return polished results
            ColumnMatrix3d result;
            result(0) = polish(x0);
            result(1) = polish(x1);
            result(2) = polish(x2);
            return result;
        }
    }

    ColumnMatrix3d
    computeEigenvalues(const Matrix3d& matrix) {
        assert((matrix - matrix.transpose()).isZero());

        double m00 = matrix(0, 0);
        double m11 = matrix(1, 1);
        double m22 = matrix(2, 2);
        double m10 = 0.5 * (matrix(1, 0) + matrix(0, 1));
        double m20 = 0.5 * (matrix(2, 0) + matrix(0, 2));
        double m21 = 0.5 * (matrix(2, 1) + matrix(1, 2));

        // Compute coefficients of matrix characteristic equation
        double a = -1.0;
        double b = m00 + m11 + m22;
        double c = m10 * m10 + m20 * m20 + m21 * m21 - m00 * m11 - m00 * m22 - m11 * m22;
        double d = m00 * m11 * m22 + 2.0 * m10 * m20 * m21 -
            (m00 * m21 * m21 + m11 * m20 * m20 + m22 * m10 * m10);

        // Find eigenvalues by solving characteristic equation
        return solveCubic(a, b, c, d);
    }

    void
    EigenDecomposition3d::compute(Matrix3d matrix) {
        assert((matrix - matrix.transpose()).isZero());

        if (matrix.isZero()) {
            _eigenvectors.setIdentity();
            _exists = true;
            return;
        }

        ColumnMatrix3d eigenvaluesFromCubic = computeEigenvalues(matrix);

        // Adjust input matrix so it is perfectly symmetric
        double m10 = 0.5 * (matrix(1, 0) + matrix(0, 1));
        double m20 = 0.5 * (matrix(2, 0) + matrix(0, 2));
        double m21 = 0.5 * (matrix(2, 1) + matrix(1, 2));
        matrix(1, 0) = m10;
        matrix(0, 1) = m10;
        matrix(2, 0) = m20;
        matrix(0, 2) = m20;
        matrix(2, 1) = m21;
        matrix(1, 2) = m21;

        Quaternion3d quaternion = Quaternion3d::Identity();
        Matrix3d diagonalMatrix;
        double lastAbsError = DBL_MAX;
        while (true) {
            _eigenvectors = quaternion.rotationMatrix();
            diagonalMatrix = _eigenvectors.transpose() * matrix * _eigenvectors;

            double d0 = 0.5 * (diagonalMatrix(2, 1) + diagonalMatrix(1, 2));
            double d1 = 0.5 * (diagonalMatrix(2, 0) + diagonalMatrix(0, 2));
            double d2 = 0.5 * (diagonalMatrix(1, 0) + diagonalMatrix(0, 1));
            double absD0 = abs(d0);
            double absD1 = abs(d1);
            double absD2 = abs(d2);
            int k = 0;
            int k1 = 0;
            int k2 = 0;
            double error = 0.0;
            double absError = 0.0;
            if (absD0 >= absD1 && absD0 >= absD2) {
                error = d0;
                absError = absD0;
                k = 0;
                k1 = 1;
                k2 = 2;
            } else if (absD1 >= absD2) {
                error = d1;
                absError = absD1;
                k = 1;
                k1 = 2;
                k2 = 0;
            } else {
                error = d2;
                absError = absD2;
                k = 2;
                k1 = 0;
                k2 = 1;
            }
            if (absError == 0.0 || (absError >= lastAbsError && lastAbsError == Zero())) {
                break;
            } else {
                lastAbsError = absError;
            }
            double theta = (diagonalMatrix(k2, k2) - diagonalMatrix(k1, k1)) / (2.0 * error);
            double sign = theta >= 0 ? 1 : -1;
            theta *= sign;
            double t = sign / (theta > 1e20 ? 2 * theta : theta + sqrt(theta * theta + 1.0));
            double c = 1.0 / sqrt(t * t + 1);
            if (c == 1.0) {
                break;
            }
            Matrix<double, 4, 1> rotationComponents;
            double axisComponent = sign * sqrt((1.0 - c) / 2.0);
            double w = sqrt(1.0 - axisComponent * axisComponent);
            if (w == 1.0) {
                break;
            }
            rotationComponents(k) = -axisComponent;
            rotationComponents(3) = w;
            quaternion = Quaternion3d(rotationComponents) * quaternion;
        }

        _eigenvalues(0) = diagonalMatrix(0, 0);
        _eigenvalues(1) = diagonalMatrix(1, 1);
        _eigenvalues(2) = diagonalMatrix(2, 2);

        // Attempt at 'polishing' eigenvectors - didn't seem to work, but might
        // be able to be adjusted 
        //
        // for (int n = 0; n < 3; ++n) {
        //     Matrix3d adjustedEigenvectors = _eigenvectors;
        //     for (int i = 0; i < 3; ++i) {
        //         int j = (i + 1) % 3;
        //         int k = (i + 2) % 3;
        //         ColumnMatrix3d v = matrix * _eigenvectors.column(i);
        //         ColumnMatrix3d ej = _eigenvectors.column(j);
        //         ColumnMatrix3d ek = _eigenvectors.column(k);
        //         double xj = v.cwiseProduct(ej).sum() / _eigenvalues(j);
        //         double xk = v.cwiseProduct(ek).sum() / _eigenvalues(k);
        //         adjustedEigenvectors.column(i) -= xj * ej;
        //         adjustedEigenvectors.column(i) -= xk * ek;
        //     }
        //     _eigenvectors = adjustedEigenvectors;
        // }

        _exists = true;
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
