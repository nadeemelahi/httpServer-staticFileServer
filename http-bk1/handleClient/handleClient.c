#include<stdio.h>
#include<string.h>

void recvReq( int fd, int smLim, 
		char methodBuf[smLim],
		char pathBuf[smLim],
		char protoBuf[smLim]   );

void writeRespTextHtml( int fd );

void sendImage( int fd, char imagepath[], char mime[] );

void sendHtml( int fd, char path[] , char mime[] );

int checkNameValidity(char name[], int len){

	int idx, vcidx;
	char validChars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-/.";
	int vclen = strlen(validChars);
	int matchFound;
	for ( idx = 0 ; idx < len ; idx++){

		// ex) /img/image01.jpg
		// idx=01234 ... len

		for(vcidx = 0 ; vcidx < vclen; vcidx++){
			// vcidx = 0123 ... vclen
			matchFound = 0;
			if( name [ idx ] == validChars[ vcidx ] ){

				matchFound = 1;
				break;

			}	
		}
		// did we break early with a match or loop entire validChars string
		if( matchFound ){
			// we broke early, the char is on of the validChars
		} else {

			// char is not a valid char
			return 2;
		}
	}
	return 0; // we have a valid char name - no errors found
}
int checkForPeriod(char name[], int len){

	int idx;
	for ( idx = 0; idx < len; idx++ ){

		if ( name[idx] == '.' ) return 0; // we have a period

	}


	return 1; // we DO NOT have a period
}
void handleClient( int fd ){
	printf("handleClient()\n");




	int smLim = 128;
	char methodBuf[smLim], 
	     pathBuf[smLim], 
	     protoBuf[smLim];

	recvReq( fd, smLim,
			methodBuf, 
			pathBuf,
			protoBuf );

	printf("method: %s\npath: %s\nprotocol: %s\n", methodBuf, pathBuf, protoBuf);

	
	char webroot[] = "/";
	int notMatching;

	notMatching = strcmp(pathBuf, webroot); // 0 -true
	if( !notMatching ) { // root path '/'

		printf("root path\n");
		//writeRespTextHtml( fd );
		sendHtml(fd, "/index.html", 0);

	} else { 

		char favicon[] = "/favicon.ico";
		notMatching = strcmp(pathBuf, favicon); // 0 -true
		if( !notMatching ){

			char mime[] = "x-icon";
		       	sendImage( fd, favicon, mime);

		} else {

			
			int pathLen = strlen(pathBuf);
			if(pathLen > 96){
				perror("path is over buffer limit of 96\n");
			} else {

				int inValid = checkNameValidity(pathBuf, pathLen);
				if ( inValid ){

					perror("invalid path name\n");

				} else {

					int noPeriod = checkForPeriod(pathBuf, pathLen);

					if ( noPeriod ) {
						// it must be ex) /about or /about/ 

						// normalize the path between ex) /about/ and /about
						// if it is /about/ make it /about, 
						if( pathBuf[pathLen - 1] == '/' ){
							pathBuf[pathLen - 1] = '\0';
							pathLen--;
						}
						printf("normalized path: %s\n", pathBuf);

						char index[] = "/index.html";
						char nameBuf[107];
						sprintf(nameBuf, "%s%s", pathBuf, index);

						char mime[] = "text/html";
						sendHtml( fd, nameBuf, mime );

					} else {
						// has period in path
						// .css .js .html
						if ( pathBuf[pathLen - 1] == 'l' && 
								pathBuf[pathLen - 2] == 'm' && 
								pathBuf[pathLen - 3] == 't' && 
								pathBuf[pathLen - 4] == 'h' && 
								pathBuf[pathLen - 5] == '.' ) {

							char mime[] = "text/html";
							sendHtml(fd, pathBuf, mime );

						} else if ( pathBuf[pathLen - 1] == 's' && 
								pathBuf[pathLen - 2] == 'j' && 
								pathBuf[pathLen - 3] == '.' ) {

							char mime[] = "text/javascript";
							sendHtml( fd, pathBuf, mime );

						} else if ( pathBuf[pathLen - 1] == 's' && 
								pathBuf[pathLen - 2] == 's' && 
								pathBuf[pathLen - 3] == 'c' && 
								pathBuf[pathLen - 4] == '.' ) {

							char mime[] = "text/css";
							sendHtml( fd, pathBuf, mime );

						} else if ( pathBuf[pathLen - 1] == 'g' && 
								pathBuf[pathLen - 2] == 'n' && 
								pathBuf[pathLen - 3] == 'p' && 
								pathBuf[pathLen - 4] == '.' ) {

							char mime[] = "image/png";
							sendImage( fd, pathBuf, mime );

						} else if ( pathBuf[pathLen - 1] == 'g' && 
								pathBuf[pathLen - 2] == 'p' && 
								pathBuf[pathLen - 3] == 'j' && 
								pathBuf[pathLen - 4] == '.' ) {

							char mime[] = "image/jpeg";
							sendImage( fd, pathBuf, mime );

						} else if ( pathBuf[pathLen - 1] == 'g' && 
								pathBuf[pathLen - 2] == 'e' && 
								pathBuf[pathLen - 3] == 'p' && 
								pathBuf[pathLen - 3] == 'j' && 
								pathBuf[pathLen - 4] == '.' ) {

							char mime[] = "image/jpeg";
							sendImage( fd, pathBuf, mime );

						} else if ( pathBuf[pathLen - 1] == 'f' && 
								pathBuf[pathLen - 2] == 'i' && 
								pathBuf[pathLen - 3] == 'g' && 
								pathBuf[pathLen - 4] == '.' ) {

							char mime[] = "image/gif";
							sendImage( fd, pathBuf, mime );

						}


					}


				}
			}

		}
	}



}
