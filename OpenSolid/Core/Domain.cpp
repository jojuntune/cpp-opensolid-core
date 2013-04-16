/************************************************************************************
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

/*
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
    Domain::Domain() :
        _implementation() {
    }
    
    Domain::Domain(const DomainImplementation* implementation) :
        _implementation(implementation) {
    }
    
    Domain::Domain(const Set<Geometry>& boundaries) :
        _implementation(new GenericDomain(boundaries)) {
    }
    
    Domain::Domain(Interval interval) :
        _implementation(new IntervalDomain(interval)) {
    }
    
    Domain::Domain(Interval uInterval, Interval vInterval) :
        _implementation(new RectangleDomain(Vector2I(uInterval, vInterval))) {
    }
    
    Domain::Domain(Interval uInterval, Interval vInterval, Interval wInterval) :
        _implementation(new CuboidDomain(Vector3I(uInterval, vInterval, wInterval))) {
    }
    
    Domain::Domain(const VectorXI& bounds) {
        assert(bounds.size() == 1 || bounds.size() == 2 || bounds.size() == 3);
        if (bounds.size() == 1) {
            _implementation = new IntervalDomain(bounds.value());
        } else if (bounds.size() == 2) {
            _implementation = new RectangleDomain(bounds);
        } else {
            _implementation = new CuboidDomain(bounds);
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
        if (implementation()) {
            return implementation()->isEmpty();
        } else {
            return true;
        }
    }
    
    int Domain::numDimensions() const {
        if (implementation()) {
            return implementation()->numDimensions();
        } else {
            return 0;
        }
    }
    
    VectorXI Domain::bounds() const {
        if (implementation()) {
            return implementation()->bounds();
        } else {
            return VectorXI();
        }
    }

    Domain Domain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        if (implementation()) {
            return implementation()->transformed(matrix, vector);
        } else {
            assert(false);
            return Domain();
        }
    }

    OPENSOLID_CORE_EXPORT Domain
    operator+(const Domain& domain, const VectorXd& vector);

    OPENSOLID_CORE_EXPORT Domain
    operator+(const VectorXd& vector, const Domain& domain);

    OPENSOLID_CORE_EXPORT Domain
    operator-(const Domain& domain, const VectorXd& vector);

    OPENSOLID_CORE_EXPORT Domain
    operator-(const VectorXd& vector, const Domain& domain);

    OPENSOLID_CORE_EXPORT Domain
    operator*(double scaleFactor, const Domain& domain);

    OPENSOLID_CORE_EXPORT Domain
    operator*(const Domain& domain, double scaleFactor);

    OPENSOLID_CORE_EXPORT Domain
    operator*(const MatrixXd& transformationMatrix, const Domain& domain);

    OPENSOLID_CORE_EXPORT Domain
    operator/(const Domain& domain, double divisor);

    VectorXI
    BoundsFunction<Domain>::operator()(const Domain& domain) const {
        return domain.bounds();
    }
}
*/
