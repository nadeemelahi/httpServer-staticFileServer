#include <stdio.h>
#include <string.h>

int checkNameValidity( char name[] , int len ) {

	int lim = 96; 
	if ( len > lim ) {
		perror("GET path is way too long, ignoring\n");
		return 1;
	}

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
