/**
 * Copyright (C) 2016-2017 Xilinx, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

// Copyright 2017 Xilinx, Inc. All rights reserved.
#include "xocl/config.h"
#include "xocl/core/error.h"

#include "plugin/xdp/profile_v2.h"
#include <CL/opencl.h>

namespace xocl {

static void
validOrError(cl_command_queue command_queue,
             cl_mem           src_image,
             cl_mem           dst_image,
             const size_t*    src_origin,
             const size_t*    dst_origin,
             const size_t*    region,
             cl_uint          num_events_in_wait_list,
             const cl_event*  event_wait_list,
             cl_event*        event)
{
  if (!config::api_checks())
    return;

  // CL_INVALID_COMMAND_QUEUE if command_queue is not a valid host
  // command-queue.

  // CL_INVALID_CONTEXT if the context associated with command_queue,
  // src_image and dst_image are not the same or if the context
  // associated with command_queue and events in event_wait_list are
  // not the same.

  // CL_INVALID_MEM_OBJECT if src_image and dst_image are not valid
  // image objects.

  // CL_IMAGE_FORMAT_MISMATCH if src_image and dst_image do not use
  // the same image format.

  // CL_INVALID_VALUE if the 2D or 3D rectangular region specified by
  // src_origin and src_origin + region refers to a region outside
  // src_image, or if the 2D or 3D rectangular region specified by
  // dst_origin and dst_origin + region refers to a region outside
  // dst_image.

  // CL_INVALID_VALUE if values in src_origin, dst_origin and region
  // do not follow rules described in the argument description for
  // src_origin, dst_origin and region.

  // CL_INVALID_EVENT_WAIT_LIST if event_wait_list is NULL and
  // num_events_in_wait_list > 0, or event_wait_list is not NULL and
  // num_events_in_wait_list is 0, or if event objects in
  // event_wait_list are not valid events.

  // CL_INVALID_IMAGE_SIZE if image dimensions (image width, height,
  // specified or compute row and/or slice pitch) for src_image or
  // dst_image are not supported by device associated with queue.

  // CL_IMAGE_FORMAT_NOT_SUPPORTED if image format (image channel
  // order and data type) for src_image or dst_image are not supported
  // by device associated with queue.

  // CL_MEM_OBJECT_ALLOCATION_FAILURE if there is a failure to
  // allocate memory for data store associated with src_image or
  // dst_image.

  // CL_OUT_OF_RESOURCES if there is a failure to allocate resources
  // required by the OpenCL implementation on the device.

  // CL_OUT_OF_HOST_MEMORY if there is a failure to allocate resources
  // required by the OpenCL implementation on the host.

  // CL_INVALID_OPERATION if the device associated with command_queue
  // does not support images (i.e. CL_DEVICE_IMAGE_SUPPORT specified
  // in the table of OpenCL Device Queries for clGetDeviceInfo is
  // CL_FALSE).

  // CL_MEM_COPY_OVERLAP if src_image and dst_image are the same image
  // object and the source and destination regions overlap.
}

static cl_int
clEnqueueCopyImage (cl_command_queue command_queue,
                    cl_mem           src_image,
                    cl_mem           dst_image,
                    const size_t*    src_origin,
                    const size_t*    dst_origin,
                    const size_t*    region,
                    cl_uint          num_events_in_wait_list,
                    const cl_event*  event_wait_list,
                    cl_event*        event)
{
  validOrError(command_queue,src_image,dst_image,src_origin,dst_origin,region,
               num_events_in_wait_list,event_wait_list,event);
  throw error(CL_XILINX_UNIMPLEMENTED,"Not implemented");
}

} // xocl

cl_int
clEnqueueCopyImage (cl_command_queue command_queue,
                    cl_mem           src_image,
                    cl_mem           dst_image,
                    const size_t*    src_origin,
                    const size_t*    dst_origin,
                    const size_t*    region,
                    cl_uint          num_events_in_wait_list,
                    const cl_event*  event_wait_list,
                    cl_event*        event)
{
  try {
    PROFILE_LOG_FUNCTION_CALL_WITH_QUEUE(command_queue);
    LOP_LOG_FUNCTION_CALL_WITH_QUEUE(command_queue);
    return xocl::clEnqueueCopyImage
      (command_queue,src_image,dst_image,src_origin,dst_origin,region
       ,num_events_in_wait_list,event_wait_list,event);
  }
  catch (const xocl::error& ex) {
    xocl::send_exception_message(ex.what());
    return ex.get_code();
  }
  catch (const std::exception& ex) {
    xocl::send_exception_message(ex.what());
    return CL_OUT_OF_HOST_MEMORY;
  }
}
