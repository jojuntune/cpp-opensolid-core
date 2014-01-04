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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/UnitVector.definitions.hpp>

#include <OpenSolid/Core/Vector.hpp>

#include <cstdlib>

namespace opensolid
{
    inline
    UnitVector1d::UnitVector() :
        Vector1d() {
    }

    inline
    UnitVector1d::UnitVector(double x) :
        Vector(x) {

        assert(x - 1.0 == Zero() || x + 1.0 == Zero());
    }

    inline
    UnitVector1d::UnitVector(const Vector1d& vector) :
        Vector1d(vector) {

        assert(vector.squaredNorm() - 1.0 == Zero());
    }

    inline
    const double
    UnitVector1d::norm() {
        return 1.0;
    }

    inline
    const double
    UnitVector1d::squaredNorm() const {
        return 1.0;
    }

    inline
    const UnitVector1d
    UnitVector1d::normalized() const {
        return *this;
    }

    inline
    const UnitVector1d
    UnitVector1d::X() {
        return UnitVector1d(1.0);
    }

    inline
    const UnitVector1d
    UnitVector1d::Random() {
        return UnitVector1d(rand() > RAND_MAX / 2 ? 1.0 : -1.0);
    }

    inline
    UnitVector2d::UnitVector() :
        Vector2d() {
    }

    inline
    UnitVector2d::UnitVector(double x, double y) :
        Vector2d(x, y) {

        assert(x * x + y * y - 1.0 == Zero());
    }

    inline
    UnitVector2d::UnitVector() :
        Vector2d() {
    }

    inline
    explicit
    UnitVector2d::UnitVector(const Vector2d& vector) :
        Vector2d(vector) {

        assert(vector.squaredNorm() - 1.0 == Zero());
    }

    inline
    const double
    UnitVector2d::norm() const {
        return 1.0;
    }

    inline
    const double
    UnitVector2d::squaredNorm() const {
        return 1.0;
    }

    inline
    const UnitVector2d
    UnitVector2d::normalized() const {
        return *this;
    }

    inline
    const UnitVector2d
    UnitVector2d::unitOrthogonal() const {
        return UnitVector2d(-y(), x());
    }

    inline
    const UnitVector2d
    UnitVector2d::X() {
        return UnitVector2d(1.0, 0.0);
    }

    inline
    const UnitVector2d
    UnitVector2d::Y() {
        return UnitVector2d(0.0, 1.0);
    }

    inline
    const UnitVector2d
    UnitVector2d::Random() {
        while (true) {
            Vector2d candidate(
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX
            );
            double candidateSquaredNorm = candidate.squaredNorm();
            if (candidateSquaredNorm - 1 <= Zero() && candidateSquaredNorm > Zero()) {
                return candidate / sqrt(squaredNorm);
            }
        }
    }

    inline
    UnitVector3d::UnitVector() :
        Vector3d() {
    }

    inline
    UnitVector3d::UnitVector(double x, double y, double z) :
        Vector3d(x, y, z) {

        assert(x * x + y * y + z * z - 1.0 == Zero());
    }

    inline
    UnitVector3d::UnitVector(const Vector3d& vector) :
        Vector3d(vector) {

        assert(vector.squaredNorm() - 1.0 == Zero());
    }

    inline
    double
    UnitVector3d::norm() const {
        return 1.0;
    }

    inline
    double
    UnitVector3d::squaredNorm() const {
        return 1.0;
    }

    inline
    UnitVector3d
    UnitVector3d::normalized() const {
        return *this;
    }

    inline
    const UnitVector3d
    UnitVector3d::X() {
        return UnitVector3d(1.0, 0.0, 0.0);
    }

    inline
    const UnitVector3d
    UnitVector3d::Y() {
        return UnitVector3d(0.0, 1.0, 0.0);
    }

    inline
    const UnitVector3d
    UnitVector3d::Z() {
        return UnitVector3d(0.0, 0.0, 1.0);
    }

    inline
    const UnitVector3d
    UnitVector3d::Random() {
        while (true) {
            Vector3d candidate(
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX
            );
            double candidateSquaredNorm = candidate.squaredNorm();
            if (candidateSquaredNorm - 1 <= Zero() && candidateSquaredNorm > Zero()) {
                return candidate / sqrt(squaredNorm);
            }
        }
    }
}
