#include<stdio.h>
#include<string.h>
#include<sys/socket.h>

void notFound404 ( int fd ){
	char mime[] = "text/html";
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
	printf("notFound404 string length, change buff size to match in hard code: %d\n", htmlLen);

	int headerLim = 100;
	char header[headerLim];
	sprintf(header,"HTTP/1.1 404 Not Found\r\nContent-Length: %d\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", htmlLen, mime);

	char resp[1280];
	sprintf(resp, "%s%s", header, html);

	int respLen = strlen(resp);
	int ret = send( fd , resp, respLen, 0 );
	if ( ret == -1 ) perror( "send file" );
}
