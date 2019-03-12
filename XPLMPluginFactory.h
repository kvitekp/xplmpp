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

#ifndef XPLMPP_XPLMPLUGINFACTORY_H
#define XPLMPP_XPLMPLUGINFACTORY_H

#include "xplmpp/Base.h"
#include "xplmpp/XPLMPlugin.h"

namespace xplmpp {

// Represents XPLM plugin factory. Provide implementation to instantiate
// your plugin.
class XPLMPluginFactory {
 public:
  XPLMPluginFactory() = default;
  virtual ~XPLMPluginFactory() = default;

  virtual std::unique_ptr<XPLMPlugin>CreatePlugin() = 0;
};

// Set this global reference early to provide plugin factory implementation.
extern std::unique_ptr<XPLMPluginFactory> g_plugin_factory;

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMPLUGINFACTORY_H
