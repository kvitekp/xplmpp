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
// Point structure declarations.

#ifndef XPLMPP_POINT_H
#define XPLMPP_POINT_H

#include <sstream>

namespace xplmpp {

template<typename T>
struct PointT {
 public:

  PointT() {}

  PointT(T xy)
  : x(xy),
    y(xy)
  {}

  PointT(T x, T y)
  : x(x),
    y(y)
  {}

  PointT(const PointT& sz)
  : x(sz.x),
    y(sz.y)
  {}

  std::string ToString() const {
    std::stringstream s;
    s << *this;
    return s.str();
  }

  T x;
  T y;
};

typedef PointT<int> Point;
typedef PointT<float> PointF;
typedef PointT<double> PointD;

template<typename T>
std::ostream& operator<<(std::ostream& o, const PointT<T>& pt) {
  o << "{"
    << pt.x << ", "
    << pt.y << "}";
  return o;
}

/*
 * OpenGL helpers
 */
#ifdef __GL_H__

inline void glVertex2(const Point& pt) {
  glVertex2i(pt.x, pt.y);
}

inline void glVertex2(const PointF& pt) {
  glVertex2f(pt.x, pt.y);
}

inline void glVertex2(const PointD& pt) {
  glVertex2d(pt.x, pt.y);
}

#endif  // #ifndef __GL_H__

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_POINT_H
