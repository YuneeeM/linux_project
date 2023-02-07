//open-pread-pwrite-pwrite-close로 만든 소스코드
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //파일열기
#include <unistd.h>
#include <string.h>

int main(){
	
	const char* buf="My";
	char temp[9]; //pread시에 데이터를 저장할 buffer
	int fd; //파일 디스크립터
	ssize_t rd;
	
	fd=open("./hello.txt",O_RDWR);
	
	if(fd==-1){
		const int err = errno;
		perror("open error!\n");
	}
	
	rd=pread(fd,temp,7,5);
	if(rd==-1){
		perror("pread error!\n");
	}
	
	rd=pwrite(fd,buf,strlen(buf),6);
	if(rd==-1){
		perror("pwrite error_1!\n");
	}
	
	rd=pwrite(fd,temp,strlen(temp),8);
	if(rd==-1){
		perror("pwrite error_2!\n");
	}
	
	close(fd);
	return 0;
}

/* open-pwrtie-close로 만든 소스코드
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //파일열기
#include <unistd.h>
#include <string.h>

int main(){
	
	//My만 buf로 저장하면 컴파일 시 
	//Hello Myorld!로 저장되기에 뒤에 구문까지 다 작성함!
	const char* buf="My World!";
	int fd;
	ssize_t nw;
	
	fd=open("./hello.txt",O_RDWR);
	
	if(fd==-1){
		const int err = errno;
		perror("open error!\n");
	}
	
	nw=pwrite(fd,buf,strlen(buf),6);
	if(nw==-1){
		perror("pwrite error!\n");
	}
	
	close(fd);
	return 0;
}
*/
