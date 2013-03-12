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

#include <OpenSolid/Core/Domain.hpp>

#include <OpenSolid/Core/DomainImplementation.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Geometry.hpp>

#include <OpenSolid/Core/DomainImplementation/CuboidDomain.hpp>
#include <OpenSolid/Core/DomainImplementation/GenericDomain.hpp>
#include <OpenSolid/Core/DomainImplementation/IntervalDomain.hpp>
#include <OpenSolid/Core/DomainImplementation/RectangleDomain.hpp>
#include <OpenSolid/Core/DomainImplementation/SimplexDomain.hpp>

namespace opensolid
{   
    Domain::Domain() : _implementation(), _type(nullptr) {
    }
    
    Domain::Domain(const DomainImplementation* implementation) :
        _implementation(implementation),
        _type(&typeid(implementation)) {
    }
    
    Domain::Domain(const Set<Geometry>& boundaries) :
        _implementation(new GenericDomain(boundaries)),
        _type(&typeid(GenericDomain)) {
    }
    
    Domain::Domain(Interval interval) :
        _implementation(new IntervalDomain(interval)),
        _type(&typeid(IntervalDomain)) {
    }
    
    Domain::Domain(Interval uInterval, Interval vInterval) :
        _implementation(new RectangleDomain(Vector2I(uInterval, vInterval))),
        _type(&typeid(RectangleDomain)) {
    }
    
    Domain::Domain(Interval uInterval, Interval vInterval, Interval wInterval) :
        _implementation(new CuboidDomain(Vector3I(uInterval, vInterval, wInterval))),
        _type(&typeid(CuboidDomain)) {
    }
    
    Domain::Domain(const VectorXI& bounds) {
        assert(bounds.size() == 1 || bounds.size() == 2 || bounds.size() == 3);
        if (bounds.size() == 1) {
            _implementation = new IntervalDomain(bounds.value());
            _type = &typeid(IntervalDomain);
        } else if (bounds.size() == 2) {
            _implementation = new RectangleDomain(bounds);
            _type = &typeid(RectangleDomain);
        } else {
            _implementation = new CuboidDomain(bounds);
            _type = &typeid(CuboidDomain);
        }
    }

    Domain::Domain(const Triangle2d& triangle) :
        _implementation(new SimplexDomain<2>(triangle)),
        _type(&typeid(SimplexDomain<2>)) {
    }

    Domain::Domain(const Tetrahedron3d& tetrahedron) :
        _implementation(new SimplexDomain<3>(tetrahedron)),
        _type(&typeid(SimplexDomain<3>)) {
    }

    const DomainImplementation* Domain::implementation() const {
        return _implementation.get();
    }
    
    Set<Geometry> Domain::boundaries() const {
        return implementation()->boundaries();
    }
    
    bool Domain::isEmpty() const {
        return implementation()->isEmpty();
    }
    
    int Domain::numDimensions() const {
        return implementation()->numDimensions();
    }
    
    VectorXI Domain::bounds() const {
        return implementation()->bounds();
    }

    Domain Domain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return implementation()->transformed(matrix, vector);
    }

    VectorXI Bounds<Domain>::operator()(const Domain& domain) const {
        return domain.bounds();
    }
    
    Interval Conversion<Domain, Interval>::operator()(const Domain& domain) const {
        assert(!domain.isEmpty());
        assert(domain.numDimensions() == 1);
        assert(domain.boundaries().size() == 2);
        return domain.bounds().value();
    }
}
