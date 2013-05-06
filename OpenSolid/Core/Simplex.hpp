/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>
 
#include <OpenSolid/Core/Simplex.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    inline
    Simplex<iNumDimensions, iNumVertices>::Simplex() {
        _vertices.setZero();
    }

    template <int iNumDimensions, int iNumVertices>
    inline
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Simplex<iNumDimensions, iNumVertices>& other
    ) : _vertices(other.vertices()) {
    }

    template <int iNumDimensions, int iNumVertices>
    inline
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Matrix<double, iNumDimensions, iNumVertices>& vertices
    ) : _vertices(vertices) {
    }
    
    template <int iNumDimensions, int iNumVertices> 
    inline Simplex<iNumDimensions, iNumVertices>&
    Simplex<iNumDimensions, iNumVertices>::operator=(
        const Simplex<iNumDimensions, iNumVertices>& other
    ) {
        vertices() = other.vertices();
        return *this;
    }

    template <int iNumDimensions, int iNumVertices>
    inline Matrix<double, iNumDimensions, iNumVertices>&
    Simplex<iNumDimensions, iNumVertices>::vertices() {
        return _vertices;
    }

    template <int iNumDimensions, int iNumVertices>
    inline const Matrix<double, iNumDimensions, iNumVertices>&
    Simplex<iNumDimensions, iNumVertices>::vertices() const {
        return _vertices;
    }

    template <int iNumDimensions, int iNumVertices>
    inline Point<iNumDimensions>
    Simplex<iNumDimensions, iNumVertices>::vertex(int index) const {
        return Point<iNumDimensions>(vertices().col(index));
    }

    template <>
    inline double
    Simplex<1, 2>::length() const {
        return abs(vertices()(0, 1) - vertices()(0, 0));
    }

    template <>
    inline double
    Simplex<2, 2>::length() const {
        return (vertices().col(1) - vertices().col(0)).norm();
    }

    template <>
    inline double
    Simplex<3, 2>::length() const {
        return (vertices().col(1) - vertices().col(0)).norm();
    }

    template <>
    inline double
    Simplex<1, 2>::squaredLength() const {
        double length = vertices()(0, 1) - vertices()(0, 0);
        return length * length;
    }

    template <>
    inline double
    Simplex<2, 2>::squaredLength() const {
        return (vertices().col(1) - vertices().col(0)).squaredNorm();
    }

    template <>
    inline double
    Simplex<3, 2>::squaredLength() const {
        return (vertices().col(1) - vertices().col(0)).squaredNorm();
    }

    template <>
    inline double
    Simplex<2, 3>::area() const {
        return (vertices().rightCols<2>().colwise() - vertices().col(0)).determinant() / 2;
    }

    template <>
    inline double
    Simplex<3, 3>::area() const {
        Vector3d firstEdge = vertices().col(1) - vertices().col(0);
        Vector3d secondEdge = vertices().col(2) - vertices().col(0);
        return firstEdge.cross(secondEdge).norm() / 2;
    }

    template <>
    inline double
    Simplex<3, 4>::volume() const {
        return (vertices().rightCols<3>().colwise() - vertices().col(0)).determinant() / 6;
    }

    template <>
    inline Matrix1d
    Simplex<1, 2>::vector() const {
        return vertices().col(1) - vertices().col(0);
    }

    template <>
    inline Vector2d
    Simplex<2, 2>::vector() const {
        return vertices().col(1) - vertices().col(0);
    }

    template <>
    inline Vector3d
    Simplex<3, 2>::vector() const {
        return vertices().col(1) - vertices().col(0);
    }
    
    template <int iNumDimensions, int iNumVertices>
    inline Point<iNumDimensions>
    Simplex<iNumDimensions, iNumVertices>::centroid() const {
        return Point<iNumDimensions>(vertices().rowwise().mean());
    }

    template <>
    inline Vector2d
    Simplex<2, 2>::normalVector() const {
        return (vertices().col(1) - vertices().col(0)).unitOrthogonal();
    }

    template <>
    inline Vector3d
    Simplex<3, 2>::normalVector() const {
        return (vertices().col(1) - vertices().col(0)).unitOrthogonal();
    }

    template <>
    inline Vector3d
    Simplex<3, 3>::normalVector() const {
        Vector3d firstEdge = vertices().col(1) - vertices().col(0);
        Vector3d secondEdge = vertices().col(2) - vertices().col(0);
        return firstEdge.cross(secondEdge).normalized();
    }
    
    template <>
    inline Simplex<2, 2>
    Simplex<2, 3>::edge(int index) const {
        assert(0 <= index && index < 3);
        Matrix2d edgeVertices;
        edgeVertices << vertices().col(index), vertices().col((index + 1) % 3);
        return Simplex<2, 2>(edgeVertices);
    }
    
    template <>
    inline Simplex<3, 2>
    Simplex<3, 3>::edge(int index) const {
        assert(0 <= index && index < 3);
        Matrix<double, 3, 2> edgeVertices;
        edgeVertices << vertices().col(index), vertices().col((index + 1) % 3);
        return Simplex<3, 2>(edgeVertices);
    }
    
    template <>
    inline Simplex<2, 2>
    Simplex<2, 3>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < 3);
        assert(0 <= endIndex && endIndex < 3);
        assert(startIndex != endIndex);
        Matrix2d edgeVertices;
        edgeVertices << vertices().col(startIndex), vertices().col(endIndex);
        return Simplex<2, 2>(edgeVertices);
    }
    
    template <>
    inline Simplex<3, 2>
    Simplex<3, 3>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < 3);
        assert(0 <= endIndex && endIndex < 3);
        assert(startIndex != endIndex);
        Matrix<double, 3, 2> edgeVertices;
        edgeVertices << vertices().col(startIndex), vertices().col(endIndex);
        return Simplex<3, 2>(edgeVertices);
    }
    
    template <>
    inline Simplex<3, 2>
    Simplex<3, 4>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < 4);
        assert(0 <= endIndex && endIndex < 4);
        assert(startIndex != endIndex);
        Matrix<double, 3, 2> edgeVertices;
        edgeVertices << vertices().col(startIndex), vertices().col(endIndex);
        return Simplex<3, 2>(edgeVertices);
    }
    
    template <>
    inline Simplex<3, 3>
    Simplex<3, 4>::face(int index) const {
        Matrix3d faceVertices;
        RowVector3i indices;
        for (int i = 0; i < 3; ++i) {
            indices(i) = (index + 1 + i) % 4;
        }
        if (index % 2 != 0) {
            indices.tail(2).reverseInPlace();
        }
        for (int i = 0; i < 3; ++i) {
            faceVertices.col(i) = vertices().col(indices(i));
        }
        return Simplex<3, 3>(faceVertices);
    }

    template <int iNumDimensions, int iNumVertices>
    Datum<iNumDimensions, iNumVertices - 1>
    Simplex<iNumDimensions, iNumVertices>::datum() const {
        return Datum<iNumDimensions, iNumVertices - 1>(
            vertex(0),
            vertices().template rightCols<iNumVertices - 1>().colwise() - vertices().col(0)
        );
    }

    template <>
    inline Datum<2, 1>
    Simplex<2, 2>::axis() const {
        return datum().normalized();
    }

    template <>
    inline Datum<3, 1>
    Simplex<3, 2>::axis() const {
        return datum().normalized();
    }

    template <>
    inline Datum<3, 2>
    Simplex<3, 3>::plane() const {
        return datum().normalized();
    }
    
    template <int iNumDimensions, int iNumVertices>
    Box<iNumDimensions>
    Simplex<iNumDimensions, iNumVertices>::bounds() const {
        return Box<iNumDimensions>(
            vertices().rowwise().minCoeff().hull(vertices().rowwise().maxCoeff())
        );
    }
        
    template <int iNumDimensions, int iNumVertices>
    bool
    Simplex<iNumDimensions, iNumVertices>::operator==(
        const Simplex<iNumDimensions, iNumVertices>& other
    ) const {
        return vertices() == other.vertices();
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Unit() {
        Matrix<double, iNumDimensions, iNumVertices> vertexMatrix;
        vertexMatrix.col(0).setZero();
        vertexMatrix.template rightCols<iNumVertices - 1>().setIdentity();
        return Simplex<iNumDimensions, iNumVertices>(vertexMatrix);
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>
    ScalingFunction<Simplex<iNumDimensions, iNumVertices>>::operator()(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        double scale
    ) const {
        return Simplex<iNumDimensions, iNumVertices>(scale * simplex.vertices());
    }

    template <int iNumDimensions, int iNumVertices> template <class TVector>
    Simplex<iNumDimensions, iNumVertices>
    TranslationFunction<Simplex<iNumDimensions, iNumVertices>>::operator()(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        const EigenBase<TVector>& vector
    ) const {
        return Simplex<iNumDimensions, iNumVertices>(
            simplex.vertices().colwise() + vector.derived()
        );
    }

    template <int iNumDimensions, int iNumVertices, int iNumTransformedDimensions>
    template <class TMatrix>
    Simplex<iNumTransformedDimensions, iNumVertices>
    TransformationFunction<Simplex<iNumDimensions, iNumVertices>, iNumTransformedDimensions>::operator()(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Simplex<iNumTransformedDimensions, iNumVertices>(
            matrix.derived() * simplex.vertices()
        );
    }

    template <int iNumDimensions, int iNumVertices, int iNumDestinationDimensions>
    inline Simplex<iNumDestinationDimensions, iNumVertices>
    MorphingFunction<Simplex<iNumDimensions, iNumVertices>, iNumDestinationDimensions>::operator()(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        const Function& function
    ) const {
        bool validInput = function.numParameters() == iNumDimensions;
        bool validOutput = function.numDimensions() == iNumDestinationDimensions;
        if (validInput && validOutput) {
            return Simplex<iNumDestinationDimensions, iNumVertices>(function(simplex.vertices()));
        } else {
            assert(false);
            return Simplex<iNumDestinationDimensions, iNumVertices>();
        }
    }
}
