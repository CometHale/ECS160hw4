// maxTweeter.c

#include <stdio.h>
#include <stdlib.h>
/*

Calculate the top 10 tweeters by volume of tweets in a given CSV file of tweets.

output on valid input:
<tweeter>:<count of tweets>

in decreasing order from the most frequent to the 10th most frequent tweeter.
*/


int main(int argc, char *argv[]){

	char *csv_path;

// handle invalid number of command-line inputs
	if (argc == 0 || argc > 2)
	{
		printf("Usage: ./maxTweeter path/to/tweet_file.csv \n");
		exit(-1);
	}
	else{
		csv_path = argv[1];
	}

// handle invalid file path

// handle incorrect file type

// handle invalid csv files


	// printf("%s\n", csv_path );
	return 0;
}