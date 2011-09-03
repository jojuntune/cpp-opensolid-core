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

#ifndef OPENSOLID__DATUMEXPRESSIONS_HPP
#define OPENSOLID__DATUMEXPRESSIONS_HPP

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <class DerivedType, int dimensions_, int axes_>
    class DatumProduct;
    
    template <class DerivedType, int dimensions_, int axes_>
    class DatumQuotient;
}

namespace Eigen
{
    namespace internal
    {
        template <class DerivedType, int dimensions_, int axes_>
        struct traits<OpenSolid::DatumProduct<DerivedType, dimensions_, axes_>>
        {
            typedef Matrix<
                typename DerivedType::Scalar,
                dimensions_,
                DerivedType::ColsAtCompileTime
            > ReturnType;
            
            static const int Flags = (traits<ReturnType>::Flags | EvalBeforeNestingBit) &
                ~DirectAccessBit;
        };
        
        template <class DerivedType, int dimensions_, int axes_>
        struct traits<OpenSolid::DatumQuotient<DerivedType, dimensions_, axes_>>
        {
            typedef Matrix<
                typename DerivedType::Scalar,
                axes_,
                DerivedType::ColsAtCompileTime
            > ReturnType;
            
            static const int Flags = (traits<ReturnType>::Flags | EvalBeforeNestingBit) &
                ~DirectAccessBit;
        };
    }
}

namespace OpenSolid
{
    template <class DerivedType, int dimensions_, int axes_>
    class DatumProduct : public ReturnByValue<DatumProduct<DerivedType, dimensions_, axes_>>
    {
    private:
        const EigenBase<DerivedType>& _matrix;
        const Datum<dimensions_, axes_>& _datum;
    public:
        DatumProduct(
            const EigenBase<DerivedType>& matrix,
            const Datum<dimensions_, axes_>& datum
        );
        
        int rows() const;
        int cols() const;
        
        template <class OtherDerivedType>
        void evalTo(EigenBase<OtherDerivedType>& result) const;

        typename DerivedType::Scalar value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template <class DerivedType, int dimensions_, int axes_>
    class DatumQuotient : public ReturnByValue<DatumQuotient<DerivedType, dimensions_, axes_>>
    {
    private:
        const EigenBase<DerivedType>& _matrix;
        const Datum<dimensions_, axes_>& _datum;
    public:
        DatumQuotient(
            const EigenBase<DerivedType>& matrix,
            const Datum<dimensions_, axes_>& datum
        );
        
        int rows() const;
        int cols() const;
        
        template <class OtherDerivedType>
        void evalTo(EigenBase<OtherDerivedType>& result) const;

        typename DerivedType::Scalar value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template <class DerivedType, int dimensions_, int axes_>
    DatumProduct<DerivedType, dimensions_, axes_> operator*(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    );
    
    template <class DerivedType, int dimensions_, int axes_>
    DatumQuotient<DerivedType, dimensions_, axes_> operator/(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    );
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class DerivedType, int dimensions_, int axes_>
    DatumProduct<DerivedType, dimensions_, axes_>::DatumProduct(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    ) : _matrix(matrix), _datum(datum) {}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int DatumProduct<DerivedType, dimensions_, axes_>::rows() const {
        return _datum.dimensions();
    }
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int DatumProduct<DerivedType, dimensions_, axes_>::cols() const {
        return _matrix.cols();
    }
    
    template <class DerivedType, int dimensions_, int axes_> template <class OtherDerivedType>
    inline void DatumProduct<DerivedType, dimensions_, axes_>::evalTo(
        EigenBase<OtherDerivedType>& result
    ) const {
        typedef typename OtherDerivedType::Scalar OtherScalar;
        result.derived() = _datum.vectors().template cast<OtherScalar>() * _matrix.derived();
        result.derived().colwise() += _datum.origin().template cast<OtherScalar>();
    }

    template <class DerivedType, int dimensions_, int axes_>
    typename DerivedType::Scalar DatumProduct<DerivedType, dimensions_, axes_>::value() const {
        Matrix<typename DerivedType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }

    template <class DerivedType, int dimensions_, int axes_>
    bool DatumProduct<DerivedType, dimensions_, axes_>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class DerivedType, int dimensions_, int axes_>
    DatumQuotient<DerivedType, dimensions_, axes_>::DatumQuotient(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    ) : _matrix(matrix), _datum(datum) {}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int DatumQuotient<DerivedType, dimensions_, axes_>::rows() const {return _datum.axes();}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int DatumQuotient<DerivedType, dimensions_, axes_>::cols() const {return _matrix.cols();}
    
    template <class DerivedType, int dimensions_, int axes_> template <class OtherDerivedType>
    inline void DatumQuotient<DerivedType, dimensions_, axes_>::evalTo(
        EigenBase<OtherDerivedType>& result
    ) const {
        typedef typename OtherDerivedType::Scalar OtherScalar;
        result.derived() = _datum.vectors().transpose().template cast<OtherScalar>() * (
            _matrix.derived().colwise() - _datum.origin().template cast<OtherScalar>()
        );
        if (!_datum._normalized) {
            result.derived().applyOnTheLeft(
                (_datum.vectors().transpose() * _datum.vectors()).ldlt().solve(
                    Matrix<double, axes_, axes_>::Identity(_datum.axes(), _datum.axes())
                ).template cast<OtherScalar>()
            );
        }
    }

    template <class DerivedType, int dimensions_, int axes_>
    typename DerivedType::Scalar DatumQuotient<DerivedType, dimensions_, axes_>::value() const {
        Matrix<typename DerivedType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }

    template <class DerivedType, int dimensions_, int axes_>
    bool DatumQuotient<DerivedType, dimensions_, axes_>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class DerivedType, int dimensions_, int axes_>
    inline DatumProduct<DerivedType, dimensions_, axes_> operator*(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    ) {return DatumProduct<DerivedType, dimensions_, axes_>(matrix, datum);}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline DatumQuotient<DerivedType, dimensions_, axes_> operator/(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    ) {return DatumQuotient<DerivedType, dimensions_, axes_>(matrix, datum);}
}

#endif
