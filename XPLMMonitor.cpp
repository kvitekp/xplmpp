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
// XPLM Monitor API wrappers.

#include "xplmpp/XPLMMonitor.h"

#include "XPLMDisplay.h"

namespace xplmpp {

namespace {

// XPLMGetAllMonitorBoundsGlobal helper
class GetAllMonitorBoundsGlobalHelper {
 public:
  GetAllMonitorBoundsGlobalHelper() {
    ::XPLMGetAllMonitorBoundsGlobal(Callback, this);
  }

  bool GetMonitors(std::vector<Rect>& monitors) {
    monitors = monitors_;
    return monitors.size();
  }

 private:
  void AddMonitor(const Rect& rc) {
    monitors_.emplace_back(rc);
  }

  static void Callback(int monitor,
                       int left, int top,
                       int right, int bottom,
                       void* refcon) {
    static_cast<GetAllMonitorBoundsGlobalHelper*>(refcon)->AddMonitor(
        Rect(left, top, right, bottom));
  }

  std::vector<Rect> monitors_;
};

// XPLMGetAllMonitorBoundsOS helper
class GetAllMonitorBoundsOSHelper {
 public:
  GetAllMonitorBoundsOSHelper() {
    ::XPLMGetAllMonitorBoundsOS(Callback, this);
  }

  bool GetMonitors(std::vector<Rect>& monitors) {
    monitors = monitors_;
    return monitors.size();
  }

 private:
  void AddMonitor(const Rect& rc) {
    monitors_.emplace_back(rc);
  }

  static void Callback(int monitor,
                       int left, int top,
                       int right, int bottom,
                       void* refcon) {
    static_cast<GetAllMonitorBoundsOSHelper*>(refcon)->AddMonitor(
        Rect(left, top, right, bottom));
  }

  std::vector<Rect> monitors_;
};

} // namespace

/*
 * XPLM Monitor API wrappers implementation.
 */
bool XPLMMonitor::GetAllMonitorBoundsGlobal(std::vector<Rect>& monitors) {
  return GetAllMonitorBoundsGlobalHelper().GetMonitors(monitors);
}

bool XPLMMonitor::GetAllMonitorBoundsOS(std::vector<Rect>& monitors) {
  return GetAllMonitorBoundsOSHelper().GetMonitors(monitors);
}

}  // namespace xplmpp
