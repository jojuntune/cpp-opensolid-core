/*************************************************************************************
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

#include"PythonModule.hpp"
#include <OpenSolid/Core/Function.hpp>

using namespace boost::python;

namespace opensolid
{
    MatrixXd* callDouble(const Function& function, double argument) {
        return new MatrixXd(function(argument));
    }
    
    MatrixXI* callInterval(const Function& function, const Interval& argument) {
        return new MatrixXI(function(argument));
    }
    
    MatrixXd* callMatrixXd(const Function& function, const MatrixXd& argument) {
        return new MatrixXd(function(argument));
    }
    
    MatrixXI* callMatrixXI(const Function& function, const MatrixXI& argument) {
        return new MatrixXI(function(argument));
    }
    
    Function callFunction(const Function& function, const Function& argument) {
        return function(argument);
    }

    Function derivative1(const Function& function, int index) {return function.derivative(index);}

    Function derivative2(const Function& function) {return function.derivative();}
            
    Function transformed(const Function& function, const MatrixXd& matrix, const MatrixXd& vector) {
        return function.transformed(matrix, VectorXd(vector));
    }
    
    Function scaled(const Function& function, double scale, const MatrixXd& point) {
        return function.scaled(scale, VectorXd(point));
    }
    
    Function translated1(const Function& function, const MatrixXd& vector) {
        return function.translated(VectorXd(vector));
    }
    
    Function translated2(const Function& function, double distance, const DatumXd& axis) {
        return function.translated(distance, axis);
    }
    
    Function rotated1(const Function& function, double angle, const MatrixXd& point) {
        return function.rotated(angle, Vector2d(point));
    }
    
    Function rotated2(const Function& function, double angle, const DatumXd& axis) {
        return function.rotated(angle, axis);
    }
    
    Function mirrored(const Function& function, const DatumXd& plane) {
        return function.mirrored(plane);
    }
    
    Function crossMatrix(const Function& function, const MatrixXd& argument) {
        return function.cross(argument);
    }
    
    Function dotMatrix(const Function& function, const MatrixXd& argument) {
        return function.dot(argument);
    }

    Function identity1() {
        return Function::Identity();
    }

    Function identity2(int dimensions) {
        return Function::Identity(dimensions);
    }

    Function parameter1() {
        return Function::Parameter();
    }

    Function parameter2(int total, int index) {
        return Function::Parameter(total, index);
    }

    Function parameters1(int total) {
        return Function::Parameters(total);
    }

    Function parameters2(int total, int index, int num) {
        return Function::Parameters(total, index, num);
    }

    Function components1(const Function& x, const Function& y) {
        return Function::Components(x, y);
    }

    Function components2(const Function& x, const Function& y, const Function& z) {
        return Function::Components(x, y, z);
    }
        
    void bindFunction() {
        return_value_policy<manage_new_object> manage_new_matrix;
        class_<Function>("Function")
            .def(init<Function>())
            .def(init<MatrixXd>())
            .def(init<double>())
            .def("parameters", &Function::parameters)
            .def("dimensions", &Function::dimensions)
            .def("isConstant", &Function::isConstant)
            .def("__call__", &callFunction)
            .def("__call__", &callMatrixXI, manage_new_matrix)
            .def("__call__", &callMatrixXd, manage_new_matrix)
            .def("__call__", &callInterval, manage_new_matrix)
            .def("__call__", &callDouble, manage_new_matrix)
            .def("derivative", &derivative1)
            .def("derivative", &derivative2)
            .def("transformed", &transformed)
            .def("scaled", &scaled)
            .def("translated", &translated1)
            .def("translated", &translated2)
            .def("rotated", &rotated1)
            .def("rotated", &rotated2)
            .def("mirrored", &mirrored)
            .def("norm", &Function::norm)
            .def("normalized", &Function::normalized)
            .def("squaredNorm", &Function::squaredNorm)
            .def("x", &Function::x)
            .def("y", &Function::y)
            .def("z", &Function::z)
            .def("component", &Function::component)
            .def("components", &Function::components)
            .def("concatenate", &Function::concatenate)
            .def("dot", &Function::dot)
            .def("cross", &Function::cross)
            .def("tangent", &Function::tangent)
            .def("curvature", &Function::curvature)
            .def("normal", &Function::normal)
            .def("binormal", &Function::binormal)
            .def(-self)
            .def(double() + self)
            .def(self + double())
            .def(MatrixXd() + self)
            .def(self + MatrixXd())
            .def(self + self)
            .def(double() - self)
            .def(self - double())
            .def(MatrixXd() - self)
            .def(self - MatrixXd())
            .def(self - self)
            .def(double() * self)
            .def(self * double())
            .def(MatrixXd() * self)
            .def(self * MatrixXd())
            .def(self * DatumXd())
            .def(self * self)
            .def(double() / self)
            .def(self / double())
            .def(MatrixXd() / self)
            .def(self / DatumXd())
            .def(self / self)
            .def(self % DatumXd())
            .def("Identity", &identity1)
            .def("Identity", &identity2)
                .staticmethod("Identity")
            .def("Parameter", &parameter1)
            .def("Parameter", &parameter2)
                .staticmethod("Parameter")
            .def("Parameters", &parameters1)
            .def("Parameters", &parameters2)
                .staticmethod("Parameters")
            .def("Components", &components1)
            .def("Components", &components2)
                .staticmethod("Components");
            
        implicitly_convertible<MatrixXd, Function>();
        implicitly_convertible<double, Function>();
            
        def("sqrt", (Function (*)(const Function&)) &sqrt);
        def("sin", (Function (*)(const Function&)) &sin);
        def("cos", (Function (*)(const Function&)) &cos);
        def("tan", (Function (*)(const Function&)) &tan);
        def("acos", (Function (*)(const Function&)) &acos);
        def("asin", (Function (*)(const Function&)) &asin);
    }
}
