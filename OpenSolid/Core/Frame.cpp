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
    
    Frame2d::Frame2d(const Vector2d& originPoint, const Matrix2d& basisMatrix) :
        Datum<2, 2>(originPoint, basisMatrix) {
    }

    Frame2d Frame2d::Unit() {
        return Frame2d(Vector2d::Zero(), Matrix2d::Identity());
    }

    Frame2d Frame2d::Unit(const Vector2d& originPoint) {
        return Frame2d(originPoint, Matrix2d::Identity());
    }

    Frame2d Frame2d::FromXAxis(const Axis2d& xAxis) {
        Matrix2d basisMatrix;
        basisMatrix << xAxis.basisVector(), xAxis.basisVector().unitOrthogonal();
        return Frame2d(xAxis.originPoint(), basisMatrix);
    }

    Frame2d Frame2d::FromYAxis(const Axis2d& yAxis) {
        Matrix2d basisMatrix;
        basisMatrix << -yAxis.basisVector().unitOrthogonal(), yAxis.basisVector();
        return Frame2d(yAxis.originPoint(), basisMatrix);
    }


    Frame3d::Frame3d() : Datum<3, 3>(Vector3d::Zero(), Matrix3d::Identity()) {
    }

    Frame3d::Frame3d(const Vector3d& originPoint) : Datum<3, 3>(originPoint, Matrix3d::Identity()) {
    }
    
    Frame3d::Frame3d(const Vector3d& originPoint, const Matrix3d& basisMatrix) :
        Datum<3, 3>(originPoint, basisMatrix) {
    }

    Frame3d Frame3d::Unit() {
        return Frame3d(Vector3d::Zero(), Matrix3d::Identity());
    }

    Frame3d Frame3d::Unit(const Vector3d& originPoint) {
        return Frame3d(originPoint, Matrix3d::Identity());
    }

    Frame3d Frame3d::FromXYPlane(const Plane3d& xyPlane) {
        Matrix3d basisMatrix;
        basisMatrix << xyPlane.basisVector(0), xyPlane.basisVector(1), xyPlane.normalVector();
        return Frame3d(xyPlane.originPoint(), basisMatrix);
    }

    Frame3d Frame3d::FromXZPlane(const Plane3d& xzPlane) {
        Matrix3d basisMatrix;
        basisMatrix << xzPlane.basisVector(0), -xzPlane.normalVector(), xzPlane.basisVector(1);
        return Frame3d(xzPlane.originPoint(), basisMatrix);
    }

    Frame3d Frame3d::FromYXPlane(const Plane3d& yxPlane) {
        Matrix3d basisMatrix;
        basisMatrix << yxPlane.basisVector(1), yxPlane.basisVector(0), -yxPlane.normalVector();
        return Frame3d(yxPlane.originPoint(), basisMatrix);
    }

    Frame3d Frame3d::FromYZPlane(const Plane3d& yzPlane) {
        Matrix3d basisMatrix;
        basisMatrix << yzPlane.normalVector(), yzPlane.basisVector(0), yzPlane.basisVector(1);
        return Frame3d(yzPlane.originPoint(), basisMatrix);
    }

    Frame3d Frame3d::FromZXPlane(const Plane3d& zxPlane) {
        Matrix3d basisMatrix;
        basisMatrix << zxPlane.basisVector(1), zxPlane.normalVector(), zxPlane.basisVector(0);
        return Frame3d(zxPlane.originPoint(), basisMatrix);
    }

    Frame3d Frame3d::FromZYPlane(const Plane3d& zyPlane) {
        Matrix3d basisMatrix;
        basisMatrix << -zyPlane.normalVector(), zyPlane.basisVector(1), zyPlane.basisVector(0);
        return Frame3d(zyPlane.originPoint(), basisMatrix);
    }
}
