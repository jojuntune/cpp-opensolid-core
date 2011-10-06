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

#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Domain/DomainImplementation/GenericDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/IntervalDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/Vector2IDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/Vector3IDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/VectorXIDomain.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{   
    Domain::Domain() : _implementation(), _type(nullptr) {}
    
    Domain::Domain(const DomainImplementation* implementation) :
        _implementation(implementation), _type(&typeid(implementation)) {}
    
    Domain::Domain(const Set<Geometry>& boundaries) :
        _implementation(new GenericDomain(boundaries)), _type(&typeid(GenericDomain)) {}
    
    Domain::Domain(const Interval& interval) :
        _implementation(new IntervalDomain(interval)), _type(&typeid(IntervalDomain)) {}
    
    Set<Geometry> Domain::boundaries() const {return implementation()->boundaries();}
    
    bool Domain::isEmpty() const {return implementation()->isEmpty();}
    
    int Domain::dimensions() const {return implementation()->dimensions();}
    
    VectorXI Domain::bounds() const {return implementation()->bounds();}

    Domain Domain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return implementation()->transformed(matrix, vector);
    }
    
    Interval Conversion<Domain, Interval>::operator()(const Domain& argument) const {
        assert(!argument.isEmpty());
        assert(argument.dimensions() == 1);
        assert(argument.boundaries().size() == 2);
        return argument.bounds().value();
    }
}
