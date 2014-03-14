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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Vector/DoubleVectorBase.declarations.hpp>

#include <OpenSolid/Core/UnitVector.definitions.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>
#include <OpenSolid/Core/Vector/VectorBase.hpp>

#include <limits>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>&
        DoubleVectorBase<iNumDimensions>::derived() const {
            return static_cast<const Vector<double, iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase() {
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase(
            const Matrix<double, iNumDimensions, 1>& components
        ) : VectorBase<double, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase(const double* sourcePtr) :
            VectorBase<double, iNumDimensions>(sourcePtr) {
        }

        template <int iNumDimensions>
        inline
        const UnitVector<iNumDimensions>
        DoubleVectorBase<iNumDimensions>::normalized() const {
            double norm = this->norm();
            if (norm == Zero()) {
                assert(false);
                return UnitVector<iNumDimensions>();
            }
            return UnitVector<iNumDimensions>((1.0 / norm) * this->components());
        }

        template <int iNumDimensions>
        inline
        double
        DoubleVectorBase<iNumDimensions>::minComponent() const {
            return this->components().reduce(
                [] (double result, double component) -> double {
                    return std::min(result, component);
                }
            );
        }

        template <int iNumDimensions>
        inline
        double
        DoubleVectorBase<iNumDimensions>::minComponent(std::int64_t& index) const {
            double result = this->component(0);
            index = 0;
            for (std::int64_t i = 1; i < iNumDimensions; ++i) {
                double component = this->component(i);
                if (component < result) {
                    result = component;
                    index = i;
                }
            }
            return result;
        }

        template <int iNumDimensions>
        inline
        double
        DoubleVectorBase<iNumDimensions>::maxComponent() const {
            return this->components().reduce(
                [] (double result, double component) -> double {
                    return std::max(result, component);
                }
            );
        }

        template <int iNumDimensions>
        inline
        double
        DoubleVectorBase<iNumDimensions>::maxComponent(std::int64_t& index) const {
            double result = this->component(0);
            index = 0;
            for (std::int64_t i = 1; i < iNumDimensions; ++i) {
                double component = this->component(i);
                if (component > result) {
                    result = component;
                    index = i;
                }
            }
            return result;
        }

        template <int iNumDimensions>
        inline
        bool
        DoubleVectorBase<iNumDimensions>::operator==(
            const Vector<double, iNumDimensions>& other
        ) const {
            return this->components() == other.components();
        }

        template <int iNumDimensions>
        inline
        bool
        DoubleVectorBase<iNumDimensions>::operator!=(
            const Vector<double, iNumDimensions>& other
        ) const {
            return this->components() != other.components();
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator*=(double scale) {
            this->components() *= scale;
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator/=(double divisor) {
            this->components() /= divisor;
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator+=(const Vector<double, iNumDimensions>& other) {
            this->components() += other.components();
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator-=(const Vector<double, iNumDimensions>& other) {
            this->components() -= other.components();
        }
    }
}
