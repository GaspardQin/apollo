/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <QTimer>
#include <QWidget>
#include <memory>
#include "modules/tools/visualizer/video_image_viewer.h"

class FixedAspectRatioWidget : public QWidget {
  Q_OBJECT

 public:
  explicit FixedAspectRatioWidget(QWidget *parent = nullptr, int index = 0);

  bool is_init(void) const { return viewer_.is_init_; }
  void SetupDynamicTexture(const std::shared_ptr<Texture> &textureObj);

  void set_index(int i) { index_ = i; }
  int index(void) const { return index_; }

  void StartOrStopUpdate(bool b);
  int innerHeight(void) { return viewer_.plane_.texHeight(); }

 signals:
  void focusOnThis(FixedAspectRatioWidget *);

 protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void contextMenuEvent(QContextMenuEvent *) override;
  void resizeEvent(QResizeEvent *) override;
  void paintEvent(QPaintEvent *event) override;

 private:
  int index_;
  QTimer refresh_timer_;
  VideoImgViewer viewer_;
};
