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

#ifndef OPENSOLID__DATUM_HPP
#define OPENSOLID__DATUM_HPP

#include <OpenSolid/config.hpp>

#include <boost/functional/hash.hpp>

#include <OpenSolid/Common/Comparison.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

#include "Traits.hpp"

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    class LinearDatum;
    
    template <class DerivedType, int dimensions_, int axes_>
    class DatumProduct;
    
    template <class DerivedType, int dimensions_, int axes_>
    class DatumQuotient;
    
    template <class DerivedType, int dimensions_, int axes_>
    class LinearDatumProduct;
    
    template <class DerivedType, int dimensions_, int axes_>
    class LinearDatumQuotient;

    template <int dimensions_, int axes_>
    class Datum
    {
    public:
        typedef Eigen::Matrix<double, dimensions_, 1> Vector;
        typedef Eigen::Matrix<double, dimensions_, axes_> Matrix;
    protected:
        Vector _origin;
        Matrix _vectors;
        bool _normalized;
        
        template <int other_dimensions_, int other_axes_>
        friend class Datum;
        
        template <int other_dimensions_>
        friend class Axis;
        
        template <int other_dimensions_>
        friend class Plane;
        
        template <int other_dimensions_>
        friend class Frame;
        
        template <class DerivedType, int other_dimensions_, int other_axes_>
        friend class DatumProduct;
        
        template <class DerivedType, int other_dimensions_, int other_axes_>
        friend class DatumQuotient;
        
        template <class DerivedType, int other_dimensions_, int other_axes_>
        friend class LinearDatumProduct;
        
        template <class DerivedType, int other_dimensions_, int other_axes_>
        friend class LinearDatumQuotient;
        
        template <class DerivedType>
        void initialize(
            const Vector& origin,
            const EigenBase<DerivedType>& vectors,
            bool normalize
        );
        
        template <int other_dimensions_, int other_axes_>
        void initialize(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        void initialize(const LinearDatum<other_dimensions_, other_axes_>& other);
    public:
        Datum();
        
        Datum(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum(const LinearDatum<other_dimensions_, other_axes_>& other);
        
        Datum<dimensions_, axes_>& operator=(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum<dimensions_, axes_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum<dimensions_, axes_>& operator=(
            const LinearDatum<other_dimensions_, other_axes_>& other
        );
        
        int dimensions() const;
        int axes() const;
        
        const Vector& origin() const;
        const Matrix& vectors() const;
        
        template <int other_dimensions_, int other_axes_>
        bool operator==(const Datum<other_dimensions_, other_axes_>& other) const;
        
        Vector operator()(double x) const;
        Vector operator()(double x, double y) const;
        Vector operator()(double x, double y, double z) const;
        Vector operator()(double x, double y, double z, double w) const;
        
        Vector vector() const;
        Vector vector(int index) const;
        Vector xVector() const;
        Vector yVector() const;
        Vector zVector() const;
        Vector wVector() const;
        Vector normalVector() const;
        
        Axis<dimensions_> axis(int index) const;
        Axis<dimensions_> xAxis() const;
        Axis<dimensions_> yAxis() const;
        Axis<dimensions_> zAxis() const;
        Axis<dimensions_> wAxis() const;
        
        Plane<dimensions_> plane(int index) const;
        Plane<3> yzPlane() const;
        Plane<3> xzPlane() const;
        Plane<3> xyPlane() const;
        
        Axis<dimensions_> normalAxis() const;
        Plane<dimensions_> normalPlane() const;
        
        Datum<dimensions_, axes_> flipped() const;
        
        Datum<dimensions_, axes_> translatedBy(const Vector& displacement) const;
        Datum<dimensions_, axes_> translatedTo(const Vector& new_origin) const;
        
        Datum<dimensions_, axes_> rotatedBy(double angle, const Vector2d& point) const;
        Datum<dimensions_, axes_> rotatedBy(double angle, const Axis<3>& axis) const;
        
        Datum<dimensions_, axes_> normalized() const;
        LinearDatum<dimensions_, axes_> linear() const;
        Frame<dimensions_> inverse() const;
    
        template <int base_dimensions_, int base_axes_>
        Datum<base_dimensions_, axes_> operator*(
            const Datum<base_dimensions_, base_axes_>& base
        ) const;
        
        template <int base_dimensions_, int base_axes_>
        Datum<base_axes_, axes_> operator/(
            const Datum<base_dimensions_, base_axes_>& base
        ) const;
    };
    
    typedef Datum<2, 2> Datum2d;
    typedef Datum<3, 3> Datum3d;
    typedef Datum<4, 4> Datum4d;
    typedef Datum<Dynamic, Dynamic> DatumXd;
    
    template <int dimensions_, int axes_>
    class LinearDatum
    {
    private:
        const Datum<dimensions_, axes_>& _datum;
    public:
        LinearDatum(const Datum<dimensions_, axes_>& datum);
        
        const Datum<dimensions_, axes_>& datum() const;
        
        typename Datum<dimensions_, axes_>::Vector operator()(
            double x
        ) const;
        
        typename Datum<dimensions_, axes_>::Vector operator()(
            double x,
            double y
        ) const;
        
        typename Datum<dimensions_, axes_>::Vector operator()(
            double x,
            double y,
            double z
        ) const;
        
        typename Datum<dimensions_, axes_>::Vector operator()(
            double x,
            double y,
            double z,
            double w
        ) const;
    };
    
    OPENSOLID_CORE_EXPORT MatrixXd orthogonalBasis(const MatrixXd& vectors);
}

////////// Implementation //////////

#include "DatumExpressions.hpp"
#include "Axis.hpp"
#include "Plane.hpp"
#include "Frame.hpp"
#include "CoordinateSystem.hpp"

namespace OpenSolid
{   
    template <int dimensions_, int axes_>
    inline std::size_t Traits<Datum<dimensions_, axes_>>::hash(
        const Datum<dimensions_, axes_>& datum
    ) {
        std::size_t result = 0;
        boost::hash_combine(result, datum.origin());
        boost::hash_combine(result, datum.vectors());
        return result;
    }
    
    template <int dimensions_, int axes_> template <class DerivedType>
    inline void Datum<dimensions_, axes_>::initialize(
        const Vector& origin,
        const EigenBase<DerivedType>& vectors,
        bool normalize
    ) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        assert(vectors.rows() == origin.size());
        assert(
            vectors.cols() == axes_ || axes_ == Dynamic || (normalize && vectors.cols() < axes_)
        );
        _origin = origin;
        if (normalize) {
            _vectors = orthogonalBasis(vectors.derived()).leftCols(
                axes_ == Dynamic ? vectors.cols() : axes_
            );
            _normalized = true;
        } else {
            _vectors.resize(origin.size(), vectors.cols());
            _vectors.leftCols(vectors.cols()) = vectors.derived();
            _normalized = _vectors.isUnitary(Comparison::tolerance());
        }
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline void Datum<dimensions_, axes_>::initialize(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(other.dimensions() == dimensions_ || dimensions_ == Dynamic);
        assert(other.axes() == axes_ || axes_ == Dynamic);
        _origin = other.origin();
        _vectors = other.vectors();
        _normalized = other._normalized;
    }
        
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline void Datum<dimensions_, axes_>::initialize(
        const LinearDatum<other_dimensions_, other_axes_>& other
    ) {
        assert(other.datum().dimensions() == dimensions_ || dimensions_ == Dynamic);
        assert(other.datum().axes() == axes_ || axes_ == Dynamic);
        _origin = Vector::Zero(other.datum().dimensions());
        _vectors = other.datum().vectors();
        _normalized = other.datum()._normalized;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum() {}
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<dimensions_, axes_>& other) {
        initialize(other);
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<other_dimensions_, other_axes_>& other) {
        initialize(other);
    }
        
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>::Datum(
        const LinearDatum<other_dimensions_, other_axes_>& other
    ) {initialize(other);}
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<dimensions_, axes_>& other
    ) {
        initialize(other);
        return *this;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        initialize(other);
        return *this;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const LinearDatum<other_dimensions_, other_axes_>& other
    ) {
        initialize(other);
        return *this;
    }
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::dimensions() const {return vectors().rows();}
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::axes() const {return vectors().cols();}
        
    template <int dimensions_, int axes_>
    inline const typename Datum<dimensions_, axes_>::Vector&
    Datum<dimensions_, axes_>::origin() const {return _origin;}
    
    template <int dimensions_, int axes_>
    inline const typename Datum<dimensions_, axes_>::Matrix&
    Datum<dimensions_, axes_>::vectors() const {return _vectors;}
        
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline bool Datum<dimensions_, axes_>::operator==(
        const Datum<other_dimensions_, other_axes_>& other
    ) const {
        assert(dimensions() == other.dimensions());
        assert(this->size() == other.size());
        return origin() == other.origin() && vectors() == other.vectors();
    }
        
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector  Datum<dimensions_, axes_>::operator()(
        double x
    ) const {
        assert(axes() == 1);
        return origin() + vectors() * x;
    }
        
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector  Datum<dimensions_, axes_>::operator()(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return origin() + vectors() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z
    ) const {
        assert(axes() == 3);
        return origin() + vectors() * Vector3d(x, y, z);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z,
        double w
    ) const {
        assert(axes() == 4);
        return origin() + vectors() * Vector4d(x, y, z, w);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::vector() const {
        assert(axes() == 1);
        return vectors();
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::vector(
        int index
    ) const {
        assert(index >= 0 && index < axes());
        return vectors().col(index);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::xVector() const {
        return vectors().col(0);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::yVector() const {
        assert(axes() >= 2);
        return vectors().col(1);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::zVector() const {
        assert(axes() >= 3);
        return vectors().col(2);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector Datum<dimensions_, axes_>::wVector() const {
        assert(axes() >= 4);
        return vectors().col(3);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector
    Datum<dimensions_, axes_>::normalVector() const {
        assert(axes() == dimensions() - 1);
        return orthogonalBasis(vectors()).col(axes());
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::axis(int index) const {
        assert(index >= 0 && index < axes());
        return Axis<dimensions_>(origin(), vector(index));
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::xAxis() const {
        return Axis<dimensions_>(origin(), xVector());
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::yAxis() const {
        return Axis<dimensions_>(origin(), yVector());
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::zAxis() const {
        return Axis<dimensions_>(origin(), zVector());
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::wAxis() const {
        return Axis<dimensions_>(origin(), wVector());
    }
        
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::plane(int index) const {
        assert(dimensions() == axes());
        assert(index >= 0 && index < dimensions());
        return Plane<dimensions_>(origin(), vector(index));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<3> Datum<dimensions_, axes_>::yzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        Plane<3>::Matrix plane_vectors;
        plane_vectors << yVector(), zVector();
        return Plane<3>(origin(), plane_vectors);
    }
    
    template <int dimensions_, int axes_>
    inline Plane<3> Datum<dimensions_, axes_>::xzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        Plane<3>::Matrix plane_vectors;
        plane_vectors << xVector(), zVector();
        return Plane<3>(origin(), plane_vectors);
    }
    
    template <int dimensions_, int axes_>
    inline Plane<3> Datum<dimensions_, axes_>::xyPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        Plane<3>::Matrix plane_vectors;
        plane_vectors << xVector(), yVector();
        return Plane<3>(origin(), plane_vectors);
    }
        
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::normalAxis() const {
        assert(axes() == dimensions() - 1);
        return Axis<dimensions_>(origin(), normalVector());
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::normalPlane() const {
        assert(axes() == 1);
        return Plane<dimensions_>(origin(), vector());
    }
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::flipped() const {
        assert(axes() == 1 || axes() == dimensions() - 1);
        Datum<dimensions_, axes_> result;
        result._origin = origin();
        if (axes() == 1) {
            result._vectors = -vectors();
            result._normalized = _normalized;
        } else {
            result._vectors = orthogonalBasis(normalVector()).rightCols(dimensions() - 1);
            result._normalized = true;
        }
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::translatedBy(
        const Vector& displacement
    ) const {
        Datum result(*this);
        result._origin += displacement;
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::translatedTo(
        const Vector& new_origin
    ) const {
        Datum result(*this);
        result._origin = new_origin;
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::rotatedBy(
        double angle,
        const Vector2d& point
    ) const {
        assert(dimensions() == 2);
        Matrix2d rotation = Matrix2d(Rotation2D<double>(angle));
        return Datum<dimensions_, axes_>(
            point + rotation * (origin() - point),
            rotation * vectors()
        );
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::rotatedBy(
        double angle,
        const Axis<3>& axis
    ) const {
        assert(dimensions() == 3);
        Matrix3d rotation = AngleAxisd(angle, axis.vector()).toRotationMatrix();
        Datum<dimensions_, axes_> result;
        result._origin = axis.origin() + rotation * (origin() - axis.origin());
        result._vectors = rotation * vectors();
        result._normalized = _normalized;
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::normalized() const {
        if (_normalized) {
            return *this;
        } else {
            Datum<dimensions_, axes_> result;
            result.initialize(origin(), vectors(), true);
            return result;
        }
    }
    
    template <int dimensions_, int axes_>
    inline LinearDatum<dimensions_, axes_> Datum<dimensions_, axes_>::linear() const {
        return LinearDatum<dimensions_, axes_>(*this);
    }
    
    template <int dimensions_, int axes_>
    inline Frame<dimensions_> Datum<dimensions_, axes_>::inverse() const {
        assert(axes() == dimensions());
        if (_normalized) {
            return Frame<dimensions_>(
                vectors().transpose() * -origin(),
                vectors().transpose()
            );
        } else {
            return Frame<dimensions_>(
                -origin() / linear(),
                vectors().inverse()
            );
        }
    }
    
    template <int dimensions_, int axes_> template <int base_dimensions_, int base_axes_>
    inline Datum<base_dimensions_, axes_> Datum<dimensions_, axes_>::operator*(
        const Datum<base_dimensions_, base_axes_>& base
    ) const {
        assert(dimensions() == base.axes());
        Datum<base_dimensions_, axes_> result;
        result.initialize(origin() * base, vectors() * base.linear(), false);
        return result;
    }
    
    template <int dimensions_, int axes_> template <int base_dimensions_, int base_axes_>
    inline Datum<base_axes_, axes_> Datum<dimensions_, axes_>::operator/(
        const Datum<base_dimensions_, base_axes_>& base
    ) const {
        assert(dimensions() == base.axes());
        Datum<base_axes_, axes_> result;
        result.initialize(origin() / base, vectors() / base.linear(), false);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline LinearDatum<dimensions_, axes_>::LinearDatum(const Datum<dimensions_, axes_>& datum) :
        _datum(datum) {}
     
    template <int dimensions_, int axes_>
    inline const Datum<dimensions_, axes_>& LinearDatum<dimensions_, axes_>::datum() const {
        return _datum;
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector
    LinearDatum<dimensions_, axes_>::operator()(
        double x
    ) const {
        assert(datum().axes() == 1);
        return datum().vectors() * x;
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y
    ) const {
        assert(datum().axes() == 2);
        return datum().vectors() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z
    ) const {
        assert(datum().axes() == 3);
        return datum().vectors() * Vector3d(x, y, z);
    }

    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::Vector
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z,
        double w
    ) const {
        assert(datum().axes() == 4);
        return datum().vectors() * Vector4d(x, y, z, w);
    }
}

#endif
