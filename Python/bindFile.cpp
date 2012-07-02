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

namespace opensolid
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
        static boost::python::object get(const File& file, const std::string& key) {
            if (!file.has(key)) {throw FileGetValueError(file.filename(), file.mode(), key, "");}
            std::string type;
            std::string data;
            file.getData(key, type, data);
            if (type == TypeName<bool>()()) {
                Conversion<std::string, bool> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<int>()()) {
                Conversion<std::string, int> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<double>()()) {
                Conversion<std::string, double> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<std::string>()()) {
                return boost::python::object(data);
            } else if (type == TypeName<Interval>()()) {
                Conversion<std::string, Interval> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<MatrixXd>()()) {
                Conversion<std::string, MatrixXd> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<MatrixXI>()()) {
                Conversion<std::string, MatrixXI> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<DatumXd>()()) {
                Conversion<std::string, DatumXd> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<SimplexXd>()()) {
                Conversion<std::string, SimplexXd> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<Function>()()) {
                Conversion<std::string, Function> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<Geometry>()()) {
                Conversion<std::string, Geometry> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<Domain>()()) {
                Conversion<std::string, Domain> deserialization;
                return boost::python::object(deserialization(data));
            } else if (type == TypeName<Object>()()) {
                Conversion<std::string, Object> deserialization;
                return boost::python::object(deserialization(data));
            }
            return boost::python::object();
        }
    };

    void bindFile() {
        class_<File, boost::noncopyable>("File", init<std::string, std::string>())
            .def("filename", &File::filename)
            .def("mode", &File::mode)
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
