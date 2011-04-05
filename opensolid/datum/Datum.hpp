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

#include <opensolid/config.hpp>

#include <opensolid/collection/List.hpp>
#include <opensolid/value/Matrix.hpp>
#include <opensolid/value/Tolerance.hpp>

namespace opensolid
{
    template <int dimensions_>
    class Axis;
    
    typedef Axis<2> Axis2d;
    typedef Axis<3> Axis3d;
    typedef Axis<4> Axis4d;
    typedef Axis<Dynamic> AxisXd;
    
    class Plane3d;
    
    template <int dimensions_>
    class Frame;
    
    typedef Frame<2> Frame2d;
    typedef Frame<3> Frame3d;
    typedef Frame<4> Frame4d;
    typedef Frame<Dynamic> FrameXd;
    
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
        typedef Matrix<double, dimensions_, 1> VectorType;
        typedef Matrix<double, dimensions_, axes_> MatrixType;
    protected:
        VectorType _origin;
        MatrixType _vectors;
        bool _normalized;

		template <int other_dimensions_, int other_axes_>
		friend class Datum;
		
		template <class DerivedType, int other_dimensions_, int other_axes_>
		friend class DatumProduct;
		
		template <class DerivedType, int other_dimensions_, int other_axes_>
		friend class DatumQuotient;
		
		template <class DerivedType, int other_dimensions_, int other_axes_>
		friend class LinearDatumProduct;
		
		template <class DerivedType, int other_dimensions_, int other_axes_>
		friend class LinearDatumQuotient;
		
		template <class DerivedType>
		void initializeVectors(const MatrixBase<DerivedType>& vectors);
    public:
        Datum();
        
        Datum(const VectorType& origin, const List<VectorType>& vectors);
        
        template <class DerivedType>
        Datum(const VectorType& origin, const MatrixBase<DerivedType>& vectors);
        
        Datum(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum(const Datum<other_dimensions_, other_axes_>& other);
        
        Datum<dimensions_, axes_>& operator=(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum<dimensions_, axes_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
        
        int dimensions() const;
        int axes() const;
        
        const VectorType& origin() const;
        const MatrixType& vectors() const;
        
        VectorType operator()(double x) const;
        VectorType operator()(double x, double y) const;
        VectorType operator()(double x, double y, double z) const;
        VectorType operator()(double x, double y, double z, double w) const;
        
        VectorType vector() const;
        VectorType vector(int index) const;
        VectorType xVector() const;
        VectorType yVector() const;
        VectorType zVector() const;
        VectorType wVector() const;
        Vector3d normalVector() const;
        
        Axis<dimensions_> axis(int index) const;
        Axis<dimensions_> xAxis() const;
        Axis<dimensions_> yAxis() const;
        Axis<dimensions_> zAxis() const;
        Axis<dimensions_> wAxis() const;
        
        Plane3d plane(int index) const;
        Plane3d yzPlane() const;
        Plane3d xzPlane() const;
        Plane3d xyPlane() const;
        
        Axis3d normalAxis() const;
        Plane3d normalPlane() const;
        
        Datum<dimensions_, axes_> flipped() const;
        
        Datum<dimensions_, axes_> translatedBy(const VectorType& displacement) const;
        Datum<dimensions_, axes_> translatedTo(const VectorType& new_origin) const;
        
        Datum<dimensions_, axes_> rotatedBy(double angle, const Vector2d& point) const;
        Datum<dimensions_, axes_> rotatedBy(double angle, const Axis3d& axis) const;
        
        Datum<dimensions_, axes_> normalized() const;
        LinearDatum<dimensions_, axes_> linear() const;
        Frame<dimensions_> inverse() const;
    };
    
    typedef Datum<Dynamic, Dynamic> DatumXd;
    
    template <int relative_dimensions_, int relative_axes_, int base_dimensions_, int base_axes_>
    Datum<base_dimensions_, relative_axes_> operator*(
        const Datum<relative_dimensions_, relative_axes_>& relative,
        const Datum<base_dimensions_, base_axes_>& base
    );
    
    template <int relative_dimensions_, int relative_axes_, int base_dimensions_, int base_axes_>
    Datum<base_axes_, relative_axes_> operator/(
        const Datum<relative_dimensions_, relative_axes_>& relative,
        const Datum<base_dimensions_, base_axes_>& base
    );
    
    template <int dimensions_>
    class Axis : public Datum<dimensions_, 1>
    {
    public:
        typedef Matrix<double, dimensions_, 1> VectorType;
        
        Axis();
        Axis(const VectorType& origin, const VectorType& vector);
        
        template <int other_dimensions_, int other_axes_>
        Axis(const Datum<other_dimensions_, other_axes_>& other);
        
        using Datum<dimensions_, 1>::operator=;
    };
    
    class Plane3d : public Datum<3, 2>
    {
    public:
        Plane3d();
        
        template <class DerivedType>
        Plane3d(const Vector3d& origin, const MatrixBase<DerivedType>& vectors);
        
        Plane3d(
            const Vector3d& origin,
            const Vector3d& first_vector,
            const Vector3d& second_vector
        );
        
        template <int other_dimensions_, int other_axes_>
        Plane3d(const Datum<other_dimensions_, other_axes_>& other);
        
        using Datum<3, 2>::operator=;
    };
    
    template <int dimensions_>
    class Frame : public Datum<dimensions_, dimensions_>
    {
    public:
        typedef Matrix<double, dimensions_, 1> VectorType;
        typedef Matrix<double, dimensions_, dimensions_> MatrixType;
        
        Frame();
        Frame(int size);
        
        Frame(const VectorType& origin);
        
        template <class DerivedType>
        Frame(const VectorType& origin, const MatrixBase<DerivedType>& vectors);
        
        Frame(const VectorType& origin, const List<VectorType>& vectors);
        
        template <int other_dimensions_, int other_axes_>
        Frame(const Datum<other_dimensions_, other_axes_>& other);
        
        using Datum<dimensions_, dimensions_>::operator=;
    };
    
    template <int dimensions_, int axes_>
    class LinearDatum
    {
    private:
        const Datum<dimensions_, axes_>& _datum;
    public:
        LinearDatum(const Datum<dimensions_, axes_>& datum);
        
        const Datum<dimensions_, axes_>& datum() const;
        
        typename Datum<dimensions_, axes_>::VectorType operator()(
            double x
        ) const;
        
        typename Datum<dimensions_, axes_>::VectorType operator()(
            double x,
            double y
        ) const;
        
        typename Datum<dimensions_, axes_>::VectorType operator()(
            double x,
            double y,
            double z
        ) const;
        
        typename Datum<dimensions_, axes_>::VectorType operator()(
            double x,
            double y,
            double z,
            double w
        ) const;
    };
    
    OPENSOLID_EXPORT MatrixXd orthogonalBasis(const MatrixXd& vectors);
}

////////// Implementation //////////

#include "DatumExpressions.hpp"

namespace opensolid
{
		
