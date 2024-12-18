#include "infinirt_cuda.h"
#include "cuda_runtime.h"
#include <iostream>

#define CUDA_CALL(x)                                                           \
    do {                                                                       \
        cudaError_t err = (x);                                                 \
        if (err != cudaSuccess) {                                              \
            std::cerr << "Ilu error: " << err << " in function " << __func__   \
                      << std::endl;                                            \
            return INFINIRT_STATUS_EXECUTION_FAILED;                           \
        }                                                                      \
    } while (0)

#define SWITCH_DEVICE(deviceId)                                                \
    do {                                                                       \
        cudaError_t err = cudaSetDevice(deviceId);                             \
        if (err != cudaSuccess) {                                              \
            std::cerr << "Ilu set device " << deviceId << "error: " << err     \
                      << " in function " << __func__ << std::endl;             \
            return INFINIRT_STATUS_BAD_DEVICE;                                 \
        }                                                                      \
    } while (0)

inline cudaStream_t getIluStream(infinirtStream_t stream) {
    if (stream == nullptr) {
        return 0;
    }
    return static_cast<cudaStream_t>(stream->stream);
}

infinirtStatus_t synchronizeIluDevice(uint32_t deviceId) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaDeviceSynchronize());
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t createIluStream(infinirtStream_t *pStream, uint32_t deviceId) {
    SWITCH_DEVICE(deviceId);
    cudaStream_t cuda_stream;
    CUDA_CALL(cudaStreamCreate(&cuda_stream));
    infinirtStream_t stream = new infinirtStream();
    stream->device = DEVICE_ILU;
    stream->device_id = deviceId;
    stream->stream = cuda_stream;
    *pStream = stream;
    return INFINIRT_STATUS_SUCCESS;
}
infinirtStatus_t destoryIluStream(infinirtStream_t stream) {
    SWITCH_DEVICE(stream->device_id);
    CUDA_CALL(cudaStreamDestroy(getIluStream(stream)));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t synchronizeIluStream(infinirtStream_t stream) {
    SWITCH_DEVICE(stream->device_id);
    CUDA_CALL(cudaStreamSynchronize(getIluStream(stream)));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t createIluEvent(infinirtEvent_t *pEvent, uint32_t deviceId) {
    SWITCH_DEVICE(deviceId);
    cudaEvent_t cuda_event;
    CUDA_CALL(cudaEventCreate(&cuda_event));
    infinirtEvent_t event = new infinirtEvent();
    event->device = DEVICE_ILU;
    event->device_id = deviceId;
    event->event = cuda_event;
    *pEvent = event;
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t destoryIluEvent(infinirtEvent_t event) {
    SWITCH_DEVICE(event->device_id);
    CUDA_CALL(cudaEventDestroy(static_cast<cudaEvent_t>(event->event)));
    delete event;
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t waitIluEvent(infinirtEvent_t event, infinirtStream_t stream) {
    SWITCH_DEVICE(event->device_id);
    CUDA_CALL(cudaStreamWaitEvent(getIluStream(stream),
                                  static_cast<cudaEvent_t>(event->event), 0));
    return INFINIRT_STATUS_SUCCESS;
}
infinirtStatus_t recordIluEvent(infinirtEvent_t event,
                                infinirtStream_t stream) {
    SWITCH_DEVICE(event->device_id);
    CUDA_CALL(cudaEventRecord(static_cast<cudaEvent_t>(event->event),
                              getIluStream(stream)));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t queryIluEvent(infinirtEvent_t event) {
    SWITCH_DEVICE(event->device_id);
    cudaError_t err = cudaEventQuery(static_cast<cudaEvent_t>(event->event));
    if (err != cudaSuccess) {
        return INFINIRT_STATUS_NOT_READY;
    }
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t synchronizeIluEvent(infinirtEvent_t event) {
    SWITCH_DEVICE(event->device_id);
    CUDA_CALL(cudaEventSynchronize(static_cast<cudaEvent_t>(event->event)));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t mallocIlu(void **pMemory, uint32_t deviceId, size_t size) {
    printf("line 110\n");
    SWITCH_DEVICE(deviceId);
    void *cuda_ptr;
    CUDA_CALL(cudaMalloc(&cuda_ptr, size));
    *pMemory = cuda_ptr;
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t mallocIluAsync(void **pMemory, uint32_t deviceId, size_t size,
                                infinirtStream_t stream) {
    printf("line 120\n");
    SWITCH_DEVICE(deviceId);
    void *cuda_ptr;
    CUDA_CALL(cudaMallocAsync(&cuda_ptr, size, getIluStream(stream)));
    *pMemory = cuda_ptr;
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t mallocHostIlu(void **pMemory, uint32_t deviceId, size_t size) {
    SWITCH_DEVICE(deviceId);
    void *host_ptr;
    CUDA_CALL(cudaMallocHost(&host_ptr, size));
    *pMemory = host_ptr;
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t freeIlu(void *ptr, uint32_t deviceId) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaFree(ptr));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t freeIluAsync(void *ptr, uint32_t deviceId,
                              infinirtStream_t stream) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaFreeAsync(ptr, getIluStream(stream)));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t freeHostIlu(void *ptr, uint32_t deviceId) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaFreeHost(ptr));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t memcpyHost2Ilu(void *dst, uint32_t deviceId, const void *src,
                                size_t size) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaMemcpy(dst, src, size, cudaMemcpyHostToDevice));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t memcpyHost2IluAsync(void *dst, uint32_t deviceId,
                                     const void *src, size_t size,
                                     infinirtStream_t stream) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaMemcpyAsync(dst, src, size, cudaMemcpyHostToDevice,
                              getIluStream(stream)));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t memcpyIlu2Host(void *dst, const void *src, uint32_t deviceId,
                                size_t size) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaMemcpy(dst, src, size, cudaMemcpyDeviceToHost));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t memcpyIlu(void *dst, const void *src, uint32_t deviceId,
                           size_t size) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaMemcpy(dst, src, size, cudaMemcpyDeviceToDevice));
    return INFINIRT_STATUS_SUCCESS;
}

infinirtStatus_t memcpyIluAsync(void *dst, const void *src, uint32_t deviceId,
                                size_t size, infinirtStream_t stream) {
    SWITCH_DEVICE(deviceId);
    CUDA_CALL(cudaMemcpyAsync(dst, src, size, cudaMemcpyDeviceToDevice,
                              getIluStream(stream)));
    return INFINIRT_STATUS_SUCCESS;
}
