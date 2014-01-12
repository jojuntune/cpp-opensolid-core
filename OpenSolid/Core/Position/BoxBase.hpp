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

#include <OpenSolid/Core/Position/BoxBase.definitions.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/IntervalMatrix.definitions.hpp>
#include <OpenSolid/Core/IntervalVector.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Position/BoxVertices.hpp>

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
        BoxBase<iNumDimensions>::BoxBase(const IntervalMatrix<iNumDimensions, 1>& components) :
            CartesianBase<Interval, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        BoxBase<iNumDimensions>::BoxBase(const Interval* sourcePtr) :
            CartesianBase<Interval, iNumDimensions>(sourcePtr) {
        }

        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::isEmpty() const {
            return components().any(
                [] (Interval component) {
                    return component.isEmpty();
                }
            );
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        Box<iNumDimensions>::minVertex() const {
            return Point<iNumDimensions>(
                components().map(
                    [] (Interval component) {
                        return component.lowerBound();
                    }
                )
            );
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        Box<iNumDimensions>::maxVertex() const {
            return Point<iNumDimensions>(
                components().map(
                    [] (Interval component) {
                        return component.upperBound();
                    }
                )
            );
        }

        template <>
        inline
        const Point<1>
        BoxBase<1>::vertex(std::int64_t index) const {
            assert(index >= 0 && index < 2);
            return Point<1>(index == 0 ? component(0).lowerBound() : component(0).upperBound());
        }

        template <int iNumDimensions>
        inline
        const Point<2>
        BoxBase<2>::vertex(std::int64_t index) const {
            assert(index >= 0 && index < 4);
            return Point<2>(
                index & 1 ? component(0).upperBound() : component(0).lowerBound(),
                index & 2 ? component(1).upperBound() : component(1).lowerBound()
            );
        }

        template <int iNumDimensions>
        inline
        const Point<3>
        BoxBase<3>::vertex(std::int64_t index) const {
            assert(index >= 0 && index < 8);
            return Point<3>(
                index & 1 ? component(0).upperBound() : component(0).lowerBound(),
                index & 2 ? component(1).upperBound() : component(1).lowerBound(),
                index & 4 ? component(2).upperBound() : component(2).lowerBound()
            );
        }

        template <int iNumDimensions>
        inline
        BoxVertices<iNumDimensions>
        BoxBase<iNumDimensions>::vertices() const {
            return BoxVertices<iNumDimensions>(derived());
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxBase<iNumDimensions>::midPoint() const {
            return Point<iNumDimensions>(
                components().map(
                    [] (Interval component) {
                        return component.median();
                    }
                )
            );
        }
        
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>
        BoxBase<iNumDimensions>::randomPoint() const {
            return Point<iNumDimensions>(
                components().map(
                    [] (Interval component) {
                        return component.randomValue();
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        const Vector<iNumDimensions>
        BoxBase<iNumDimensions>::diagonalVector() const {
            return Point<iNumDimensions>(
                components().map(
                    [] (Interval component) {
                        return component.width();
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::overlaps(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return components().binaryAll(
                other.components(),
                [] (Interval component, Interval otherComponent) {
                    return component.overlaps(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::strictlyOverlaps(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return components().binaryAll(
                other.components(),
                [] (Interval component, Interval otherComponent) {
                    return component.strictlyOverlaps(otherComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::contains(
            const Point<iNumDimensions>& point,
            double precision
        ) const {
            return components().binaryAll(
                point.components(),
                [] (Interval component, double pointComponent) {
                    return component.contains(pointComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::strictlyContains(
            const Point<iNumDimensions>& point,
            double precision
        ) const {
            return components().binaryAll(
                point.components(),
                [] (Interval component, double pointComponent) {
                    return component.strictlyContains(pointComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::contains(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return components().binaryAll(
                other.components(),
                [] (Interval component, Interval otherComponent) {
                    return component.contains(otherComponent, precision);
                }
            );
        }
        
        template <int iNumDimensions>
        inline
        const bool
        BoxBase<iNumDimensions>::strictlyContains(
            const Box<iNumDimensions>& other,
            double precision
        ) const {
            return components().binaryAll(
                other.components(),
                [] (Interval component, Interval otherComponent) {
                    return component.strictlyContains(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>
        BoxBase<iNumDimensions>::hull(const Point<iNumDimensions>& point) const {
            return Box<iNumDimensions>(
                components.binaryMap(
                    point.components(),
                    [] (Interval component, double pointComponent) {
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
                components.binaryMap(
                    other.components(),
                    [] (Interval component, Interval otherComponent) {
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
                components.binaryMap(
                    other.components(),
                    [] (Interval component, Interval otherComponent) {
                        return component.intersection(otherComponent);
                    }
                )
            );
        }
    }
}
