#include "main.h"





void FetchVoters(LinearHash& linearHash, const char* _filename)
{
	EnumerateFile enumerator(_filename);
	while (enumerator.MoveNext())
	{
		Voter* voter = new Voter(enumerator.get_FirstName(), enumerator.get_LastName(), enumerator.get_PIN(), enumerator.get_PostalCode());

		linearHash.insert(voter->getPIN(), 0, voter);
	}
}


void multiplePINs(LinearHash& linearhash, PostalCodeList& listPostalCode, const char* filename)
{
	FILE* cfPtr = NULL;
	cfPtr = fopen(filename, "r");
	if (cfPtr == NULL)
	{
		fprintf(stderr, "Could not open input file!\n");
		return;
	}

	while (1)
	{
		char lineBuffer[256] = { 0 };

		if (fgets((char*)lineBuffer, sizeof(lineBuffer) - 1, cfPtr) == NULL)
			break;

		int pin = atoi(lineBuffer);
		ChangeVoteStatus(linearhash, listPostalCode, pin);
	}

	fclose(cfPtr);
}


void ChangeVoteStatus(LinearHash& linearhash, PostalCodeList& listPostalCode, int pin)
{

	for (int idx = 0; idx < linearhash.getNumBuckets(); idx++)
	{
		HashNode* currentPtr = linearhash.getBuckets(idx);

		while (currentPtr != NULL)
		{
			for (int i = 0; i < currentPtr->get_numOfKeys(); i++)
			{
				if (currentPtr->get_Voter(i) != NULL && currentPtr->get_Voter(i)->getPIN() == pin)
				{
					if (currentPtr->get_Voter(i)->getVoteStatus() == false)
					{
						currentPtr->get_Voter(i)->setVoteStatus(true);
						//now add it to the postalcode list!!!
						listPostalCode.insert(currentPtr->get_Voter(i));
						cout << "|" << currentPtr->get_Voter(i)->getPIN() << "| " << "Marked Voted" << endl;
					}
					else
					{
						printf("The Voter with the PIN = %d has already voted!\n", pin);
					}
					return;
				}
			}
			currentPtr = currentPtr->next;
		}
	}
	printf("%d does not exist!\n", pin);
}




void findPIN(LinearHash& linearHash, int pin)
{
	Voter* voter = linearHash.searchPIN(pin);

	if (voter == NULL)
		cout << "\"Participant " << pin << " not in cohort\"" << endl;
	else
		voter->printVoter();

}

void insertVoter(LinearHash& linearHash, char* buffer)
{
	//i <pin> <lname> <fname> <zip>
	const char* separator = " ";
	char* token = NULL;
	const char* option = "i";

	char firstname[128] = { 0 };
	char lastname[128] = { 0 };
	int pin = 0;
	int postalcode = 0;

	if ((token = strtok(buffer, separator)) == NULL)
		exit(-1);

	if (strcmp(token, option) != 0)
	{
		printf("Unknown command!\n");
		return;
	}

	if ((token = strtok(NULL, separator)) == NULL)
		exit(-1);

	pin = atoi(token);

	if ((token = strtok(NULL, separator)) == NULL)
		exit(-1);
	strcpy(lastname, token);

	if ((token = strtok(NULL, separator)) == NULL)
		exit(-1);
	strcpy(firstname, token);

	if ((token = strtok(NULL, separator)) == NULL)
		exit(-1);
	postalcode = atoi(token);

	Voter* newNode = new Voter(firstname, lastname, pin, postalcode);
	if (linearHash.searchPIN(pin) == NULL)
	{
		linearHash.insert(pin, 0, newNode);
		cout << "\"Inserted " << pin << ", " << lastname << ", " << firstname << ", " << postalcode << ", false\"" << endl;
	}
	else
		printf("%d already exists", pin);
}

void zipcodePINs(PostalCodeList& postalList, int postalCode)
{
	PostalCodeNode* currentPtr = postalList.startPtr;

	if (currentPtr == NULL)
	{
		printf("No voter has voted yet!\n");
		return;
	}

	while (currentPtr->nextPtr != NULL)
	{
		if (currentPtr->postalCode == postalCode)
		{
			printf("\"%d voted in %d\"\n", currentPtr->numOfVoters, postalCode);
			currentPtr->printListOfVoters();
			return;
		}
		currentPtr = currentPtr->nextPtr;
	}

	if (currentPtr->postalCode == postalCode)
	{
		printf("\"%d voted in %d\"\n", currentPtr->numOfVoters, postalCode);
		currentPtr->printListOfVoters();
	}
	else
	{
		printf("No voter with this PIN has voted yet!\n");
	}

}


void findPercentage(LinearHash& linearHash, PostalCodeList& postalList)
{
	float perc = ((float)postalList.numberOfEntries) * (float)(100 / (float)linearHash.getNumberOfVoters());
	printf("percentage = %.3f\n", perc);
}