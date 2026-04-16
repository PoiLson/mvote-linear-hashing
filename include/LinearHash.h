#pragma once




class HashNode {
private:
    const int m_numOfKeys;
    int* m_keys;
    Voter** m_values;
    bool m_ownsVoter;
public:
    int m_id;

    HashNode* next;


    HashNode(int numOfKeys) : HashNode(numOfKeys, true)
    {
        //cout << "HashNode ctor.0..." << endl;

    }
    HashNode(int numOfKeys, bool ownsVoter) : m_numOfKeys(numOfKeys), m_ownsVoter(ownsVoter)
    {
        //cout << "HashNode ctor.1..." << endl;

        m_keys = new int[m_numOfKeys];
        m_values = new Voter * [m_numOfKeys];
        Empty();
    }

    HashNode(const HashNode& src) = delete;
    HashNode& operator=(const HashNode& src) = delete;
    HashNode(HashNode&&) = delete;
    HashNode& operator=(const HashNode&&) = delete;

    ~HashNode()
    {
        //cout << "HashNode dtor..., id="<< m_id << endl;
        if (m_ownsVoter)
        {
            for (int idx = 0; idx < m_numOfKeys; idx++)
            {
                if (m_values[idx] != NULL)
                {
                    delete m_values[idx];
                    m_values[idx] = NULL;
                }
                m_keys[idx] = -1;
            }
        }

        delete[] m_values;
        delete[] m_keys;
    }


    void Empty()
    {
        for (int idx = 0; idx < m_numOfKeys; idx++)
        {
            m_values[idx] = NULL;
            m_keys[idx] = -1;
        }

        this->next = NULL;
    }


    int get_numOfKeys()
    {
        return this->m_numOfKeys;
    }

    int get_key(int idx)
    {
        if (idx < 0 || idx >= m_numOfKeys)
        {
            fprintf(stderr, "HashNode::get_key(%d) -> out of range\n", idx);
            exit(-1);
        }
        return m_keys[idx];
    }
    void set_key(int idx, int value)
    {
        if (idx < 0 || idx >= m_numOfKeys)
        {
            fprintf(stderr, "HashNode::set_key(%d, %d) -> out of range\n", idx, value);
            exit(-1);
        }
        m_keys[idx] = value;
    }

    Voter* get_Voter(int idx)
    {
        if (idx < 0 || idx >= m_numOfKeys)
        {
            fprintf(stderr, "HashNode::get_Voter(%d) -> out of range\n", idx);
            exit(-1);
        }

        return m_values[idx];
    }

    void set_Voter(int idx, Voter* value)
    {
        if (idx < 0 || idx >= m_numOfKeys)
        {
            fprintf(stderr, "HashNode::set_Voter(%d) -> out of range\n", idx);
            exit(-1);
        }

        m_values[idx] = value;
    }


};




class LinearHash {
private:
    const int initialSizeOfBuckets;
    const int _sizeOfKeys;
    const double loadFactorThreshold;
    HashNode** buckets;
    int numBuckets;
    int currentRound;
    int p;  // Pointer to the next bucket to be split
    int numOfKeys;
    int capacityOfBuckets;
    int doubleBuckets;
    int numberOfVoters;

    int hashFunction(int key, int round);

    void splitBucket();

    void insertIntoBucket(int key, int bucketIndex, Voter* voter);



    HashNode* make_HashNode()
    {
        return new HashNode(_sizeOfKeys);
    }
    HashNode* make_HashNode(bool ownsVoter)
    {
        return new HashNode(_sizeOfKeys, ownsVoter);
    }

    HashNode** increaseBuckets(HashNode** buckets, int size)
    {
        HashNode** nbuckets = new HashNode*[size];
        nbuckets[size - 1] = make_HashNode();

        for (int idx = 0; idx < (size - 1); idx++)
        {
            nbuckets[idx] = buckets[idx];
        }

        delete[] buckets;
        return nbuckets;
    }

public:
    //constructor
    LinearHash(int sizeOfKeys, int sizeOfBuckets, double loadFactorThreshold);

    //destructor
    ~LinearHash();


    //if comeFrom = 1, it comes from split and we re-arrange values so we do not check doubleBuckets
    //if comeFrom = 0, it comes from inserting new values from main function
    void insert(int value, int comeFrom, Voter* person);
    int getNumberOfVoters();
    void printHashTable();
    Voter* searchPIN(int pin);

    int getNumBuckets()
    {
        return numBuckets;
    }
    HashNode* getBuckets(int idx)
    {
        return buckets[idx];
    }
};