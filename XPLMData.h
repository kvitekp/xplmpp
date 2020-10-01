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
// XPLM data reference abstraction.

#ifndef XPLMPP_XPLMDATA_H
#define XPLMPP_XPLMDATA_H

#include <vector>

#include "xplmpp/Base.h"

#include "XPLMDataAccess.h"

namespace xplmpp {

// Represents XPLM DataRef.
class XPLMData {
 public:

  explicit XPLMData(const char* name = nullptr);
  ~XPLMData();

  XPLMDataRef data_ref() const { return data_ref_; }

  XPLMDataRef Find(const char* name);
  XPLMDataRef Find(const std::string& name) {
    return Find(name.c_str());
  }

  // XPLM DataRef API wrappers
  static XPLMDataRef FindDataRef(const char* name);
  static XPLMDataRef FindDataRef(const std::string& name) {
    return FindDataRef(name.c_str());
  }

  bool CanWriteDataRef();

  bool IsDataRefGood();

  XPLMDataTypeID GetDataRefTypes();

  int GetDatai();
  void SetDatai(int value);

  float GetDataf();
  void SetDataf(float value);

  double GetDatad();
  void SetDatad(double value);

  // TODO(kvitekp): wrap array accessors

 private:
  XPLMDataRef data_ref_ = nullptr;
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMDATA_H
