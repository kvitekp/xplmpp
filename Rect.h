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

#include "xplmpp/Size.h"
#include "xplmpp/Point.h"

#include <sstream>

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

  T Width() const {
    return right - left;
  }

  T Height() const {
    return top - bottom;
  }

  SizeT<T> Size() const {
    return SizeT<T>(Width(), Height());
  }

  PointT<T> TopLeft() const {
    return PointT<T>(left, top);
  }

  PointT<T> BottomLeft() const {
    return PointT<T>(left, bottom);
  }

  PointT<T> TopRight() const {
    return PointT<T>(right, top);
  }

  PointT<T> BottomRight() const {
    return PointT<T>(right, bottom);
  }

  PointT<T> Center() const {
    return PointT<T>(left + Width() / 2, bottom + Height() / 2);
  }

  bool NotEmpty() const {
    return right > left && top > bottom;
  }

  bool IsEmpty() const {
    return !NotEmpty();
  }

  void Inflate(T x, T y) {
    left -= x;
    top += y;
    right += x;
    bottom -= y;
  }

  void Inflate(const SizeT<T>& sz) {
    Inflate(sz.width, sz.height);
  }

  void Deflate(T x, T y) {
    left += x;
    top -= y;
    right -= x;
    bottom += y;
  }

  void Deflate(const SizeT<T>& sz) {
    Deflate(sz.width, sz.height);
  }

  void Offset(T x, T y) {
    left += x;
    top += y;
    right += x;
    bottom += y;
  }

  void Offset(const SizeT<T>& sz) {
    Offset(sz.width, sz.hight);
  }

  void Offset(const PointT<T>& pt) {
    Offset(pt.x, pt.y);
  }

  void MoveToX(T x) {
    right = x + Width();
    left = x;
  }

  void MoveToY(T y) {
    top = y + Height();
    bottom = y;
  }

  void MoveToXY(T x, T y) {
    MoveToX(x);
    MoveToY(y);
  }

  void MoveToXY(const PointT<T>& pt) {
    MoveToXY(pt.x, pt.y);
  }

  std::string ToString() const {
    std::stringstream s;
    s << *this;
    return s.str();
  }

  T left;
  T top;
  T right;
  T bottom;
};

typedef RectT<int> Rect;
typedef RectT<float> RectF;
typedef RectT<double> RectD;

template<typename T>
std::ostream& operator<<(std::ostream& o, const RectT<T>& rc) {
  o << "{"
    << rc.left   << ", "
    << rc.bottom << ", "
    << rc.right  << ", "
    << rc.top    << "}";
  return o;
}

/*
 * OpenGL helpers
 */
#ifdef __GL_H__

inline void glVertex2(const Rect& rc) {
  glVertex2i(rc.left, rc.bottom);
  glVertex2i(rc.left, rc.top);
  glVertex2i(rc.right, rc.top);
  glVertex2i(rc.right, rc.bottom);
}

inline void glVertex2(const RectF& rc) {
  glVertex2f(rc.left, rc.bottom);
  glVertex2f(rc.left, rc.top);
  glVertex2f(rc.right, rc.top);
  glVertex2f(rc.right, rc.bottom);
}

inline void glVertex2(const RectD& rc) {
  glVertex2d(rc.left, rc.bottom);
  glVertex2d(rc.left, rc.top);
  glVertex2d(rc.right, rc.top);
  glVertex2d(rc.right, rc.bottom);
}

#endif  // #ifndef __GL_H__

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_RECT_H
