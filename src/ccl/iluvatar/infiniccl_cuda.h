#ifndef INFINICCL_ILU_H_
#define INFINICCL_ILU_H_
#include "infiniccl.h"

#ifdef ENABLE_ILU_BI
#define IMPL_WITH_ILU ;
#else
#define IMPL_WITH_ILU                                                          \
    { return INFINICCL_STATUS_DEVICE_NOT_SUPPORTED; }
#endif

infinicclStatus_t infinicclCudaCommInitAll(
    infinicclComm_t *comms, unsigned int numDevices,
    unsigned int const *deviceIDs) IMPL_WITH_ILU infinicclStatus_t
    infinicclCudaCommDestroy(infinicclComm_t comm)
        IMPL_WITH_ILU infinicclStatus_t
    infinicclCudaAllReduceSum(infinicclComm_t comm, void *sendbuf,
                              void *recvbuf, size_t count,
                              InfiniDataType_t datatype,
                              infinirtStream_t stream) IMPL_WITH_ILU

#endif /* INFINICCL_ILU_H_ */
