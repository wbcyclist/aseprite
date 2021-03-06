/* Aseprite
 * Copyright (C) 2001-2013  David Capello
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

#ifndef APP_DOCUMENT_API_H_INCLUDED
#define APP_DOCUMENT_API_H_INCLUDED
#pragma once

#include "gfx/rect.h"
#include "raster/algorithm/flip_type.h"
#include "raster/color.h"
#include "raster/dithering_method.h"
#include "raster/frame_number.h"
#include "raster/pixel_format.h"

namespace raster {
  class Cel;
  class Image;
  class Layer;
  class LayerFolder;
  class LayerImage;
  class Mask;
  class Palette;
  class Sprite;
}

namespace undo {
  class UndoersCollector;
  class ObjectsContainer;
}

namespace app {
  class Document;

  using namespace raster;

  // High-level API to modify a document in an undoable and observable way.
  // Each method of this class take care of three important things:
  // 1) Do the given action with low-level operations (raster
  //    namespace mainly),
  // 2) Add undoers so the action can be undone in the
  //    future (undoers namespace mainly),
  // 3) Notify observers of the document that a change
  //    was made (call DocumentObserver methods).
  class DocumentApi {
  public:
    DocumentApi(Document* document, undo::UndoersCollector* undoers);

    // Sprite API
    void setSpriteSize(Sprite* sprite, int w, int h);
    void setSpriteTransparentColor(Sprite* sprite, color_t maskColor);
    void cropSprite(Sprite* sprite, const gfx::Rect& bounds, color_t bgcolor);
    void trimSprite(Sprite* sprite, color_t bgcolor);
    void setPixelFormat(Sprite* sprite, PixelFormat newFormat, DitheringMethod dithering_method);

    // Frames API
    void addFrame(Sprite* sprite, FrameNumber newFrame);
    void addEmptyFrame(Sprite* sprite, FrameNumber newFrame, color_t bgcolor);
    void copyFrame(Sprite* sprite, FrameNumber fromFrame, FrameNumber newFrame);
    void removeFrame(Sprite* sprite, FrameNumber frame);
    void setTotalFrames(Sprite* sprite, FrameNumber frames);
    void setFrameDuration(Sprite* sprite, FrameNumber frame, int msecs);
    void setFrameRangeDuration(Sprite* sprite, FrameNumber from, FrameNumber to, int msecs);
    void moveFrame(Sprite* sprite, FrameNumber frame, FrameNumber beforeFrame);

    // Cels API
    void addCel(LayerImage* layer, Cel* cel);
    void removeCel(LayerImage* layer, Cel* cel);
    void setCelPosition(Sprite* sprite, Cel* cel, int x, int y);
    void setCelOpacity(Sprite* sprite, Cel* cel, int newOpacity);
    void cropCel(Sprite* sprite, Cel* cel, int x, int y, int w, int h, color_t bgcolor);
    void moveCel(
      LayerImage* srcLayer, FrameNumber srcFrame,
      LayerImage* dstLayer, FrameNumber dstFrame, color_t bgcolor);
    void copyCel(
      LayerImage* srcLayer, FrameNumber srcFrame,
      LayerImage* dstLayer, FrameNumber dstFrame, color_t bgcolor);

    // Layers API
    LayerImage* newLayer(Sprite* sprite);
    LayerFolder* newLayerFolder(Sprite* sprite);
    void addLayer(LayerFolder* folder, Layer* newLayer, Layer* afterThis);
    void removeLayer(Layer* layer);
    void restackLayerAfter(Layer* layer, Layer* afterThis);
    void restackLayerBefore(Layer* layer, Layer* beforeThis);
    void cropLayer(Layer* layer, int x, int y, int w, int h, color_t bgcolor);
    void displaceLayers(Layer* layer, int dx, int dy);
    void backgroundFromLayer(LayerImage* layer, color_t bgcolor);
    void layerFromBackground(Layer* layer);
    void flattenLayers(Sprite* sprite, color_t bgcolor);
    void duplicateLayerAfter(Layer* sourceLayer, Layer* afterLayer);
    void duplicateLayerBefore(Layer* sourceLayer, Layer* beforeLayer);

    // Images stock API
    Cel* addImage(LayerImage* layer, FrameNumber frameNumber, Image* image);
    int addImageInStock(Sprite* sprite, Image* image);
    void removeImageFromStock(Sprite* sprite, int imageIndex);
    void replaceStockImage(Sprite* sprite, int imageIndex, Image* newImage);

    // Image API
    void clearMask(Layer* layer, Cel* cel, color_t bgcolor);
    void flipImage(Image* image, const gfx::Rect& bounds, raster::algorithm::FlipType flipType);
    void flipImageWithMask(Image* image, const Mask* mask, raster::algorithm::FlipType flipType, color_t bgcolor);
    void pasteImage(Sprite* sprite, Cel* cel, const Image* src_image, int x, int y, int opacity);

    // Mask API
    void copyToCurrentMask(Mask* mask);
    void setMaskPosition(int x, int y);
    void deselectMask();

    // Palette API
    void setPalette(Sprite* sprite, FrameNumber frame, Palette* newPalette);

  private:
    undo::ObjectsContainer* getObjects() const;
    void setCelFramePosition(LayerImage* layer, Cel* cel, FrameNumber frame);
    void displaceFrames(Layer* layer, FrameNumber frame);
    void copyFrameForLayer(Layer* layer, FrameNumber fromFrame, FrameNumber frame);
    void removeFrameOfLayer(Layer* layer, FrameNumber frame);
    void moveFrameLayer(Layer* layer, FrameNumber frame, FrameNumber beforeFrame);
    void configureLayerAsBackground(LayerImage* layer);
    bool undoEnabled();

    Document* m_document;
    undo::UndoersCollector* m_undoers;
  };

} // namespace app

#endif
