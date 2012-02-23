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

#include <OpenSolid/Core/File/File.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    void setObject(File& file, const std::string& name, const Object& value) {
        file.set(name, value);
    }

    void setDomain(File& file, const std::string& name, const Domain& value) {
        file.set(name, value);
    }

    void setGeometry(File& file, const std::string& name, const Geometry& value) {
        file.set(name, value);
    }

    void setFunction(File& file, const std::string& name, const Function& value) {
        file.set(name, value);
    }

    void setSimplexXd(File& file, const std::string& name, const SimplexXd& value) {
        file.set(name, value);
    }

    void setDatumXd(File& file, const std::string& name, const DatumXd& value) {
        file.set(name, value);
    }

    void setMatrixXI(File& file, const std::string& name, const MatrixXI& value) {
        file.set(name, value);
    }

    void setMatrixXd(File& file, const std::string& name, const MatrixXd& value) {
        file.set(name, value);
    }

    void setInterval(File& file, const std::string& name, const Interval& value) {
        file.set(name, value);
    }

    void setString(File& file, const std::string& name, const std::string& value) {
        file.set(name, value);
    }

    void setDouble(File& file, const std::string& name, double value) {
        file.set(name, value);
    }

    void setInt(File& file, const std::string& name, int value) {
        file.set(name, value);
    }

    void setBool(File& file, const std::string& name, bool value) {
        file.set(name, value);
    }

    struct GetFileProperty
    {
        static boost::python::object get(const File& file, const std::string& name) {
            if (!file.has(name)) {
                throw FilePropertyError(file.filename(), file.mode(), file.isOpen(), name, "");
            }
            std::string type;
            std::string data;
            file.getData(name, type, data);
            if (type == "bool") {
                Deserialization<bool> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "int") {
                Deserialization<int> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "double") {
                Deserialization<double> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "string") {
                Deserialization<std::string> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "Interval") {
                Deserialization<Interval> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "MatrixXd") {
                Deserialization<MatrixXd> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "MatrixXI") {
                Deserialization<MatrixXI> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "DatumXd") {
                Deserialization<DatumXd> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "SimplexXd") {
                Deserialization<SimplexXd> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "Function") {
                Deserialization<Function> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "Geometry") {
                Deserialization<Geometry> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "Domain") {
                Deserialization<Domain> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == "Object") {
                Deserialization<Object> deserialization;
                return boost::python::object(deserialization(data));
            }
            return boost::python::object();
        }
    };

    void bindFile() {
        class_<File, boost::noncopyable>("File", init<std::string>())
            .def("filename", &File::filename)
            .def("open", &File::open)
            .def("mode", &File::mode)
            .def("isOpen", &File::isOpen)
            .def("close", &File::close)
            .def("has", &File::has)
            .def("get", &GetFileProperty::get)
            .def("set", &setObject)
            .def("set", &setDomain)
            .def("set", &setGeometry)
            .def("set", &setFunction)
            .def("set", &setSimplexXd)
            .def("set", &setDatumXd)
            .def("set", &setMatrixXI)
            .def("set", &setMatrixXd)
            .def("set", &setInterval)
            .def("set", &setString)
            .def("set", &setDouble)
            .def("set", &setInt)
            .def("set", &setBool);
    }
}
