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
// XPLM Window abstraction implementation.

#include "xplmpp/XPLMWindow.h"

namespace xplmpp {

/*
 * XPLM Window callback thunks.
 */
namespace {

void XPLMDrawWindowThunk(XPLMWindowID id, void* refcon) {
  XPLMWindow* wnd = static_cast<XPLMWindow*>(refcon);
  assert(wnd->id() == id);
  wnd->OnDrawWindow();
}

void XPLMHandleKeyThunk(
    XPLMWindowID id, char key, XPLMKeyFlags flags, char vkey,
    void* refcon, int losingFocus) {
  XPLMWindow* wnd = static_cast<XPLMWindow*>(refcon);
  assert(wnd->id() == id);
  wnd->OnKey(key, flags, vkey, !!losingFocus);
}

int XPLMHandleMouseClickThunk(
    XPLMWindowID id, int x, int y, XPLMMouseStatus status, void* refcon) {
  XPLMWindow* wnd = static_cast<XPLMWindow*>(refcon);
  assert(wnd->id() == id);
  wnd->OnMouseClick(x, y, status);
  // Always consume the click because doing otherwise will cause mouse
  // tracking problems in X-Plane, see XPLMDisplay.h
  return 1;
}

int XPLMHandleRightClickThunk(
    XPLMWindowID id, int x, int y, XPLMMouseStatus status, void* refcon) {
  XPLMWindow* wnd = static_cast<XPLMWindow*>(refcon);
  assert(wnd->id() == id);
  wnd->OnRightClick(x, y, status);
  // Always consume the click because doing otherwise will cause mouse
  // tracking problems in X-Plane, see XPLMDisplay.h
  return 1;
}

int XPLMHandleMouseWheelThunk(
    XPLMWindowID id, int x, int y, int wheel, int clicks, void* refcon) {
  XPLMWindow* wnd = static_cast<XPLMWindow*>(refcon);
  assert(wnd->id() == id);
  wnd->OnMouseWheel(x, y, wheel, clicks);
  // Always consume the click because doing otherwise will cause mouse
  // tracking problems in X-Plane, see XPLMDisplay.h
  return 1;
}

XPLMCursorStatus XPLMHandleCursorThunk(
    XPLMWindowID id, int x, int y, void* refcon) {
  XPLMWindow* wnd = static_cast<XPLMWindow*>(refcon);
  assert(wnd->id() == id);
  return wnd->OnCursor(x, y);
}

}  // namespace

/*
 * XPLM Window implementation.
 */
XPLMWindow::XPLMWindow() {
}

XPLMWindow::XPLMWindow(Builder& builder) {
  builder
    .SetRefCon(this)
    .SetDrawWindowFunc(XPLMDrawWindowThunk)
    .SetHandleKeyFunc(XPLMHandleKeyThunk)
    .SetHandleMouseClickFunc(XPLMHandleMouseClickThunk)
    .SetHandleRightClickFunc(XPLMHandleRightClickThunk)
    .SetHandleMouseWheelFunc(XPLMHandleMouseWheelThunk)
    .SetHandleCursorFunc(XPLMHandleCursorThunk);

  id_ = ::XPLMCreateWindowEx(builder.Build());
}

XPLMWindow::~XPLMWindow() {
  DestroyWindow();
}

XPLMWindowID XPLMWindow::Create(const Rect& rc,
                                XPLMWindowVisibility visibility,
                                XPLMWindowLayer layer,
                                XPLMWindowDecoration decoration) {
  id_ = ::XPLMCreateWindowEx(Builder()
    .SetRect(rc)
    .SetVisible(visibility == visible)
    .SetWindowLayer(layer)
    .SetWindowDecoration(decoration)
    .SetRefCon(this)
    .SetDrawWindowFunc(XPLMDrawWindowThunk)
    .SetHandleKeyFunc(XPLMHandleKeyThunk)
    .SetHandleMouseClickFunc(XPLMHandleMouseClickThunk)
    .SetHandleRightClickFunc(XPLMHandleRightClickThunk)
    .SetHandleMouseWheelFunc(XPLMHandleMouseWheelThunk)
    .SetHandleCursorFunc(XPLMHandleCursorThunk)
    .Build());

  return id_;
}

void XPLMWindow::DestroyWindow() {
  if (id_) {
    ::XPLMDestroyWindow(id_);
    id_ = nullptr;
  }
}

void XPLMWindow::GetWindowGeometry(Rect& rc) {
  assert(id_ != nullptr);

  ::XPLMGetWindowGeometry(id_, &rc.left, &rc.top, &rc.right, &rc.bottom);
}

void XPLMWindow::SetWindowGeometry(const Rect& rc) {
  assert(id_ != nullptr);

  ::XPLMSetWindowGeometry(id_, rc.left, rc.top, rc.right, rc.bottom);
}

void XPLMWindow::GetWindowGeometryOS(Rect& rc) {
  assert(id_ != nullptr);

  ::XPLMGetWindowGeometryOS(id_, &rc.left, &rc.top, &rc.right, &rc.bottom);
}

void XPLMWindow::SetWindowGeometryOS(const Rect& rc) {
  assert(id_ != nullptr);

  ::XPLMSetWindowGeometryOS(id_, rc.left, rc.top, rc.right, rc.bottom);
}

void XPLMWindow::GetWindowGeometryVR(Size& sz) {
  assert(id_ != nullptr);

  ::XPLMGetWindowGeometryVR(id_, &sz.width, &sz.height);
}

void XPLMWindow::SetWindowGeometryVR(const Size& sz) {
  assert(id_ != nullptr);

  ::XPLMSetWindowGeometryVR(id_, sz.width, sz.height);
}

bool XPLMWindow::GetWindowIsVisible() {
  assert(id_ != nullptr);

  return !!::XPLMGetWindowIsVisible(id_);
}

void XPLMWindow::SetWindowIsVisible(bool visible) {
  assert(id_ != nullptr);

  ::XPLMSetWindowIsVisible(id_, visible);
}

bool XPLMWindow::WindowIsPoppedOut() {
  assert(id_ != nullptr);

  return !!::XPLMWindowIsPoppedOut(id_);
}

bool XPLMWindow::WindowIsInVR() {
  assert(id_ != nullptr);

  return !!::XPLMWindowIsInVR(id_);
}

void XPLMWindow::SetWindowGravity(const RectF& rc) {
  assert(id_ != nullptr);

  ::XPLMSetWindowGravity(id_, rc.left, rc.top, rc.right, rc.bottom);
}

void XPLMWindow::SetWindowResizingLimits(const Size& szMin,
                                         const Size& szMax) {
  assert(id_ != nullptr);

  ::XPLMSetWindowResizingLimits(id_,
                                szMin.width, szMin.height,
                                szMax.width, szMax.height);
}

void XPLMWindow::SetWindowPositioningMode(XPLMWindowPositioningMode mode,
                                          int monitor) {
  assert(id_ != nullptr);

  ::XPLMSetWindowPositioningMode(id_, mode, monitor);
}

void XPLMWindow::SetWindowTitle(const char* title) {
  assert(id_ != nullptr);

  ::XPLMSetWindowTitle(id_, title);
}

void XPLMWindow::TakeKeyboardFocus() {
  assert(id_ != nullptr);

  ::XPLMTakeKeyboardFocus(id_);
}

bool XPLMWindow::HasKeyboardFocus() {
  assert(id_ != nullptr);

  return !!::XPLMHasKeyboardFocus(id_);
}

void XPLMWindow::BringToFront() {
  assert(id_ != nullptr);

  ::XPLMBringWindowToFront(id_);
}

bool XPLMWindow::IsInFront() {
  assert(id_ != nullptr);

  return !!::XPLMIsWindowInFront(id_);
}

}  // namespace xplmpp
