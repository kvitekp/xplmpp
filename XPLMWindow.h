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
// XPLM Window abstraction.

#ifndef XPLMPP_XPLMWINDOW_H
#define XPLMPP_XPLMWINDOW_H

#include "xplmpp/Base.h"
#include "xplmpp/Rect.h"
#include "xplmpp/Size.h"

#include "XPLMDisplay.h"

namespace xplmpp {

// Represents XPLM window.
class XPLMWindow {
 public:
  class Builder;
  XPLMWindow();
  XPLMWindow(Builder& builder);
  virtual ~XPLMWindow();

  enum XPLMWindowVisibility { visible, hidden };

  XPLMWindowID Create(const Rect& rc,
                      XPLMWindowVisibility visibility = visible,
                      XPLMWindowLayer layer = xplm_WindowLayerFloatingWindows,
                      XPLMWindowDecoration decoration = xplm_WindowDecorationRoundRectangle);

  XPLMWindowID id() const { return id_; }

  // XPLM API wrappers
  void DestroyWindow();

  void GetWindowGeometry(Rect& rc);
  void SetWindowGeometry(const Rect& rc);

  void GetWindowGeometryOS(Rect& rc);
  void SetWindowGeometryOS(const Rect& rc);

  void GetWindowGeometryVR(Size& sz);
  void SetWindowGeometryVR(const Size& sz);

  bool GetWindowIsVisible();
  void SetWindowIsVisible(bool visible = true);

  bool WindowIsPoppedOut();
  bool WindowIsInVR();

  void SetWindowGravity(const RectF& rc);

  void SetWindowResizingLimits(const Size& szMin, const Size& szMax);

  void SetWindowPositioningMode(XPLMWindowPositioningMode mode, int monitor = -1);

  void SetWindowTitle(const char* title);
  void SetWindowTitle(const std::string& title) { SetWindowTitle(title.c_str()); }

  void TakeKeyboardFocus();
  bool HasKeyboardFocus();

  void BringToFront();
  bool IsInFront();

  // XPLM window callbacks
  virtual void OnDrawWindow() {}
  virtual void OnKey(char key, XPLMKeyFlags flags, unsigned char vkey, bool losingFocus) {}
  virtual void OnMouseClick(int x, int y, XPLMMouseStatus status) {}
  virtual void OnRightClick(int x, int y, XPLMMouseStatus status) {}
  virtual void OnMouseWheel(int x, int y, int wheel, int clicks) {}
  virtual XPLMCursorStatus OnCursor(int x, int y) { return xplm_CursorDefault; }

 private:
  XPLMWindowID id_ = nullptr;
};

// Implements XPLM window builder.
class XPLMWindow::Builder {
public:
  XPLMCreateWindow_t* Build() { return &data_; }

  Builder() {
    data_.structSize = sizeof(XPLMCreateWindow_t);
    data_.left = 0;
    data_.top = 0;
    data_.right = 0;
    data_.bottom = 0;
    data_.visible = false;
    data_.drawWindowFunc = nullptr;
    data_.handleMouseClickFunc = nullptr;
    data_.handleKeyFunc = nullptr;
    data_.handleCursorFunc = nullptr;
    data_.handleMouseWheelFunc = nullptr;
    data_.refcon = nullptr;
    data_.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
    data_.layer = xplm_WindowLayerFloatingWindows;
    data_.handleRightClickFunc = nullptr;
  }

  Builder& SetRect(const Rect& rc) {
    data_.left = rc.left;
    data_.top = rc.top;
    data_.right = rc.right;
    data_.bottom = rc.bottom;
    return *this;
  }

  Builder& SetVisible(bool visible) {
    data_.visible = visible;
    return *this;
  }

  Builder& SetDrawWindowFunc(XPLMDrawWindow_f fn) {
    data_.drawWindowFunc = fn;
    return *this;
  }

  Builder& SetHandleMouseClickFunc(XPLMHandleMouseClick_f fn) {
    data_.handleMouseClickFunc = fn;
    return *this;
  }
  Builder& SetHandleKeyFunc(XPLMHandleKey_f fn) {
    data_.handleKeyFunc = fn;
    return *this;
  }
  Builder& SetHandleCursorFunc(XPLMHandleCursor_f fn) {
    data_.handleCursorFunc = fn;
    return *this;
  }
  Builder& SetHandleMouseWheelFunc(XPLMHandleMouseWheel_f fn) {
    data_.handleMouseWheelFunc = fn;
    return *this;
  }

  Builder& SetRefCon(void* refcon) {
    data_.refcon = refcon;
    return *this;
  }

  Builder& SetWindowDecoration(XPLMWindowDecoration decoration) {
    data_.decorateAsFloatingWindow = decoration;
    return *this;
  }

  Builder& SetWindowLayer(XPLMWindowLayer layer) {
    data_.layer = layer;
    return *this;
  }

  Builder& SetHandleRightClickFunc(XPLMHandleMouseClick_f fn) {
    data_.handleRightClickFunc = fn;
    return *this;
  }

private:
  XPLMCreateWindow_t data_;
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMWINDOW_H
