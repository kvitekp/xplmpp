// Copyright 2019 Peter Kvitek.
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

#include "xplmpp/XPLMData.h"

namespace xplmpp {

/*
 * XPLM data abstraction implementation.
 */
XPLMData::XPLMData(const char* name) {
  if (name) {
    Find(name);
  }
}

XPLMData::~XPLMData() {
}

XPLMDataRef XPLMData::Find(const char* name) {
  data_ref_ = FindDataRef(name);
  return data_ref_;
}

// API wrappers
XPLMDataRef XPLMData::FindDataRef(const char* name) {
  return ::XPLMFindDataRef(name);
}

bool XPLMData::CanWriteDataRef() {
  assert(data_ref_ != nullptr);

  return !!::XPLMCanWriteDataRef(data_ref_);
}

bool XPLMData::IsDataRefGood() {
  assert(data_ref_ != nullptr);

  return !!::XPLMIsDataRefGood(data_ref_);
}

XPLMDataTypeID XPLMData::GetDataRefTypes() {
  assert(data_ref_ != nullptr);

  return ::XPLMGetDataRefTypes(data_ref_);
}

int XPLMData::GetDatai() {
  assert(data_ref_ != nullptr);

  return ::XPLMGetDatai(data_ref_);
}

void XPLMData::SetDatai(int value) {
  assert(data_ref_ != nullptr);

  ::XPLMSetDatai(data_ref_, value);
}

float XPLMData::GetDataf() {
  assert(data_ref_ != nullptr);

  return ::XPLMGetDataf(data_ref_);
}

void XPLMData::SetDataf(float value) {
  assert(data_ref_ != nullptr);

  ::XPLMSetDataf(data_ref_, value);
}

double XPLMData::GetDatad() {
  assert(data_ref_ != nullptr);

  return ::XPLMGetDatad(data_ref_);
}

void XPLMData::SetDatad(double value) {
  assert(data_ref_ != nullptr);

  ::XPLMSetDatad(data_ref_, value);
}

}  // namespace xplmpp
