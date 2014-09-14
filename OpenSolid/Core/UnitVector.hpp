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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/UnitVector.definitions.hpp>

#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    inline
    UnitVector1d::UnitVector() :
        Vector1d() {
    }

    inline
    UnitVector1d::UnitVector(double x) :
        Vector1d(x) {

        assert(abs(x) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector1d::UnitVector(const Matrix1d& components) :
        Vector1d(components) {

        assert(abs(components.value()) - 1.0 == opensolid::Zero());
    }

    inline
    double
    UnitVector1d::norm() {
        return 1.0;
    }

    inline
    double
    UnitVector1d::squaredNorm() const {
        return 1.0;
    }

    inline
    const UnitVector1d
    UnitVector1d::normalized() const {
        return *this;
    }

    inline
    UnitVector2d::UnitVector() :
        Vector2d() {
    }

    inline
    UnitVector2d::UnitVector(double x, double y) :
        Vector2d(x, y) {

        assert(sqrt(x * x + y * y) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector2d::UnitVector(const ColumnMatrix2d& components) :
        Vector2d(components) {

        assert(sqrt(components.cwiseSquared().sum()) - 1.0 == opensolid::Zero());
    }

    inline
    double
    UnitVector2d::norm() const {
        return 1.0;
    }

    inline
    double
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
    UnitVector3d::UnitVector() :
        Vector3d() {
    }

    inline
    UnitVector3d::UnitVector(double x, double y, double z) :
        Vector3d(x, y, z) {

        assert(sqrt(x * x + y * y + z * z) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector3d::UnitVector(const ColumnMatrix3d& components) :
        Vector3d(components) {

        assert(sqrt(components.cwiseSquared().sum()) - 1.0 == opensolid::Zero());
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
    const UnitVector1d
    operator-(const UnitVector1d& unitVector) {
        return UnitVector1d(unitVector.value());
    }

    inline
    const UnitVector2d
    operator-(const UnitVector2d& unitVector) {
        return UnitVector2d(-unitVector.x(), -unitVector.y());
    }

    inline
    const UnitVector3d
    operator-(const UnitVector3d& unitVector) {
        return UnitVector3d(-unitVector.x(), -unitVector.y(), -unitVector.z());
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const UnitVector<iNumDimensions>& unitVector) {
        stream << "UnitVector" << iNumDimensions << "d";
        stream << "(";
        for (int index = 0; index < iNumDimensions; ++index) {
            stream << unitVector.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }

    template <int iNumDimensions>
    inline
    const UnitVector<iNumDimensions>&
    TranslationFunction<UnitVector<iNumDimensions>>::operator()(
        const UnitVector<iNumDimensions>& unitVector,
        const Vector<double, iNumDimensions>& vector
    ) const {
        return unitVector;
    }
}
