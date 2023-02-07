//port번호 5392 사용

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	
    char buf[256];
	char message[]="Thank you!!";

    int nbyte = 256;
    size_t filesize = 0;
	size_t bufsize = 256;
	
    FILE *fp = NULL;

	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	
   //서버 소켓 생성
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() 연결 실패!!");
	
	
    //주소정보 초기화
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	
    //주소정보 할당(ip주소와 port번호 할당)
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() 연결 실패!!"); 

	
	//연결요청 가능상태로 변경
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() 연결 실패!!");
	
	
	clnt_addr_size=sizeof(clnt_addr);  

	
	//연결요청에 대한 수락
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() 연결 실패!!");  
	
	
	write(clnt_sock, message, sizeof(message));
	
	
    fp = fopen("hello.txt", "wt");

    while(nbyte!=0) {
        nbyte = recv(clnt_sock, buf, bufsize, 0);
        fwrite(buf, sizeof(char), nbyte, fp);		
    
    }
	
	fclose(fp);
	close(clnt_sock);	
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
