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

#include <OpenSolid/Core/Vector/VectorBase.declarations.hpp>

#include <OpenSolid/Core/IntervalVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class VectorBase
    {
    private:
        double _components[iNumDimensions];
    protected:
        VectorBase(double x);

        VectorBase(double x, double y);

        VectorBase(double x, double y, double z);
    public:
        const double
        operator()(std::int64_t index) const;

        const double
        squaredNorm() const;

        const double
        norm() const;

        const UnitVector<iNumDimensions>
        normalized() const;

        const double
        dot(const Vector<iNumDimensions>& other) const;

        const Interval
        dot(const IntervalVector<iNumDimensions>& intervalVector) const;

        const bool
        operator==(const Vector<iNumDimensions>& other) const;
    };
}
