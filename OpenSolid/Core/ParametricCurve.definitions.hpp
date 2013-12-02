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

#include <OpenSolid/Core/ParametricCurve.declarations.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricCurve/CurveConstructors.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class ParametricCurve :
        public CurveConstructors<iNumDimensions>,
        public Transformable<ParametricCurve<iNumDimensions>>
    {
    private:
        ParametricExpression<iNumDimensions, 1> _expression;
        Interval _domain;
        Box<iNumDimensions> _bounds;
    public:
        ParametricCurve();

        ParametricCurve(const ParametricCurve<iNumDimensions>& other);

        ParametricCurve(ParametricCurve<iNumDimensions>&& other);

        ParametricCurve(
            const ParametricExpression<iNumDimensions, 1>& expression,
            Interval domain
        );

        const ParametricExpression<iNumDimensions, 1>&
        expression() const;

        Interval
        domain() const;

        const Box<iNumDimensions>&
        bounds() const;

        Point<iNumDimensions>
        evaluate(double parameterValue) const;

        Box<iNumDimensions>
        evaluate(Interval parameterBounds) const;

        ParametricExpression<iNumDimensions, 1>
        tangentVector() const;

        ParametricExpression<iNumDimensions, 1>
        normalVector() const;

        ParametricExpression<iNumDimensions, 1>
        binormalVector() const;

        ParametricExpression<1, 1>
        curvature() const;

        ParametricCurve<iNumDimensions>
        reversed() const;

        Point<iNumDimensions>
        startPoint() const;

        Point<iNumDimensions>
        endPoint() const;


    };

    typedef ParametricCurve<2> ParametricCurve2d;
    typedef ParametricCurve<3> ParametricCurve3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        typedef ParametricCurve<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        typedef ParametricCurve<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScalingFunction<ParametricCurve<iNumDimensions>>
    {
        ParametricCurve<iNumDimensions>
        operator()(const ParametricCurve<iNumDimensions>& curve, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<ParametricCurve<iNumDimensions>>
    {
        template <class TVector>
        ParametricCurve<iNumDimensions>
        operator()(
            const ParametricCurve<iNumDimensions>& curve,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        ParametricCurve<iNumResultDimensions>
        operator()(
            const ParametricCurve<iNumDimensions>& curve,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        ParametricCurve<iNumResultDimensions>
        operator()(
            const ParametricCurve<iNumDimensions>& curve,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
