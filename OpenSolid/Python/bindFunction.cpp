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
#include <OpenSolid/Python/BoostPython.hpp>

using namespace boost::python;

namespace OpenSolid
{
    MatrixXD* vector(const Function& function) {
        return new MatrixXD(function.as<ConstantFunction>().vector());
    }
    
    MatrixXD* callDouble(const Function& function, double argument) {
        return new MatrixXD(function(argument));
    }
    
    MatrixXI* callInterval(const Function& function, const Interval& argument) {
        return new MatrixXI(function(argument));
    }
    
    MatrixXD* callMatrixXD(const Function& function, const MatrixXD& argument) {
        return new MatrixXD(function(argument));
    }
    
    MatrixXI* callMatrixXI(const Function& function, const MatrixXI& argument) {
        return new MatrixXI(function(argument));
    }
    
    Function callFunction(const Function& function, const Function& argument) {
        return function(argument);
    }
    
    Function crossMatrix(const Function& function, const MatrixXD& argument) {
        return function.cross(argument);
    }
    
    Function dotMatrix(const Function& function, const MatrixXD& argument) {
        return function.dot(argument);
    }
        
    void bindFunction() {
        class_<Function> function_class("Function");
        function_class
            .def(init<Function>())
            .def(init<MatrixXD>())
            .def(init<Double>())
            .def(init<double>())
            .def(init<Function, Function>())
            .def(init<Function, Function, Function>())
            .def(init<Function, Function, Function, Function>())
            .def("parameters", &Function::parameters)
            .def("dimensions", &Function::dimensions)
            .def("hashValue", &Function::hashValue)
            .def("__call__", &callFunction)
            .def("__call__", &callMatrixXI, return_value_policy<manage_new_object>())
            .def("__call__", &callMatrixXD, return_value_policy<manage_new_object>())
            .def("__call__", &callInterval, return_value_policy<manage_new_object>())
            .def("__call__", &callDouble, return_value_policy<manage_new_object>())
            .def("derivative", &Function::derivative)
            .def("norm", &Function::norm)
            .def("normalized", &Function::normalized)
            .def("squaredNorm", &Function::squaredNorm)
            .def("component", &Function::component)
            .def("components", &Function::components)
            .def("concatenate", &Function::concatenate)
            .def("dot", &Function::dot)
            .def("cross", &Function::cross)
            .def("tangent", &Function::tangent)
            .def("curvature", &Function::curvature)
            .def("normal", &Function::normal)
            .def("binormal", &Function::binormal)
            .def("CurveParameter", &Function::CurveParameter)
                .staticmethod("CurveParameter")
            .def("SurfaceParameter", &Function::SurfaceParameter)
                .staticmethod("SurfaceParameter")
            .def("VolumeParameter", &Function::VolumeParameter)
                .staticmethod("VolumeParameter")
            .def("HypervolumeParameter", &Function::HypervolumeParameter)
                .staticmethod("HypervolumeParameter")
            .def("Parameter", &Function::Parameter)
                .staticmethod("Parameter")
            .def(self == self)
            .def(-self)
            .def(self + self)
            .def(self - self)
            .def(self * self)
            .def(self / self);
            
        implicitly_convertible<MatrixXD, Function>();
        implicitly_convertible<Double, Function>();
        implicitly_convertible<double, Function>();
            
        function_class.attr("t") = object(Function::t);
        function_class.attr("u") = object(Function::u);
        function_class.attr("v") = object(Function::v);
            
        def("sqrt", (Function (*)(const Function&)) &sqrt);
        def("sin", (Function (*)(const Function&)) &sin);
        def("cos", (Function (*)(const Function&)) &cos);
    }
}
