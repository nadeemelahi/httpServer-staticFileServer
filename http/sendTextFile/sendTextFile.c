#include<stdio.h>
#include<string.h>
#include<sys/socket.h>

void notFound404 ( int fd ) ;

void sendTextFile(int fd, char path[], char mime[]){

	printf("sendTextFile ()\n");

	FILE *file = fopen(path, "r");
	if(file == NULL){
		perror("error file not found\n");
		printf("at path: %s\n", path);
		
		notFound404 ( fd ) ;
	
	} else {

		int charCount = 0; // max 2^10 = 5024, 2^16 = 65536
		int fileSizeMax = 1048576; // 2^20
		char fileData[fileSizeMax];
		char eachChar;
		while(1){
			eachChar = fgetc(file);
			if(feof(file)) break;
			fileData[charCount] = eachChar;
			charCount++;
			if(charCount > fileSizeMax) {
				printf("buffer overflow sentTextFile read, aborting\n");
				return;
			}
		}

		int smBuf = 128;
		char header[smBuf];
		sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", 
				charCount , mime );

		int headerLen = strlen(header);

		int ret = send(fd, header, headerLen , 0);
		if (ret == -1 ) perror("send file");

		ret = send(fd, fileData, charCount , 0);
		if (ret == -1 ) perror("send file");
	}

}


