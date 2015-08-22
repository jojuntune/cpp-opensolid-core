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

#include <OpenSolid/Core/Globalization.declarations.hpp>

#include <OpenSolid/Core/Frame.definitions.hpp>
#include <OpenSolid/Core/Transformation.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Globalization :
        public Transformation<Globalization<iNumDimensions>>
    {
    private:
        Frame<iNumDimensions> _frame;
    public:
        Globalization(const Frame<iNumDimensions>& frame);

        const Frame<iNumDimensions>&
        frame() const;

        double
        scale() const;

        Handedness
        transform(Handedness handedness) const;

        Point<iNumDimensions>
        transform(const Point<iNumDimensions>& point) const;

        template <class TParameter>
        ParametricExpression<Point<iNumDimensions>, TParameter>
        transform(const ParametricExpression<Point<iNumDimensions>, TParameter>& expression) const;

        Vector<double, iNumDimensions>
        transform(const Vector<double, iNumDimensions>& vector) const;

        template <class TParameter>
        ParametricExpression<Vector<double, iNumDimensions>, TParameter>
        transform(
            const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression
        ) const;

        UnitVector<iNumDimensions>
        transform(const UnitVector<iNumDimensions>& unitVector) const;

        template <class TParameter>
        ParametricExpression<UnitVector<iNumDimensions>, TParameter>
        transform(
            const ParametricExpression<UnitVector<iNumDimensions>, TParameter>& expression
        ) const;
    };

    typedef Globalization<2> Globalization2d;
    typedef Globalization<3> Globalization3d;
}
