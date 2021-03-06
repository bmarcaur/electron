// Copyright (c) 2019 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_OSR_OSR_VIDEO_CONSUMER_H_
#define ATOM_BROWSER_OSR_OSR_VIDEO_CONSUMER_H_

#include <memory>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "components/viz/host/client_frame_sink_video_capturer.h"

namespace atom {

class OffScreenRenderWidgetHostView;

typedef base::RepeatingCallback<void(const gfx::Rect&, const SkBitmap&)>
    OnPaintCallback;

class OffScreenVideoConsumer : public viz::mojom::FrameSinkVideoConsumer {
 public:
  OffScreenVideoConsumer(OffScreenRenderWidgetHostView* view,
                         OnPaintCallback callback);
  ~OffScreenVideoConsumer() override;

  void SetActive(bool active);
  void SetFrameRate(int frame_rate);
  void SizeChanged();

 private:
  // viz::mojom::FrameSinkVideoConsumer implementation.
  void OnFrameCaptured(
      base::ReadOnlySharedMemoryRegion data,
      ::media::mojom::VideoFrameInfoPtr info,
      const gfx::Rect& content_rect,
      viz::mojom::FrameSinkVideoConsumerFrameCallbacksPtr callbacks) override;
  void OnStopped() override;

  bool CheckContentRect(const gfx::Rect& content_rect);

  OnPaintCallback callback_;

  OffScreenRenderWidgetHostView* view_;
  std::unique_ptr<viz::ClientFrameSinkVideoCapturer> video_capturer_;

  base::WeakPtrFactory<OffScreenVideoConsumer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(OffScreenVideoConsumer);
};

}  // namespace atom

#endif  // ATOM_BROWSER_OSR_OSR_VIDEO_CONSUMER_H_
