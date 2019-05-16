// Copyright (c) 2019 Peter Kvitek.
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
// XPLM error callback abstraction implementation.

#include "xplmpp/XPLMErrorCallback.h"

#include <list>

namespace xplmpp {

// This class delivers error notifications to all existing instances of
// XPLMErrorCallback.
class XPLMErrorCallback::ErrorCallbacks : public std::list<XPLMErrorCallback*> {
public:
  void Add(XPLMErrorCallback* callback) {
    emplace_back(callback);
  }

  void Delete(XPLMErrorCallback* callback) {
    const_iterator it = find(cbegin(), cend(), callback);
    if (it != cend()) {
      erase(it);
    }
  }

  void Notify(const char* error) {
    for (auto callback : *this) {
      callback->OnErrorCallback(error);
    }
  }

} error_callbacks;

XPLMErrorCallback::XPLMErrorCallback(Handler* handler)
: handler_(handler) {
  error_callbacks.Add(this);

  static bool xplm_error_callback_set = false;
  if (!xplm_error_callback_set) {
    ::XPLMSetErrorCallback(ErrorCallback);
    xplm_error_callback_set = true;
  }
}

XPLMErrorCallback::~XPLMErrorCallback() {
  error_callbacks.Delete(this);
}

void XPLMErrorCallback::ErrorCallback(const char* error) {
  error_callbacks.Notify(error);
}

void XPLMErrorCallback::OnErrorCallback(const char* error) {
  if (handler_) {
    handler_->OnPluginError(error);
  }
}

}  // namespace xplmpp
