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

#include <OpenSolid/Core/Box.definitions.hpp>

#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        BoxVertices<iNumDimensions>::BoxVertices(const Box<iNumDimensions>& box) :
            _box(box) {
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>&
        BoxVertices<iNumDimensions>::box() const {
            return _box;
        }

        template <int iNumDimensions>
        inline
        IndexIterator<BoxVertices<iNumDimensions>>
        BoxVertices<iNumDimensions>::begin() const {
            return IndexIterator<BoxVertices<iNumDimensions>>::begin(this);
        }

        template <int iNumDimensions>
        inline
        IndexIterator<BoxVertices<iNumDimensions>>
        BoxVertices<iNumDimensions>::end() const {
            return IndexIterator<BoxVertices<iNumDimensions>>::end(this);
        }

        template <int iNumDimensions>
        inline
        bool
        BoxVertices<iNumDimensions>::isEmpty() const {
            return false;
        }

        template <int iNumDimensions>
        inline
        std::size_t
        BoxVertices<iNumDimensions>::size() const {
            return 1 << iNumDimensions;
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxVertices<iNumDimensions>::operator[](std::size_t index) const {
            return box().vertex(int(index));
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>&
        BoxCommon<iNumDimensions>::derived() const {
            return static_cast<const Box<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        BoxCommon<iNumDimensions>::BoxCommon() {
        }

        template <int iNumDimensions>
        inline
        BoxCommon<iNumDimensions>::BoxCommon(Interval x, Interval y) :
            CartesianBase<Interval, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        BoxCommon<iNumDimensions>::BoxCommon(Interval x, Interval y, Interval z) :
            CartesianBase<Interval, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        BoxCommon<iNumDimensions>::BoxCommon(
            const Matrix<Interval, iNumDimensions, 1>& components
        ) : CartesianBase<Interval, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::isEmpty() const {
            return this->components().any(
                [] (Interval component) -> bool {
                    return component.isEmpty();
                }
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>&
        BoxCommon<iNumDimensions>::bounds() const {
            return derived();
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxCommon<iNumDimensions>::minVertex() const {
            return Point<iNumDimensions>(this->components().cwiseLowerBound());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxCommon<iNumDimensions>::maxVertex() const {
            return Point<iNumDimensions>(this->components().cwiseUpperBound());
        }

        template <>
        inline
        const Point<2>
        BoxCommon<2>::vertex(int index) const {
            assert(index >= 0 && index < 4);
            return Point<2>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound()
            );
        }

        template <>
        inline
        const Point<3>
        BoxCommon<3>::vertex(int index) const {
            assert(index >= 0 && index < 8);
            return Point<3>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound(),
                index & 4 ? this->component(2).upperBound() : this->component(2).lowerBound()
            );
        }

        template <int iNumDimensions>
        inline
        const BoxVertices<iNumDimensions>
        BoxCommon<iNumDimensions>::vertices() const {
            return BoxVertices<iNumDimensions>(derived());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxCommon<iNumDimensions>::centroid() const {
            return Point<iNumDimensions>(this->components().cwiseMedian());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxCommon<iNumDimensions>::randomPoint() const {
            return Point<iNumDimensions>(
                this->components().map(
                    [] (Interval component) -> double {
                        return component.randomValue();
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>
        BoxCommon<iNumDimensions>::diagonalVector() const {
            return Vector<double, iNumDimensions>(this->components().cwiseWidth());
        }

        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::overlaps(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.overlaps(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::strictlyOverlaps(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.strictlyOverlaps(otherComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::contains(
            const Point<iNumDimensions>& point,
            double precision
        ) const {
            return this->components().binaryAll(
                point.components(),
                [precision] (Interval component, double pointComponent) -> bool {
                    return component.contains(pointComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::strictlyContains(
            const Point<iNumDimensions>& point,
            double precision
        ) const {
            return this->components().binaryAll(
                point.components(),
                [precision] (Interval component, double pointComponent) -> bool {
                    return component.strictlyContains(pointComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::contains(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.contains(otherComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        bool
        BoxCommon<iNumDimensions>::strictlyContains(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.strictlyContains(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxCommon<iNumDimensions>::hull(const Point<iNumDimensions>& point) const {
            return Box<iNumDimensions>(
                this->components().binaryMap(
                    point.components(),
                    [] (Interval component, double pointComponent) -> Interval {
                        return component.hull(pointComponent);
                    }
                )
            );
        }
        
        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxCommon<iNumDimensions>::hull(const Box<iNumDimensions>& other) const {
            return Box<iNumDimensions>(
                this->components().binaryMap(
                    other.components(),
                    [] (Interval component, Interval otherComponent) -> Interval {
                        return component.hull(otherComponent);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxCommon<iNumDimensions>::intersection(const Box<iNumDimensions>& other) const {
            return Box<iNumDimensions>(
                this->components().binaryMap(
                    other.components(),
                    [] (Interval component, Interval otherComponent) -> Interval {
                        return component.intersection(otherComponent);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxCommon<iNumDimensions>::UNIT() {
            return Box<iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::UNIT())
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxCommon<iNumDimensions>::EMPTY() {
            return Box<iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::EMPTY())
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxCommon<iNumDimensions>::WHOLE() {
            return Box<iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::WHOLE())
            );
        }
    }

    inline
    Box2d::Box() {
    }

    inline
    Box2d::Box(Interval x, Interval y) :
        detail::BoxCommon<2>(x, y) {        
    }

    inline
    Box2d::Box(const IntervalVector2d& intervalVector) :
        detail::BoxCommon<2>(intervalVector.components()) {
    }

    inline
    Box2d::Box(const IntervalColumnMatrix2d& components) :
        detail::BoxCommon<2>(components) {
    }

    inline
    Point2d
    Box2d::interpolated(double x, double y) const {
        return minVertex() + Vector2d(x * this->x().width(), y * this->y().width());
    }

    inline
    Box2d
    Box2d::interpolated(Interval x, Interval y) const {
        return minVertex() + IntervalVector2d(x * this->x().width(), y * this->y().width());
    }

    inline
    Box2d
    Box2d::scaledAbout(const Point2d& point, double scale) const {
        return Box2d(point + scale * (*this - point));
    }

    inline
    Box2d
    Box2d::translatedBy(const Vector2d& vector) const {
        return *this + vector;
    }

    inline
    Box3d::Box() {
    }

    inline
    Box3d::Box(Interval x, Interval y, Interval z) :
        detail::BoxCommon<3>(x, y, z) {        
    }

    inline
    Box3d::Box(const IntervalVector3d& intervalVector) :
        detail::BoxCommon<3>(intervalVector.components()) {
    }

    inline
    Box3d::Box(const IntervalColumnMatrix3d& components) :
        detail::BoxCommon<3>(components) {
    }

    inline
    Point3d
    Box3d::interpolated(double x, double y, double z) const {
        Vector3d vector(x * this->x().width(), y * this->y().width(), z * this->z().width());
        return minVertex() + vector;
    }

    inline
    Box3d
    Box3d::interpolated(Interval x, Interval y, Interval z) const {
        IntervalVector3d intervalVector(
            x * this->x().width(),
            y * this->y().width(),
            z * this->z().width()
        );
        return minVertex() + intervalVector;
    }

    inline
    Box3d
    Box3d::scaledAbout(const Point3d& point, double scale) const {
        return Box3d(point + scale * (*this - point));
    }

    inline
    Box3d
    Box3d::translatedBy(const Vector3d& vector) const {
        return *this + vector;
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(point.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Box<iNumDimensions>& box) {
        return Vector<Interval, iNumDimensions>(point.components() - box.components());
    }

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Point<iNumDimensions>& point) {
        return Vector<Interval, iNumDimensions>(box.components() - point.components());
    }

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& firstBox, const Box<iNumDimensions>& secondBox) {
        return Vector<Interval, iNumDimensions>(firstBox.components() - secondBox.components());
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Box<iNumDimensions>& box) {
        stream << "Box" << iNumDimensions << "d";
        stream << "(";
        for (int index = 0; index < iNumDimensions; ++index) {
            stream << box.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }
}
