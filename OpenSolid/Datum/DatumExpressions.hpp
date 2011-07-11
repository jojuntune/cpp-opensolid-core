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
    
    template <class DerivedType, int dimensions_, int axes_>
    class LinearDatumProduct;
    
    template <class DerivedType, int dimensions_, int axes_>
    class LinearDatumQuotient;
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
        
        template <class DerivedType, int dimensions_, int axes_>
        struct traits<OpenSolid::LinearDatumProduct<DerivedType, dimensions_, axes_>>
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
        struct traits<OpenSolid::LinearDatumQuotient<DerivedType, dimensions_, axes_>>
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
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
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
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
    };
    
    template <class DerivedType, int dimensions_, int axes_>
    class LinearDatumProduct :
        public ReturnByValue<LinearDatumProduct<DerivedType, dimensions_, axes_>>
    {
    private:
        const EigenBase<DerivedType>& _matrix;
        const Datum<dimensions_, axes_>& _datum;
    public:
        LinearDatumProduct(
            const EigenBase<DerivedType>& matrix,
            const Datum<dimensions_, axes_>& datum
        );
        
        int rows() const;
        int cols() const;
        
        template <class OtherDerivedType>
        void evalTo(EigenBase<OtherDerivedType>& result) const;

        typename DerivedType::Scalar value() const;
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
    };
    
    template <class DerivedType, int dimensions_, int axes_>
    class LinearDatumQuotient :
        public ReturnByValue<LinearDatumQuotient<DerivedType, dimensions_, axes_>>
    {
    private:
        const EigenBase<DerivedType>& _matrix;
        const Datum<dimensions_, axes_>& _datum;
    public:
        LinearDatumQuotient(
            const EigenBase<DerivedType>& matrix,
            const Datum<dimensions_, axes_>& datu
        );
        
        int rows() const;
        int cols() const;
        
        template <class OtherDerivedType>
        void evalTo(EigenBase<OtherDerivedType>& result) const;

        typename DerivedType::Scalar value() const;
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
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
    
    template <class DerivedType, int dimensions_, int axes_>
    LinearDatumProduct<DerivedType, dimensions_, axes_> operator*(
        const EigenBase<DerivedType>& matrix,
        const LinearDatum<dimensions_, axes_>& linear_datum
    );
    
    template <class DerivedType, int dimensions_, int axes_>
    LinearDatumQuotient<DerivedType, dimensions_, axes_> operator/(
        const EigenBase<DerivedType>& matrix,
        const LinearDatum<dimensions_, axes_>& linear_datum
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
        result.derived() = (
            _datum.vectors().template cast<typename OtherDerivedType::Scalar>() * _matrix.derived()
        ).colwise() + _datum.origin().template cast<typename OtherDerivedType::Scalar>();
    }

    template <class DerivedType, int dimensions_, int axes_>
    typename DerivedType::Scalar DatumProduct<DerivedType, dimensions_, axes_>::value() const {
        Matrix<typename DerivedType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }

    template <class DerivedType, int dimensions_, int axes_>
    bool DatumProduct<DerivedType, dimensions_, axes_>::isZero(Double precision) const {
        return this->eval().isZero(precision)
    };
    
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
        if (_datum._normalized) {
            result.derived() =
                _datum.vectors().transpose().template cast<typename OtherDerivedType::Scalar>() * (
                    _matrix.derived().colwise() -
                    _datum.origin().template cast<typename OtherDerivedType::Scalar>()
                );
        } else {
            Matrix<typename OtherDerivedType::Scalar, axes_, axes_> symmetric_inverse =
                (_datum.vectors().transpose() * _datum.vectors()).ldlt().solve(
                    Matrix<Double, axes_, axes_>::Identity(_datum.axes(), _datum.axes())
                ).template cast<typename OtherDerivedType::Scalar>();
            result.derived() = symmetric_inverse * (
                _datum.vectors().transpose().template cast<typename OtherDerivedType::Scalar>() * (
                    _matrix.derived().colwise() -
                    _datum.origin().template cast<typename OtherDerivedType::Scalar>()
                )
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
    bool DatumQuotient<DerivedType, dimensions_, axes_>::isZero(Double precision) const {
        return this->eval().isZero(precision)
    };
    
    template <class DerivedType, int dimensions_, int axes_>
    LinearDatumProduct<DerivedType, dimensions_, axes_>::LinearDatumProduct(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    ) : _matrix(matrix), _datum(datum) {}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int LinearDatumProduct<DerivedType, dimensions_, axes_>::rows() const {
        return _datum.dimensions();
    }
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int LinearDatumProduct<DerivedType, dimensions_, axes_>::cols() const {
        return _matrix.cols();
    }
    
    template <class DerivedType, int dimensions_, int axes_> template <class OtherDerivedType>
    inline void LinearDatumProduct<DerivedType, dimensions_, axes_>::evalTo(
        EigenBase<OtherDerivedType>& result
    ) const {
        result.derived() =
            _datum.vectors().template cast<typename OtherDerivedType::Scalar>() *
            _matrix.derived();
    }

    template <class DerivedType, int dimensions_, int axes_>
    typename DerivedType::Scalar LinearDatumProduct<DerivedType, dimensions_, axes_>::value() const {
        Matrix<typename DerivedType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }

    template <class DerivedType, int dimensions_, int axes_>
    bool LinearDatumProduct<DerivedType, dimensions_, axes_>::isZero(Double precision) const {
        return this->eval().isZero(precision)
    };
    
    template <class DerivedType, int dimensions_, int axes_>
    LinearDatumQuotient<DerivedType, dimensions_, axes_>::LinearDatumQuotient(
        const EigenBase<DerivedType>& matrix,
        const Datum<dimensions_, axes_>& datum
    ) : _matrix(matrix), _datum(datum) {}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int LinearDatumQuotient<DerivedType, dimensions_, axes_>::rows() const {
        return _datum.axes();
    }
    
    template <class DerivedType, int dimensions_, int axes_>
    inline int LinearDatumQuotient<DerivedType, dimensions_, axes_>::cols() const {
        return _matrix.cols();
    }
    
    template <class DerivedType, int dimensions_, int axes_> template <class OtherDerivedType>
    inline void LinearDatumQuotient<DerivedType, dimensions_, axes_>::evalTo(
        EigenBase<OtherDerivedType>& result
    ) const {
        if (_datum._normalized) {
            result.derived() =
                _datum.vectors().transpose().template cast<typename OtherDerivedType::Scalar>() *
                _matrix.derived();
        } else {
            Matrix<Double, axes_, dimensions_> temp = (
                _datum.vectors().transpose() * _datum.vectors()
            ).ldlt().solve(_datum.vectors().transpose());
            result.derived() =
                temp.template cast<typename DerivedType::Scalar>() * _matrix.derived();
        }
    }

    template <class DerivedType, int dimensions_, int axes_>
    typename DerivedType::Scalar LinearDatumQuotient<DerivedType, dimensions_, axes_>::value() const {
        Matrix<typename DerivedType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }

    template <class DerivedType, int dimensions_, int axes_>
    bool LinearDatumQuotient<DerivedType, dimensions_, axes_>::isZero(Double precision) const {
        return this->eval().isZero(precision)
    };
    
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
    
    template <class DerivedType, int dimensions_, int axes_>
    inline LinearDatumProduct<DerivedType, dimensions_, axes_> operator*(
        const EigenBase<DerivedType>& matrix,
        const LinearDatum<dimensions_, axes_>& linear_datum
    ) {return LinearDatumProduct<DerivedType, dimensions_, axes_>(matrix, linear_datum.datum());}
    
    template <class DerivedType, int dimensions_, int axes_>
    inline LinearDatumQuotient<DerivedType, dimensions_, axes_> operator/(
        const EigenBase<DerivedType>& matrix,
        const LinearDatum<dimensions_, axes_>& linear_datum
    ) {return LinearDatumQuotient<DerivedType, dimensions_, axes_>(matrix, linear_datum.datum());}
}

#endif
