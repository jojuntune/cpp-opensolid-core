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

    template <int dimensions_, int axes_>
    class Datum
    {
    public:
        typedef Matrix<double, dimensions_, 1> VectorType;
        typedef Matrix<double, dimensions_, axes_> MatrixType;
    protected:
        VectorType _origin;
        MatrixType _unit_vectors;

		template <int other_dimensions_, int other_axes_>
		friend class Datum;
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
        const MatrixType& unitVectors() const;
        
        VectorType operator()(double x) const;
        VectorType operator()(double x, double y) const;
        VectorType operator()(double x, double y, double z) const;
        VectorType operator()(double x, double y, double z, double w) const;
        
        VectorType unitVector() const;
        VectorType unitVector(int index) const;
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
        
        template <int other_dimensions_, int other_axes_>
        Datum<other_dimensions_, axes_> operator*(
            const Datum<other_dimensions_, other_axes_>& other
        ) const;
        
        template <int other_dimensions_>
        Datum<dimensions_, axes_> operator/(const Frame<other_dimensions_>& other) const;
        
        LinearDatum<dimensions_, axes_> linear() const;
        Frame<dimensions_> inverse() const;
    };
    
    typedef Datum<Dynamic, Dynamic> DatumXd;
    
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
        
        static Axis<dimensions_> FromPoints(const VectorType& origin, const VectorType& point);
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
        
        static Plane3d FromPoints(
            const Vector3d& origin,
            const Vector3d& first_point,
            const Vector3d& second_point
        );
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
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum() {}
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(
        const VectorType& origin,
        const List<VectorType>& vectors
    ) : _origin(origin) {
        MatrixXd temp(origin.size(), vectors.size());
        for (int i = 0; i < vectors.size(); ++i) {
            assert(vectors[i].size() == origin.size());
            temp.col(i) = vectors[i];
        }
        if (axes_ == Dynamic) {
            _unit_vectors = orthogonalBasis(temp).leftCols(vectors.size());
        } else {
            _unit_vectors = orthogonalBasis(temp).leftCols(axes_);
        }
    }
    
    template <int dimensions_, int axes_> template <class DerivedType>
    inline Datum<dimensions_, axes_>::Datum(
        const VectorType& origin,
        const MatrixBase<DerivedType>& vectors
    ) : _origin(origin) {
        if (axes_ == Dynamic) {
            _unit_vectors = orthogonalBasis(vectors).leftCols(vectors.cols());
        } else {
            _unit_vectors = orthogonalBasis(vectors).leftCols(axes_);
        }
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<dimensions_, axes_>& other) : 
        _origin(other.origin()), _unit_vectors(other.unitVectors()) {}
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<other_dimensions_, other_axes_>& other) :
        _origin(other.origin()), _unit_vectors(other.unitVectors()) {}
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<dimensions_, axes_>& other
    ) {
        assert(dimensions() == other.dimensions());
        assert(axes() == other.axes());
        _origin = other.origin();
        _unit_vectors = other.unitVectors();
        return *this;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(dimensions() == other.dimensions());
        assert(axes() == other.axes());
        _origin = other.origin();
        _unit_vectors = other.unitVectors();
        return *this;
    }
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::dimensions() const {return unitVectors().rows();}
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::axes() const {return unitVectors().cols();}
        
    template <int dimensions_, int axes_>
    inline const typename Datum<dimensions_, axes_>::VectorType&
    Datum<dimensions_, axes_>::origin() const {return _origin;}
    
    template <int dimensions_, int axes_>
    inline const typename Datum<dimensions_, axes_>::MatrixType&
    Datum<dimensions_, axes_>::unitVectors() const {return _unit_vectors;}
        
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType  Datum<dimensions_, axes_>::operator()(
        double x
    ) const {
        assert(axes() == 1);
        return origin() + unitVectors() * x;
    }
        
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType  Datum<dimensions_, axes_>::operator()(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return origin() + unitVectors() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType Datum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z
    ) const {
        assert(axes() == 3);
        return origin() + unitVectors() * Vector3d(x, y, z);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType Datum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z,
        double w
    ) const {
        assert(axes() == 4);
        return origin() + unitVectors() * Vector4d(x, y, z, w);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::unitVector() const {
        assert(axes() == 1);
        return unitVectors();
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType Datum<dimensions_, axes_>::unitVector(
        int index
    ) const {
        assert(index >= 0 && index < axes());
        return unitVectors().col(index);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::xVector() const {
        return unitVectors().col(0);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::yVector() const {
        assert(axes() >= 2);
        return unitVectors().col(1);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::zVector() const {
        assert(axes() >= 3);
        return unitVectors().col(2);
    }
    
    template <int dimensions_, int axes_>    
    inline typename Datum<dimensions_, axes_>::VectorType
    Datum<dimensions_, axes_>::wVector() const {
        assert(axes() >= 4);
        return unitVectors().col(3);
    }
    
    template <int dimensions_, int axes_>    
    inline Vector3d Datum<dimensions_, axes_>::normalVector() const {
        assert(dimensions() == 3 && axes() == 2);
        return unitVectors().col(0).cross(unitVectors().col(1));
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::axis(int index) const {
        assert(index >= 0 && index < axes());
        Axis<dimensions_> result;
        result._origin = origin();
        result._unit_vectors = unitVector(index);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::xAxis() const {
        Axis<dimensions_> result;
        result._origin = origin();
        result._unit_vectors = xVector();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::yAxis() const {
        assert(axes() >= 2);
        Axis<dimensions_> result;
        result._origin = origin();
        result._unit_vectors = yVector();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::zAxis() const {
        assert(axes() >= 3);
        Axis<dimensions_> result;
        result._origin = origin();
        result._unit_vectors = zVector();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::wAxis() const {
        assert(axes() >= 4);
        Axis<dimensions_> result;
        result._origin = origin();
        result._unit_vectors = wVector();
        return result;
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
        Plane3d result;
        result._origin = origin();
        result._unit_vectors = unitVectors().rightCols(2);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::xzPlane() const {
        assert(dimensions() == 3 && axes == 3);
        Plane3d result;
        result._origin = origin();
        result._unit_vectors.leftCols<1>() = unitVectors().col(0);
        result._unit_vectors.rightCols<1>() = unitVectors().col(2);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::xyPlane() const {
        assert(dimensions() == 3 && axes == 3);
        Plane3d result;
        result._origin = origin();
        result._unit_vectors = unitVectors().leftCols(2);
        return result;
    }
        
    template <int dimensions_, int axes_>
    inline Axis3d Datum<dimensions_, axes_>::normalAxis() const {
        assert(dimensions() == 3 && axes() == 2);
        Axis3d result;
        result._origin = origin();
        result._unit_vectors = normalVector();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Plane3d Datum<dimensions_, axes_>::normalPlane() const {
        assert(dimensions() == 3 && axes() == 1);
        Plane3d result;
        result._origin = origin();
        result._unit_vectors = orthogonalBasis(unitVectors()).rightCols(2);
        return result;
    }
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::flipped() const {
        assert(axes() == 1 || (axes() == 2 && dimensions() == 3));
        Datum<dimensions_, axes_> result;
        result._origin = origin();
        if (axes() == 1) {
            result._unit_vectors = -unitVectors();
        } else {
            result._unit_vectors.col(0) = unitVectors().col(1);
            result._unit_vectors.col(1) = unitVectors().col(0);
        }
        return result;
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
        Datum<dimensions_, axes_> result;
        result._origin = point + rotation * (origin() - point);
        result._unit_vectors = rotation * unitVectors();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::rotatedBy(
        double angle,
        const Axis3d& axis
    ) const {
        assert(dimensions() == 3);
        Matrix3d rotation = AngleAxisd(angle, axis.unitVector()).toRotationMatrix();
        Datum<dimensions_, axes_> result;
        result._origin = axis.origin() + rotation * (origin() - axis.origin());
        result._unit_vectors = rotation * unitVectors();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline LinearDatum<dimensions_, axes_> Datum<dimensions_, axes_>::linear() const {
        return LinearDatum<dimensions_, axes_>(*this);
    }
        
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<other_dimensions_, axes_> Datum<dimensions_, axes_>::operator*(
        const Datum<other_dimensions_, other_axes_>& other
    ) const {
        assert(dimensions() == other.axes());
        Datum<other_dimensions_, axes_> result;
        result._origin = origin() * other;
        result._unit_vectors = unitVectors() * other.linear();
        return result;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::operator/(
        const Frame<other_dimensions_>& other
    ) const {
        assert(other.axes() == other.dimensions());
        assert(dimensions() == other.dimensions());
        Datum<dimensions_, axes_> result;
        result._origin = origin() / other;
        result._unit_vectors = unitVectors() / other.linear();
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Frame<dimensions_> Datum<dimensions_, axes_>::inverse() const {
        assert(axes() == dimensions());
        Datum<dimensions_, axes_> result;
        result._origin = unitVectors().transpose() * -origin();
        result._unit_vectors = unitVectors().transpose();
        return result;
    }
    
    template <int dimensions_>
    inline Axis<dimensions_>::Axis() {}
    
    template <int dimensions_>
    inline Axis<dimensions_>::Axis(const VectorType& origin, const VectorType& vector) {
        this->_origin = origin;
        this->_unit_vectors = vector.normalized();
    }
    
    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Axis<dimensions_>::Axis(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<dimensions_, 1>(other) {}
    
    template <int dimensions_>
    inline Axis<dimensions_> Axis<dimensions_>::FromPoints(
        const VectorType& origin,
        const VectorType& point
    ) {return Axis<dimensions_>(origin, point - origin);}
    
    inline Plane3d::Plane3d() {}
    
    template <class DerivedType>
    inline Plane3d::Plane3d(const Vector3d& origin, const MatrixBase<DerivedType>& vectors) {
        this->_origin = origin;
        assert(vectors.cols() == 1 || vectors.cols() == 2);
        if (vectors.cols() == 1) {
            this->_unit_vectors = orthogonalBasis(vectors).rightCols(2);
        } else {
            this->_unit_vectors = orthogonalBasis(vectors).leftCols(2);
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
    
    inline Plane3d Plane3d::FromPoints(
        const Vector3d& origin,
        const Vector3d& first_point,
        const Vector3d& second_point
    ) {return Plane3d(origin, first_point - origin, second_point - origin);}
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame() {
        this->_origin.setZero();
        this->_unit_vectors.setIdentity();
    }
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(int size) {
        this->_origin = VectorType::Zero(size);
        this->_unit_vectors = MatrixType::Identity(size, size);
    }
        
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const VectorType& origin) {
        this->_origin = origin;
        this->_unit_vectors = MatrixType::Identity(origin.size(), origin.size());
    }
    
    template <int dimensions_> template <class DerivedType>
    inline Frame<dimensions_>::Frame(
        const VectorType& origin,
        const MatrixBase<DerivedType>& vectors
    ) {
        this->_origin = origin;
        this->_unit_vectors = orthogonalBasis(vectors);
    }
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const VectorType& origin, const List<VectorType>& vectors) {
        this->_origin = origin;
        MatrixType temp(vectors.size(), vectors.size());
        for (int i = 0; i < vectors.size(); ++i) {temp.col(i) = vectors[i];}
        this->_unit_vectors = orthogonalBasis(temp);
    }
        
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
        return datum().unitVectors() * x;
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y
    ) const {
        assert(datum().axes() == 2);
        return datum().unitVectors() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline typename Datum<dimensions_, axes_>::VectorType
    LinearDatum<dimensions_, axes_>::operator()(
        double x,
        double y,
        double z
    ) const {
        assert(datum().axes() == 3);
        return datum().unitVectors() * Vector3d(x, y, z);
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
        return datum().unitVectors() * Vector4d(x, y, z, w);
    }
}

#endif
