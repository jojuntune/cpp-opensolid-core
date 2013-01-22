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

bool isEmpty() const;

CwiseUnaryOp<LowerOperation, const Derived> cwiseLower() const;
CwiseUnaryOp<UpperOperation, const Derived> cwiseUpper() const;
CwiseUnaryOp<MedianOperation, const Derived> cwiseMedian() const;
CwiseUnaryOp<RandomOperation, const Derived> cwiseRandom() const;
CwiseUnaryOp<WidthOperation, const Derived> cwiseWidth() const;

template <class TOther>
bool overlaps(const DenseBase<TOther>& other, double precision = 1e-12) const;

template <class TOther>
bool strictlyOverlaps(const DenseBase<TOther>& other, double precision = 1e-12) const;

template <class TOther>
bool contains(const DenseBase<TOther>& other, double precision = 1e-12) const;

template <class TOther>
bool strictlyContains(const DenseBase<TOther>& other, double precision = 1e-12) const;

template <class TOther>
CwiseBinaryOp<HullOperation, const Derived, const TOther> hull(
    const DenseBase<TOther>& other
) const;

template <class TOther>
CwiseBinaryOp<IntersectionOperation, const Derived, const TOther> intersection(
    const DenseBase<TOther>& other
) const;

static const RandomAccessLinSpacedReturnType LinSpaced(Index size, opensolid::Interval interval);

static const RandomAccessLinSpacedReturnType LinSpaced(opensolid::Interval interval);

template <class TFirst, class TSecond>
static CwiseBinaryOp<HullOperation, const TFirst, const TSecond> Hull(
    const DenseBase<TFirst>& first,
    const DenseBase<TSecond>& second
);

static const ConstantReturnType Empty();
static const ConstantReturnType Empty(Index size);
static const ConstantReturnType Empty(Index rows, Index cols);

static const ConstantReturnType Whole();
static const ConstantReturnType Whole(Index size);
static const ConstantReturnType Whole(Index rows, Index cols);


