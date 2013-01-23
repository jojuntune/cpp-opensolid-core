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

    Plane3d::Plane3d(
        const Vector3d& originPoint,
        const Vector3d& xVector,
        const Vector3d& yVector
    ) : Datum<3, 2>() {
        Matrix<double, 3, 2> basisMatrix;
        basisMatrix << xVector, yVector;
        *this = Datum<3, 2>(originPoint, basisMatrix).normalized();
    }

    Plane3d Plane3d::FromPointAndNormal(const Vector3d& originPoint, const Vector3d& normalVector) {
        Vector3d xVector = normalVector.unitOrthogonal();
        Vector3d yVector = normalVector.cross(xVector);
        return Plane3d(originPoint, xVector, yVector);
    }

    Plane3d Plane3d::ThroughPoints(
        const Vector3d& originPoint,
        const Vector3d& xAxisPoint,
        const Vector3d& planePoint
    ) {
        return Plane3d(originPoint, xAxisPoint - originPoint, planePoint - originPoint);
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
}
