int checkForPeriod(char name[], int len){

	int idx;
	for ( idx = 0; idx < len; idx++ ){

		if ( name[idx] == '.' ) return 0; // we have a period

	}


	return 1; // we DO NOT have a period
}
