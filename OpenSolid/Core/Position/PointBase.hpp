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

#include <OpenSolid/Core/Position/PointBase.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase() :
            _vector(Matrix<double, iNumDimensions, 1>::Zero()) {
        }

        template <int iNumDimensions> template <class TVector>
        inline
        PointBase<iNumDimensions>::PointBase(const EigenBase<TVector>& vector) :
            _vector(vector.derived()) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double value) :
            _vector(Matrix<double, iNumDimensions, 1>::Constant(value)) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double x, double y) :
            _vector(x, y) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double x, double y, double z) :
            _vector(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        const Matrix<double, iNumDimensions, 1>&
        PointBase<iNumDimensions>::vector() const {
            return _vector;
        }

        template <int iNumDimensions>
        inline
        Matrix<double, iNumDimensions, 1>&
        PointBase<iNumDimensions>::vector() {
            return _vector;
        }

        template <int iNumDimensions>
        inline
        const double*
        PointBase<iNumDimensions>::data() const {
            return vector().data();
        }

        template <int iNumDimensions>
        inline
        double*
        PointBase<iNumDimensions>::data() {
            return vector().data();
        }

        template <int iNumDimensions>
        inline
        double&
        PointBase<iNumDimensions>::operator()(int index) {
            return vector()(index);
        }
        
        template <int iNumDimensions>
        inline
        double
        PointBase<iNumDimensions>::operator()(int index) const {
            return vector()(index);
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointBase<iNumDimensions>::hull(const Point<iNumDimensions>& other) const {
            return Box<iNumDimensions>(vector().hull(other.vector()));
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::isOrigin(double precision) const {
            return vector().isZero(precision);
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::operator==(const Point<iNumDimensions>& other) const {
            return vector() == other.vector();
        }

        template <int iNumDimensions>
        inline
        Matrix<double, iNumDimensions, 1>
        PointBase<iNumDimensions>::operator-(const Point<iNumDimensions>& other) const {
            return vector() - other.vector();
        }

        template <int iNumDimensions>
        inline
        Matrix<Interval, iNumDimensions, 1>
        PointBase<iNumDimensions>::operator-(const Box<iNumDimensions>& box) const {
            return vector().template cast<Interval>() - box.vector();
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::Origin() {
            return Point<iNumDimensions>(Matrix<double, iNumDimensions, 1>::Zero());
        }
    }
}
