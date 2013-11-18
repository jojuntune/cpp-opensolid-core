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

#include <OpenSolid/Core/Geometry.declarations.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Domain.definitions.hpp>
#include <OpenSolid/Core/Geometry/BoundsType.definitions.hpp>
#include <OpenSolid/Core/Geometry/Transformable.definitions.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionEvaluation.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Simplex.declarations.hpp>
#include <OpenSolid/Core/SpatialSet.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    class Geometry :
        public Convertible<Geometry<iNumDimensions, iNumParameters>>,
        public Transformable<Geometry<iNumDimensions, iNumParameters>>
    {
    private:
        ParametricExpression<iNumDimensions, iNumParameters> _expression;
        Domain<iNumParameters> _domain;
        Box<iNumDimensions> _bounds;
    public:
        Geometry();
        
        Geometry(
            const ParametricExpression<iNumDimensions, iNumParameters>& expression,
            const Domain<iNumParameters>& domain
        );

        Geometry(const Simplex<iNumDimensions, iNumParameters + 1>& simplex);
        
        const ParametricExpression<iNumDimensions, iNumParameters>&
        expression() const;
        
        const Domain<iNumParameters>&
        domain() const;

        bool
        isValid() const;
        
        const Box<iNumDimensions>&
        bounds() const;
        
        template <class TVector>
        Point<iNumDimensions>
        operator()(const EigenBase<TVector>& parameterValues) const;

        SpatialSet<Geometry<iNumDimensions, iNumParameters - 1>>
        boundaries() const;
    };

    template <int iNumDimensions>
    class Geometry<iNumDimensions, 1> :
        public Convertible<Geometry<iNumDimensions, 1>>,
        public Transformable<Geometry<iNumDimensions, 1>>
    {
    private:
        ParametricExpression<iNumDimensions, 1> _expression;
        Interval _domain;
        Box<iNumDimensions> _bounds;
    public:
        Geometry();

        Geometry(
            const ParametricExpression<iNumDimensions, 1>& expression,
            Interval domain
        );

        Geometry(const Simplex<iNumDimensions, 2>& simplex);

        const ParametricExpression<iNumDimensions, 1>&
        expression() const;
        
        Interval
        domain() const;

        bool
        isValid() const;
        
        const Box<iNumDimensions>&
        bounds() const;

        Point<iNumDimensions>
        operator()(double parameterValue) const;

        SpatialSet<Point<iNumDimensions>>
        boundaries() const;
    };
}
