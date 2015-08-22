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

#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    UnitVector2d
    Vector2d::unitRandom() {
        while (true) {
            Vector2d candidate(
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX
            );
            double candidateSquaredNorm = candidate.squaredNorm();
            if (candidateSquaredNorm >= 0.25 && candidateSquaredNorm <= 1.0) {
                return UnitVector2d((candidate / sqrt(candidateSquaredNorm)).components());
            }
        }
    }

    UnitVector3d
    Vector3d::unitOrthogonal() const {
        if (isZero()) {
            assert(false);
            return UnitVector3d();
        } else {
            double absX = abs(x());
            double absY = abs(y());
            double absZ = abs(z());
            if (absX <= absY) {
                if (absX <= absZ) {
                    return Vector3d::unitX().cross(*this).normalized();
                } else {
                    return Vector3d::unitZ().cross(*this).normalized();
                }
            } else {
                if (absY <= absZ) {
                    return Vector3d::unitY().cross(*this).normalized();
                } else {
                    return Vector3d::unitZ().cross(*this).normalized();
                }
            }
        }
    }

    UnitVector3d
    Vector3d::unitRandom() {
        while (true) {
            Vector3d candidate(
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX
            );
            double candidateSquaredNorm = candidate.squaredNorm();
            if (candidateSquaredNorm >= 0.25 && candidateSquaredNorm <= 1.0) {
                return UnitVector3d((candidate / sqrt(candidateSquaredNorm)).components());
            }
        }
    }

    std::ostream&
    operator<<(std::ostream& stream, const Vector2d& vector) {
        stream << "Vector2d(" << vector.x() << "," << vector.y() << ")";
        return stream;
    }

    std::ostream&
    operator<<(std::ostream& stream, const Vector3d& vector) {
        stream << "Vector3d(" << vector.x() << "," << vector.y() << vector.z() << ")";
        return stream;
    }

    std::ostream&
    operator<<(std::ostream& stream, const IntervalVector2d& vector) {
        stream << "IntervalVector2d(" << vector.x() << "," << vector.y() << ")";
        return stream;
    }

    std::ostream&
    operator<<(std::ostream& stream, const IntervalVector3d& vector) {
        stream << "IntervalVector3d(" << vector.x() << "," << vector.y() << vector.z() << ")";
        return stream;
    }
}
