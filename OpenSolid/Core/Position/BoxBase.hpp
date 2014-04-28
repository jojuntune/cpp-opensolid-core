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

#include <OpenSolid/Core/Position/BoxBase.definitions.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Position/BoxVertices.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>&
        BoxBase<iNumDimensions>::derived() const {
            return static_cast<const Box<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase() {
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase(Interval value) :
            CartesianBase<Interval, iNumDimensions>(value) {
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase(Interval x, Interval y) :
            CartesianBase<Interval, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase(Interval x, Interval y, Interval z) :
            CartesianBase<Interval, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase(const Matrix<Interval, iNumDimensions, 1>& components) :
            CartesianBase<Interval, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase(const Interval* sourcePtr) :
            CartesianBase<Interval, iNumDimensions>(sourcePtr) {
        }

        template <int iNumDimensions>
        inline
        bool
        BoxBase<iNumDimensions>::isEmpty() const {
            return this->components().any(
                [] (Interval component) -> bool {
                    return component.isEmpty();
                }
            );
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxBase<iNumDimensions>::minVertex() const {
            return Point<iNumDimensions>(this->components().cwiseLowerBound());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxBase<iNumDimensions>::maxVertex() const {
            return Point<iNumDimensions>(this->components().cwiseUpperBound());
        }

        template <>
        inline
        const Point<1>
        BoxBase<1>::vertex(int index) const {
            assert(index >= 0 && index < 2);
            return Point<1>(
                index == 0 ? this->component(0).lowerBound() : this->component(0).upperBound()
            );
        }

        template <>
        inline
        const Point<2>
        BoxBase<2>::vertex(int index) const {
            assert(index >= 0 && index < 4);
            return Point<2>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound()
            );
        }

        template <>
        inline
        const Point<3>
        BoxBase<3>::vertex(int index) const {
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
        BoxBase<iNumDimensions>::vertices() const {
            return BoxVertices<iNumDimensions>(derived());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxBase<iNumDimensions>::centroid() const {
            return Point<iNumDimensions>(this->components().cwiseMedian());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxBase<iNumDimensions>::randomPoint() const {
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
        BoxBase<iNumDimensions>::diagonalVector() const {
            return Vector<double, iNumDimensions>(this->components().cwiseWidth());
        }

        template <int iNumDimensions>
        inline
        bool
        BoxBase<iNumDimensions>::overlaps(
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
        BoxBase<iNumDimensions>::strictlyOverlaps(
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
        BoxBase<iNumDimensions>::contains(
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
        BoxBase<iNumDimensions>::strictlyContains(
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
        BoxBase<iNumDimensions>::contains(
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
        BoxBase<iNumDimensions>::strictlyContains(
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
        BoxBase<iNumDimensions>::hull(const Point<iNumDimensions>& point) const {
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
        BoxBase<iNumDimensions>::hull(const Box<iNumDimensions>& other) const {
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
        BoxBase<iNumDimensions>::intersection(const Box<iNumDimensions>& other) const {
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
        BoxBase<iNumDimensions>::Unit() {
            return Box<iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Unit())
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxBase<iNumDimensions>::Empty() {
            return Box<iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Empty())
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxBase<iNumDimensions>::Whole() {
            return Box<iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Whole())
            );
        }
    }
}
