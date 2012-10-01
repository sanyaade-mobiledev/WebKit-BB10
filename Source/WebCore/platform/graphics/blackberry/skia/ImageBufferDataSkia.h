/*
 * Copyright (c) 2008, 2009, Google Inc. All rights reserved.
 * Copyright (c) 2011, Research In Motion. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ImageBufferDataSkia_h
#define ImageBufferDataSkia_h

#include "BlackBerryPlatformGraphics.h"
#include "PlatformContextSkia.h"
#if USE(ACCELERATED_COMPOSITING) && ENABLE(ACCELERATED_2D_CANVAS)
#include "CanvasLayerWebKitThread.h"
#endif

namespace WebCore {

class ImageBufferData {
public:
    ImageBufferData(const IntSize&);

    OwnPtr<SkCanvas> m_canvas;
    PlatformContextSkia m_platformContext;
#if USE(ACCELERATED_COMPOSITING) && ENABLE(ACCELERATED_2D_CANVAS)
    RefPtr<CanvasLayerWebKitThread> m_platformLayer;
#endif
};

} // namespace WebCore

#endif // ImageBufferDataSkia_h