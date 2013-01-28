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

#include "DomainImplementation.hpp"

#include <OpenSolid/Core/Domain.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class SimplexDomain : public DomainImplementation
    {
    private:
        Simplex<iNumDimensions, iNumDimensions + 1> _simplex;
    public:
        SimplexDomain(const Simplex<iNumDimensions, iNumDimensions + 1>& simplex);

        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;

        bool isEmpty() const;
        int numDimensions() const;
        VectorXI bounds() const;
        Domain transformed(const MatrixXd& matrix, const VectorXd& vector) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions>
    SimplexDomain<iNumDimensions>::SimplexDomain(
        const Simplex<iNumDimensions, iNumDimensions + 1>& simplex
    ) : _simplex(simplex) {
    }

    template <int iNumDimensions>
    bool SimplexDomain<iNumDimensions>::isEmpty() const {
        return false;
    }

    template <int iNumDimensions>
    int SimplexDomain<iNumDimensions>::numDimensions() const {
        return iNumDimensions;
    }

    template <int iNumDimensions>
    VectorXI SimplexDomain<iNumDimensions>::bounds() const {
        return _simplex.bounds();
    }

    template <int iNumDimensions>
    Domain SimplexDomain<iNumDimensions>::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        assert(matrix.rows() == iNumDimensions);
        assert(matrix.cols() == iNumDimensions);
        assert(vector.size() == iNumDimensions);

        return new SimplexDomain<iNumDimensions>(
            matrix.topLeftCorner<iNumDimensions, iNumDimensions>() * _simplex + vector
        );
    }
}
