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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    Plane3d::Plane3d() : Datum<3, 2>() {
    }

    Plane3d::Plane3d(
        const Vector3d& originPoint,
        const Vector3d& xVector,
        const Vector3d& xyVector
    ) : Datum<3, 2>() {
        Matrix<double, 3, 2> basisMatrix;
        basisMatrix << xVector, xyVector;
        *this = Datum<3, 2>(originPoint, basisMatrix).normalized();
    }

    Plane3d Plane3d::FromPointAndNormal(const Vector3d& originPoint, const Vector3d& normalVector) {
        Vector3d xBasisVector = normalVector.unitOrthogonal();
        Vector3d yBasisVector = normalVector.cross(xBasisVector).normalized();
        return Plane3d::FromBasisVectors(originPoint, xBasisVector, yBasisVector);
    }

    Plane3d Plane3d::ThroughPoints(
        const Vector3d& originPoint,
        const Vector3d& xPoint,
        const Vector3d& xyPoint
    ) {
        return Plane3d(originPoint, xPoint - originPoint, xyPoint - originPoint);
    }

    Plane3d Plane3d::Midplane(const Vector3d& pointBelow, const Vector3d& pointAbove) {
        Vector3d displacementVector = pointAbove - pointBelow;
        return Plane3d::FromPointAndNormal(
            pointBelow + 0.5 * displacementVector,
            displacementVector
        );
    }

    Plane3d Plane3d::Midplane(const Plane3d planeBelow, const Plane3d planeAbove) {
        Vector3d displacementVector = planeAbove.originPoint() - planeBelow.originPoint();

        Vector3d originPoint = planeBelow.originPoint() + 0.5 * displacementVector;

        Vector3d belowNormalVector = planeBelow.normalVector();
        if (belowNormalVector.dot(displacementVector) < Zero()) {
            belowNormalVector = -belowNormalVector;
        }

        Vector3d aboveNormalVector = planeAbove.normalVector();
        if (aboveNormalVector.dot(displacementVector) < Zero()) {
            aboveNormalVector = -aboveNormalVector;
        }

        assert(belowNormalVector.cross(aboveNormalVector).isZero());

        Vector3d normalVector = belowNormalVector + 0.5 * (aboveNormalVector - belowNormalVector);

        return Plane3d::FromPointAndNormal(originPoint, normalVector);
    }

    Plane3d Plane3d::ThroughAxisAndPoint(const Axis3d& axis, const Vector3d& point) {
        return Plane3d(axis.originPoint(), axis.basisVector(), point - axis.originPoint());
    }

    Plane3d Plane3d::ThroughAxis(const Axis3d& axis) {
        return Plane3d(axis.originPoint(), axis.basisVector(), axis.normalVector());
    }

    Plane3d Plane3d::XY() {
        return Plane3d::FromBasisVectors(Vector3d::Zero(), Vector3d::UnitX(), Vector3d::UnitY());
    }

    Plane3d Plane3d::XY(const Vector3d& originPoint) {
        return Plane3d::FromBasisVectors(originPoint, Vector3d::UnitX(), Vector3d::UnitY());
    }

    Plane3d Plane3d::XZ() {
        return Plane3d::FromBasisVectors(Vector3d::Zero(), Vector3d::UnitX(), Vector3d::UnitZ());
    }

    Plane3d Plane3d::XZ(const Vector3d& originPoint) {
        return Plane3d::FromBasisVectors(originPoint, Vector3d::UnitX(), Vector3d::UnitZ());
    }

    Plane3d Plane3d::YX() {
        return Plane3d::FromBasisVectors(Vector3d::Zero(), Vector3d::UnitY(), Vector3d::UnitX());
    }

    Plane3d Plane3d::YX(const Vector3d& originPoint) {
        return Plane3d::FromBasisVectors(originPoint, Vector3d::UnitY(), Vector3d::UnitX());
    }

    Plane3d Plane3d::YZ() {
        return Plane3d::FromBasisVectors(Vector3d::Zero(), Vector3d::UnitY(), Vector3d::UnitZ());
    }

    Plane3d Plane3d::YZ(const Vector3d& originPoint) {
        return Plane3d::FromBasisVectors(originPoint, Vector3d::UnitY(), Vector3d::UnitZ());
    }

    Plane3d Plane3d::ZX() {
        return Plane3d::FromBasisVectors(Vector3d::Zero(), Vector3d::UnitZ(), Vector3d::UnitX());
    }

    Plane3d Plane3d::ZX(const Vector3d& originPoint) {
        return Plane3d::FromBasisVectors(originPoint, Vector3d::UnitZ(), Vector3d::UnitX());
    }

    Plane3d Plane3d::ZY() {
        return Plane3d::FromBasisVectors(Vector3d::Zero(), Vector3d::UnitZ(), Vector3d::UnitY());
    }

    Plane3d Plane3d::ZY(const Vector3d& originPoint) {
        return Plane3d::FromBasisVectors(originPoint, Vector3d::UnitZ(), Vector3d::UnitY());
    }

    Plane3d Plane3d::FromBasisVectors(
        const Vector3d& originPoint,
        const Vector3d& xBasisVector,
        const Vector3d& yBasisVector
    ) {
        Matrix<double, 3, 2> basisMatrix;
        basisMatrix << xBasisVector, yBasisVector;
        return Datum<3, 2>(originPoint, basisMatrix);
    }

    Plane3d Plane3d::FromBasisMatrix(
        const Vector3d& originPoint,
        const Matrix<double, 3, 2>& basisMatrix
    ) {
        return Datum<3, 2>(originPoint, basisMatrix);
    }
}