	template <int dimensions_, int axes_> template <class DerivedType>
    inline void Datum<dimensions_, axes_>::initializeVectors(
        const MatrixBase<DerivedType>& vectors
    ) {
	    if (_vectors.cols() == vectors.cols()) {
	        _vectors = vectors.derived();
	    } else {
            _vectors.leftCols(vectors.cols()) = vectors.derived();
            _vectors.rightCols(_vectors.cols() - vectors.cols()) = orthogonalBasis(
                _vectors.leftCols(vectors.cols())
            ).rightCols(_vectors.cols() - vectors.cols());
        }
    }
		
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum() {}
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(
        const VectorType& origin,
        const List<VectorType>& vectors
    ) : _origin(origin), _vectors(origin.size(), axes_ == Dynamic ? vectors.size() : axes_) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        assert(vectors.size() <= axes_ || axes_ == Dynamic);
        MatrixXd temp(origin.size(), vectors.size());
        vectors.copy(temp.colBegin());
        initializeVectors(temp);
        _normalized = _vectors.isUnitary(Tolerance::roundoff());
    }
    
    template <int dimensions_, int axes_> template <class DerivedType>
    inline Datum<dimensions_, axes_>::Datum(
        const VectorType& origin,
        const MatrixBase<DerivedType>& vectors
    ) : _origin(origin), _vectors(origin.size(), axes_ == Dynamic ? vectors.cols() : axes_) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        assert(vectors.rows() == origin.size());
        assert(vectors.cols() <= axes_ || axes_ == Dynamic);
        initializeVectors(vectors);
        _normalized = _vectors.isUnitary(Tolerance::roundoff());
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<dimensions_, axes_>& other) :
        _origin(other.origin()), _vectors(other.vectors()), _normalized(other._normalized) {}
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<other_dimensions_, other_axes_>& other) :
        _origin(other.origin()),
        _vectors(other.dimensions(), axes_ == Dynamic ? other.axes() : axes_),
        _normalized(other._normalized) {
        assert(other.dimensions() == dimensions_ || dimensions_ == Dynamic);
        assert(other_axes_ == axes_ || axes_ == Dynamic);
        initializeVectors(other.vectors());
    }
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<dimensions_, axes_>& other
    ) {
        assert(dimensions() == other.dimensions());
        assert(axes() == other.axes());
        _origin = other.origin();
        _vectors = other.vectors();
        _normalized = other._normalized;
        return *this;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(dimensions() == other.dimensions());
        assert(axes() == other.axes());
        _origin = other.origin();
        _vectors = other.vectors();
        _normalized = other._normalized;
        return *this;
    }
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::dimensions() const {return vectors().rows();}
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::axes() const {return vectors().cols();}
        
    template <int dimensions_, int axes_>
    inline const typename Datum<dimensions_, axes_>::VectorType&
    Datum<dimensions_, axes_>::origin() const {return _origin;}
    
    template <int dimensions_, int axes_>
    inline const typename Datum<dimensions_, axes_>::MatrixType&
    Datum<dimensions_, axes_>::vectors() const {return _vectors;}
        
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType  Datum<dimensions_, axes_>::operator()(
        double x
    ) const {
        assert(axes() == 1);
        return origin() + vectors() * x;
    }
        
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType  Datum<dimensions_, axes_>::operator()(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return origin() + vectors() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType Datum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z
    ) const {
        assert(axes() == 3);
        return origin() + vectors() * Vector3d(x, y, z);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType Datum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z,
        double w
    ) const {
        assert(axes() == 4);
        return origin() + vectors() * Vector4d(x, y, z, w);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::vector() const {
        assert(axes() == 1);
        return vectors();
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType Datum<dimensions_, axes_>::vector(
        int index
    ) const {
        assert(index >= 0 && index < axes());
        return vectors().col(index);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::xVector() const {
        return vectors().col(0);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::yVector() const {
        assert(axes() >= 2);
        return vectors().col(1);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::zVector() const {
        assert(axes() >= 3);
        return vectors().col(2);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::wVector() const {
        assert(axes() >= 4);
        return vectors().col(3);
    }
    
    template <int dimensions_, int axes_>    
    inline Vector3d Datum<dimensions_, axes_>::normalVector() const {
        assert(dimensions() == 3 && axes() == 2);
        return vectors().col(0).cross(vectors().col(1));
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
    inline Plane3d Datum<dimensions_, axes_>::plane(int index) const {
        assert(dimensions() == 3 && axes() == 3);
        assert(index >= 0 && index < 3);
        switch (index) {
            case 0: return yzPlane();
            case 1: return xzPlane();
            case 2: return xyPlane();
        }
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::yzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), yVector(), zVector());
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::xzPlane() const {
        assert(dimensions() == 3 && axes == 3);
        return Plane3d(origin(), xVector(), zVector());
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::xyPlane() const {
        assert(dimensions() == 3 && axes == 3);
        return Plane3d(origin(), xVector(), yVector());
    }
        
    template <int dimensions_, int axes_>
    inline Axis3d Datum<dimensions_, axes_>::normalAxis() const {
        assert(dimensions() == 3 && axes() == 2);
        return Axis3d(origin(), normalVector());
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::normalPlane() const {
        assert(dimensions() == 3 && axes() == 1);
        Vector3d x_vector = vector().unitOrthogonal();
        Vector3d y_vector = vector().cross(x_vector);
        return Plane3d(origin(), x_vector, y_vector);
    }
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::flipped() const {
        assert(axes() == 1 || (axes() == 2 && dimensions() == 3));
        if (axes() == 1) {
            return Axis<dimensions_>(origin(), -vector());
        } else {
            return Plane3d(origin(), yVector(), xVector());
        }
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::translatedBy(
        const VectorType& displacement
    ) const {
        Datum result(*this);
        result._origin += displacement;
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::translatedTo(
        const VectorType& new_origin
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
        const Axis3d& axis
    ) const {
        assert(dimensions() == 3);
        Matrix3d rotation = AngleAxisd(angle, axis.vector()).toRotationMatrix();
        return Datum<dimensions_, axes_>(
            axis.origin() + rotation * (origin() - axis.origin()),
            rotation * vectors()
        );
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::normalized() const {
        if (_normalized) {
            return *this;
        } else {
            return Datum<dimensions_, axes_>(
                origin(),
                orthogonalBasis(vectors()).leftCols(vectors.cols())
            );
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
            return Datum<dimensions_, axes_>(
                vectors().transpose() * -origin(),
                vectors().transpose()
            );
        } else {
            return Datum<dimensions_, axes_>(
                -origin() / linear(),
                vectors().inverse()
            );
        }
    }
    
    template <int relative_dimensions_, int relative_axes_, int base_dimensions_, int base_axes_>
    inline Datum<base_dimensions_, relative_axes_> operator*(
        const Datum<relative_dimensions_, relative_axes_>& relative,
        const Datum<base_dimensions_, base_axes_>& base
    ) {
        assert(relative.dimensions() == base.axes());
        return Datum<base_dimensions_, relative_axes_>(
            relative.origin() * base,
            relative.vectors() * base.linear()
        );
    }
    
    template <int relative_dimensions_, int relative_axes_, int base_dimensions_, int base_axes_>
    inline Datum<base_axes_, relative_axes_> operator/(
        const Datum<relative_dimensions_, relative_axes_>& relative,
        const Datum<base_dimensions_, base_axes_>& base
    ) {
        assert(relative.dimensions() == base.dimensions());
        return Datum<base_axes_, relative_axes_>(
            relative.origin() / base,
            relative.vectors() / base.linear()
        );
    }
    
    template <int dimensions_>
    inline Axis<dimensions_>::Axis() {}
    
    template <int dimensions_>
    inline Axis<dimensions_>::Axis(const VectorType& origin, const VectorType& vector) :
        Datum<dimensions_, 1>(origin, vector) {}
    
    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Axis<dimensions_>::Axis(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<dimensions_, 1>(other) {}
    
    inline Plane3d::Plane3d() {}
    
    template <class DerivedType>
    inline Plane3d::Plane3d(const Vector3d& origin, const MatrixBase<DerivedType>& vectors) {
        this->_origin = origin;
        assert(vectors.cols() == 1 || vectors.cols() == 2);
        if (vectors.cols() == 1) {
            Vector3d normal = vectors.derived();
            this->_vectors.col(0) = normal.unitOrthogonal();
            this->_vectors.col(1) = normal.cross(this->_vectors.col(0)).normalized();
            this->_normalized = true;
        } else {
            this->_vectors = vectors.derived();
            this->_normalized = this->_vectors.isUnitary(Tolerance::roundoff());
        }
    }
    
    inline Plane3d::Plane3d(
        const Vector3d& origin,
        const Vector3d& first_vector,
        const Vector3d& second_vector
    ) : Datum<3, 2>(origin, (Matrix<double, 3, 2>() << first_vector, second_vector).finished()) {}
    
    template <int other_dimensions_, int other_axes_>
    inline Plane3d::Plane3d(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<3, 2>(other) {}
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame() {
        this->_origin.setZero();
        this->_vectors.setIdentity();
        this->_normalized = true;
    }
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(int size) {
        assert(size == dimensions_ || dimensions_ == Dynamic);
        this->_origin = VectorType::Zero(size);
        this->_vectors = MatrixType::Identity(size, size);
        this->_normalized = true;
    }
        
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const VectorType& origin) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        this->_origin = origin;
        this->_vectors = MatrixType::Identity(origin.size(), origin.size());
        this->_normalized = true;
    }
    
    template <int dimensions_> template <class DerivedType>
    inline Frame<dimensions_>::Frame(
        const VectorType& origin,
        const MatrixBase<DerivedType>& vectors
    ) : Datum<dimensions_, dimensions_>(origin, vectors) {}
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const VectorType& origin, const List<VectorType>& vectors) :
        Datum<dimensions_, dimensions_>(origin, vectors) {}
        
    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    Frame<dimensions_>::Frame(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<dimensions_, dimensions_>(other) {}
    
    template <int dimensions_, int axes_>
    inline LinearDatum<dimensions_, axes_>::LinearDatum(const Datum<dimensions_, axes_>& datum) :
        _datum(datum) {}
     
    template <int dimensions_, int axes_>   
    inline const Datum<dimensions_, axes_>& LinearDatum<dimensions_, axes_>::datum() const {
        return _datum;
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType
    LinearDatum<dimensions_, axes_>::operator()(
        double x
    ) const {
        assert(datum().axes() == 1);
        return datum().vectors() * x;
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y
    ) const {
        assert(datum().axes() == 2);
        return datum().vectors() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z
    ) const {
        assert(datum().axes() == 3);
        return datum().vectors() * Vector3d(x, y, z);
    }

    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType
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
