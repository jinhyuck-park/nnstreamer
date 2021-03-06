/**
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2018 Jijoong Moon <jijoong.moon@samsung.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 */
/**
 * @file	tensordec.h
 * @date	26 Mar 2018
 * @brief	GStreamer plugin to convert tensors to media types
 *
 * @see		http://github.com/TO-BE-DETERMINED-SOON
 * @see		https://github.sec.samsung.net/STAR/nnstreamer
 * @author	Jijoong Moon <jijoong.moon@samsung.com>
 * @bug		No known bugs except for NYI items
 *
 */

#ifndef __GST_TENSORDEC_H__
#define __GST_TENSORDEC_H__

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>
#include <gst/video/video-info.h>
#include <gst/video/video-frame.h>
#include <tensor_common.h>

G_BEGIN_DECLS

/* #defines don't like whitespacey bits */
#define GST_TYPE_TENSORDEC \
  (gst_tensordec_get_type())
#define GST_TENSORDEC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_TENSORDEC,GstTensorDec))
#define GST_TENSORDEC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_TENSORDEC,GstTensorDecClass))
#define GST_IS_TENSORDEC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_TENSORDEC))
#define GST_IS_TENSORDEC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_TENSORDEC))
#define GST_TENSORDEC_CAST(obj)  ((GstTensorDec *)(obj))

typedef struct _GstTensorDec GstTensorDec;

typedef struct _GstTensorDecClass GstTensorDecClass;

typedef enum _video_interlaced_mode {
    _VIDEO_PROGRESSIVE = 0,
    _VIDEO_PLAIN_INTERLACED,
    _VIDEO_TELECINE
} interlaced_mode;

/**
 * @brief Internal data structure for tensordec instances.
 */
struct _GstTensorDec
{
  GstBaseTransform element;	/**< This is the parent object */

  /* For transformer */
  gboolean negotiated; /**< %TRUE if tensor metadata is set */
  media_type output_media_type; /**< Denotes the input media stream type */
  gboolean addPadding; /* If TRUE, zero-padding must be removed during transform */
  gint format;
  interlaced_mode mode;
  tensor_dim dimension;

  /* For Tensor */
  gboolean silent;	/**< True if logging is minimized */
  gboolean Configured;	/**< True if already successfully configured tensor metadata */
  tensor_type type;		/**< Type of each element in the tensor. User must designate this. Otherwise, this is UINT8 for video/x-raw byte stream */
  gint  views;
  gint framerate_numerator;	/**< framerate is in fraction, which is numerator/denominator */
  gint framerate_denominator;	/**< framerate is in fraction, which is numerator/denominator */
};

/*
 * @brief GstTensorDecClass inherits GstBaseTransformClass.
 *
 * Referring another child (sibiling), GstVideoFilter (abstract class) and
 * its child (concrete class) GstVideoConverter.
 * Note that GstTensorDecClass is a concrete class; thus we need to look at both.
 */
struct _GstTensorDecClass
{
  GstBaseTransformClass parent_class;	/**< Inherits GstBaseTransformClass */
};

/*
 * @brief Get Type function required for gst elements
 */
GType gst_tensordec_get_type (void);

G_END_DECLS

#endif /* __GST_TENSORDEC_H__ */
