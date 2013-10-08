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
 
#include <OpenSolid/Core/Simplex.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    class Simplex :
        public Transformable<Simplex<iNumDimensions, iNumVertices>>,
        public Convertible<Simplex<iNumDimensions, iNumVertices>>
    {
    private:
        Matrix<double, iNumDimensions, iNumVertices> _vertices;
    public:
        Simplex();
        
        Simplex(const Simplex<iNumDimensions, iNumVertices>& other);
        
        explicit
        Simplex(const Matrix<double, iNumDimensions, iNumVertices>& vertices);
            
        Simplex<iNumDimensions, iNumVertices>&
        operator=(const Simplex<iNumDimensions, iNumVertices>& other);
        
        Matrix<double, iNumDimensions, iNumVertices>&
        vertices();
        
        const Matrix<double, iNumDimensions, iNumVertices>&
        vertices() const;
        
        Point<iNumDimensions>
        vertex(int index) const;
        
        double
        length() const;
        
        double
        squaredLength() const;

        double
        area() const;

        double
        volume() const;
        
        Matrix<double, iNumDimensions, 1>
        vector() const;
        
        Point<iNumDimensions>
        centroid() const;
        
        Matrix<double, iNumDimensions, 1>
        normalVector() const;
        
        Simplex<iNumDimensions, 2>
        edge(int index) const;
        
        Simplex<iNumDimensions, 2>
        edge(int startIndex, int endIndex) const;

        Simplex<iNumDimensions, 3>
        face(int index) const;
        
        CoordinateSystem<iNumDimensions, iNumVertices - 1>
        coordinateSystem() const;
        
        Axis<iNumDimensions>
        axis() const;
        
        Plane3d
        plane() const;
        
        Box<iNumDimensions>
        bounds() const;
        
        bool
        operator==(const Simplex<iNumDimensions, iNumVertices>& other) const;

        static Simplex<iNumDimensions, iNumVertices>
        Unit();
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    struct NumDimensions<Simplex<iNumDimensions, iNumVertices>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumVertices, int iNumResultDimensions>
    struct ChangeDimensions<Simplex<iNumDimensions, iNumVertices>, iNumResultDimensions>
    {
        typedef Simplex<iNumResultDimensions, iNumVertices> Type;
    };

    template <int iNumDimensions, int iNumVertices>
    struct ScalingFunction<Simplex<iNumDimensions, iNumVertices>>
    {
        Simplex<iNumDimensions, iNumVertices>
        operator()(const Simplex<iNumDimensions, iNumVertices>& simplex, double scale) const;
    };

    template <int iNumDimensions, int iNumVertices>
    struct TranslationFunction<Simplex<iNumDimensions, iNumVertices>>
    {
        template <class TVector>
        Simplex<iNumDimensions, iNumVertices>
        operator()(
            const Simplex<iNumDimensions, iNumVertices>& simplex,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumVertices, int iNumResultDimensions>
    struct TransformationFunction<Simplex<iNumDimensions, iNumVertices>, iNumResultDimensions>
    {
        template <class TMatrix>
        Simplex<iNumResultDimensions, iNumVertices>
        operator()(
            const Simplex<iNumDimensions, iNumVertices>& simplex,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumVertices, int iNumResultDimensions>
    struct MorphingFunction<Simplex<iNumDimensions, iNumVertices>, iNumResultDimensions>
    {
        Simplex<iNumResultDimensions, iNumVertices>
        operator()(
            const Simplex<iNumDimensions, iNumVertices>& simplex,
            const Function<iNumResultDimensions, iNumDimensions>& function
        ) const;
    };

    template <int iNumDimensions, int iNumVertices>
    struct BoundsType<Simplex<iNumDimensions, iNumVertices>>
    {
        typedef Box<iNumDimensions> Type;
    };
}
