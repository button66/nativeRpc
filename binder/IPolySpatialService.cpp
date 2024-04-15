#include "IPolySpatialService.h"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

namespace android
{
   
	BpPolySpatialService::BpPolySpatialService(const sp<IBinder>& impl) :
			BpInterface<IPolySpatialService>(impl) {
	m_sharedMemory = new PolySpatialIpc::PolySpatialSharedMemoryAndroid();
	}
	
}
