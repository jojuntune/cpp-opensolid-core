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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Utils/ReferenceCounted.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Set.hpp>

namespace opensolid
{
    class Domain;
    class Geometry;

    class GeometryImplementation : public ReferenceCounted
    {
    public:
        virtual ~GeometryImplementation();
        
        virtual Function function() const = 0;
        virtual Domain domain() const = 0;
        
        virtual int numParameters() const;
        virtual int numDimensions() const;
        virtual void evaluate(const MapXcd& parameter_values, MapXd& results) const;
        virtual void evaluate(const MapXcI& parameter_bounds, MapXI& results) const;
        virtual bool isConstant() const;
        virtual VectorXI bounds() const;
        virtual Set<Geometry> boundaries() const;
        virtual Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        virtual Geometry reversed() const;
    };
}
