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

#include <OpenSolid/Core/Domain.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Geometry.declarations.hpp>
#include <OpenSolid/Core/Geometry/BoundsType.definitions.hpp>
#include <OpenSolid/Core/Geometry/Transformable.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Domain :
        public Transformable<Domain<iNumDimensions>>,
        public Convertible<Domain<iNumDimensions>>
    {
    private:
        SpatialSet<Geometry<iNumDimensions, iNumDimensions - 1>> _boundaries;
    public:
        Domain();

        explicit
        Domain(const SpatialSet<Geometry<iNumDimensions, iNumDimensions - 1>>& boundaries);
        
        const SpatialSet<Geometry<iNumDimensions, iNumDimensions - 1>>&
        boundaries() const;

        bool
        isEmpty() const;

        Box<iNumDimensions>
        bounds() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<Domain<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct ScalingFunction<Domain<iNumDimensions>>
    {
        Domain<iNumDimensions>
        operator()(const Domain<iNumDimensions>& domain, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Domain<iNumDimensions>>
    {
        template <class TVector>
        Domain<iNumDimensions>
        operator()(const Domain<iNumDimensions>& domain, const EigenBase<TVector>& vector) const;
    };

    template <int iNumDimensions>
    struct TransformationFunction<Domain<iNumDimensions>, iNumDimensions>
    {
        template <class TMatrix>
        Domain<iNumDimensions>
        operator()(const Domain<iNumDimensions>& domain, const EigenBase<TMatrix>& matrix) const;
    };

    template <int iNumDimensions>
    struct MorphingFunction<Domain<iNumDimensions>, iNumDimensions>
    {
        Domain<iNumDimensions>
        operator()(
            const Domain<iNumDimensions>& domain,
            const Function<iNumDimensions, iNumDimensions>& function
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsType<Domain<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };
}
