#include "IPolySpatialService.h"


namespace android{
	void BnPolySpatialService::sayHello() {
		printf("BnPolySpatialService::sayHello\n");
	};

	status_t BnPolySpatialService::onTransact(uint_t code, const Parcel& data,
			Parcel* reply, uint32_t flags) {
		switch (code) {
		case HELLO: {    
			printf("BnPolySpatialService:: got the client hello\n");
			CHECK_INTERFACE(IPolySpatialService, data, reply);
			int fd = data.readFileDescriptor();
			getFileSize(fd);
			printf("BnPolySpatialService:: readFileDescriptor fd=%d,isvalid= %d\n",fd,isFdValid(fd));
			sayHello();
			flags = NO_ERROR;
			reply->writeInt32(2015);
			return NO_ERROR;
		}
			break;
		case MEMORY_SHARE:{
			printf("BnPolySpatialService:: got the client memory share\n");
			CHECK_INTERFACE(IPolySpatialService, data, reply);
			int fd = data.readFileDescriptor();
			readMemory(fd);
			break;
		}
		default:
			break;
		}
		return NO_ERROR;
	};

	void BnPolySpatialService::readMemory(int fd){
		printf("readMemory fd=%d,isvalid = %d\n",fd,isFdValid(fd));
		m_sharedMemory->OpenMemory(fd);
		char buffer[1024];
		memset(buffer,8,sizeof(char)*1024);
		printf("readMemory data[0]=%d\n",buffer[1023]);
		m_sharedMemory->ReadBuffer(buffer,1024,0);
		printf("readMemory data[0]=%d\n",buffer[1023]);
	};

	void BnPolySpatialService::shareMemory() {
		printf("BnPolySpatialService::shareMemory\n");
		int fd = m_sharedMemory->RegisterMemory("shared_memory", 1024);
		printf("shareMemory fd=%d,valid = %d\n",fd,isFdValid(fd));
	};
}

int main() {
	sp < IServiceManager > sm = defaultServiceManager();
	BnPolySpatialService* service =  new BnPolySpatialService();
	sm->addService(String16("service.PolySpatialService"),service);

	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
	return 0;
}
