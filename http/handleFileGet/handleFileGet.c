#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sendTextFile( int fd, char filepath[], char mime[] );

int checkNameValidity( char name[], int len );

int checkForPeriod(char name[],  int len);

void handleFileGet( int fd , char *path ){
	printf("handleFileGet()\n");

	char *hmpage = "/";
	char *webroot = "./webroot";
	char *index = "index.html";
	int miniLim = 32;

	// https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types
	char mimeHTML[] = "text/html";
	char mimeCSS[] = "text/css";
	char mimeJS[] = "text/javascript";
	char mimeICO[] = "image/x-icon";
	char mimeJPEG[] = "image/jpeg";
	char mimePNG[] = "image/png";
	char mimeGIF[] = "image/gif";

	int lim = 96;
	char fullPath[96];

	int notMatch = strcmp ( path , hmpage ) ; 
	// return 0 if match
	if ( !notMatch ) {
		// serve /index.html
		printf("hmpage\n");
		sprintf(fullPath, "%s/%s", webroot, index);
		sendTextFile( fd , fullPath , mimeHTML);
		return ;
	}

	int len = strlen(path);

	int notValid = checkNameValidity ( path , len ) ;

	if ( notValid ) return ;

	int noPeriod = checkForPeriod ( path , len ) ;
	
	if ( noPeriod ) {
		// definitely index.html
		// might have trailing slash or not
		// ex) /about or /about/
		if ( *( path + len - 1 ) == '/' ) {
			
			*( path + len - 1 ) = '\0' ;
		}

		sprintf ( fullPath, "%s%s/%s", 
				webroot, 
				path,
				index );

		sendTextFile( fd , fullPath , mimeHTML );

		return;
	} 

	sprintf ( fullPath, "%s%s", webroot , path ) ;
	
	// text) .html, .css, .js
	if( *( path + len - 1 ) == 'l' 
		&& *( path + len - 2 ) == 'm' 
		&& *( path + len - 3 ) == 't' 
		&& *( path + len - 4 ) == 'h' 
		&& *( path + len - 5 ) == '.' ){

		sendTextFile( fd , fullPath , mimeHTML);
		return;
	}	
	
	if( *( path + len - 1 ) == 's' 
		&& *( path + len - 2 ) == 's' 
		&& *( path + len - 3 ) == 'c' 
		&& *( path + len - 4 ) == '.' ){

		sendTextFile( fd , fullPath , mimeCSS);
		return;
	}	
		
	if( *( path + len - 1 ) == 's' 
		&& *( path + len - 2 ) == 'j' 
		&& *( path + len - 3 ) == '.' ){

		sendTextFile( fd , fullPath , mimeJS);
		return;
	}	


	// binary) .ico .png .jpg .gif 
	if( *( path + len - 1 ) == 'o' 
		&& *( path + len - 2 ) == 'c' 
		&& *( path + len - 3 ) == 'i' 
		&& *( path + len - 4 ) == '.' ){

		sendBinaryFile( fd , fullPath , mimeICO);
		return;
	}	
		

	// binary) .ico .png .jpg .gif 
	if( *( path + len - 1 ) == 'g' 
		&& *( path + len - 2 ) == 'p' 
		&& *( path + len - 3 ) == 'j' 
		&& *( path + len - 4 ) == '.' 
		|| 
		*( path + len - 1 ) == 'g' 
		&& *( path + len - 2 ) == 'e' 
		&& *( path + len - 3 ) == 'p' 
		&& *( path + len - 4 ) == 'j' 
		&& *( path + len - 5 ) == '.' ){

		sendBinaryFile( fd , fullPath , mimeJPEG);
		return;
	}	
		

	// binary) .ico .png .jpg .gif 
	if( *( path + len - 1 ) == 'g' 
		&& *( path + len - 2 ) == 'n' 
		&& *( path + len - 3 ) == 'p' 
		&& *( path + len - 4 ) == '.' ){

		sendBinaryFile( fd , fullPath , mimePNG);
		return;
	}	
		

	// binary) .ico .png .jpg .gif 
	if( *( path + len - 1 ) == 'f' 
		&& *( path + len - 2 ) == 'i' 
		&& *( path + len - 3 ) == 'g' 
		&& *( path + len - 4 ) == '.' ){

		sendBinaryFile( fd , fullPath , mimeGIF);
		return;
	}	
		


}
