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

#include <OpenSolid/Core/Position/PointBase.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class PointBase
        {
        private:
            Matrix<double, iNumDimensions, 1> _vector;
        protected:
            PointBase();

            template <class TVector>
            PointBase(const EigenBase<TVector>& vector);

            PointBase(double value);

            PointBase(double x, double y);

            PointBase(double x, double y, double z);
        public:
            const Matrix<double, iNumDimensions, 1>&
            vector() const;

            Matrix<double, iNumDimensions, 1>&
            vector();

            const double*
            data() const;
            
            double*
            data();

            double&
            operator()(int index);
            
            double
            operator()(int index) const;

            Box<iNumDimensions>
            hull(const Point<iNumDimensions>& other) const;

            bool
            isOrigin(double precision = 1e-12) const;

            bool
            operator==(const Point<iNumDimensions>& other) const;

            Matrix<double, iNumDimensions, 1>
            operator-(const Point<iNumDimensions>& other) const;

            Matrix<Interval, iNumDimensions, 1>
            operator-(const Box<iNumDimensions>& box) const;

            static Point<iNumDimensions>
            Origin();
        };
    }
}
