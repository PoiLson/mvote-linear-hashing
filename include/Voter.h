#pragma once



class Voter
{
private:
	char firstname[128];
	char lastname[128];
	int pin;
	int postalCode;
	bool vote;
	char m_fullname[256];

public:
	//constructor
	Voter(const char* firstname, const char* lastname, int Id, int postalCode); 

	Voter(const Voter& src) = delete;
	Voter& operator=(const Voter& src) = delete;
	Voter(Voter&&) = delete;
	Voter& operator=(const Voter&&) = delete;

	//destructor
	~Voter();

	unsigned int getPIN() const
	{
		return this->pin;
	}

	const char* getLastName() const
	{
		return this->lastname;
	}

	const char* getFirstName() const
	{
		return this->firstname;
	}

	int getPostalCode() const
	{
		return this->postalCode;
	}

	bool getVoteStatus() const
	{
		return this->vote;
	}

	const char* getFullName() const
	{
		return m_fullname;
	}


	void setVoteStatus(bool status);

	void printVoter() const;


};


class ListNode
{
public:
	Voter* person;
	ListNode* nextPtr;

	ListNode(Voter* v)
	{
		person = v;
		nextPtr = NULL;
	}
	~ListNode()
	{

	}

	void print()
	{
		if(person!= nullptr)
			cout << "\"" << person->getPIN() << "\"" << endl;
		else
			cout << "\"" << " NULL " << "\"" << endl;
	}

};
