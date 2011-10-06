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

#ifndef OPENSOLID__CONSTANTGEOMETRY_HPP
#define OPENSOLID__CONSTANTGEOMETRY_HPP

#include <OpenSolid/config.hpp>
#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Geometry/GeometryImplementation/GeometryImplementation.hpp>

namespace OpenSolid
{
    class ConstantGeometry : public GeometryImplementation
    {
    private:
        VectorXd _vector;
    public:
        OPENSOLID_CORE_EXPORT ConstantGeometry(const VectorXd& vector);

        Function function() const;
        Domain domain() const;
        
        int parameters() const;
        int dimensions() const;
        bool isConstant() const;
        VectorXI bounds() const;
        Set<Geometry> boundaries() const;
        Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        Geometry reversed() const;
    };
}

#endif
