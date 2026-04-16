#include "../include/main.h"



char* getFlags(int argc, char* argv[], int* bucketEntries);
char* getOption(char* buffer, int size);
void printInstructions();



/*
* 
* entry of our program!!!
* main(int argc, char* argv[])
* 
*/
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("No flags were inserted!\n");
		return 0;
	}

	int bucketEntries = 0;
	char* _filename = getFlags(argc, argv, &bucketEntries);


	//create and fill hashtable
	int initialSize = 2;  // Initial size as 2^0 = 1
	double loadFactorThreshold = 0.75;
	LinearHash linearHash(bucketEntries, initialSize, loadFactorThreshold);
	FetchVoters(linearHash, _filename);


	//create postal code list
	PostalCodeList postalList;


	//find the option
	while (1)
	{
		char buffer[100] = { 0 };
		const char* separator = " ";
		char* token = NULL;

		printInstructions();
		getOption(buffer, sizeof(buffer));


		if (buffer[0] == 'l' && buffer[1] == ' ')
		{
			//l <pin>, find this pin	const char* separator = " ";
			int pin = atoi(&buffer[2]);
			findPIN(linearHash, pin);
		}
		else if (buffer[0] == 'i' && buffer[1] == ' ')
		{
			insertVoter(linearHash, buffer);
		}
		else if (buffer[0] == 'm' && buffer[1] == ' ')
		{
			int pin = atoi(&buffer[2]);
			ChangeVoteStatus(linearHash, postalList, pin);
		}
		else if (buffer[0] == 'b' && buffer[1] == 'v' && buffer[2] == ' ')
		{
			char filename[128] = { 0 };
			strcpy(filename, &buffer[3]);
			multiplePINs(linearHash, postalList, filename);
		}
		else if (buffer[0] == 'v' && buffer[1] == '\0')
		{
			printf("Voted So Far: %d\n", postalList.numberOfEntries);
		}
		else if (strcmp(buffer, "perc") == 0)
		{
			findPercentage(linearHash, postalList);
		}
		else if (buffer[0] == 'z' && buffer[1] == ' ')
		{
			int postalCode = atoi(&buffer[2]);
			zipcodePINs(postalList, postalCode);
		}
		else if (buffer[0] == 'o' && buffer[1] == '\0')
		{
			postalList.BubbleSort();
			postalList.printPostalList();
		}
		else if (strcmp(buffer,"exit") ==0)
		{
			break;
		}
		else
		{
			printf("Unknown command!\n");
		}

	}



	return 0;
}





char* getFlags(int argc, char* argv[], int* bucketEntries)
{
	char* _filename = NULL;

	for (int idx = 1; idx < argc; idx++)
	{
		char* argument = argv[idx];

		if (strcmp(argument, "-f") == 0)
		{
			idx++;
			_filename = argv[idx];
		}

		if (strcmp(argument, "-b") == 0)
		{
			idx++;
			*bucketEntries = atoi(argv[idx]);
		}
	}

	if (_filename == NULL)
	{
		printf("No flag for file was inserted!\n");
		exit(-1);
	}


	if ((*bucketEntries) == 0)
	{
		printf("No flag for bucket entries was inserted!\n");
		exit(-1);
	}

	return _filename;
}


char* getOption(char* buffer, int size)
{
	memset(buffer, 0, size);
	if (fgets(buffer, size, stdin) != NULL)
	{
		int length = strlen(buffer);
		if (length > 0 && buffer[length - 1] == '\n')
			buffer[length - 1] = '\0';

		return buffer;
	}
	else
	{
		printf("Error in input\n");
		exit(-1);
	}

	return NULL;
}


void printInstructions()
{
	printf("\n\n\n");
	printf("There are these instructions:\n");
	printf("-> l <pin>: find the voter with this <pin>\n");
	printf("-> i <pin> <lname> <fname> <zip>: insert a voter with these characteristics\n");
	printf("-> m <pin>: change vote status to true for the voter with this <pin>\n");
	printf("-> bv <fileOfKeys>: change the vote status to true for all the voters inside the <fileOfKeys>\n");
	printf("-> v: number of voters who have vote\n");
	printf("-> perc: percentage of voters who have vote and all of the voters\n");
	printf("-> z <zipcode>: show the number of voters with this postal code <zipcode> and print their PINs\n");
	printf("-> o: show the postal codes of all voters who have voted (with fthinousa seira)\n");
	printf("-> exit: end program\n");
	printf("\nEnter your desired option:\t");
}


