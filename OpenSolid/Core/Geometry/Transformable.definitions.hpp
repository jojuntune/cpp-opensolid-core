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

#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Geometry.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    struct NumDimensions<Geometry<iNumDimensions, iNumParameters>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    struct ChangeDimensions<Geometry<iNumDimensions, iNumParameters>, iNumResultDimensions>
    {
        typedef Geometry<iNumResultDimensions, iNumParameters> Type;
    };

    template <int iNumDimensions, int iNumParameters>
    struct ScalingFunction<Geometry<iNumDimensions, iNumParameters>>
    {
        Geometry<iNumDimensions, iNumParameters>
        operator()(const Geometry<iNumDimensions, iNumParameters>& geometry, double scale) const;
    };

    template <int iNumDimensions, int iNumParameters>
    struct TranslationFunction<Geometry<iNumDimensions, iNumParameters>>
    {
        template <class TVector>
        Geometry<iNumDimensions, iNumParameters>
        operator()(
            const Geometry<iNumDimensions, iNumParameters>& geometry,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    struct TransformationFunction<Geometry<iNumDimensions, iNumParameters>, iNumResultDimensions>
    {
        template <class TMatrix>
        Geometry<iNumResultDimensions, iNumParameters>
        operator()(
            const Geometry<iNumDimensions, iNumParameters>& geometry,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    struct MorphingFunction<Geometry<iNumDimensions, iNumParameters>, iNumResultDimensions>
    {
        Geometry<iNumResultDimensions, iNumParameters>
        operator()(
            const Geometry<iNumDimensions, iNumParameters>& geometry,
            const Function<iNumResultDimensions, iNumDimensions>& function
        ) const;
    };
}
