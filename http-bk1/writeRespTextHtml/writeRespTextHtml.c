#include<stdio.h>
#include<string.h>
#include<sys/socket.h> // send()

void writeRespTextHtml( int fd ){
	printf("writeRespTextHtml()\n");
	


	char html[1024] =
		"<!DOCTYPE html>\n"
		"<html lang='en'>\n"
		"<head>\n"
		"   <meta charset='UTF-8'>\n"
		"   <meta name='viewport' content='width=device-width, initial-scale=1'>\n"
		"   <title>basic http web service</title>\n"
		"   <link rel='icon' type='image/x-icon' href='favicon.ico'>\n"
		"</head>\n"
		"<body>\n"
		"   <h1>hello World - web server</h1>\n"
		"   <a href='./contact.html'>contact pg</a>\n"
		"   <a href='./about'>about pg</a>\n"
		"   <img src='./img/1080p.jpg'>\n"
		"   <img src='./img/1080p.png'>\n"
		"   <img src='./img/1080p.gif'>\n"
		"</body>\n"
		"</html>\n\0";

	int len = strlen(html); // not including header
	// for Content-length: 
	printf("len html[] = %d\n", len);

	int headerLen = 87;
	char header[headerLen];
	//                        10        20        30        40        50        60        70        80
	//               123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", len );

	char resp[1280]; // 1024 + 256
	sprintf(resp, "%s%s", 
			header,
			html );
	
	len = strlen(resp); // including header
	// for len passed to send()

	int ret = send(fd, resp, (size_t)len, 0);

	if(ret == -1) perror("perror send: ");	
}
