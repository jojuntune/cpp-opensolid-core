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
#include <OpenSolid/Datum/Plane.hpp>

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
    template Datum<2, 1>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, 1>&);
    template Datum<2, 2>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, 2>&);
    template Datum<2, 3>::Datum(const Matrix<double, 2, 1>&, const Matrix<double, 2, 3>&);
    template Datum<3, 1>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&);
    template Datum<3, 2>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, 2>&);
    template Datum<3, 3>::Datum(const Matrix<double, 3, 1>&, const Matrix<double, 3, 3>&);
    template Datum<Dynamic, Dynamic>::Datum(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, Dynamic>&);

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_>::Datum() {}
    
    template Datum<1, 1>::Datum();
    template Datum<1, 2>::Datum();
    template Datum<1, 3>::Datum();
    template Datum<2, 1>::Datum();
    template Datum<2, 2>::Datum();
    template Datum<2, 3>::Datum();
    template Datum<3, 1>::Datum();
    template Datum<3, 2>::Datum();
    template Datum<3, 3>::Datum();
    template Datum<Dynamic, Dynamic>::Datum();
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::point(double x) const {
        assert(axes() == 1);
        return origin() + basis() * x;
    }

    template Matrix<double, 1, 1> Datum<1, 1>::point(double) const;
    template Matrix<double, 2, 1> Datum<2, 1>::point(double) const;
    template Matrix<double, 3, 1> Datum<3, 1>::point(double) const;
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
    template Matrix<double, 3, 1> Datum<3, 2>::point(double, double) const;
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
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::point(double, double, double) const;
        
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(double x) const {
        assert(axes() == 1);
        return basis() * x;
    }
    
    template Matrix<double, 1, 1> Datum<1, 1>::vector(double) const;
    template Matrix<double, 2, 1> Datum<2, 1>::vector(double) const;
    template Matrix<double, 3, 1> Datum<3, 1>::vector(double) const;
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
    template Matrix<double, 3, 1> Datum<3, 2>::vector(double, double) const;
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
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::vector(double, double, double) const;

    template<int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::xDirection() const {
        return basis().col(0);
    }

    template Matrix<double, 1, 1> Datum<1, 1>::xDirection() const;
    template Matrix<double, 2, 1> Datum<2, 1>::xDirection() const;
    template Matrix<double, 2, 1> Datum<2, 2>::xDirection() const;
    template Matrix<double, 3, 1> Datum<3, 1>::xDirection() const;
    template Matrix<double, 3, 1> Datum<3, 2>::xDirection() const;
    template Matrix<double, 3, 1> Datum<3, 3>::xDirection() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::xDirection() const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::yDirection() const {
        assert(axes() >= 2);
        return basis().col(1);
    }

    template Matrix<double, 2, 1> Datum<2, 2>::yDirection() const;
    template Matrix<double, 3, 1> Datum<3, 2>::yDirection() const;
    template Matrix<double, 3, 1> Datum<3, 3>::yDirection() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::yDirection() const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::zDirection() const {
        assert(axes() >= 3);
        return basis().col(2);
    }

    template Matrix<double, 3, 1> Datum<3, 3>::zDirection() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::zDirection() const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::direction(int index) const {
        assert(index >= 0 && index < axes());
        return basis().col(index);
    }

    template Matrix<double, 1, 1> Datum<1, 1>::direction(int) const;
    template Matrix<double, 2, 1> Datum<2, 1>::direction(int) const;
    template Matrix<double, 2, 1> Datum<2, 2>::direction(int) const;
    template Matrix<double, 3, 1> Datum<3, 1>::direction(int) const;
    template Matrix<double, 3, 1> Datum<3, 2>::direction(int) const;
    template Matrix<double, 3, 1> Datum<3, 3>::direction(int) const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::direction(int) const;
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::direction() const {
        assert(axes() == 1);
        return basis();
    }

    template Matrix<double, 1, 1> Datum<1, 1>::direction() const;
    template Matrix<double, 2, 1> Datum<2, 1>::direction() const;
    template Matrix<double, 3, 1> Datum<3, 1>::direction() const;
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
    template Matrix<double, 3, 1> Datum<3, 1>::normal() const;
    template Matrix<double, 3, 1> Datum<3, 2>::normal() const;
    template Matrix<double, Dynamic, 1> Datum<Dynamic, Dynamic>::normal() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::AxisType Datum<dimensions_, axes_>::xAxis() const {
        return AxisType(origin(), basis().col(0));
    }

    template Datum<1, 1>::AxisType Datum<1, 1>::xAxis() const;
    template Datum<2, 1>::AxisType Datum<2, 1>::xAxis() const;
    template Datum<2, 2>::AxisType Datum<2, 2>::xAxis() const;
    template Datum<3, 1>::AxisType Datum<3, 1>::xAxis() const;
    template Datum<3, 2>::AxisType Datum<3, 2>::xAxis() const;
    template Datum<3, 3>::AxisType Datum<3, 3>::xAxis() const;
    template Datum<Dynamic, Dynamic>::AxisType Datum<Dynamic, Dynamic>::xAxis() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::AxisType Datum<dimensions_, axes_>::yAxis() const {
        assert(axes() >= 2);
        return AxisType(origin(), basis().col(1));
    }

    template Datum<2, 2>::AxisType Datum<2, 2>::yAxis() const;
    template Datum<3, 2>::AxisType Datum<3, 2>::yAxis() const;
    template Datum<3, 3>::AxisType Datum<3, 3>::yAxis() const;
    template Datum<Dynamic, Dynamic>::AxisType Datum<Dynamic, Dynamic>::yAxis() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::AxisType Datum<dimensions_, axes_>::zAxis() const {
        assert(axes() >= 3);
        return AxisType(origin(), basis().col(2));
    }

    template Datum<3, 3>::AxisType Datum<3, 3>::zAxis() const;
    template Datum<Dynamic, Dynamic>::AxisType Datum<Dynamic, Dynamic>::zAxis() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::AxisType Datum<dimensions_, axes_>::axis(int index) const {
        assert(index >= 0 && index < axes());
        return AxisType(origin(), basis().col(index));
    }

    template Datum<1, 1>::AxisType Datum<1, 1>::axis(int) const;
    template Datum<2, 1>::AxisType Datum<2, 1>::axis(int) const;
    template Datum<2, 2>::AxisType Datum<2, 2>::axis(int) const;
    template Datum<3, 1>::AxisType Datum<3, 1>::axis(int) const;
    template Datum<3, 2>::AxisType Datum<3, 2>::axis(int) const;
    template Datum<3, 3>::AxisType Datum<3, 3>::axis(int) const;
    template Datum<Dynamic, Dynamic>::AxisType Datum<Dynamic, Dynamic>::axis(int) const;
        
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::AxisType Datum<dimensions_, axes_>::normalAxis() const {
        assert(axes() < dimensions());
        return AxisType(origin(), normal());
    }

    template Datum<2, 1>::AxisType Datum<2, 1>::normalAxis() const;
    template Datum<3, 1>::AxisType Datum<3, 1>::normalAxis() const;
    template Datum<3, 2>::AxisType Datum<3, 2>::normalAxis() const;
    template Datum<Dynamic, Dynamic>::AxisType Datum<Dynamic, Dynamic>::normalAxis() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::xyPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), basis().col(0), basis().col(1));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::xyPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::xyPlane() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::xzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), basis().col(0), basis().col(2));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::xzPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::xzPlane() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::yxPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), basis().col(1), basis().col(0));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::yxPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::yxPlane() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::yzPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), basis().col(1), basis().col(2));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::yzPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::yzPlane() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::zxPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), basis().col(2), basis().col(0));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::zxPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::zxPlane() const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::zyPlane() const {
        assert(dimensions() == 3 && axes() == 3);
        return Plane3d(origin(), basis().col(2), basis().col(1));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::zyPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::zyPlane() const;

    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::plane(
        int first_index,
        int second_index
    ) const {
        assert(dimensions() == 3 && axes() == 3);
        assert(first_index >= 0 && first_index < 3);
        assert(second_index >= 0 && second_index < 3);
        assert(first_index != second_index);
        return Plane3d(origin(), basis().col(first_index), basis().col(second_index));
    }

    template Datum<3, 3>::PlaneType Datum<3, 3>::plane(int, int) const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::plane(int, int) const;
    
    template <int dimensions_, int axes_>
    typename Datum<dimensions_, axes_>::PlaneType Datum<dimensions_, axes_>::normalPlane() const {
        assert(axes() == 1);
        return Plane3d(origin(), direction());
    }

    template Datum<3, 1>::PlaneType Datum<3, 1>::normalPlane() const;
    template Datum<Dynamic, Dynamic>::PlaneType Datum<Dynamic, Dynamic>::normalPlane() const;

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::scaled(double scale) const {
        return this->scaled(scale, origin());
    }
    
    template Datum<1, 1> Datum<1, 1>::scaled(double) const;
    template Datum<1, 2> Datum<1, 2>::scaled(double) const;
    template Datum<1, 3> Datum<1, 3>::scaled(double) const;
    template Datum<2, 1> Datum<2, 1>::scaled(double) const;
    template Datum<2, 2> Datum<2, 2>::scaled(double) const;
    template Datum<2, 3> Datum<2, 3>::scaled(double) const;
    template Datum<3, 1> Datum<3, 1>::scaled(double) const;
    template Datum<3, 2> Datum<3, 2>::scaled(double) const;
    template Datum<3, 3> Datum<3, 3>::scaled(double) const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::scaled(double) const;
        
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::xReversed() const {
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(0) = -result._basis.col(0);
        return result;
    }
    
    template Datum<1, 1> Datum<1, 1>::xReversed() const;
    template Datum<1, 2> Datum<1, 2>::xReversed() const;
    template Datum<1, 3> Datum<1, 3>::xReversed() const;
    template Datum<2, 1> Datum<2, 1>::xReversed() const;
    template Datum<2, 2> Datum<2, 2>::xReversed() const;
    template Datum<2, 3> Datum<2, 3>::xReversed() const;
    template Datum<3, 1> Datum<3, 1>::xReversed() const;
    template Datum<3, 2> Datum<3, 2>::xReversed() const;
    template Datum<3, 3> Datum<3, 3>::xReversed() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::xReversed() const;

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::yReversed() const {
        assert(axes() >= 2);
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(1) = -result._basis.col(1);
        return result;
    }
    
    template Datum<1, 2> Datum<1, 2>::yReversed() const;
    template Datum<1, 3> Datum<1, 3>::yReversed() const;
    template Datum<2, 2> Datum<2, 2>::yReversed() const;
    template Datum<2, 3> Datum<2, 3>::yReversed() const;
    template Datum<3, 2> Datum<3, 2>::yReversed() const;
    template Datum<3, 3> Datum<3, 3>::yReversed() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::yReversed() const;

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::zReversed() const {
        assert(axes() >= 3);
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(2) = -result._basis.col(2);
        return result;
    }
    
    template Datum<1, 3> Datum<1, 3>::zReversed() const;
    template Datum<2, 3> Datum<2, 3>::zReversed() const;
    template Datum<3, 3> Datum<3, 3>::zReversed() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::zReversed() const;

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::reversed(int index) const {
        assert(index >= 0 && index < axes());
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(index) = -result._basis.col(index);
        return result;
    }
    
    template Datum<1, 1> Datum<1, 1>::reversed(int) const;
    template Datum<1, 2> Datum<1, 2>::reversed(int) const;
    template Datum<1, 3> Datum<1, 3>::reversed(int) const;
    template Datum<2, 1> Datum<2, 1>::reversed(int) const;
    template Datum<2, 2> Datum<2, 2>::reversed(int) const;
    template Datum<2, 3> Datum<2, 3>::reversed(int) const;
    template Datum<3, 1> Datum<3, 1>::reversed(int) const;
    template Datum<3, 2> Datum<3, 2>::reversed(int) const;
    template Datum<3, 3> Datum<3, 3>::reversed(int) const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::reversed(int) const;

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::reversed() const {
        return Datum(origin(), -basis());
    }
    
    template Datum<1, 1> Datum<1, 1>::reversed() const;
    template Datum<1, 2> Datum<1, 2>::reversed() const;
    template Datum<1, 3> Datum<1, 3>::reversed() const;
    template Datum<2, 1> Datum<2, 1>::reversed() const;
    template Datum<2, 2> Datum<2, 2>::reversed() const;
    template Datum<2, 3> Datum<2, 3>::reversed() const;
    template Datum<3, 1> Datum<3, 1>::reversed() const;
    template Datum<3, 2> Datum<3, 2>::reversed() const;
    template Datum<3, 3> Datum<3, 3>::reversed() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::reversed() const;
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::normalized() const {
        return Datum<dimensions_, axes_>(
            origin(),
            orthonormalBasis(basis()).leftCols(basis().cols())
        );
    }
    
    template Datum<1, 1> Datum<1, 1>::normalized() const;
    template Datum<1, 2> Datum<1, 2>::normalized() const;
    template Datum<1, 3> Datum<1, 3>::normalized() const;
    template Datum<2, 1> Datum<2, 1>::normalized() const;
    template Datum<2, 2> Datum<2, 2>::normalized() const;
    template Datum<2, 3> Datum<2, 3>::normalized() const;
    template Datum<3, 1> Datum<3, 1>::normalized() const;
    template Datum<3, 2> Datum<3, 2>::normalized() const;
    template Datum<3, 3> Datum<3, 3>::normalized() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::normalized() const;
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::orientation() const {
        Datum<dimensions_, axes_> result(*this);
        result._origin.setZero();
        return result;
    }
    
    template Datum<1, 1> Datum<1, 1>::orientation() const;
    template Datum<1, 2> Datum<1, 2>::orientation() const;
    template Datum<1, 3> Datum<1, 3>::orientation() const;
    template Datum<2, 1> Datum<2, 1>::orientation() const;
    template Datum<2, 2> Datum<2, 2>::orientation() const;
    template Datum<2, 3> Datum<2, 3>::orientation() const;
    template Datum<3, 1> Datum<3, 1>::orientation() const;
    template Datum<3, 2> Datum<3, 2>::orientation() const;
    template Datum<3, 3> Datum<3, 3>::orientation() const;
    template Datum<Dynamic, Dynamic> Datum<Dynamic, Dynamic>::orientation() const;

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
