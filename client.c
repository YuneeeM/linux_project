//port번호 5392 사용

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUF_SIZ 1024

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int serv_sock;
    struct sockaddr_in serv_addr;
	char msg[30];
    int str_len, len;
	size_t fsize, nsize = 0;

    
	char buf[BUF_SIZ];
    FILE* fp = NULL;
	int fd;
    
	if(argc!=3){
		printf("Usage : %s <IP> <PORT> \n", argv[0]);
		exit(1);
	}
	
    //소켓 생성
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() 연결 요청!!");
        
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
    
    // connect 함수호출을 총해 서버 프로그램 요청함
	if(connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() 연결 요청!!");
	
	str_len=read(serv_sock, msg, sizeof(msg)-1);
	if(str_len==-1)
		error_handling("read() 실패!!");
	printf("Message from server: %s \n", msg);
    
    
    //전송할 파일이름 작성
	fp = fopen("hello.txt" , "rt");
	
    // 파일 크기 계산
	fseek(fp, 0, SEEK_END);
	fsize=ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//file 전송
	while (nsize!=fsize) {
		int fpsize = fread(buf, 1, 256, fp);
		nsize += fpsize;
		send(serv_sock, buf, fpsize, 0);
	}	

	fclose(fp);
	close(serv_sock);
	return 0;
}

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
