/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__DECLARATIONS_HPP
#define OPENSOLID__DECLARATIONS_HPP

namespace Eigen
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    class Matrix;
}

namespace OpenSolid
{
    class Interval;

    template <class Type>
    class Set;

    template <class DerivedType, class ResultType>
    class Transformable;
    
    template <class ArgumentType>
    class TransformableMatrix;
    
    template <int dimensions_>
    class Axis;
    
    template <int dimensions_>
    class Plane;
    
    template <int dimensions_>
    class Frame;

    template <int dimensions_, int axes_>
    class CoordinateSystem;

    template <int dimensions_, int axes_>
    class Datum;
    
    template <int dimensions_, int size_>
    class Simplex;

    class Function;

    class Domain;
    
    class Geometry;
}

#endif
