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
#include <OpenSolid/Core/Function.definitions.hpp>
#include <OpenSolid/Core/Function/MatrixReturnValue.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
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
        Function _function;
        Domain<iNumParameters> _domain;
        Box<iNumDimensions> _bounds;
    public:
        Geometry();
        
        Geometry(const Function& function, const Domain<iNumParameters>& domain);
        
        const Function&
        function() const;
        
        const Domain<iNumParameters>&
        domain() const;
        
        const Box<iNumDimensions>&
        bounds() const;
        
        template <class TArgument>
        MatrixReturnValue<TArgument>
        operator()(const TArgument& argument) const;

        Set<Geometry<iNumDimensions, iNumParameters - 1>>
        boundaries() const;
    };

    template <int iNumDimensions>
    class Geometry<iNumDimensions, 1>
    {
    private:
        Function _function;
        Interval _domain;
        Box<iNumDimensions> _bounds;
    public:
        Geometry();

        Geometry(const Function& function, Interval domain);

        const Function&
        function() const;
        
        Interval
        domain() const;
        
        const Box<iNumDimensions>&
        bounds() const;

        template <class TArgument>
        MatrixReturnValue<TArgument>
        operator()(const TArgument& argument) const;

        Set<Point<iNumDimensions>>
        boundaries() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
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

    template <int iNumDimensions, int iNumParameters, int iTransformedDimensions>
    struct TransformationFunction<Geometry<iNumDimensions, iNumParameters>, iTransformedDimensions>
    {
        typedef Geometry<iTransformedDimensions, iNumParameters> ResultType;

        template <class TMatrix>
        Geometry<iTransformedDimensions, iNumParameters>
        operator()(
            const Geometry<iNumDimensions, iNumParameters>& geometry,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumParameters, int iNumDestinationDimensions>
    struct MappingFunction<Geometry<iNumDimensions, iNumParameters>, iNumDestinationDimensions>
    {
        typedef Geometry<iNumDestinationDimensions, iNumParameters> ResultType;

        Geometry<iNumDestinationDimensions, iNumParameters>
        operator()(
            const Geometry<iNumDimensions, iNumParameters>& geometry,
            const Function& function
        ) const;
    };
}
