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

#ifndef OPENSOLID__DICTIONARY_HPP
#define OPENSOLID__DICTIONARY_HPP

#include <string>

#include <boost/lexical_cast.hpp>

#include <OpenSolid/Core/config.hpp>
#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Common/Transformable.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>

namespace opensolid
{
    class Object;

    template <class Derived>
    class Dictionary
    {
    private:
        Derived& derived();
        const Derived& derived() const;
        
        void getValue(const std::string& key, bool& result) const;
        void getValue(const std::string& key, int& result) const;
        void getValue(const std::string& key, double& result) const;
        void getValue(const std::string& key, std::string& result) const;
        void getValue(const std::string& key, Interval& result) const;
        void getValue(const std::string& key, MatrixXd& result) const;
        void getValue(const std::string& key, MatrixXI& result) const;
        void getValue(const std::string& key, DatumXd& result) const;
        void getValue(const std::string& key, SimplexXd& result) const;
        void getValue(const std::string& key, Function& result) const;
        void getValue(const std::string& key, Geometry& result) const;
        void getValue(const std::string& key, Domain& result) const;
        void getValue(const std::string& key, Object& result) const;

        template <class MatrixType>
        void getValue(const std::string& key, EigenBase<MatrixType>& result) const;

        template <int dimensions_, int axes_>
        void getValue(const std::string& key, Datum<dimensions_, axes_>& result) const;

        template <int dimensions_, int size_>
        void getValue(const std::string& key, Simplex<dimensions_, size_>& result) const;

        template <class Type>
        auto getValue(
            const std::string& key,
            Type& result
        ) const -> decltype(Conversion<Object, Type>()(Object()))*;
    public:
        void set(const std::string& key, bool value);
        void set(const std::string& key, int value);
        void set(const std::string& key, double value);
        void set(const std::string& key, const std::string& value);
        void set(const std::string& key, const Interval& value);
        void set(const std::string& key, const MatrixXd& value);
        void set(const std::string& key, const MatrixXI& value);
        void set(const std::string& key, const DatumXd& value);
        void set(const std::string& key, const SimplexXd& value);
        void set(const std::string& key, const Function& value);
        void set(const std::string& key, const Geometry& value);
        void set(const std::string& key, const Domain& value);
        void set(const std::string& key, const Object& value);

        template <class MatrixType>
        void set(const std::string& key, const EigenBase<MatrixType>& value);

        template <int dimensions_, int axes_>
        void set(const std::string& key, const Datum<dimensions_, axes_>& value);

        template <int dimensions_, int size_>
        void set(const std::string& key, const Simplex<dimensions_, size_>& value);

        template <class Type>
        auto set(
            const std::string& key,
            const Type& value
        ) -> decltype(Conversion<Type, Object>()(value))*;

        template <class Type>
        Type get(const std::string& key) const;

        void set(int key, bool value);
        void set(int key, int value);
        void set(int key, double value);
        void set(int key, const std::string& value);
        void set(int key, const Interval& value);
        void set(int key, const MatrixXd& value);
        void set(int key, const MatrixXI& value);
        void set(int key, const DatumXd& value);
        void set(int key, const SimplexXd& value);
        void set(int key, const Function& value);
        void set(int key, const Geometry& value);
        void set(int key, const Domain& value);
        void set(int key, const Object& value);
        
        template <class MatrixType>
        void set(int key, const EigenBase<MatrixType>& value);

        template <int dimensions_, int axes_>
        void set(int key, const Datum<dimensions_, axes_>& value);

        template <int dimensions_, int size_>
        void set(int key, const Simplex<dimensions_, size_>& value);

        template <class Type>
        auto set(
            int key,
            const Type& value
        ) -> decltype(Conversion<Type, Object>()(value))*;

        template <class Type>
        Type get(int key) const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class DictionaryError
    {
    private:
        std::string _key;
        std::string _requested_type;
    public:
        OPENSOLID_CORE_EXPORT DictionaryError(
            const std::string& key,
            const std::string& requested_type
        );
        
        OPENSOLID_CORE_EXPORT ~DictionaryError() throw();

        OPENSOLID_CORE_EXPORT std::string key() const;
        OPENSOLID_CORE_EXPORT std::string requestedType() const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Core/Object/Object.hpp>

namespace opensolid
{
    template <class Derived>
    inline Derived& Dictionary<Derived>::derived() {
        return static_cast<Derived&>(*this);
    }

    template <class Derived>
    inline const Derived& Dictionary<Derived>::derived() const {
        return static_cast<const Derived&>(*this);
    }

    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        bool& result
    ) const {derived().getValue(key, result);}

    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        int& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        double& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        std::string& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        Interval& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        MatrixXd& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        MatrixXI& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        DatumXd& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        SimplexXd& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        Function& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        Geometry& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        Domain& result
    ) const {derived().getValue(key, result);}
    
    template <class Derived>
    inline void Dictionary<Derived>::getValue(
        const std::string& key,
        Object& result
    ) const {derived().getValue(key, result);}

