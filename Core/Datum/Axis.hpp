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

#ifndef OPENSOLID__AXIS_HPP
#define OPENSOLID__AXIS_HPP

#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>

namespace opensolid
{
    class Axis2d : public Datum<2, 1>
    {
    public:
        Axis2d();

        template <class OriginType, class DirectionType>
        Axis2d(const EigenBase<OriginType>& origin, const EigenBase<DirectionType>& direction);

        template <int dimensions_, int axes_>
        Axis2d(const Datum<dimensions_, axes_>& datum);
    };

    class Axis3d : public Datum<3, 1>
    {
    public:
        Axis3d();

        template <class OriginType, class DirectionType>
        Axis3d(const EigenBase<OriginType>& origin, const EigenBase<DirectionType>& direction);

        template <int dimensions_, int axes_>
        Axis3d(const Datum<dimensions_, axes_>& datum);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Axis2d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
    
    template <>
    struct TypeName<Axis3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class Axis2dConstructionError : public Error
    {
    private:
        MatrixXd _origin;
        MatrixXd _direction;
    public:
        OPENSOLID_CORE_EXPORT Axis2dConstructionError(
            const MatrixXd& origin,
            const MatrixXd& direction
        );
        
        OPENSOLID_CORE_EXPORT ~Axis2dConstructionError() throw ();
        
        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT MatrixXd origin() const;
        OPENSOLID_CORE_EXPORT MatrixXd direction() const;
    };

    class Axis2dCopyConstructionError : public Error
    {
    private:
        DatumXd _argument;
    public:
        OPENSOLID_CORE_EXPORT Axis2dCopyConstructionError(const DatumXd& argument);
        
        OPENSOLID_CORE_EXPORT ~Axis2dCopyConstructionError() throw ();

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT DatumXd argument() const;
    };

    class Axis3dConstructionError : public Error
    {
    private:
        MatrixXd _origin;
        MatrixXd _direction;
    public:
        OPENSOLID_CORE_EXPORT Axis3dConstructionError(
            const MatrixXd& origin,
            const MatrixXd& direction
        );
        
        OPENSOLID_CORE_EXPORT ~Axis3dConstructionError() throw ();
        
        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT MatrixXd origin() const;
        OPENSOLID_CORE_EXPORT MatrixXd direction() const;
    };

    class Axis3dCopyConstructionError : public Error
    {
    private:
        DatumXd _argument;
    public:
        OPENSOLID_CORE_EXPORT Axis3dCopyConstructionError(const DatumXd& argument);
        
        OPENSOLID_CORE_EXPORT ~Axis3dCopyConstructionError() throw ();

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT DatumXd argument() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Axis2d::Axis2d() {initialize(Vector2d::Zero(), Vector2d::UnitX());}

    template <class OriginType, class DirectionType>
    inline Axis2d::Axis2d(
        const EigenBase<OriginType>& origin,
        const EigenBase<DirectionType>& direction
    ) {
        if (
            origin.cols() != 1 ||
            origin.rows() != 2 ||
            direction.cols() != 1 ||
            direction.rows() != 2 ||
            direction.derived().isZero()
        ) {throw Axis2dConstructionError(origin, direction);}
        initialize(origin.derived(), direction.derived().normalized());
    }

    template <int dimensions_, int axes_>
    inline Axis2d::Axis2d(const Datum<dimensions_, axes_>& datum) {
        if (
            datum.dimensions() != 2 ||
            datum.axes() != 1 ||
            datum.basis().squaredNorm() - 1 != Zero()
        ) {throw Axis2dCopyConstructionError(datum);}
        initialize(datum);
    }

    inline Axis3d::Axis3d() {initialize(Vector3d::Zero(), Vector3d::UnitX());}

    template <class OriginType, class DirectionType>
    inline Axis3d::Axis3d(
        const EigenBase<OriginType>& origin,
        const EigenBase<DirectionType>& direction
    ) {
        if (
            origin.cols() != 1 ||
            origin.rows() != 3 ||
            direction.cols() != 1 ||
            direction.rows() != 3 ||
            direction.derived().isZero()
        ) {throw Axis3dConstructionError(origin, direction);}
        initialize(origin.derived(), direction.derived().normalized());
    }

    template <int dimensions_, int axes_>
    inline Axis3d::Axis3d(const Datum<dimensions_, axes_>& datum) {
        if (
            datum.dimensions() != 3 ||
            datum.axes() != 1 ||
            datum.basis().squaredNorm() - 1 != Zero()
        ) {throw Axis3dCopyConstructionError(datum);}
        initialize(datum);
    }
}

#endif
