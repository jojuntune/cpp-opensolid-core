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
 
#include <opensolid/core/simplex/Simplex.hpp>

#include <opensolid/core/datum/Datum.hpp>

namespace opensolid
{   
    template <int dimensions_, int size_>
    Simplex<dimensions_, size_>::Simplex() : _vertices() {}
    
    template Simplex<1, 2>::Simplex();
    template Simplex<2, 2>::Simplex();
    template Simplex<3, 2>::Simplex();
    template Simplex<2, 3>::Simplex();
    template Simplex<3, 3>::Simplex();
    template Simplex<3, 4>::Simplex();
    template Simplex<Dynamic, Dynamic>::Simplex();
        
    template <int dimensions_, int size_>
    Simplex<dimensions_, size_>::Simplex(const Matrix<double, dimensions_, size_>& vertices) :
        _vertices(vertices) {}
    
    template Simplex<1, 2>::Simplex(const Matrix<double, 1, 2>&);
    template Simplex<2, 2>::Simplex(const Matrix<double, 2, 2>&);
    template Simplex<3, 2>::Simplex(const Matrix<double, 3, 2>&);
    template Simplex<2, 3>::Simplex(const Matrix<double, 2, 3>&);
    template Simplex<3, 3>::Simplex(const Matrix<double, 3, 3>&);
    template Simplex<3, 4>::Simplex(const Matrix<double, 3, 4>&);
    template Simplex<Dynamic, Dynamic>::Simplex(const Matrix<double, Dynamic, Dynamic>&);
        
    template <int dimensions_, int size_>
    Simplex<dimensions_, size_>::Simplex(double first_vertex, double second_vertex) {
        _vertices.resize(1, 2);
        _vertices(0) = first_vertex;
        _vertices(1) = second_vertex;
    }
    
    template Simplex<1, 2>::Simplex(double, double);
    template Simplex<Dynamic, Dynamic>::Simplex(double, double);

