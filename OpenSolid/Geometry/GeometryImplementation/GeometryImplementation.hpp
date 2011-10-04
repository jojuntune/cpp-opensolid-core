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

#ifndef OPENSOLID__GEOMETRYIMPLEMENTATION_HPP
#define OPENSOLID__GEOMETRYIMPLEMENTATION_HPP

#include <OpenSolid/config.hpp>
#include <OpenSolid/Common/ReferenceCounted.hpp>
#include <OpenSolid/Function/Function.hpp>

namespace OpenSolid
{
    class Domain;
    class Geometry;

    class GeometryImplementation : public ReferenceCounted<GeometryImplementation>
    {
    public:
        OPENSOLID_CORE_EXPORT virtual ~GeometryImplementation();
        
        OPENSOLID_CORE_EXPORT virtual Function function() const = 0;
        OPENSOLID_CORE_EXPORT virtual Domain domain() const = 0;
        
        OPENSOLID_CORE_EXPORT virtual int parameters() const;
        OPENSOLID_CORE_EXPORT virtual int dimensions() const;
        OPENSOLID_CORE_EXPORT virtual bool isConstant() const;
        OPENSOLID_CORE_EXPORT virtual VectorXI bounds() const;
        OPENSOLID_CORE_EXPORT virtual Set<Geometry> boundaries() const;

        OPENSOLID_CORE_EXPORT virtual Geometry transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;

        OPENSOLID_CORE_EXPORT virtual Geometry reversed() const;
    };
}

#endif
