#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int pipe_fd = open("/proc/xenomai/registry/native/pipes/mypipe", O_RDWR);
	if (pipe_fd < 0){
		fprintf(stderr, "Unable to open\n");
	}
	/* Wait for the prompt string "Hello"... */
	const int len = 1000;
	char buf[len];
	while(1){
		read(pipe_fd, buf, sizeof(buf));
		printf("Received: \"%s\"\n", buf);
		/* Then send the reply string "World": */
		write(pipe_fd, "World", sizeof("World"));
	}
}
