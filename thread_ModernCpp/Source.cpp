#include <iostream>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <cerrno> // get the error number
#include <cstdlib>// print the error string
#include <Windows.h>
static int value_{ 1 };
constexpr int MAX_THREAD_{3};
pthread_t thread;
int ret;

void* start(void* ptr) {
	pthread_t tid = pthread_self();
	if (pthread_equal(tid, thread)) {
		std::cout << "Thread: " << GetThreadId << std::endl;
		 ret= 100;
		 Sleep(5);
		pthread_exit(&ret);
	}
	return nullptr;
}

int main() {
	std::cout << "Main thread Start" << std::endl;
	pthread_attr_t* attrp;
	pthread_attr_t attr;
	int* thread_return_value = nullptr;
	int ret;
	char buff[256];

	ret = pthread_attr_init(&attr);
	if (ret != 0) {
		std::cout << "Error during Init: " << strerror_s(buff,errno) << std::endl;
	}
	
	ret = pthread_attr_setinheritsched(&attr,PTHREAD_CREATE_JOINABLE);
	if (ret != 0) {
		std::cout << "Error during inheritched: " << strerror_s(buff,errno) << std::endl;
	}

	ret = pthread_create(&thread,&attr ,start, (void*)1);
	if (ret != 0) {
		std::cout << "Error during creation: " << strerror_s(buff, errno) << std::endl;
	}
	ret = pthread_join(thread, (void**)&thread_return_value);
	if (ret != 0) {
		std::cout << "Error during join: " << strerror_s(buff, errno) << std::endl;
	}
	std::cout << "Main Thread: "<< GetCurrentProcessId << " retVal: " << *thread_return_value <<std::endl;
	return 0;
}

/* Output
Without pthread_join() 
Main thread Start
Main Thread: 00007FF819EF4830  -----> Here Mian thread is not waiting for child thread to terminate
Thread: 00007FF819EF4830

With phtread_join()
Main thread Start
Thread: 00007FF819EF4830
Main Thread: 00007FF819EF4830 ------> Here Main thread waited for child thread to terminate.
*/