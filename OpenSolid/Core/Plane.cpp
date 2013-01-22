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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    Plane3d::Plane3d() : Datum<3, 2>() {
    }

    Plane3d::Plane3d(const Vector3d& originPoint, const Matrix<double, 3, 2>& basisMatrix) :
        Datum<3, 2>(originPoint, basisMatrix) {
    }

    namespace detail
    {
        Matrix<double, 3, 2> planeBasisFromNormal(const Vector3d& normalVector) {
            Matrix<double, 3, 2> basisMatrix;
            basisMatrix.col(0) = normalVector.unitOrthogonal();
            basisMatrix.col(1) = normalVector.cross(basisMatrix.col(0)).normalized();
            return basisMatrix;
        }
    }

    Plane3d Plane3d::FromPointAndNormal(const Vector3d& originPoint, const Vector3d& normalVector) {
        return Plane3d(originPoint, detail::planeBasisFromNormal(normalVector));
    }

    Plane3d Plane3d::ThroughPoints(
        const Vector3d& originPoint,
        const Vector3d& xAxisPoint,
        const Vector3d& planePoint
    ) {
        Matrix<double, 3, 2> basisMatrix;
        basisMatrix.col(0) = xAxisPoint - originPoint;
        basisMatrix.col(1) = planePoint - originPoint;

        return Plane3d(originPoint, basisMatrix);
    }

    Plane3d Plane3d::Midplane(const Vector3d& pointBelow, const Vector3d& pointAbove) {
        return Plane3d(
            pointBelow + 0.5 * (pointAbove - pointBelow),
            detail::planeBasisFromNormal(pointAbove - pointBelow)
        );
    }

    Plane3d Plane3d::Midplane(const Plane3d planeBelow, const Plane3d planeAbove) {
        Vector3d originPoint = planeBelow.originPoint() +
            0.5 * (planeAbove.originPoint() - planeBelow.originPoint());

        Matrix<double, 3, 2> basisMatrix = planeBelow.basisMatrix();
        Matrix3d checkMatrix;
        checkMatrix << basisMatrix, planeAbove.originPoint() - planeBelow.originPoint();
        if (checkMatrix.determinant() < Zero()) {
            basisMatrix.col(0) = -basisMatrix.col(0);
        }

        return Plane3d(originPoint, basisMatrix);
    }

    Plane3d Plane3d::ThroughAxisAndPoint(const Axis3d& axis, const Vector3d& point) {
        Matrix<double, 3, 2> basisMatrix;
        basisMatrix.col(0) = axis.basisVector();
        basisMatrix.col(1) = point - axis.originPoint();

        return Plane3d(axis.originPoint(), basisMatrix);
    }

    Plane3d Plane3d::ThroughAxis(const Axis3d& axis) {
        Matrix<double, 3, 2> basisMatrix;
        basisMatrix.col(0) = axis.basisVector();
        basisMatrix.col(1) = axis.normalVector();

        return Plane3d(axis.originPoint(), basisMatrix);
    }
}
