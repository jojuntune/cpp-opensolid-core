/*************************************************************************************
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

#include "DomainImplementation.hpp"

#include <OpenSolid/Core/Domain.hpp>

namespace opensolid
{
    class VectorXIDomain : public DomainImplementation
    {
    private:
        VectorXI _bounds;
    public:
        OPENSOLID_CORE_EXPORT VectorXIDomain(const VectorXI& bounds);

        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        OPENSOLID_CORE_EXPORT bool isEmpty() const;
        OPENSOLID_CORE_EXPORT int numDimensions() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;

        OPENSOLID_CORE_EXPORT Domain transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;
    };
}
