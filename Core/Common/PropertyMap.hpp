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

#ifndef OPENSOLID__PROPERTYMAP_HPP
#define OPENSOLID__PROPERTYMAP_HPP

#include <string>

#include <OpenSolid/Core/config.hpp>
#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Common/Convertible.hpp>
#include <OpenSolid/Core/Common/Transformable.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>

namespace OpenSolid
{
    class Object;

    template <class Derived>
    class PropertyMap
    {
    private:
        Derived& derived();
        const Derived& derived() const;

        void getProperty(const std::string& name, int& result) const;
        void getProperty(const std::string& name, double& result) const;
        void getProperty(const std::string& name, std::string& result) const;
        void getProperty(const std::string& name, Interval& result) const;
        void getProperty(const std::string& name, MatrixXd& result) const;
        void getProperty(const std::string& name, MatrixXI& result) const;
        void getProperty(const std::string& name, DatumXd& result) const;
        void getProperty(const std::string& name, SimplexXd& result) const;
        void getProperty(const std::string& name, Function& result) const;
        void getProperty(const std::string& name, Geometry& result) const;
        void getProperty(const std::string& name, Domain& result) const;
        void getProperty(const std::string& name, Object& result) const;

        template <class MatrixType>
        void getProperty(const std::string& name, EigenBase<MatrixType>& matrix) const;
    public:
        void set(const std::string& name, int value);
        void set(const std::string& name, double value);
        void set(const std::string& name, const std::string& value);
        void set(const std::string& name, const Interval& value);
        void set(const std::string& name, const MatrixXd& value);
        void set(const std::string& name, const MatrixXI& value);
        void set(const std::string& name, const DatumXd& value);
        void set(const std::string& name, const SimplexXd& value);
        void set(const std::string& name, const Function& value);
        void set(const std::string& name, const Geometry& value);
        void set(const std::string& name, const Domain& value);
        void set(const std::string& name, const Object& value);

        template <class MatrixType>
        void set(const std::string& name, const EigenBase<MatrixType>& matrix);

        template <class Type>
        Type get(const std::string& name);
    };
}

////////// Errors //////////

namespace OpenSolid
{
    class PropertyError : public Error
    {
    private:
        std::string _name;
        std::string _requested_type;
    public:
        OPENSOLID_CORE_EXPORT PropertyError(
            const std::string& name,
            const std::string& requested_type
        );

        OPENSOLID_CORE_EXPORT std::string name() const;
        OPENSOLID_CORE_EXPORT std::string requestedType() const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Core/Object/Object.hpp>

namespace OpenSolid
{
    template <class Derived>
    inline Derived& PropertyMap<Derived>::derived() {
        return static_cast<Derived&>(*this);
    }

    template <class Derived>
    inline const Derived& PropertyMap<Derived>::derived() const {
        return static_cast<const Derived&>(*this);
    }

    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, int& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, double& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, std::string& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, Interval& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, MatrixXd& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, MatrixXI& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, DatumXd& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, SimplexXd& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, Function& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, Geometry& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, Domain& result) const {
        derived().getProperty(name, result);
    }
    
    template <class Derived>
    inline void PropertyMap<Derived>::getProperty(const std::string& name, Object& result) const {
        derived().getProperty(name, result);
    }

    template <class Derived> template <class MatrixType>
    void PropertyMap<Derived>::getProperty(const std::string& name, EigenBase<MatrixType>& matrix) const {
        typedef Matrix<typename MatrixType::Scalar, Dynamic, Dynamic> DynamicMatrixType;
        DynamicMatrixType dynamic_matrix;
        try {
            derived().getProperty(name, dynamic_matrix);
        } catch (const PropertyError&) {
            derived().throwPropertyError(name, TypeName<MatrixType>()());
        }
        int compile_time_rows = MatrixType::RowsAtCompileTime;
        int compile_time_cols = MatrixType::ColsAtCompileTime;
        if (
            (dynamic_matrix.rows() != compile_time_rows && compile_time_rows != Dynamic) ||
            (dynamic_matrix.cols() != compile_time_cols && compile_time_cols != Dynamic)
        ) {derived().throwPropertyError(name, TypeName<MatrixType>()());}
        matrix.derived() = dynamic_matrix;
    }

    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, int value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, double value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const std::string& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const Interval& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const MatrixXd& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const MatrixXI& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const DatumXd& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const SimplexXd& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const Function& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const Geometry& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const Domain& value) {
        derived().setProperty(name, value);
    }
    
    template <class Derived>
    void PropertyMap<Derived>::set(const std::string& name, const Object& value) {
        derived().setProperty(name, value);
    }

    template <class Derived> template <class MatrixType>
    void PropertyMap<Derived>::set(const std::string& name, const EigenBase<MatrixType>& matrix) {
        typedef Matrix<typename MatrixType::Scalar, Dynamic, Dynamic> DynamicMatrixType;
        derived().setProperty(name, DynamicMatrixType(matrix));
    }

    template <class Derived> template <class Type>
    Type PropertyMap<Derived>::get(const std::string& name) {
        if (derived().has(name)) {
            Type result;
            getProperty(name, result);
            return std::move(result);
        } else {
            derived().throwPropertyError(name, TypeName<Type>()());
            return Type();
        }
    }
}

#endif
