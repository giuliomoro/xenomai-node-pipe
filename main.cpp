#include "Pipe.h"
#include <native/task.h>

Pipe pipe;

void readLoop(void* arg){
	rt_printf("Starting to read\n");
	Pipe* pipe = (Pipe*)arg;
	const int length = 100;
	char data[length];	
	while(1){
		int ret = pipe->read(length, data, 100000000);
		if(ret >= 0){
			rt_printf("\nReturned  %d bytes: %s\n", ret, ret > 0 ? data : "\0" );
		} else {
			rt_printf("r");
		}
	}
}

void writeLoop(void* arg){
	rt_printf("Starting to write\n");
	Pipe* pipe = (Pipe*)arg;
	int ret;
	while(1){
		pipe->write("xenomai");
		rt_printf("w");
		rt_task_sleep(100000000);
	}
}

int main(){
	pipe.init("mypipe", 8192);
	printf("PipePath: %s\n", pipe.getPath());
	RT_TASK readTask;
	RT_TASK writeTask;
	rt_task_create(&readTask, "readTask", 0, 90, T_JOINABLE);
	rt_task_create(&writeTask, "writeTask", 0, 90, T_JOINABLE);
	rt_task_start(&readTask, readLoop, &pipe);
	rt_task_start(&writeTask, writeLoop, &pipe);
	rt_task_join(&readTask);
	rt_task_join(&writeTask);
	return 0;
}

