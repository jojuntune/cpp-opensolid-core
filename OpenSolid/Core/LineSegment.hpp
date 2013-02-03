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

#pragma once

// Public headers
#include <OpenSolid/Core/Simplex.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class LineSegment : public Simplex<iNumDimensions, 2>
    {
    public:
        LineSegment(const Simplex<iNumDimensions, 2>& otherLineSegment);

        LineSegment(
            const Matrix<double, iNumDimensions, 1>& firstVertex,
            const Matrix<double, iNumDimensions, 1>& secondVertex
        );
    };

    typedef LineSegment<2> LineSegment2d;
    typedef LineSegment<3> LineSegment3d;

    template <>
    class LineSegment<1> : public Simplex<1, 2>
    {
    public:
        LineSegment(const Simplex<1, 2>& otherLineSegment);

        LineSegment(double startPoint, double endPoint);

        double startPoint() const;
        double endPoint() const;

        static LineSegment<1> Unit();
    };

    typedef LineSegment<1> LineSegment1d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct Bounds<LineSegment<iNumDimensions>> : public Bounds<Simplex<iNumDimensions, 2>>
    {
    };

    template <int iNumDimensions, int iNumTransformedDimensions>
    struct Transformed<LineSegment<iNumDimensions>, iNumTransformedDimensions> :
        public Transformed<Simplex<iNumDimensions, 2>, iNumTransformedDimensions>
    {
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions>
    inline LineSegment<iNumDimensions>::LineSegment(
        const Simplex<iNumDimensions, 2>& otherLineSegment
    ) : Simplex<iNumDimensions, 2>(otherLineSegment) {
    }

    template <int iNumDimensions>
    inline LineSegment<iNumDimensions>::LineSegment(
        const Matrix<double, iNumDimensions, 1>& firstVertex,
        const Matrix<double, iNumDimensions, 1>& secondVertex
    ) {
        Matrix<double, iNumDimensions, 2> vertices;
        vertices << firstVertex, secondVertex;
        *this = Simplex<iNumDimensions, 2>(vertices);
    }

    inline LineSegment<1>::LineSegment(const Simplex<1, 2>& otherLineSegment) :
        Simplex<1, 2>(otherLineSegment) {
    }

    inline LineSegment<1>::LineSegment(double startPoint, double endPoint) :
        Simplex<1, 2>(RowVector2d(startPoint, endPoint)) {
    }

    inline double LineSegment<1>::startPoint() const {
        return vertices()(0);
    }

    inline double LineSegment<1>::endPoint() const {
        return vertices()(1);
    }

    inline LineSegment<1> LineSegment<1>::Unit() {
        return LineSegment<1>(0.0, 1.0);
    }
}
