#pragma once

//list of voters to be inserted by their postal code
//only if they have already voted!
class PostalCodeNode
{
public:
	int postalCode;
	ListNode* ListOfVoters;
	PostalCodeNode* nextPtr;
	int numOfVoters;

	PostalCodeNode(Voter* v, int code)
	{
		ListOfVoters = new ListNode(v);
		postalCode = code;
		nextPtr = NULL;
		numOfVoters = 1;
	}

	PostalCodeNode(const PostalCodeNode& src) = delete;
	PostalCodeNode& operator=(const PostalCodeNode& src) = delete;
	PostalCodeNode(PostalCodeNode&&) = delete;
	PostalCodeNode& operator=(const PostalCodeNode&&) = delete;

	~PostalCodeNode()
	{
		ListNode* currentPtr = ListOfVoters;
		while (currentPtr != NULL)
		{
			ListNode* tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		}
	}

	void AddVoter(Voter* voter)
	{
		ListNode* cPtr = ListOfVoters;
		while (cPtr->nextPtr != NULL)
		{
			cPtr = cPtr->nextPtr;
		}
		cPtr->nextPtr = new ListNode(voter);
		numOfVoters++;
	}

	void printListOfVoters()
	{
		//print list of voters who have the same postal code
		ListNode* currentPtr = ListOfVoters;
		while (currentPtr != NULL)
		{
			currentPtr->print();
			currentPtr = currentPtr->nextPtr;
		}
	}



};



class PostalCodeList
{
public:

	PostalCodeNode* startPtr;
	int numberOfEntries;

	PostalCodeList() :startPtr(nullptr), numberOfEntries(0)
	{

	}	
	
	~PostalCodeList()
	{
		//Free PostalCodeNode(s)
		PostalCodeNode* currentPtr = startPtr;

		while(currentPtr != NULL)
		{
			PostalCodeNode* tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		}

	}


	void insert(Voter* person);

	void swapElements(PostalCodeNode* a, PostalCodeNode* b) {
		// Swap postalCode
		int tempPostalCode = a->postalCode;
		a->postalCode = b->postalCode;
		b->postalCode = tempPostalCode;

		// Swap numOfVoters
		int tempNumOfVoters = a->numOfVoters;
		a->numOfVoters = b->numOfVoters;
		b->numOfVoters = tempNumOfVoters;

		// Swap ListOfVoters
		ListNode* tempList = a->ListOfVoters;
		a->ListOfVoters = b->ListOfVoters;
		b->ListOfVoters = tempList;
	}

	void BubbleSort()
	{
		PostalCodeNode* currentPtr = startPtr;
		/*while (currentPtr != NULL)
		{*/

		for (unsigned int pass = 1; pass < numberOfEntries; ++pass)
		{
			// loop to control number of comparisons per pass
			for (size_t j = 0; j < numberOfEntries - 1; ++j)
			{

				// swap elements if out of order
				if (currentPtr != NULL)
				{
					if (currentPtr->nextPtr != NULL)
					{
						if (currentPtr->numOfVoters < currentPtr->nextPtr->numOfVoters)
						{
							swapElements(currentPtr, currentPtr->nextPtr);
						}
					}
					currentPtr = currentPtr->nextPtr;
				}

			}

			currentPtr = startPtr;
		}
	}

	void printPostalList()
	{

		PostalCodeNode* currentPtr = startPtr;
		while (currentPtr != NULL)
		{
			printf("\"%d %d\"\n", currentPtr->postalCode, currentPtr->numOfVoters);
			ListNode* tempPtr = currentPtr->ListOfVoters;
			while (tempPtr != NULL)
			{
				//printf("\t");
				//tempPtr->print();
				tempPtr = tempPtr->nextPtr;
			}
			currentPtr = currentPtr->nextPtr;
		}

	}


};