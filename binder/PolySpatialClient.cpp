#include "IPolySpatialService.h"


namespace android
{
	void BpPolySpatialService::sayHello() {
		printf("BpPolySpatialService::sayHello\n");
		Parcel data, reply;
		data.writeInterfaceToken(IPolySpatialService::getInterfaceDescriptor());
		 
		int fd = open("/sdcard/window_dump.xml", O_RDWR);
		printf("open BpPolySpatialService fd = %d\n", fd);
		getFileSize(fd);
		data.writeFileDescriptor(fd);
		remote()->transact(HELLO, data, &reply);
		printf("get num from BnPolySpatialService: %d\n", reply.readInt32());
	};


	void BpPolySpatialService::shareMemory() {
		printf("BpPolySpatialService::shareMemory\n");
		int fd = m_sharedMemory->RegisterMemory("shared_memory", 1024);
		printf("shareMemory fd=%d,valid = %d\n",fd,isFdValid(fd));

		char buffer[1024];
		memset(buffer,6,sizeof(char)*1024);
		m_sharedMemory->WriteBuffer(buffer, 1024, 0);
		printf("BpPolySpatialService::shareMemory buffer[0]=%d\n",buffer[1023]);
		Parcel data, reply;
		data.writeInterfaceToken(IPolySpatialService::getInterfaceDescriptor());
		data.writeFileDescriptor(fd);
		remote()->transact(MEMORY_SHARE, data, &reply);

	};
}

int main() {
	sp < IServiceManager > sm = defaultServiceManager(); // 
	sp < IBinder > binder = sm->getService(String16("service.PolySpatialService"));//
	sp<IPolySpatialService> cs = interface_cast <IPolySpatialService> (binder);//
	cs->shareMemory();//
	return 0;
}
