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
// XPLM Plugin abstraction.

#ifndef XPLMPP_XPLMPLUGIN_H
#define XPLMPP_XPLMPLUGIN_H

#include "xplmpp/Base.h"

#include "SDK/CHeaders/XPLM/XPLMPlugin.h"

namespace xplmpp {

// Represents XPLM plugin.
class XPLMPlugin {
 public:
  XPLMPlugin();
  virtual ~XPLMPlugin();

  static const int kMaxOnStartStringLength = 256; // TODO: check later

  virtual bool OnStart(char* name, char* signature, char* description) = 0;
  virtual bool OnEnable() = 0;
  virtual void OnDisable() = 0;
  virtual void OnStop() = 0;
  virtual void OnReceiveMessage(XPLMPluginID from, int msg, void* param) = 0;

 private:

};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMPLUGIN_H
