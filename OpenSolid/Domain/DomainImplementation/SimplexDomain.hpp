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

#ifndef OPENSOLID__SIMPLEXDOMAIN_HPP
#define OPENSOLID__SIMPLEXDOMAIN_HPP

#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Domain/DomainImplementation/DomainImplementation.hpp>

namespace OpenSolid
{
    class SimplexDomain : public DomainImplementation
    {
    private:
        SimplexXd _simplex;
    public:
        SimplexDomain(const SimplexXd& simplex);

        Set<Geometry> boundaries() const override;

        bool isEmpty() const override;
        int dimensions() const override;
        VectorXI bounds() const override;
        Domain transformed(const MatrixXd& matrix, const VectorXd& vector) const override;
    };
}

#endif
