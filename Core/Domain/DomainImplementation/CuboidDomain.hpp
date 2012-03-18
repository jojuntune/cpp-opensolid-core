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

#ifndef OPENSOLID__CUBOIDDOMAIN_HPP
#define OPENSOLID__CUBOIDDOMAIN_HPP

#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Domain/DomainImplementation/DomainImplementation.hpp>

namespace opensolid
{
    class CuboidDomain : public DomainImplementation
    {
    private:
        Vector3I _bounds;
    public:
        CuboidDomain(const Vector3I& bounds);

        Set<Geometry> boundaries() const;

        bool isEmpty() const;
        int dimensions() const;
        VectorXI bounds() const;
        Domain transformed(const MatrixXd& matrix, const VectorXd& vector) const;
    };
}

#endif
