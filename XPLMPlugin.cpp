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
// XPLM Plugin abstraction implementation.
//
// See https ://developer.x-plane.com/article/developing-plugins/ for details.

#include "xplmpp/XPLMPlugin.h"
#include "xplmpp/XPLMPluginFactory.h"

#include "XPLMDisplay.h"

namespace xplmpp {

/*
 * XPLM plugin callback thunks.
 */
namespace {

// Global reference to the plugin instance
std::unique_ptr<XPLMPlugin> g_plugin;

// This is called when the plugin is first loaded.
PLUGIN_API int XPluginStart(char* name, char* signature, char* description) {
  assert(g_plugin == nullptr);
  assert(g_plugin_factory != nullptr);

  g_plugin = g_plugin_factory->CreatePlugin();

  return g_plugin->OnStart(name, signature, description);
}

// This is called when the plugin is enabled.
PLUGIN_API int XPluginEnable() {
  assert(g_plugin != nullptr);
  return g_plugin->OnEnable();
}

// This is called when the plugin is disabled
PLUGIN_API void XPluginDisable() {
  assert(g_plugin != nullptr);
  g_plugin->OnDisable();
}

// This is called right before the plugin is unloaded.
PLUGIN_API void XPluginStop() {
  assert(g_plugin != nullptr);
  g_plugin->OnStop();
}

// This is called when a plugin or X-Plane sends the plugin a message.
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID from, int msg, void* param) {
  assert(g_plugin != nullptr);
  g_plugin->OnReceiveMessage(from, msg, param);
}

}  // namespace

/*
 * XPLM Plugin implementation.
 */
XPLMPlugin::XPLMPlugin() {
}

XPLMPlugin::~XPLMPlugin() {
}

}  // namespace xplmpp
