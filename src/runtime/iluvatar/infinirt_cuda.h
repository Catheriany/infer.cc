#ifndef INFINIRT_ILU_H
#define INFINIRT_ILU_H
#include "../runtime.h"

#ifdef ENABLE_ILU_BI
#define IMPL_WITH_ILU ;
#else
#define IMPL_WITH_ILU                                                          \
    { return INFINIRT_STATUS_DEVICE_NOT_SUPPORTED; }
#endif

infinirtStatus_t synchronizeIluDevice(uint32_t deviceId) IMPL_WITH_ILU

    infinirtStatus_t
    createIluStream(infinirtStream_t *pStream,
                     uint32_t deviceId) IMPL_WITH_ILU infinirtStatus_t
    destoryIluStream(infinirtStream_t stream) IMPL_WITH_ILU infinirtStatus_t
    synchronizeIluStream(infinirtStream_t stream) IMPL_WITH_ILU

    infinirtStatus_t
    createIluEvent(infinirtEvent_t *pEvent,
                    uint32_t deviceId) IMPL_WITH_ILU infinirtStatus_t
    destoryIluEvent(infinirtEvent_t event) IMPL_WITH_ILU infinirtStatus_t
    waitIluEvent(infinirtEvent_t event,
                  infinirtStream_t stream) IMPL_WITH_ILU infinirtStatus_t
    recordIluEvent(infinirtEvent_t event,
                    infinirtStream_t stream) IMPL_WITH_ILU infinirtStatus_t
    queryIluEvent(infinirtEvent_t event) IMPL_WITH_ILU infinirtStatus_t
    synchronizeIluEvent(infinirtEvent_t event) IMPL_WITH_ILU

    infinirtStatus_t mallocIlu(void **pMemory, uint32_t deviceId,
                               size_t size) IMPL_WITH_ILU infinirtStatus_t
    mallocIluAsync(void **pMemory, uint32_t deviceId, size_t size,
                    infinirtStream_t stream) IMPL_WITH_ILU infinirtStatus_t
    mallocHostIlu(void **pMemory, uint32_t deviceId,
                   size_t size) IMPL_WITH_ILU infinirtStatus_t
    freeIlu(void *ptr, uint32_t deviceId) IMPL_WITH_ILU infinirtStatus_t
    freeIluAsync(void *ptr, uint32_t deviceId,
                  infinirtStream_t stream) IMPL_WITH_ILU infinirtStatus_t
    freeHostIlu(void *ptr, uint32_t deviceId) IMPL_WITH_ILU infinirtStatus_t
    memcpyHost2Ilu(void *dst, uint32_t deviceId, const void *src,
                    size_t size) IMPL_WITH_ILU infinirtStatus_t
    memcpyHost2IluAsync(void *dst, uint32_t deviceId, const void *src,
                         size_t size,
                         infinirtStream_t stream) IMPL_WITH_ILU infinirtStatus_t
    memcpyIlu2Host(void *dst, const void *src, uint32_t deviceId,
                    size_t size) IMPL_WITH_ILU infinirtStatus_t
    memcpyIlu(void *dst, const void *src, uint32_t deviceId,
               size_t size) IMPL_WITH_ILU infinirtStatus_t
    memcpyIluAsync(void *dst, const void *src, uint32_t deviceId, size_t size,
                    infinirtStream_t stream) IMPL_WITH_ILU
#endif
