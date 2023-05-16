
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>

void sendHtml(int fd, char path[], char mime[]){

	printf("sendHtml()\n");
	// /index.html
	// 12345678901=11
	int max = 107;
       	// 96 is buf lim set in handClient
        //+ 11 for index.html	

	char prependPathname[] = "./webroot";

	char nameBuf[150];
	sprintf(nameBuf,"%s%s",
			prependPathname,
			path );


	char *name = nameBuf;
	FILE *file = fopen(name, "r");
	if(file == NULL){
		perror("error file not found\n");
		// todo 404 error header and send()

		char html[1024] =
			"<!DOCTYPE html>\n"
			"<html lang='en'>\n"
			"<head>\n"
			"   <meta charset='UTF-8'>\n"
			"   <title>404 Not Found</title>\n"
			"</head>\n"
			"<body>\n"
			"   <h1>404 Not Found</h1>\n"
			"</body>\n"
			"</html>\n\0";

		int htmlLen = strlen(html);

		int headerLim = 100;
		char header[headerLim];
		sprintf(header,"HTTP/1.1 404 Not Found\r\nContent-Length: %d\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", htmlLen, mime);

		char resp[1280];
		sprintf(resp, "%s%s", header, html);

		int respLen = strlen(resp);
		int ret = send( fd , resp, respLen, 0 );
		if ( ret == -1 ) perror( "send file" );
	
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
			if(charCount > fileSizeMax) break;
		}
		fileData[charCount] = '\0';
		charCount++;

		int headerLen = 87;
		char header[headerLen];
		//                                   10        20        30        40        50        60        70        80   
		//                         123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
		sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", charCount);

		int respLen = headerLen + charCount;
		char resp[ respLen ];
		sprintf(resp, "%s%s", header, fileData);

		int ret = send(fd, resp, respLen, 0);
		if (ret == -1 ) perror("send file");

	}

}


