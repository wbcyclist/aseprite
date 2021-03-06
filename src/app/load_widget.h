/* Aseprite
 * Copyright (C) 2001-2014  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef APP_LOAD_WIDGET_H_INCLUDED
#define APP_LOAD_WIDGET_H_INCLUDED
#pragma once

#include "app/widget_loader.h"
#include "base/unique_ptr.h"

namespace app {

  template<class T>
  inline T* load_widget(const char* fileName, const char* widgetId, T* widget = NULL) {
    WidgetLoader loader;
    return loader.loadWidgetT<T>(fileName, widgetId, widget);
  }

} // namespace app

#endif
