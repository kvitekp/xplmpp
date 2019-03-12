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
// XPLM error callback abstraction.

#ifndef XPLMPP_XPLMERRORCALLBACK_H
#define XPLMPP_XPLMERRORCALLBACK_H

#include "xplmpp/Base.h"

#include "XPLMUtilities.h"

namespace xplmpp {

class XPLMErrorCallback {
 public:

  struct Handler {
    virtual void OnPluginError(const char* error) = 0;
  };

  XPLMErrorCallback(Handler* handler = nullptr);
  ~XPLMErrorCallback();

  Handler* handler() const { return handler_; }
  void set_handler(Handler* handler) { handler_ = handler; }

 private:
  class ErrorCallbacks;
  friend ErrorCallbacks;

  static void ErrorCallback(const char* error);
  void OnErrorCallback(const char* error);

  Handler* handler_ = nullptr;
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMERRORCALLBACK_H
