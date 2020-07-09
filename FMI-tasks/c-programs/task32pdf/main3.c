#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>

int main(void){
	
	int fd; 
	if((fd = open("f2",O_CREAT| O_WRONLY, S_IRUSR | S_IWUSR))== -1){
		err(1,"Cannot open f2");
	}
	for(uint32_t i =0;i<35000;i++){
		write(fd,&i,sizeof(i));
	}
	exit(0);
}	