    template <int dimensions_, int size_>
    Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, 1>& first_vertex,
        const Matrix<double, dimensions_, 1>& second_vertex
    ) {
        assert(first_vertex.size() == second_vertex.size());
        _vertices.resize(first_vertex.size(), 2);
        _vertices.col(0) = first_vertex;
        _vertices.col(1) = second_vertex;
    }
    
    template Simplex<1, 2>::Simplex(const Matrix<double, 1, 1>&, const Matrix<double, 1, 1>&);
    template Simplex<2, 2>::Simplex(const Matrix<double, 2, 1>&, const Matrix<double, 2, 1>&);
    template Simplex<3, 2>::Simplex(const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&);
    template Simplex<Dynamic, Dynamic>::Simplex(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&);
        
    template <int dimensions_, int size_>
    Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, 1>& first_vertex,
        const Matrix<double, dimensions_, 1>& second_vertex,
        const Matrix<double, dimensions_, 1>& third_vertex
    ) {
        assertCompatible<size_, 3>();
        assert(first_vertex.size() == second_vertex.size());
        assert(first_vertex.size() == third_vertex.size());
        _vertices.resize(first_vertex.size(), 3);
        _vertices.col(0) = first_vertex;
        _vertices.col(1) = second_vertex;
        _vertices.col(2) = third_vertex;
    }
    
    template Simplex<2, 3>::Simplex(const Matrix<double, 2, 1>&, const Matrix<double, 2, 1>&, const Matrix<double, 2, 1>&);
    template Simplex<3, 3>::Simplex(const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&);
    template Simplex<Dynamic, Dynamic>::Simplex(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&);
    
    template <int dimensions_, int size_> 
    Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, 1>& first_vertex,
        const Matrix<double, dimensions_, 1>& second_vertex,
        const Matrix<double, dimensions_, 1>& third_vertex,
        const Matrix<double, dimensions_, 1>& fourth_vertex
    ) {
        assertCompatible<size_, 4>();
        assert(first_vertex.size() == second_vertex.size());
        assert(first_vertex.size() == third_vertex.size());
        assert(first_vertex.size() == fourth_vertex.size());
        _vertices.resize(first_vertex.size(), 4);
        _vertices.col(0) = first_vertex;
        _vertices.col(1) = second_vertex;
        _vertices.col(2) = third_vertex;
        _vertices.col(3) = fourth_vertex;
    }
    
    template Simplex<3, 4>::Simplex(const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&, const Matrix<double, 3, 1>&);
    template Simplex<Dynamic, Dynamic>::Simplex(const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&, const Matrix<double, Dynamic, 1>&);
    
    template <int dimensions_, int size_>
    int Simplex<dimensions_, size_>::dimensions() const {return _vertices.rows();}
    
    template int Simplex<1, 2>::dimensions() const;
    template int Simplex<2, 2>::dimensions() const;
    template int Simplex<3, 2>::dimensions() const;
    template int Simplex<2, 3>::dimensions() const;
    template int Simplex<3, 3>::dimensions() const;
    template int Simplex<3, 4>::dimensions() const;
    template int Simplex<Dynamic, Dynamic>::dimensions() const;
    
    template <int dimensions_, int size_>
    int Simplex<dimensions_, size_>::size() const {return _vertices.cols();}
    
    template int Simplex<1, 2>::size() const;
    template int Simplex<2, 2>::size() const;
    template int Simplex<3, 2>::size() const;
    template int Simplex<2, 3>::size() const;
    template int Simplex<3, 3>::size() const;
    template int Simplex<3, 4>::size() const;
    template int Simplex<Dynamic, Dynamic>::size() const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Vertices& Simplex<dimensions_, size_>::vertices() {
        return _vertices;
    }
    
    template Simplex<1, 2>::Vertices& Simplex<1, 2>::vertices();
    template Simplex<2, 2>::Vertices& Simplex<2, 2>::vertices();
    template Simplex<3, 2>::Vertices& Simplex<3, 2>::vertices();
    template Simplex<2, 3>::Vertices& Simplex<2, 3>::vertices();
    template Simplex<3, 3>::Vertices& Simplex<3, 3>::vertices();
    template Simplex<3, 4>::Vertices& Simplex<3, 4>::vertices();
    template Simplex<Dynamic, Dynamic>::Vertices& Simplex<Dynamic, Dynamic>::vertices();
    
    template <int dimensions_, int size_>
    const typename Simplex<dimensions_, size_>::Vertices&
    Simplex<dimensions_, size_>::vertices() const {return _vertices;}
    
    template const Simplex<1, 2>::Vertices& Simplex<1, 2>::vertices() const;
    template const Simplex<2, 2>::Vertices& Simplex<2, 2>::vertices() const;
    template const Simplex<3, 2>::Vertices& Simplex<3, 2>::vertices() const;
    template const Simplex<2, 3>::Vertices& Simplex<2, 3>::vertices() const;
    template const Simplex<3, 3>::Vertices& Simplex<3, 3>::vertices() const;
    template const Simplex<3, 4>::Vertices& Simplex<3, 4>::vertices() const;
    template const Simplex<Dynamic, Dynamic>::Vertices& Simplex<Dynamic, Dynamic>::vertices() const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Vertex Simplex<dimensions_, size_>::vertex(int index) {
        return _vertices.col(index);
    }
    
    template Simplex<1, 2>::Vertex Simplex<1, 2>::vertex(int);
    template Simplex<2, 2>::Vertex Simplex<2, 2>::vertex(int);
    template Simplex<3, 2>::Vertex Simplex<3, 2>::vertex(int);
    template Simplex<2, 3>::Vertex Simplex<2, 3>::vertex(int);
    template Simplex<3, 3>::Vertex Simplex<3, 3>::vertex(int);
    template Simplex<3, 4>::Vertex Simplex<3, 4>::vertex(int);
    template Simplex<Dynamic, Dynamic>::Vertex Simplex<Dynamic, Dynamic>::vertex(int);
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::ConstVertex
    Simplex<dimensions_, size_>::vertex(int index) const {return _vertices.col(index);}
    
    template Simplex<1, 2>::ConstVertex Simplex<1, 2>::vertex(int) const;
    template Simplex<2, 2>::ConstVertex Simplex<2, 2>::vertex(int) const;
    template Simplex<3, 2>::ConstVertex Simplex<3, 2>::vertex(int) const;
    template Simplex<2, 3>::ConstVertex Simplex<2, 3>::vertex(int) const;
    template Simplex<3, 3>::ConstVertex Simplex<3, 3>::vertex(int) const;
    template Simplex<3, 4>::ConstVertex Simplex<3, 4>::vertex(int) const;
    template Simplex<Dynamic, Dynamic>::ConstVertex Simplex<Dynamic, Dynamic>::vertex(int) const;
    
    template <int dimensions_, int size_>
    double Simplex<dimensions_, size_>::length() const {
        assert(size() == 2);
        if (dimensions() == 1) {
            return vertices()(0, 1) - vertices()(0, 0);
        } else {
            return (vertex(1) - vertex(0)).norm();
        }
    }
    
    template double Simplex<1, 2>::length() const;
    template double Simplex<2, 2>::length() const;
    template double Simplex<3, 2>::length() const;
    template double Simplex<Dynamic, Dynamic>::length() const;

    template <class SimplexType>
    inline double triangleArea2d(const SimplexType& triangle) {
        Matrix2d edges;
        edges.col(0) = triangle.vertex(1) - triangle.vertex(0);
        edges.col(1) = triangle.vertex(2) - triangle.vertex(0);
        return edges.determinant() / 2;
    }

    template <class SimplexType>
    inline double triangleArea3d(const SimplexType& triangle) {
        Vector3d first_edge = triangle.vertex(1) - triangle.vertex(0);
        Vector3d second_edge = triangle.vertex(2) - triangle.vertex(0);
        return first_edge.cross(second_edge).norm() / 2;
    }

    inline double triangleArea(const Simplex<2, 3>& triangle) {return triangleArea2d(triangle);}

    inline double triangleArea(const Simplex<3, 3>& triangle) {return triangleArea3d(triangle);}

    inline double triangleArea(const Simplex<Dynamic, Dynamic>& triangle) {
        return triangle.dimensions() == 2 ? triangleArea2d(triangle) : triangleArea3d(triangle);
    }
    
    template <int dimensions_, int size_>
    double Simplex<dimensions_, size_>::area() const {
        assert(size() == 3);
        assert(dimensions() >= 2);
        return triangleArea(*this);
    }
    
    template double Simplex<2, 3>::area() const;
    template double Simplex<3, 3>::area() const;
    template double Simplex<Dynamic, Dynamic>::area() const;
    
    template <int dimensions_, int size_>
    double Simplex<dimensions_, size_>::volume() const {
        assert(size() == 4);
        assert(dimensions() == 3);
        return (vertices().template rightCols<3>().colwise() - vertex(0)).determinant() / 6;
    }
    
    template double Simplex<3, 4>::volume() const;
    template double Simplex<Dynamic, Dynamic>::volume() const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Vector Simplex<dimensions_, size_>::vector() const {
        assert(size() == 2);
        return vertex(1) - vertex(0);
    }
    
    template Simplex<2, 2>::Vector Simplex<2, 2>::vector() const;
    template Simplex<3, 2>::Vector Simplex<3, 2>::vector() const;
    template Simplex<Dynamic, Dynamic>::Vector Simplex<Dynamic, Dynamic>::vector() const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Vector
    Simplex<dimensions_, size_>::centroid() const {return vertices().rowwise().mean();}
    
    template Simplex<1, 2>::Vector Simplex<1, 2>::centroid() const;
    template Simplex<2, 2>::Vector Simplex<2, 2>::centroid() const;
    template Simplex<3, 2>::Vector Simplex<3, 2>::centroid() const;
    template Simplex<2, 3>::Vector Simplex<2, 3>::centroid() const;
    template Simplex<3, 3>::Vector Simplex<3, 3>::centroid() const;
    template Simplex<3, 4>::Vector Simplex<3, 4>::centroid() const;
    template Simplex<Dynamic, Dynamic>::Vector Simplex<Dynamic, Dynamic>::centroid() const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Vector Simplex<dimensions_, size_>::normal() const {
        assert(size() <= dimensions());
        return coordinateSystem().normal();
    }
    
    template Simplex<2, 2>::Vector Simplex<2, 2>::normal() const;
    template Simplex<3, 2>::Vector Simplex<3, 2>::normal() const;
    template Simplex<3, 3>::Vector Simplex<3, 3>::normal() const;
    template Simplex<Dynamic, Dynamic>::Vector Simplex<Dynamic, Dynamic>::normal() const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Edge Simplex<dimensions_, size_>::edge(int index) const {
        assert(0 <= index && index < size());
        return Edge(vertex(index), vertex((index + 1) % size()));
    }
    
    template Simplex<1, 2>::Edge Simplex<1, 2>::edge(int) const;
    template Simplex<2, 2>::Edge Simplex<2, 2>::edge(int) const;
    template Simplex<3, 2>::Edge Simplex<3, 2>::edge(int) const;
    template Simplex<2, 3>::Edge Simplex<2, 3>::edge(int) const;
    template Simplex<3, 3>::Edge Simplex<3, 3>::edge(int) const;
    template Simplex<3, 4>::Edge Simplex<3, 4>::edge(int) const;
    template Simplex<Dynamic, Dynamic>::Edge Simplex<Dynamic, Dynamic>::edge(int) const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Edge Simplex<dimensions_, size_>::edge(
        int start_index,
        int end_index
    ) const {
        assert(0 <= start_index && start_index < size());
        assert(0 <= end_index && end_index < size());
        assert(start_index != end_index);
        return Edge(vertex(start_index), vertex(end_index));
    }
    
    template Simplex<1, 2>::Edge Simplex<1, 2>::edge(int, int) const;
    template Simplex<2, 2>::Edge Simplex<2, 2>::edge(int, int) const;
    template Simplex<3, 2>::Edge Simplex<3, 2>::edge(int, int) const;
    template Simplex<2, 3>::Edge Simplex<2, 3>::edge(int, int) const;
    template Simplex<3, 3>::Edge Simplex<3, 3>::edge(int, int) const;
    template Simplex<3, 4>::Edge Simplex<3, 4>::edge(int, int) const;
    template Simplex<Dynamic, Dynamic>::Edge Simplex<Dynamic, Dynamic>::edge(int, int) const;
    
    template <int dimensions_, int size_>
    typename Simplex<dimensions_, size_>::Face Simplex<dimensions_, size_>::face(int index) const {
        typename Face::Vertices face_vertices(dimensions(), size() - 1);
        Matrix<int, 1, (size_ == Dynamic ? Dynamic : size_ - 1)> indices(size() - 1);
        for (int i = 0; i < indices.size(); ++i) {indices(i) = (index + 1 + i) % size();}
        if (size() % 2 != 0 || index % 2 != 0) {indices.tail(2).reverseInPlace();}
        for (int i = 0; i < indices.size(); ++i) {face_vertices.col(i) = vertex(indices(i));}
        return Face(face_vertices);
    }
    
    template Simplex<2, 3>::Face Simplex<2, 3>::face(int) const;
    template Simplex<3, 3>::Face Simplex<3, 3>::face(int) const;
    template Simplex<3, 4>::Face Simplex<3, 4>::face(int) const;
    template Simplex<Dynamic, Dynamic>::Face Simplex<Dynamic, Dynamic>::face(int) const;

    template <int dimensions_, int size_>
    Datum<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>
    Simplex<dimensions_, size_>::coordinateSystem() const {
        return Datum<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>(
            vertex(0),
            vertices().rightCols(size() - 1).colwise() - vertex(0)
        );
    }
    
    template Datum<1, 1> Simplex<1, 2>::coordinateSystem() const;
    template Datum<2, 1> Simplex<2, 2>::coordinateSystem() const;
    template Datum<3, 1> Simplex<3, 2>::coordinateSystem() const;
    template Datum<2, 2> Simplex<2, 3>::coordinateSystem() const;
    template Datum<3, 2> Simplex<3, 3>::coordinateSystem() const;
    template Datum<3, 3> Simplex<3, 4>::coordinateSystem() const;
    template Datum<Dynamic, Dynamic> Simplex<Dynamic, Dynamic>::coordinateSystem() const;
    
    template <int dimensions_, int size_>
    Matrix<Interval, dimensions_, 1> Simplex<dimensions_, size_>::bounds() const {
        return _vertices.rowwise().minCoeff().hull(_vertices.rowwise().maxCoeff());
    }
    
    template Matrix<Interval, 1, 1> Simplex<1, 2>::bounds() const;
    template Matrix<Interval, 2, 1> Simplex<2, 2>::bounds() const;
    template Matrix<Interval, 3, 1> Simplex<3, 2>::bounds() const;
    template Matrix<Interval, 2, 1> Simplex<2, 3>::bounds() const;
    template Matrix<Interval, 3, 1> Simplex<3, 3>::bounds() const;
    template Matrix<Interval, 3, 1> Simplex<3, 4>::bounds() const;
    template Matrix<Interval, Dynamic, 1> Simplex<Dynamic, Dynamic>::bounds() const;
        
    template <int dimensions_, int size_>
    bool Simplex<dimensions_, size_>::operator==(const Simplex<dimensions_, size_>& other) const {
        assert(dimensions() == other.dimensions());
        assert(size() == other.size());
        return vertices() == other.vertices();
    }
    
    template bool Simplex<1, 2>::operator==(const Simplex<1, 2>&) const;
    template bool Simplex<2, 2>::operator==(const Simplex<2, 2>&) const;
    template bool Simplex<3, 2>::operator==(const Simplex<3, 2>&) const;
    template bool Simplex<2, 3>::operator==(const Simplex<2, 3>&) const;
    template bool Simplex<3, 3>::operator==(const Simplex<3, 3>&) const;
    template bool Simplex<3, 4>::operator==(const Simplex<3, 4>&) const;
    template bool Simplex<Dynamic, Dynamic>::operator==(const Simplex<Dynamic, Dynamic>&) const;

    std::string TypeName<Line1d>::operator()() const {return "Line1d";}

    std::string TypeName<Line2d>::operator()() const {return "Line2d";}

    std::string TypeName<Line3d>::operator()() const {return "Line3d";}

    std::string TypeName<Triangle2d>::operator()() const {return "Triangle2d";}

    std::string TypeName<Triangle3d>::operator()() const {return "Triangle3d";}

    std::string TypeName<Tetrahedron3d>::operator()() const {return "Tetrahedron3d";}

    std::string TypeName<SimplexXd>::operator()() const {return "SimplexXd";}
}
