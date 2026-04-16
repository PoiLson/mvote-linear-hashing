#include "../include/main.h"


LinearHash::LinearHash(int sizeOfKeys, int sizeOfBuckets, double loadFactorThreshold)
    :_sizeOfKeys(sizeOfKeys), initialSizeOfBuckets(sizeOfBuckets), loadFactorThreshold(loadFactorThreshold)
{
    numBuckets = initialSizeOfBuckets;

    this->buckets = new HashNode*[numBuckets];
    for (int i = 0; i < initialSizeOfBuckets; i++) {
        this->buckets[i] = make_HashNode();
    }

    currentRound = 0;
    p = 0;
    numOfKeys = 0;
    capacityOfBuckets = numBuckets * 2;
    doubleBuckets = initialSizeOfBuckets;
    numberOfVoters = 0;
}


LinearHash::~LinearHash()
{
    //cout << "LinearHash dtor..." << endl;

    for (int idx = 0; idx < numBuckets; idx++)
    {
        HashNode* currentPtr = buckets[idx];
        while (currentPtr != NULL)
        {
            HashNode* tempPtr = currentPtr;
            currentPtr = currentPtr->next;

            delete tempPtr;
        }
    }
    delete[] buckets;
}

int LinearHash::hashFunction(int key, int round)
{
    int range = initialSizeOfBuckets * pow(2, round);
    return key % range;
}

void LinearHash::splitBucket()
{
    //increase number of buckets in hashing table
    numBuckets++;
    capacityOfBuckets = numBuckets * 2;


    //add a new bucket at the end of our buckets
    buckets = increaseBuckets(buckets, numBuckets);


    //make a new pointer to LinkedLists
    HashNode* ptr = make_HashNode(false);
    HashNode* startptr = ptr;
    //copy all elements

    HashNode* currentPtr = buckets[p];
    int idx = 0;
    while (currentPtr != NULL)
    {
        //copy data
        for (int idx = 0; idx < currentPtr->get_numOfKeys(); idx++)
        {
            if (currentPtr->get_key(idx) != -1)
            {
                ptr->set_key(idx, currentPtr->get_key(idx));
                ptr->set_Voter(idx, currentPtr->get_Voter(idx));
                numOfKeys--;
            }
        }


        currentPtr = currentPtr->next;
        if (currentPtr != NULL)
        {
            ptr->next = make_HashNode(false);
            ptr = ptr->next;
        }
    }

    buckets[p]->Empty();


    //and we have all of our data sorted in ptr
    //and we need to re-insert them

    //i must change the round cause
    //we use the hash_function of this round + 1
    currentRound++;

    ptr = startptr;
    while (ptr != NULL)
    {
        for (int idx = 0; idx < ptr->get_numOfKeys(); idx++)
        {
            if (ptr->get_key(idx) != -1)
            {
                insert(ptr->get_key(idx), 1, ptr->get_Voter(idx));
            }
        }

        ptr = ptr->next;
    }


    //WE HAVE TO DE-ALLOCATE PTR
    ptr = startptr;
    while (ptr !=NULL)
    {
        HashNode* tempPtr = ptr;
        ptr = ptr->next;
        delete tempPtr;
    }


    currentRound--;

    //and last move the pointer p
    p++;
}

void LinearHash::insertIntoBucket(int key, int bucketIndex, Voter* voter)
{
    HashNode* theBucket = this->buckets[bucketIndex];

    for (int idx = 0; idx < theBucket->get_numOfKeys(); idx++)
    {
        if (theBucket->get_key(idx) == -1)
        {
            theBucket->set_key(idx, key);
            theBucket->set_Voter(idx, voter);

            numOfKeys++;
            return;
        }
    }

    /*
    *  we have an overflow!
    */
    HashNode* prvPtr = NULL;
    while (theBucket != NULL) {
        prvPtr = theBucket;
        theBucket = theBucket->next;
    }

    //or add in a already filled node
    for (int idx = 0; idx < prvPtr->get_numOfKeys(); idx++)
    {
        if (prvPtr->get_key(idx) == -1)
        {
            prvPtr->set_key(idx, key);
            prvPtr->set_Voter(idx, voter);

            numOfKeys++;
            return;
        }
    }

    //we may either have to add a new node
    HashNode* newNode = make_HashNode();
    newNode->set_key(0, key);
    newNode->set_Voter(0, voter);

    prvPtr->next = newNode;


    numOfKeys++;
}


//if comeFrom = 1, it comes from split and we re-arrange values so we do not check doubleBuckets
//if comeFrom = 0, it comes from inserting new values from main function
void LinearHash::insert(int value, int comeFrom, Voter* person)
{
    if (comeFrom == 0)
        numberOfVoters++;

    //first of all we have to check if we need to change round
    if (comeFrom == 0 && numBuckets == 2 * doubleBuckets)
    {
        doubleBuckets = numBuckets;
        //go to the next round
        currentRound++;
        //reset pointer p to the start of our buckets
        p = 0;
    }

    int round = currentRound;
    int hash = hashFunction(value, round);

    if (hash < p)
    {
        //we need to re-hash the key
        hash = hashFunction(value, round + 1);
    }


    insertIntoBucket(value, hash, person);

    // Check and split if load factor exceeds the threshold
    double loadFactor = (double)(numOfKeys) / capacityOfBuckets;

    if (loadFactor > loadFactorThreshold)
    {
        currentRound = round;
        splitBucket();
    }

}

int LinearHash::getNumberOfVoters()
{
    return this->numberOfVoters;
}

void LinearHash::printHashTable()
{

    for (int idx = 0; idx < numBuckets; idx++)
    {
        printf("buckets[%d]", idx);
        HashNode* currentPtr = buckets[idx];
        while (currentPtr != NULL)
        {
            printf(" ->");

            for (int i = 0; i < currentPtr->get_numOfKeys(); i++)
            {
                printf("(%d - ", currentPtr->get_key(i));
                if (currentPtr->get_Voter(i) != NULL)
                    printf("%s)", currentPtr->get_Voter(i)->getFullName());
                else
                    printf("null), ");
            }

            currentPtr = currentPtr->next;
        }
        puts("");
    }
    printf("----------------------------\n");
}

Voter* LinearHash::searchPIN(int pin)
{
    int exist = 0;
    for (int idx = 0; idx < numBuckets; idx++)
    {
        HashNode* currentPtr = buckets[idx];
        while (currentPtr != NULL)
        {
            for (int i = 0; i < currentPtr->get_numOfKeys(); i++)
            {
                if (currentPtr->get_Voter(i) != NULL && currentPtr->get_Voter(i)->getPIN() == pin)
                {
                    return currentPtr->get_Voter(i);
                }
            }

            currentPtr = currentPtr->next;
        }
    }
    return NULL;
}
