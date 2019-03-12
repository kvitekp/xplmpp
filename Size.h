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
// Size structure declarations.

#ifndef XPLMPP_SIZE_H
#define XPLMPP_SIZE_H

namespace xplmpp {

template<typename T>
struct SizeT {
 public:

  SizeT() {}

  SizeT(T size)
  : width(0),
    height(0)
  {}

  SizeT(T width, T height)
  : width(width),
    height(height)
  {}

  SizeT(const SizeT& sz)
  : width(sz.width),
    height(sz.height)
  {}

  T width;
  T height;
};

typedef SizeT<int> Size;
typedef SizeT<float> SizeF;
typedef SizeT<double> SizeD;

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_SIZE_H
