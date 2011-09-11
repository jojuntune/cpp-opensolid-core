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

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_>::Datum(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, axes_>& basis
    ) : _origin(origin),
        _basis(basis),
        _inverse_matrix((_basis.transpose() * _basis).inverse() * _basis.transpose()),
        _projection_matrix(_basis * _inverse_matrix) {
        assert(origin.size() >= 1);
        assert(basis.cols() >= 1);
        assert(origin.size() == basis.rows());
    }
    
    template Datum<1, 1>::Datum(const Matrix<double, 1, 1>&, const Matrix<double, 1, 1>&);
    template Datum<1, 2>::Datum(const Matrix<double, 1, 1>&, const Matrix<double, 1, 2>&);
    template Datum<1, 3>::Datum(const Matrix<double, 1, 1>&, const Matrix<double, 1, 3>&);
    template Datum<1, Dynamic>::Datum(const Matrix<double, 1, 1>&, const Matrix<double, 1, Dynamic>&);
    template Datum<2, 1>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, 1>&);
    template Datum<2, 2>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, 2>&);
    template Datum<2, 3>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, 3>&);
    template Datum<2, Dynamic>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, Dynamic>&);
    template Datum<3, 1>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&);
    template Datum<3, 2>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, 2>&);
    template Datum<3, 3>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, 3>&);
    template Datum<3, Dynamic>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, Dynamic>&);
    template Datum<Dynamic, 1>::Datum(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&);
    template Datum<Dynamic, 2>::Datum(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 2>&);
    template Datum<Dynamic, 3>::Datum(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 3>&);
    template Datum<Dynamic, Dynamic>::Datum(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, Dynamic>&);

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_>::Datum() {}
    
    template Datum<1, 1>::Datum();
    template Datum<1, 2>::Datum();
    template Datum<1, 3>::Datum();
    template Datum<1, Dynamic>::Datum();
    template Datum<2, 1>::Datum();
    template Datum<2, 2>::Datum();
    template Datum<2, 3>::Datum();
    template Datum<2, Dynamic>::Datum();
    template Datum<3, 1>::Datum();
    template Datum<3, 2>::Datum();
    template Datum<3, 3>::Datum();
    template Datum<3, Dynamic>::Datum();
    template Datum<Dynamic, 1>::Datum();
    template Datum<Dynamic, 2>::Datum();
    template Datum<Dynamic, 3>::Datum();
    template Datum<Dynamic, Dynamic>::Datum();
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_>::Datum(const Datum<dimensions_, axes_>& other) :
        _origin(other.origin()),
        _basis(other.basis()),
        _inverse_matrix(other.inverseMatrix()),
        _projection_matrix(other.projectionMatrix()) {}
    
    template Datum<1, 1>::Datum(const Datum<1, 1>&);
    template Datum<1, 2>::Datum(const Datum<1, 2>&);
    template Datum<1, 3>::Datum(const Datum<1, 3>&);
    template Datum<1, Dynamic>::Datum(const Datum<1, Dynamic>&);
    template Datum<2, 1>::Datum(const Datum<2, 1>&);
    template Datum<2, 2>::Datum(const Datum<2, 2>&);
    template Datum<2, 3>::Datum(const Datum<2, 3>&);
    template Datum<2, Dynamic>::Datum(const Datum<2, Dynamic>&);
    template Datum<3, 1>::Datum(const Datum<3, 1>&);
    template Datum<3, 2>::Datum(const Datum<3, 2>&);
    template Datum<3, 3>::Datum(const Datum<3, 3>&);
    template Datum<3, Dynamic>::Datum(const Datum<3, Dynamic>&);
    template Datum<Dynamic, 1>::Datum(const Datum<Dynamic, 1>&);
    template Datum<Dynamic, 2>::Datum(const Datum<Dynamic, 2>&);
    template Datum<Dynamic, 3>::Datum(const Datum<Dynamic, 3>&);
    template Datum<Dynamic, Dynamic>::Datum(const Datum<Dynamic, Dynamic>&);
        
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<dimensions_, axes_>& othe
    ) {
        _origin = other.origin();
        _basis = other.basis();
        _inverse_matrix = other.inverseMatrix();
        _projection_matrix = other.projectionMatrix();
        return *this;
    }
    
    template Datum<1, 1>& Datum<1, 1>::operator=(const Datum<1, 1>&);
    template Datum<1, 2>& Datum<1, 2>::operator=(const Datum<1, 2>&);
    template Datum<1, 3>& Datum<1, 3>::operator=(const Datum<1, 3>&);
    template Datum<1, Dynamic>& Datum<1, Dynamic>::operator=(const Datum<1, Dynamic>&);
    template Datum<2, 1>& Datum<2, 1>::operator=(const Datum<2, 1>&);
    template Datum<2, 2>& Datum<2, 2>::operator=(const Datum<2, 2>&);
    template Datum<2, 3>& Datum<2, 3>::operator=(const Datum<2, 3>&);
    template Datum<2, Dynamic>& Datum<2, Dynamic>::operator=(const Datum<2, Dynamic>&);
    template Datum<3, 1>& Datum<3, 1>::operator=(const Datum<3, 1>&);
    template Datum<3, 2>& Datum<3, 2>::operator=(const Datum<3, 2>&);
    template Datum<3, 3>& Datum<3, 3>::operator=(const Datum<3, 3>&);
    template Datum<3, Dynamic>& Datum<3, Dynamic>::operator=(const Datum<3, Dynamic>&);
    template Datum<Dynamic, 1>& Datum<Dynamic, 1>::operator=(const Datum<Dynamic, 1>&);
    template Datum<Dynamic, 2>& Datum<Dynamic, 2>::operator=(const Datum<Dynamic, 2>&);
    template Datum<Dynamic, 3>& Datum<Dynamic, 3>::operator=(const Datum<Dynamic, 3>&);
    template Datum<Dynamic, Dynamic>& Datum<Dynamic, Dynamic>::operator=(const Datum<Dynamic, Dynamic>&);
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::point(double x) const {
        assert(axes() == 1);
        return origin() + basis() * x;
    }

    template Matrix<double, 1, 1> Datum<1, 1>::point(double) const;
    template Matrix<double, 1, 1> Datum<1, Dynamic>::point(double) const;
    template Matrix<double, 2, 1> Datum<2, 1>::point(double) const;
    template Matrix<double, 2, 1> Datum<2, Dynamic>::point(double) const;
    template Matrix<double, 3, 1> Datum<3, 1>::point(double) const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::point(double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 1>::point(double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::point(double) const;
        
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::point(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return origin() + basis() * Vector2d(x, y);
    }
    
    template Matrix<double, 2, 1> Datum<2, 2>::point(double, double) const;
    template Matrix<double, 2, 1> Datum<2, Dynamic>::point(double, double) const;
    template Matrix<double, 3, 1> Datum<3, 2>::point(double, double) const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::point(double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 2>::point(double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::point(double, double) const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::point(
        double x,
        double y,
        double z
    ) const {
        assert(axes() == 3);
        return origin() + basis() * Vector3d(x, y, z);
    }
    
    template Matrix<double, 3, 1> Datum<3, 3>::point(double, double, double) const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::point(double, double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 3>::point(double, double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::point(double, double, double) const;
        
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(double x) const {
        assert(axes() == 1);
        return basis() * x;
    }
    
    template Matrix<double, 1, 1> Datum<1, 1>::vector(double) const;
    template Matrix<double, 1, 1> Datum<1, Dynamic>::vector(double) const;
    template Matrix<double, 2, 1> Datum<2, 1>::vector(double) const;
    template Matrix<double, 2, 1> Datum<2, Dynamic>::vector(double) const;
    template Matrix<double, 3, 1> Datum<3, 1>::vector(double) const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::vector(double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 1>::vector(double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::vector(double) const;
        
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return basis() * Vector2d(x, y);
    }
    
    template Matrix<double, 2, 1> Datum<2, 2>::vector(double, double) const;
    template Matrix<double, 2, 1> Datum<2, Dynamic>::vector(double, double) const;
    template Matrix<double, 3, 1> Datum<3, 2>::vector(double, double) const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::vector(double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 2>::vector(double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::vector(double, double) const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::vector(
        double x,
        double y,
        double z
    ) const {
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return basis() * Vector3d(x, y, z);
    }
    
    template Matrix<double, 3, 1> Datum<3, 3>::vector(double, double, double) const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::vector(double, double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 3>::vector(double, double, double) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::vector(double, double, double) const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::direction() const {
        assert(axes() == 1);
        assert(basis().squaredNorm() == One());
        return basis();
    }

    template Matrix<double, 1, 1> Datum<1, 1>::direction() const;
    template Matrix<double, 1, 1> Datum<1, Dynamic>::direction() const;
    template Matrix<double, 2, 1> Datum<2, 1>::direction() const;
    template Matrix<double, 2, 1> Datum<2, Dynamic>::direction() const;
    template Matrix<double, 3, 1> Datum<3, 1>::direction() const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::direction() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 1>::direction() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::direction() const;

    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1, 0, dimensions_, 1>
    datumNormal(const Datum<dimensions_, axes_>& datum) {
        return orthonormalBasis(datum.basis()).col(datum.axes());
    }

    template <>
    inline Matrix<double, 2, 1, 0, 2, 1> datumNormal(const Datum<2, 1>& datum) {
        return datum.basis().unitOrthogonal();
    }

    template <>
    inline Matrix<double, 3, 1, 0, 3, 1> datumNormal(const Datum<3, 1>& datum) {
        return datum.basis().unitOrthogonal();
    }

    template <>
    inline Matrix<double, Dynamic, 1, 0, Dynamic, 1> datumNormal(
        const Datum<Dynamic, 1>& datum
    ) {return datum.basis().unitOrthogonal();}

    template <>
    inline Matrix<double, 3, 1, 0, 3, 1> datumNormal(const Datum<3, 2>& datum) {
        return datum.basis().col(0).cross(datum.basis().col(1)).normalized();
    }
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::normal() const {
        assert(axes() < dimensions());
        return datumNormal(*this);
    }

    template Matrix<double, 2, 1> Datum<2, 1>::normal() const;
    template Matrix<double, 2, 1> Datum<2, Dynamic>::normal() const;
    template Matrix<double, 3, 1> Datum<3, 1>::normal() const;
    template Matrix<double, 3, 1> Datum<3, 2>::normal() const;
    template Matrix<double, 3, 1> Datum<3, Dynamic>::normal() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 1>::normal() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, 2>::normal() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::normal() const;
    
    template <int dimensions_, int axes_>
    Axis<dimensions_> Datum<dimensions_, axes_>::xAxis() const {
        assert(basis().isUnitary());
        return Axis<dimensions_>(origin(), basis().col(0));
    }

    template Axis<1> Datum<1, 1>::xAxis() const;
    template Axis<1> Datum<1, Dynamic>::xAxis() const;
    template Axis<2> Datum<2, 1>::xAxis() const;
    template Axis<2> Datum<2, 2>::xAxis() const;
    template Axis<2> Datum<2, Dynamic>::xAxis() const;
    template Axis<3> Datum<3, 1>::xAxis() const;
    template Axis<3> Datum<3, 2>::xAxis() const;
    template Axis<3> Datum<3, 3>::xAxis() const;
    template Axis<3> Datum<3, Dynamic>::xAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 1>::xAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 2>::xAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 3>::xAxis() const;
    template Axis<Dynamic> Datum<Dynamic, Dynamic>::xAxis() const;
    
    template <int dimensions_, int axes_>
    Axis<dimensions_> Datum<dimensions_, axes_>::yAxis() const {
        assert(basis().isUnitary());
        assert(axes() >= 2);
        return Axis<dimensions_>(origin(), basis().col(1));
    }

    template Axis<2> Datum<2, 2>::yAxis() const;
    template Axis<2> Datum<2, Dynamic>::yAxis() const;
    template Axis<3> Datum<3, 2>::yAxis() const;
    template Axis<3> Datum<3, 3>::yAxis() const;
    template Axis<3> Datum<3, Dynamic>::yAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 2>::yAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 3>::yAxis() const;
    template Axis<Dynamic> Datum<Dynamic, Dynamic>::yAxis() const;
    
    template <int dimensions_, int axes_>
    Axis<dimensions_> Datum<dimensions_, axes_>::zAxis() const {
        assert(basis().isUnitary());
        assert(axes() >= 3);
        return Axis<dimensions_>(origin(), basis().col(2));
    }

    template Axis<3> Datum<3, 3>::zAxis() const;
    template Axis<3> Datum<3, Dynamic>::zAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 3>::zAxis() const;
    template Axis<Dynamic> Datum<Dynamic, Dynamic>::zAxis() const;
    
    template <int dimensions_, int axes_>
    Axis<dimensions_> Datum<dimensions_, axes_>::axis(int index) const {
        assert(basis().isUnitary());
        assert(index >= 0 && index < axes());
        return Axis<dimensions_>(origin(), basis().col(index));
    }

    template Axis<1> Datum<1, 1>::axis(int) const;
    template Axis<1> Datum<1, Dynamic>::axis(int) const;
    template Axis<2> Datum<2, 1>::axis(int) const;
    template Axis<2> Datum<2, 2>::axis(int) const;
    template Axis<2> Datum<2, Dynamic>::axis(int) const;
    template Axis<3> Datum<3, 1>::axis(int) const;
    template Axis<3> Datum<3, 2>::axis(int) const;
    template Axis<3> Datum<3, 3>::axis(int) const;
    template Axis<3> Datum<3, Dynamic>::axis(int) const;
    template Axis<Dynamic> Datum<Dynamic, 1>::axis(int) const;
    template Axis<Dynamic> Datum<Dynamic, 2>::axis(int) const;
    template Axis<Dynamic> Datum<Dynamic, 3>::axis(int) const;
    template Axis<Dynamic> Datum<Dynamic, Dynamic>::axis(int) const;
        
    template <int dimensions_, int axes_>
    Axis<dimensions_> Datum<dimensions_, axes_>::normalAxis() const {
        assert(axes() < dimensions());
        return Axis<dimensions_>(origin(), normal());
    }

    template Axis<2> Datum<2, 1>::normalAxis() const;
    template Axis<2> Datum<2, Dynamic>::normalAxis() const;
    template Axis<3> Datum<3, 1>::normalAxis() const;
    template Axis<3> Datum<3, 2>::normalAxis() const;
    template Axis<3> Datum<3, Dynamic>::normalAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 1>::normalAxis() const;
    template Axis<Dynamic> Datum<Dynamic, 2>::normalAxis() const;
    template Axis<Dynamic> Datum<Dynamic, Dynamic>::normalAxis() const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::xyPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<dimensions_>(origin(), basis().col(0), basis().col(1));
    }

    template Plane<3> Datum<3, 3>::xyPlane() const;
    template Plane<3> Datum<3, Dynamic>::xyPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 3>::xyPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::xyPlane() const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::xzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(0), basis().col(2));
    }

    template Plane<3> Datum<3, 3>::xzPlane() const;
    template Plane<3> Datum<3, Dynamic>::xzPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 3>::xzPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::xzPlane() const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::yxPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(1), basis().col(0));
    }

    template Plane<3> Datum<3, 3>::yxPlane() const;
    template Plane<3> Datum<3, Dynamic>::yxPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 3>::yxPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::yxPlane() const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::yzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(1), basis().col(2));
    }

    template Plane<3> Datum<3, 3>::yzPlane() const;
    template Plane<3> Datum<3, Dynamic>::yzPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 3>::yzPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::yzPlane() const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::zxPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(2), basis().col(0));
    }

    template Plane<3> Datum<3, 3>::zxPlane() const;
    template Plane<3> Datum<3, Dynamic>::zxPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 3>::zxPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::zxPlane() const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::zyPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(2), basis().col(1));
    }

    template Plane<3> Datum<3, 3>::zyPlane() const;
    template Plane<3> Datum<3, Dynamic>::zyPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 3>::zyPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::zyPlane() const;

    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::plane(
        int first_index,
        int second_index
    ) const {
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        assert(first_index >= 0 && first_index < 3);
        assert(second_index >= 0 && second_index < 3);
        assert(first_index != second_index);
        return Plane<3>(origin(), basis().col(first_index), basis().col(second_index));
    }

    template Plane<3> Datum<3, 3>::plane(int, int) const;
    template Plane<3> Datum<3, Dynamic>::plane(int, int) const;
    template Plane<Dynamic> Datum<Dynamic, 3>::plane(int, int) const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::plane(int, int) const;
    
    template <int dimensions_, int axes_>
    Plane<dimensions_> Datum<dimensions_, axes_>::normalPlane() const {
        assert(axes() == 1);
        return Plane<dimensions_>(origin(), direction());
    }

    template Plane<2> Datum<2, 1>::normalPlane() const;
    template Plane<2> Datum<2, Dynamic>::normalPlane() const;
    template Plane<3> Datum<3, 1>::normalPlane() const;
    template Plane<3> Datum<3, Dynamic>::normalPlane() const;
    template Plane<Dynamic> Datum<Dynamic, 1>::normalPlane() const;
    template Plane<Dynamic> Datum<Dynamic, Dynamic>::normalPlane() const;
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::orthonormalized() const {
        return Datum<dimensions_, axes_>(
            origin(),
            orthonormalBasis(basis()).leftCols(basis().cols())
        );
    }
    
    template Datum<1, 1> Datum<1, 1>::orthonormalized() const;
    template Datum<1, 2> Datum<1, 2>::orthonormalized() const;
    template Datum<1, 3> Datum<1, 3>::orthonormalized() const;
    template Datum<1, Dynamic> Datum<1, Dynamic>::orthonormalized() const;
    template Datum<2, 1> Datum<2, 1>::orthonormalized() const;
    template Datum<2, 2> Datum<2, 2>::orthonormalized() const;
    template Datum<2, 3> Datum<2, 3>::orthonormalized() const;
    template Datum<2, Dynamic> Datum<2, Dynamic>::orthonormalized() const;
    template Datum<3, 1> Datum<3, 1>::orthonormalized() const;
    template Datum<3, 2> Datum<3, 2>::orthonormalized() const;
    template Datum<3, 3> Datum<3, 3>::orthonormalized() const;
    template Datum<3, Dynamic> Datum<3, Dynamic>::orthonormalized() const;
    template Datum<Dynamic, 1> Datum<Dynamic, 1>::orthonormalized() const;
    template Datum<Dynamic, 2> Datum<Dynamic, 2>::orthonormalized() const;
    template Datum<Dynamic, 3> Datum<Dynamic, 3>::orthonormalized() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::orthonormalized() const;
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::orientation() const {
        Datum<dimensions_, axes_> result(*this);
        result._origin.setZero();
        return result;
    }
    
    template Datum<1, 1> Datum<1, 1>::orientation() const;
    template Datum<1, 2> Datum<1, 2>::orientation() const;
    template Datum<1, 3> Datum<1, 3>::orientation() const;
    template Datum<1, Dynamic> Datum<1, Dynamic>::orientation() const;
    template Datum<2, 1> Datum<2, 1>::orientation() const;
    template Datum<2, 2> Datum<2, 2>::orientation() const;
    template Datum<2, 3> Datum<2, 3>::orientation() const;
    template Datum<2, Dynamic> Datum<2, Dynamic>::orientation() const;
    template Datum<3, 1> Datum<3, 1>::orientation() const;
    template Datum<3, 2> Datum<3, 2>::orientation() const;
    template Datum<3, 3> Datum<3, 3>::orientation() const;
    template Datum<3, Dynamic> Datum<3, Dynamic>::orientation() const;
    template Datum<Dynamic, 1> Datum<Dynamic, 1>::orientation() const;
    template Datum<Dynamic, 2> Datum<Dynamic, 2>::orientation() const;
    template Datum<Dynamic, 3> Datum<Dynamic, 3>::orientation() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::orientation() const;

    template <int dimensions_, int axes_>
    Frame<dimensions_> Datum<dimensions_, axes_>::frame() const {
        return Frame<dimensions_>(origin(), orthonormalBasis(basis()));
    }
    
    template Frame<1> Datum<1, 1>::frame() const;
    template Frame<1> Datum<1, 2>::frame() const;
    template Frame<1> Datum<1, 3>::frame() const;
    template Frame<1> Datum<1, Dynamic>::frame() const;
    template Frame<2> Datum<2, 1>::frame() const;
    template Frame<2> Datum<2, 2>::frame() const;
    template Frame<2> Datum<2, 3>::frame() const;
    template Frame<2> Datum<2, Dynamic>::frame() const;
    template Frame<3> Datum<3, 1>::frame() const;
    template Frame<3> Datum<3, 2>::frame() const;
    template Frame<3> Datum<3, 3>::frame() const;
    template Frame<3> Datum<3, Dynamic>::frame() const;
    template Frame<Dynamic> Datum<Dynamic, 1>::frame() const;
    template Frame<Dynamic> Datum<Dynamic, 2>::frame() const;
    template Frame<Dynamic> Datum<Dynamic, 3>::frame() const;
    template Frame<Dynamic> Datum<Dynamic, Dynamic>::frame() const;

    MatrixXd orthonormalBasis(const MatrixXd& vectors) {
        MatrixXd result = vectors.householderQr().householderQ();
        int num_candidate_directions = min(vectors.cols(), vectors.rows() - 1);
        for (int i = 0; i < num_candidate_directions; ++i) {
            if (vectors.col(i).dot(result.col(i)) < 0) {result.col(i) = -result.col(i);}
        }
        if (result.determinant() < 0) {
            result.col(num_candidate_directions) = -result.col(num_candidate_directions);
        }
        return result;
    }
}
