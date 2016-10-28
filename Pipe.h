/*
 * Pipe.h
 *
 * Created on: 28 Oct 2016
 * Author: giulio
 */

#include <fcntl.h>
#include <errno.h>
#include <rtdk.h>
#include <native/pipe.h>
#include <native/task.h>

class Pipe{
public:
	Pipe() :
		pipePath(NULL)
	{}

	~Pipe(){
		dealloc();
	}

	int init(const char* const newPipeName, size_t pipeSize){
		dealloc();
		// check size of the path
		int size = snprintf(pipePath, 0, "/proc/xenomai/registry/native/pipes/%s", newPipeName);
		// allocate and store the path
		pipePath = new char[size + 1];
		snprintf(pipePath, size + 1, "/proc/xenomai/registry/native/pipes/%s", newPipeName);
		// create the pipe
		int ret = rt_pipe_create(&pipe, newPipeName, P_MINOR_AUTO, pipeSize);
		if(ret < 0){
			fprintf(stderr, "Error while creating pipe %s: %s\n", newPipeName, strerror(-ret));
			return -1;
		}
		return 0;
	}

	char* getPath(){
		return pipePath;
	}
		
	int write(const char* const string, bool urgent=false){
		write(strlen(string) + 1, (void*)string, urgent);
	}

	int write(size_t length, void* data, bool urgent=false){
		int ret = rt_pipe_write(&pipe, data, length, urgent ? P_URGENT : P_NORMAL);
		if(ret < 0){
			rt_fprintf(stderr, "Error while writing to pipe %s: %s\n", pipePath, strerror(-ret));
			return ret;
		}
		return 0;
	}

	int read(size_t length, void* data, RTIME timeout=TM_INFINITE){
		int ret = rt_pipe_read(&pipe, data, length, timeout == 0 ? TM_NONBLOCK : timeout);
		if(ret < 0){
			return ret;
		}
		return ret;
	}

private:
	void dealloc(){
		delete [] pipePath;
		rt_pipe_delete(&pipe);
	}
	char* pipePath;
	RT_PIPE pipe;
};

