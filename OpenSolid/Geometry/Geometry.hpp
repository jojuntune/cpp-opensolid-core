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

#ifndef OPENSOLID__GEOMETRY_HPP
#define OPENSOLID__GEOMETRY_HPP

#include <boost/intrusive_ptr.hpp>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Evaluation/Evaluation.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Simplex/Simplex.hpp>

namespace OpenSolid
{
    class Domain;
    class GeometryImplementation;

    class Geometry : public Convertible<Geometry>, public Transformable<Geometry>
    {
    private:
        boost::intrusive_ptr<const GeometryImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Geometry();
        OPENSOLID_CORE_EXPORT Geometry(const GeometryImplementation* implementation);
        OPENSOLID_CORE_EXPORT Geometry(const Function& function, const Domain& domain);
        OPENSOLID_CORE_EXPORT Geometry(double value);
        template <class DerivedType> Geometry(const EigenBase<DerivedType>& vector);
        template <int dimensions_, int size_> Geometry(const Simplex<dimensions_, size_>& simplex);

        const GeometryImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT Function function() const;
        OPENSOLID_CORE_EXPORT Domain domain() const;
        
        template <class ArgumentType>
        Evaluation<Geometry, ArgumentType> operator()(const ArgumentType& argument) const;
        
        OPENSOLID_CORE_EXPORT int parameters() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT bool isConstant() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        OPENSOLID_CORE_EXPORT Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        OPENSOLID_CORE_EXPORT Geometry reversed() const;
    };
    
    template <>
    class Conversion<Geometry, double>
    {
    public:
        OPENSOLID_CORE_EXPORT double operator()(const Geometry& argument) const;
    };
    
    template <>
    class Conversion<Geometry, Vector2d>
    {
    public:
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Geometry& argument) const;
    };
    
    template <>
    class Conversion<Geometry, Vector3d>
    {
    public:
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Geometry& argument) const;
    };
    
    template <>
    class Conversion<Geometry, VectorXd>
    {
    public:
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Geometry& argument) const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Geometry/GeometryImplementation/ConstantGeometry.hpp>
#include <OpenSolid/Geometry/GeometryImplementation/SimplexGeometry.hpp>

namespace OpenSolid
{
    template <class DerivedType>
    Geometry::Geometry(const EigenBase<DerivedType>& vector) :
        _implementation(new ConstantGeometry(vector)), _type(&typeid(ConstantGeometry)) {}

    template <int dimensions_, int size_>
    Geometry::Geometry(const Simplex<dimensions_, size_>& simplex) :
        _implementation(new SimplexGeometry(simplex)), _type(&typeid(SimplexGeometry)) {}

    inline const GeometryImplementation* Geometry::implementation() const {
        assert(_implementation);
        return _implementation.get();
    }

    template <class ArgumentType>
    inline Evaluation<Geometry, ArgumentType> Geometry::operator()(const ArgumentType& argument) const {
        return Evaluation<Geometry, ArgumentType>(*this, argument);
    }
}

#endif
