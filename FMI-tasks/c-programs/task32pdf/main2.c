// this is to create f1 

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>

int main(void){
	
	struct pair_t{
		uint32_t x;
		uint32_t y;
	};
	int fd;
	fd = open("f1",O_CREAT | O_APPEND | O_RDWR , S_IRUSR | S_IWUSR);
	if (fd == -1){
		close(fd);
		err(1,"Cannot opoen f1");
	}
	struct pair_t instance;
	instance.x=30000;
	instance.y=20;
	write(fd,&instance,sizeof(instance));
	instance.x=19000;
	instance.y= 10;
	write(fd,&instance,sizeof(instance));
	close(fd);
	exit(0);
}
