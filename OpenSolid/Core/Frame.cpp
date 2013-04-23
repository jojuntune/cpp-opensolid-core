/************************************************************************************
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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    Frame<2>::Frame() {
    }

    Frame<2>::Frame(const Point2d& originPoint) :
        Datum<2, 2>(originPoint) {
    }
    
    Frame<2>::Frame(
        const Point2d& originPoint,
        const Vector2d& xVector,
        const Vector2d& xyVector
    ) : Datum<2, 2>() {

        Matrix2d basisMatrix;
        basisMatrix << xVector, xyVector;
        *this = Datum<2, 2>(originPoint, basisMatrix).normalized();
    }

    Frame<2>
    Frame<2>::XY() {
        return Frame<2>();
    }

    Frame<2>
    Frame<2>::XY(const Point2d& originPoint) {
        return Frame<2>(originPoint);
    }

    Frame<2>
    Frame<2>::FromXAxis(const Axis2d& xAxis) {
        return Frame<2>::FromBasisVectors(
            xAxis.originPoint(),
            xAxis.basisVector().normalized(),
            xAxis.basisVector().unitOrthogonal()
        );
    }

    Frame<2>
    Frame<2>::FromYAxis(const Axis2d& yAxis) {
        return Frame<2>::FromBasisVectors(
            yAxis.originPoint(),
            -yAxis.basisVector().unitOrthogonal(),
            yAxis.basisVector().normalized()
        );
    }

    Frame<2>
    Frame<2>::FromBasisVectors(
        const Point2d& originPoint,
        const Vector2d& xBasisVector,
        const Vector2d& yBasisVector
    ) {
        Matrix2d basisMatrix;
        basisMatrix << xBasisVector, yBasisVector;
        return Datum<2, 2>(originPoint, basisMatrix);
    }
    
    Frame<2>
    Frame<2>::FromBasisMatrix(const Point2d& originPoint, const Matrix2d& basisMatrix) {
        return Datum<2, 2>(originPoint, basisMatrix);
    }

    Frame<3>::Frame() :
        Datum<3, 3>() {
    }

    Frame<3>::Frame(const Point3d& originPoint) :
        Datum<3, 3>(originPoint) {
    }
    
    Frame<3>::Frame(
        const Point3d& originPoint,
        const Vector3d& xVector,
        const Vector3d& xyVector,
        const Vector3d& xyzVector
    ) : Datum<3, 3>() {

        Matrix3d basisMatrix;
        basisMatrix << xVector, xyVector, xyzVector;
        *this = Datum<3, 3>(originPoint, basisMatrix).normalized();
    }

    Frame<3>
    Frame<3>::XYZ() {
        return Frame<3>();
    }

    Frame<3>
    Frame<3>::XYZ(const Point3d& originPoint) {
        return Frame<3>(originPoint);
    }

    Frame<3>
    Frame<3>::FromXYPlane(const Plane3d& xyPlane) {
        return Frame<3>(
            xyPlane.originPoint(),
            xyPlane.basisVector(0),
            xyPlane.basisVector(1),
            xyPlane.normalVector()
        );
    }

    Frame<3>
    Frame<3>::FromXZPlane(const Plane3d& xzPlane) {
        return Frame<3>(
            xzPlane.originPoint(),
            xzPlane.basisVector(0),
            -xzPlane.normalVector(),
            xzPlane.basisVector(1)
        );
    }

    Frame<3>
    Frame<3>::FromYXPlane(const Plane3d& yxPlane) {
        return Frame<3>(
            yxPlane.originPoint(),
            yxPlane.basisVector(1),
            yxPlane.basisVector(0),
            -yxPlane.normalVector()
        );
    }

    Frame<3>
    Frame<3>::FromYZPlane(const Plane3d& yzPlane) {
        return Frame<3>(
            yzPlane.originPoint(),
            yzPlane.normalVector(),
            yzPlane.basisVector(0),
            yzPlane.basisVector(1)
        );
    }

    Frame<3>
    Frame<3>::FromZXPlane(const Plane3d& zxPlane) {
        return Frame<3>(
            zxPlane.originPoint(),
            zxPlane.basisVector(1),
            zxPlane.normalVector(),
            zxPlane.basisVector(0)
        );
    }

    Frame<3>
    Frame<3>::FromZYPlane(const Plane3d& zyPlane) {
        return Frame<3>(
            zyPlane.originPoint(),
            -zyPlane.normalVector(),
            zyPlane.basisVector(1),
            zyPlane.basisVector(0)
        );
    }

    Frame<3>
    Frame<3>::FromBasisVectors(
        const Point3d& originPoint,
        const Vector3d& xBasisVector,
        const Vector3d& yBasisVector,
        const Vector3d& zBasisVector
    ) {
        Matrix3d basisMatrix;
        basisMatrix << xBasisVector, yBasisVector, zBasisVector;
        return Datum<3, 3>(originPoint, basisMatrix);
    }
    
    Frame<3>
    Frame<3>::FromBasisMatrix(const Point3d& originPoint, const Matrix3d& basisMatrix) {
        return Datum<3, 3>(originPoint, basisMatrix);
    }
}
