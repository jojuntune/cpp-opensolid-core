/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
 *************************************************************************************/

#include <OpenSolid/Core/Frame.hpp>

namespace opensolid
{
    Frame2d::Frame2d() {
    }

    Frame2d::Frame2d(const Vector2d& originPoint) : Datum<2, 2>(originPoint) {
    }
    
    Frame2d::Frame2d(
        const Vector2d& originPoint,
        const Vector2d& xVector,
        const Vector2d& xyVector
    ) : Datum<2, 2>() {

        Matrix2d basisMatrix;
        basisMatrix << xVector, xyVector;
        *this = Datum<2, 2>(originPoint, basisMatrix).normalized();
    }

    Frame2d Frame2d::XY() {
        return Frame2d();
    }

    Frame2d Frame2d::XY(const Vector2d& originPoint) {
        return Frame2d(originPoint);
    }

    Frame2d Frame2d::FromXAxis(const Axis2d& xAxis) {
        return Frame2d::FromBasisVectors(
            xAxis.originPoint(),
            xAxis.basisVector().normalized(),
            xAxis.basisVector().unitOrthogonal()
        );
    }

    Frame2d Frame2d::FromYAxis(const Axis2d& yAxis) {
        return Frame2d::FromBasisVectors(
            yAxis.originPoint(),
            -yAxis.basisVector().unitOrthogonal(),
            yAxis.basisVector().normalized()
        );
    }

    Frame2d Frame2d::FromBasisVectors(
        const Vector2d& originPoint,
        const Vector2d& xBasisVector,
        const Vector2d& yBasisVector
    ) {
        Matrix2d basisMatrix;
        basisMatrix << xBasisVector, yBasisVector;
        return Datum<2, 2>(originPoint, basisMatrix);
    }
    
    Frame2d Frame2d::FromBasisMatrix(
        const Vector2d& originPoint,
        const Matrix2d& basisMatrix
    ) {
        return  Datum<2, 2>(originPoint, basisMatrix);
    }

    Frame3d::Frame3d() : Datum<3, 3>() {
    }

    Frame3d::Frame3d(const Vector3d& originPoint) : Datum<3, 3>(originPoint) {
    }
    
    Frame3d::Frame3d(
        const Vector3d& originPoint,
        const Vector3d& xVector,
        const Vector3d& xyVector,
        const Vector3d& xyzVector
    ) : Datum<3, 3>() {
        Matrix3d basisMatrix;
        basisMatrix << xVector, xyVector, xyzVector;
        *this = Datum<3, 3>(originPoint, basisMatrix).normalized();
    }

    Frame3d Frame3d::XYZ() {
        return Frame3d();
    }

    Frame3d Frame3d::XYZ(const Vector3d& originPoint) {
        return Frame3d(originPoint);
    }

    Frame3d Frame3d::FromXYPlane(const Plane3d& xyPlane) {
        return Frame3d(
            xyPlane.originPoint(),
            xyPlane.basisVector(0),
            xyPlane.basisVector(1),
            xyPlane.normalVector()
        );
    }

    Frame3d Frame3d::FromXZPlane(const Plane3d& xzPlane) {
        return Frame3d(
            xzPlane.originPoint(),
            xzPlane.basisVector(0),
            -xzPlane.normalVector(),
            xzPlane.basisVector(1)
        );
    }

    Frame3d Frame3d::FromYXPlane(const Plane3d& yxPlane) {
        return Frame3d(
            yxPlane.originPoint(),
            yxPlane.basisVector(1),
            yxPlane.basisVector(0),
            -yxPlane.normalVector()
        );
    }

    Frame3d Frame3d::FromYZPlane(const Plane3d& yzPlane) {
        return Frame3d(
            yzPlane.originPoint(),
            yzPlane.normalVector(),
            yzPlane.basisVector(0),
            yzPlane.basisVector(1)
        );
    }

    Frame3d Frame3d::FromZXPlane(const Plane3d& zxPlane) {
        return Frame3d(
            zxPlane.originPoint(),
            zxPlane.basisVector(1),
            zxPlane.normalVector(),
            zxPlane.basisVector(0)
        );
    }

    Frame3d Frame3d::FromZYPlane(const Plane3d& zyPlane) {
        return Frame3d(
            zyPlane.originPoint(),
            -zyPlane.normalVector(),
            zyPlane.basisVector(1),
            zyPlane.basisVector(0)
        );
    }

    Frame3d Frame3d::FromBasisVectors(
        const Vector3d& originPoint,
        const Vector3d& xBasisVector,
        const Vector3d& yBasisVector,
        const Vector3d& zBasisVector
    ) {
        Matrix3d basisMatrix;
        basisMatrix << xBasisVector, yBasisVector, zBasisVector;
        return Datum<3, 3>(originPoint, basisMatrix);
    }
    
    Frame3d Frame3d::FromBasisMatrix(
        const Vector3d& originPoint,
        const Matrix3d& basisMatrix
    ) {
        return  Datum<3, 3>(originPoint, basisMatrix);
    }
}
