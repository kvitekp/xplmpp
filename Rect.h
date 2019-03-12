// Copyright (c) 2019 Peter Kvitek. All rights reserved.
//
// Author: Peter Kvitek (pete@kvitek.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Rectangle structure declarations.

#ifndef XPLMPP_RECT_H
#define XPLMPP_RECT_H

#include "xplmpp/Point.h"

namespace xplmpp {

template<typename T>
struct RectT {
 public:

  RectT() {}

  RectT(T size)
  : left(0),
    top(size),
    right(size),
    bottom(0)
  {}

  RectT(T width, T height)
  : left(0),
    top(height),
    right(width),
    bottom(0)
  {}

  RectT(T left, T top, T right, T bottom)
  : left(left),
    top(top),
    right(right),
    bottom(bottom)
  {}

  RectT(const RectT& rc)
  : left(rc.left),
    top(rc.top),
    right(rc.right),
    bottom(rc.bottom)
  {}

  bool PtInRect(T x, T y) const {
    return x >= left && x <= right && y >= bottom && y <= top;
  }

  bool PtInRect(const PointT<T>& pt) const {
    return PtInRect(pt.x, pt.y);
  }

  PointT<T> TopLeft() const {
    return PointT<T>(left, top);
  }

  PointT<T> BottomRight() const {
    return PointT<T>(right, bottom);
  }

  PointT<T> Center() const {
    return PointT<T>(left + (right - left) / 2, bottom + (top - bottom) / 2);
  }

  T left;
  T top;
  T right;
  T bottom;
};

typedef RectT<int> Rect;
typedef RectT<float> RectF;
typedef RectT<double> RectD;

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_RECT_H
