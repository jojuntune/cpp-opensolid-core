/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    MatrixXd* vector(const Function& function) {
        return new MatrixXd(function.to<VectorXd>());
    }
    
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

    MatrixXd roots(const Function& function, const Interval& domain) {
        return function.roots(domain);
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
        
    void bindFunction() {
        class_<Function>("Function")
            .def(init<Function>())
            .def(init<MatrixXd>())
            .def(init<double>())
            .def(init<Function, Function>())
            .def(init<Function, Function, Function>())
            .def("parameters", &Function::parameters)
            .def("dimensions", &Function::dimensions)
            .def("isConstant", &Function::isConstant)
            .def("__call__", &callFunction)
            .def("__call__", &callMatrixXI, return_value_policy<manage_new_object>())
            .def("__call__", &callMatrixXd, return_value_policy<manage_new_object>())
            .def("__call__", &callInterval, return_value_policy<manage_new_object>())
            .def("__call__", &callDouble, return_value_policy<manage_new_object>())
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
            .def("roots", &roots)
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
            .def("Identity", &Function::Identity)
                .staticmethod("Identity")
            .def("Parameter", &parameter1)
            .def("Parameter", &parameter2)
                .staticmethod("Parameter")
            .def("Parameters", &parameters1)
            .def("Parameters", &parameters2)
                .staticmethod("Parameters");
            
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
