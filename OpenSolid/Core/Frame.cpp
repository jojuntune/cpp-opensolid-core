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

#include <OpenSolid/Core/Frame.hpp>

namespace opensolid
{
    Frame2d::Frame2d() : Datum<2, 2>(Vector2d::Zero(), Matrix2d::Identity()) {
    }

    Frame2d::Frame2d(const Vector2d& originPoint) : Datum<2, 2>(originPoint, Matrix2d::Identity()) {
    }
    
    Frame2d::Frame2d(
        const Vector2d& originPoint,
        const Vector2d& xBasisVector,
        const Vector2d& yBasisVector
    ) : Datum<2, 2>() {
        Matrix2d basisMatrix;
        basisMatrix << xBasisVector, yBasisVector;
        initialize(originPoint, basisMatrix);
    }

    Frame2d Frame2d::Unit() {
        return Frame2d(Vector2d::Zero(), Vector2d::UnitX(), Vector2d::UnitY());
    }

    Frame2d Frame2d::Unit(const Vector2d& originPoint) {
        return Frame2d(originPoint, Vector2d::UnitX(), Vector2d::UnitY());
    }

    Frame2d Frame2d::FromXAxis(const Axis2d& xAxis) {
        return Frame2d(
            xAxis.originPoint(),
            xAxis.basisVector().normalized(),
            xAxis.basisVector().unitOrthogonal()
        );
    }

    Frame2d Frame2d::FromYAxis(const Axis2d& yAxis) {
        return Frame2d(
            yAxis.originPoint(),
            -yAxis.basisVector().unitOrthogonal(),
            yAxis.basisVector().normalized()
        );
    }


    Frame3d::Frame3d() : Datum<3, 3>(Vector3d::Zero(), Matrix3d::Identity()) {
    }

    Frame3d::Frame3d(const Vector3d& originPoint) : Datum<3, 3>(originPoint, Matrix3d::Identity()) {
    }
    
    Frame3d::Frame3d(
        const Vector3d& originPoint,
        const Vector3d& xBasisVector,
        const Vector3d& yBasisVector,
        const Vector3d& zBasisVector
    ) : Datum<3, 3>() {
        Matrix3d basisMatrix;
        basisMatrix << xBasisVector, yBasisVector, zBasisVector;
        initialize(originPoint, basisMatrix);
    }

    Frame3d Frame3d::Unit() {
        return Frame3d(Vector3d::Zero(), Vector3d::UnitX(), Vector3d::UnitY(), Vector3d::UnitZ());
    }

    Frame3d Frame3d::Unit(const Vector3d& originPoint) {
        return Frame3d(originPoint, Vector3d::UnitX(), Vector3d::UnitY(), Vector3d::UnitZ());
    }

    Frame3d Frame3d::FromXYPlane(const Plane3d& xyPlane) {
        return Frame3d(
            xyPlane.originPoint(),
            xyPlane.basisVector(0),
            xyPlane.basisVector(1),
            xyPlane.normalVector()
        ).normalized();
    }

    Frame3d Frame3d::FromXZPlane(const Plane3d& xzPlane) {
        return Frame3d(
            xzPlane.originPoint(),
            xzPlane.basisVector(0),
            -xzPlane.normalVector(),
            xzPlane.basisVector(1)
        ).normalized();
    }

    Frame3d Frame3d::FromYXPlane(const Plane3d& yxPlane) {
        return Frame3d(
            yxPlane.originPoint(),
            yxPlane.basisVector(1),
            yxPlane.basisVector(0),
            -yxPlane.normalVector()
        ).normalized();
    }

    Frame3d Frame3d::FromYZPlane(const Plane3d& yzPlane) {
        return Frame3d(
            yzPlane.originPoint(),
            yzPlane.normalVector(),
            yzPlane.basisVector(0),
            yzPlane.basisVector(1)
        ).normalized();
    }

    Frame3d Frame3d::FromZXPlane(const Plane3d& zxPlane) {
        return Frame3d(
            zxPlane.originPoint(),
            zxPlane.basisVector(1),
            zxPlane.normalVector(),
            zxPlane.basisVector(0)
        ).normalized();
    }

    Frame3d Frame3d::FromZYPlane(const Plane3d& zyPlane) {
        return Frame3d(
            zyPlane.originPoint(),
            -zyPlane.normalVector(),
            zyPlane.basisVector(1),
            zyPlane.basisVector(0)
        ).normalized();
    }
}