    template <class Derived> template <class MatrixType>
    void Dictionary<Derived>::getValue(
        const std::string& key,
        EigenBase<MatrixType>& result
    ) const {
        typedef Matrix<typename MatrixType::Scalar, Dynamic, Dynamic> DynamicMatrixType;
        DynamicMatrixType temp;
        try {
            derived().getValue(key, temp);
        } catch (const DictionaryError&) {
            derived().throwDictionaryError(key, TypeName<MatrixType>()());
        }
        int compile_time_rows = MatrixType::RowsAtCompileTime;
        int compile_time_cols = MatrixType::ColsAtCompileTime;
        if (
            (temp.rows() != compile_time_rows && compile_time_rows != Dynamic) ||
            (temp.cols() != compile_time_cols && compile_time_cols != Dynamic)
        ) {derived().throwDictionaryError(key, TypeName<MatrixType>()());}
        result.derived() = temp;
    }

    template <class Derived> template <int dimensions_, int axes_>
    void Dictionary<Derived>::getValue(
        const std::string& key,
        Datum<dimensions_, axes_>& result
    ) const {
        DatumXd temp;
        try {
            derived().getValue(key, temp);
        } catch (const DictionaryError&) {
            derived().throwDictionaryError(key, "");
        }
        if (
            (temp.dimensions() != dimensions_ && dimensions_ != Dynamic) ||
            (temp.axes() != axes_ && axes_ != Dynamic)
        ) {derived().throwDictionaryError(key, "");}
        result = temp;
    }

    template <class Derived> template <int dimensions_, int size_>
    void Dictionary<Derived>::getValue(
        const std::string& key,
        Simplex<dimensions_, size_>& result
    ) const {
        SimplexXd temp;
        try {
            derived().getValue(key, temp);
        } catch (const DictionaryError&) {
            derived().throwDictionaryError(key, "");
        }
        if (
            (temp.dimensions() != dimensions_ && dimensions_ != Dynamic) ||
            (temp.size() != size_ && size_ != Dynamic)
        ) {derived().throwDictionaryError(key, "");}
        result = temp;
    }

    template <class Derived> template <class Type>
    auto Dictionary<Derived>::getValue(
        const std::string& key,
        Type& result
    ) const -> decltype(Conversion<Object, Type>()(Object()))* {
        Object object;
        try {
            derived().getValue(key, object);
        } catch (const DictionaryError&) {
            derived().throwDictionaryError(key, TypeName<Type>()());
        }
        result = object.as<Type>();
        return nullptr;
    }

    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, bool value) {
        derived().setValue(key, value);
    }

    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, int value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, double value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const std::string& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const Interval& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const MatrixXd& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const MatrixXI& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const DatumXd& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const SimplexXd& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const Function& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const Geometry& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const Domain& value) {
        derived().setValue(key, value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(const std::string& key, const Object& value) {
        derived().setValue(key, value);
    }

    template <class Derived> template <class MatrixType>
    void Dictionary<Derived>::set(const std::string& key, const EigenBase<MatrixType>& value) {
        typedef Matrix<typename MatrixType::Scalar, Dynamic, Dynamic> DynamicMatrixType;
        derived().setValue(key, DynamicMatrixType(value));
    }

    template <class Derived> template <int dimensions_, int axes_>
    void Dictionary<Derived>::set(
        const std::string& key,
        const Datum<dimensions_, axes_>& value
    ) {derived().setValue(key, DatumXd(value));}

    template <class Derived> template <int dimensions_, int size_>
    void Dictionary<Derived>::set(
        const std::string& key,
        const Simplex<dimensions_, size_>& value
    ) {derived().setValue(key, SimplexXd(value));}

    template <class Derived> template <class Type>
    auto Dictionary<Derived>::set(
        const std::string& key,
        const Type& value
    ) -> decltype(Conversion<Type, Object>()(value))* {
        derived().setValue(key, Conversion<Type, Object>()(value));
        return nullptr;
    }

    template <class Derived> template <class Type>
    Type Dictionary<Derived>::get(const std::string& key) const {
        if (derived().has(key)) {
            Type result;
            getValue(key, result);
            return std::move(result);
        } else {
            derived().throwDictionaryError(key, TypeName<Type>()());
            return Type();
        }
    }

    template <class Derived>
    void Dictionary<Derived>::set(int key, bool value) {
        set(boost::lexical_cast<std::string>(key), value);
    }

    template <class Derived>
    void Dictionary<Derived>::set(int key, int value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, double value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const std::string& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const Interval& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const MatrixXd& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const MatrixXI& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const DatumXd& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const SimplexXd& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }

    template <class Derived> template <class Type>
    auto Dictionary<Derived>::set(
        int key,
        const Type& value
    ) -> decltype(Conversion<Type, Object>()(value))* {
        return set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const Function& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const Geometry& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const Domain& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }
    
    template <class Derived>
    void Dictionary<Derived>::set(int key, const Object& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }

    template <class Derived> template <class MatrixType>
    void Dictionary<Derived>::set(int key, const EigenBase<MatrixType>& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }

    template <class Derived> template <int dimensions_, int axes_>
    void Dictionary<Derived>::set(int key, const Datum<dimensions_, axes_>& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }

    template <class Derived> template <int dimensions_, int size_>
    void Dictionary<Derived>::set(int key, const Simplex<dimensions_, size_>& value) {
        set(boost::lexical_cast<std::string>(key), value);
    }

    template <class Derived> template <class Type>
    Type Dictionary<Derived>::get(int key) const {
        return get<Type>(boost::lexical_cast<std::string>(key));
    }
}

#endif
