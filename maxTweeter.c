// maxTweeter.c

#include <stdio.h>
#include <stdlib.h>
/*

Calculate the top 10 tweeters by volume of tweets in a given CSV file of tweets.

output on valid input:
<tweeter>:<count of tweets>

in decreasing order from the most frequent to the 10th most frequent tweeter.


The valid headers were left largely unconstrained deliberately.  There is no guarantee on the number of columns in a valid file, just that 1 column (in potentially any column) is called "name".  You could get a file with just 1 column of names, or several columns with the name column in the beginning, middle, or at the end.  You'd call a file invalid only if the name column didn't appear anywhere in the header row, assuming the file didn't violate another constraint such as being too long in line length or in the number of rows.

max line length, row count, and max number of tweeters

require a name to be at least less than the constraint on line length

can consider empty string as a tweeter name

for ties: just print out whatever you get out of the sort
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

// handle too-long file ( > 20000 )


// handle invalid csv files


	// handle empty file
	
	// handle code injection
	
	// handle no header

	// handle no 'name' column
	
	// handle too many tweeters

	// handle commas inside of tweet

	// handle weird unicode characters inside of tweet

	// handle too-long tweet

// handle valid csv files
/* 
 A valid file is:
-- comma separated : has columns separated with commas, but cannot assume the position of the 'name' column

-- has a header

-- has a column containing tweeter names that is called 'name'

-- has maximum line length not longer than the longest line in the csv file given for hw3

--length <= 20000
-- max number of tweeters is not longer than the set of tweeters in the cl-tweets-short.csv file

-- has no commas inside the tweet
*/




	// printf("%s\n", csv_path );
	return 0;
}
