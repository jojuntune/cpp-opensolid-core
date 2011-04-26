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

#include <boost/python.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/manage_new_object.hpp>

#include <OpenSolid/Function/Function.hpp>

using namespace boost::python;

namespace opensolid
{
    MatrixXd* value(const Function& function) {
        return new MatrixXd(function.as<ConstantFunction>().value());
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
    
    Function crossMatrix(const Function& function, const MatrixXd& argument) {
        return function.cross(argument);
    }
    
    Function dotMatrix(const Function& function, const MatrixXd& argument) {
        return function.dot(argument);
    }
        
    void bindFunction() {
        class_<Function> function_class("Function", no_init);
        function_class
            .def("CurveParameter", &Function::CurveParameter)
            .staticmethod("CurveParameter")
            .def("SurfaceParameter", &Function::SurfaceParameter)
            .staticmethod("SurfaceParameter")
            .def("VolumeParameter", &Function::VolumeParameter)
            .staticmethod("VolumeParameter")
            .def("HypervolumeParameter", &Function::HypervolumeParameter)
            .staticmethod("HypervolumeParameter")
            .def("Parameter", &Function::Parameter).staticmethod("Parameter")
            .def("parameters", &Function::parameters)
            .def("dimensions", &Function::dimensions)
            .def("__call__", &callDouble, return_value_policy<manage_new_object>())
            .def("__call__", &callInterval, return_value_policy<manage_new_object>())
            .def("__call__", &callMatrixXd, return_value_policy<manage_new_object>())
            .def("__call__", &callMatrixXI, return_value_policy<manage_new_object>())
            .def("__call__", &callFunction)
            .def("derivative", &Function::derivative)
            .def("component", &Function::component)
            .def("cross", &Function::cross)
            .def("cross", &crossMatrix)
            .def("dot", &Function::dot)
            .def("dot", &dotMatrix)
            .def("norm", &Function::norm)
            .def("normalized", &Function::normalized)
            .def("squaredNorm", &Function::squaredNorm)
            .def(-self)
            .def(self + self)
            .def(self - self)
            .def(self * self)
            .def(self / self)
            .def(double() + self)
            .def(self + double())
            .def(double() - self)
            .def(self - double())
            .def(double() * self)
            .def(self * double())
            .def(double() / self)
            .def(self / double())
            .def(MatrixXd() + self)
            .def(self + MatrixXd())
            .def(MatrixXd() - self)
            .def(self - MatrixXd())
            .def(MatrixXd() * self)
            .def(self * MatrixXd())
            .def(MatrixXd() / self);
            
        function_class.attr("t") = object(Function::t);
        function_class.attr("u") = object(Function::u);
        function_class.attr("v") = object(Function::v);
            
        def("sqrt", (Function (*)(const Function&)) &sqrt);
        def("sin", (Function (*)(const Function&)) &sin);
        def("cos", (Function (*)(const Function&)) &cos);
    }
}
