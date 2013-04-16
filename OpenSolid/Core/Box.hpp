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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>

#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Interval.hpp>

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions>
    inline
    Box<iNumDimensions>::Box() :
        _vector(Matrix<Interval, iNumDimensions, 1>::Empty()) {
    }

    template <int iNumDimensions> template <class TVector>
    inline
    Box<iNumDimensions>::Box(const EigenBase<TVector>& vector) :
        _vector(vector) {
    }

    template <>
    inline
    Box<1>::Box(Interval x) :
        _vector(Matrix1I::Constant(x)) {        
    }

    template <>
    inline
    Box<2>::Box(Interval x, Interval y) :
        _vector(x, y) {        
    }

    template <>
    inline
    Box<3>::Box(Interval x, Interval y, Interval z) :
        _vector(x, y, z) {        
    }

    template <int iNumDimensions>
    inline const Interval*
    Box<iNumDimensions>::data() const {
        return vector().data();
    }

    template <int iNumDimensions>
    inline Interval*
    Box<iNumDimensions>::data() {
        return vector().data();
    }

    template <int iNumDimensions>
    inline Matrix<Interval, iNumDimensions, 1>&
    Box<iNumDimensions>::vector() {
        return _vector;
    }

    template <int iNumDimensions>
    inline const Matrix<Interval, iNumDimensions, 1>&
    Box<iNumDimensions>::vector() const {
        return _vector;
    }

    template <int iNumDimensions>
    inline Interval&
    Box<iNumDimensions>::x() {
        return vector().x();
    }
    
    template <int iNumDimensions>
    inline Interval
    Box<iNumDimensions>::x() const {
        return vector().x();
    }

    template <int iNumDimensions>
    inline Interval&
    Box<iNumDimensions>::y() {
        return vector().y();
    }
    
    template <int iNumDimensions>
    inline Interval
    Box<iNumDimensions>::y() const {
        return vector().y();
    }

    template <int iNumDimensions>
    inline Interval&
    Box<iNumDimensions>::z() {
        return vector().z();
    }
    
    template <int iNumDimensions>
    inline Interval
    Box<iNumDimensions>::z() const {
        return vector().z();
    }

    template <int iNumDimensions>
    inline Interval&
    Box<iNumDimensions>::operator()(int index) {
        return vector()(index);
    }
    
    template <int iNumDimensions>
    inline Interval
    Box<iNumDimensions>::operator()(int index) const {
        return vector()(index);
    }

    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::isEmpty() const {
        return vector().isEmpty();
    }

    template <int iNumDimensions>
    inline Point<iNumDimensions>
    Box<iNumDimensions>::minPoint() const {
        return Point<iNumDimensions>(vector().cwiseLower());
    }
    
    template <int iNumDimensions>
    inline Point<iNumDimensions>
    Box<iNumDimensions>::maxPoint() const {
        return Point<iNumDimensions>(vector().cwiseUpper());
    }
    
    template <int iNumDimensions>
    inline Point<iNumDimensions>
    Box<iNumDimensions>::midPoint() const {
        return Point<iNumDimensions>(vector().cwiseMedian());
    }
    
    template <int iNumDimensions>
    inline Point<iNumDimensions>
    Box<iNumDimensions>::randomPoint() const {
        return Point<iNumDimensions>(vector().cwiseRandom());
    }

    template <int iNumDimensions>
    inline Matrix<double, iNumDimensions, 1>
    Box<iNumDimensions>::diagonalVector() const {
        return vector().cwiseWidth();
    }

    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::overlaps(const Box<iNumDimensions>& other, double precision) const {
        return vector().overlaps(other.vector(), precision);
    }

    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::strictlyOverlaps(
        const Box<iNumDimensions>& other,
        double precision
    ) const {
        return vector().strictlyOverlaps(other.vector(), precision);
    }
    
    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::contains(const Point<iNumDimensions>& point, double precision) const {
        return vector().contains(point.vector().template cast<Interval>(), precision);
    }
    
    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::strictlyContains(
        const Point<iNumDimensions>& point,
        double precision
    ) const {
        return vector().strictlyContains(point.vector().template cast<Interval>(), precision);
    }
    
    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::contains(const Box<iNumDimensions>& other, double precision) const {
        return vector().contains(other.vector(), precision);
    }
    
    template <int iNumDimensions>
    inline bool
    Box<iNumDimensions>::strictlyContains(
        const Box<iNumDimensions>& other,
        double precision
    ) const {
        return vector().strictlyContains(other.vector(), precision);
    }

    template <int iNumDimensions>
    inline Box<iNumDimensions>
    Box<iNumDimensions>::hull(const Point<iNumDimensions>& point) const {
        return Box<iNumDimensions>(vector().hull(point.vector().template cast<Interval>()));
    }
    
    template <int iNumDimensions>
    inline Box<iNumDimensions>
    Box<iNumDimensions>::hull(const Box<iNumDimensions>& other) const {
        return Box<iNumDimensions>(vector().hull(other.vector()));
    }

    template <int iNumDimensions>
    inline Box<iNumDimensions>
    Box<iNumDimensions>::intersection(const Box<iNumDimensions>& other) const {
        return Box<iNumDimensions>(vector().intersection(other.vector()));
    }

    template <int iNumDimensions>
    inline Matrix<Interval, iNumDimensions, 1>
    Box<iNumDimensions>::operator-(const Point<iNumDimensions>& point) const {
        return vector() - point.vector().template cast<Interval>();
    }

    template <int iNumDimensions>
    inline Matrix<Interval, iNumDimensions, 1>
    Box<iNumDimensions>::operator-(const Box<iNumDimensions>& other) const {
        return vector() - other.vector();
    }

    template <int iNumDimensions>
    inline Box<iNumDimensions>
    Box<iNumDimensions>::Empty() {
        return Box<iNumDimensions>(Matrix<Interval, iNumDimensions, 1>::Empty());
    }

    template <int iNumDimensions>
    inline Box<iNumDimensions>
    Box<iNumDimensions>::Unit() {
        return Box<iNumDimensions>(Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Unit()));
    }

    template <int iNumDimensions>
    std::ostream& operator<<(std::ostream& stream, const Box<iNumDimensions>& box) {
        stream << box.vector();
        return stream;
    }

    inline Box1d
    ScalingFunction<Box1d>::operator()(const Box1d& box, double scale) const {
        return Box1d(scale * box.x());
    }

    inline Box2d
    ScalingFunction<Box2d>::operator()(const Box2d& box, double scale) const {
        return Box2d(scale * box.x(), scale * box.y());
    }

    inline Box3d
    ScalingFunction<Box3d>::operator()(const Box3d& box, double scale) const {
        return Box3d(scale * box.x(), scale * box.y(), scale * box.z());
    }

    template <int iNumDimensions> template <class TVector>
    Box<iNumDimensions>
    TranslationFunction<Box<iNumDimensions>>::operator()(
        const Box<iNumDimensions>& box,
        const EigenBase<TVector>& vector
    ) const {
        return Box<iNumDimensions>(box.vector() + vector.derived().template cast<Interval>());
    }

    template <int iTransformedDimensions> template <class TMatrix>
    Box<iTransformedDimensions>
    TransformationFunction<Box1d, iTransformedDimensions>::operator()(
        const Box1d& box,
        const EigenBase<TMatrix>& matrix
    ) const {
        Box<iTransformedDimensions> result;
        for (int i = 0; i < iTransformedDimensions; ++i) {
            result(i) = matrix.derived()(i, 0) * box.x();
        }
        return result;
    }

    template <int iTransformedDimensions> template <class TMatrix>
    Box<iTransformedDimensions>
    TransformationFunction<Box2d, iTransformedDimensions>::operator()(
        const Box2d& box,
        const EigenBase<TMatrix>& matrix
    ) const {
        Box<iTransformedDimensions> result;
        for (int i = 0; i < iTransformedDimensions; ++i) {
            result(i) = matrix.derived()(i, 0) * box.x() + matrix.derived()(i, 1) * box.y();
        }
        return result;
    }

    template <int iTransformedDimensions> template <class TMatrix>
    Box<iTransformedDimensions>
    TransformationFunction<Box3d, iTransformedDimensions>::operator()(
        const Box3d& box,
        const EigenBase<TMatrix>& matrix
    ) const {
        Box<iTransformedDimensions> result;
        for (int i = 0; i < iTransformedDimensions; ++i) {
            result(i) = matrix.derived()(i, 0) * box.x() + matrix.derived()(i, 1) * box.y() +
                matrix.derived()(i, 2) * box.z();
        }
        return result;
    }

    template <int iNumDimensions>
    inline const Box<iNumDimensions>&
    BoundsFunction<Box<iNumDimensions>>::operator()(const Box<iNumDimensions>& box) const {
        return box;
    }
}
