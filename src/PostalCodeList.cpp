#include "../include/main.h"

void PostalCodeList::insert(Voter* person)
{
	if (person->getVoteStatus() == true)
	{
		numberOfEntries++;
		int postalCode = person->getPostalCode();


		if (startPtr == NULL)
		{
			startPtr = new PostalCodeNode(person, postalCode);
		}
		else
		{
			bool exist = false;
			PostalCodeNode* tempPtr = startPtr;
			while (tempPtr->nextPtr != NULL)
			{
				if (tempPtr->postalCode == postalCode)
				{
					tempPtr->AddVoter(person);
					exist = true;
					return;
				}
				tempPtr = tempPtr->nextPtr;
			}

			if(tempPtr->postalCode == postalCode)
			{
				tempPtr->AddVoter(person);
				exist = true;
				return;
			}

			if (exist == false)
				tempPtr->nextPtr = new PostalCodeNode(person, postalCode);
		}
	}
}
