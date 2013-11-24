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

typedef Matrix vector_type;
typedef Scalar value_type;
static const int size_ = MaxSizeAtCompileTime;

Matrix
operator%(const Matrix& other) const;

Scalar
operator|(const Matrix& other) const;

template <class TFunction>
Matrix
apply(const TFunction& function) const;

Matrix&
vectorize(const Scalar& value);

Scalar
length() const;

Scalar
sqrnorm() const;

Matrix&
normalize();

Matrix&
normalize_cond();

Scalar
l1_norm() const;

Scalar
l8_norm() const;

Scalar
max() const;

Scalar
max_abs() const;

Scalar
min() const;

Scalar
min_abs() const;

Scalar
mean_abs() const;

Matrix&
minimize(const Matrix& other);

bool
minimized(const Matrix& other);

Matrix&
maximize(const Matrix& other);

bool
maximized(const Matrix& other);

Matrix
min(const Matrix& other) const;

Matrix
max(const Matrix& other) const;

static Matrix
vectorized(const Scalar& value);

template <class TOther>
static Matrix
From(const TOther& argument);
