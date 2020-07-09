#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char** argv){
	
	if (argc != 3 ){
		errx(1,"Invalid number of arguments!");
	}
	off_t f1_size;
	off_t f2_size;

	struct stat st;
	if(stat("f1",&st)<0){
		err(7,"Cannot stat f1");
	}
	f1_size = st.st_size;
	if(stat("f2",&st) < 0){
		err(8,"Cannot stat f2");
	}
	f2_size = st.st_size;
	
	struct pair_t{
		uint32_t x;
		uint32_t y;
	};
	if(f1_size%sizeof(struct pair_t) != 0){
		errx(10,"Wrong size in f1");	
	}
	if(f2_size%sizeof(uint32_t) != 0){
		errx(11,"Wrong size in f2");
	}

	int fd1;
	int fd2; 
	if ((fd1 = open(argv[1],O_RDONLY)) == -1){
		err(2,"Cannot open file descriptor 1");
	}

	if ((fd2 = open(argv[2],O_RDONLY)) == -1){
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(2,"Cannot open file descriptor 2");
	}
	
	int fd3;
	if((fd3 = open("f3",O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1 ){
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(4,"Cannot open fd3");
	}
	struct pair_t instance;

	while(read(fd1,&instance,sizeof(instance)) > 0){
		
		off_t check= lseek(fd2,instance.x*sizeof(uint32_t),SEEK_SET);
			if(check < 0){
				int olderrno = errno;
				close(fd1);
				close(fd2);
				close(fd3);
				errno=olderrno;
				err(5,"Error in lseek!");
			}	
		uint32_t storage;
		uint32_t number_count =0;
		while(read(fd2,&storage,sizeof(storage)) > 0){
			write(fd3,&storage,sizeof(storage));
			number_count++;
			if ( number_count == instance.y){
				break;
			}
		}
	}

	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
