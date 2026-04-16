#include "main.h"



Voter::Voter(const char* firstname, const char* lastname, int Id, int postalCode)
{
	//cout << "Voter ctor.0 for (" << lastname << ", " << firstname << ")" << endl;
	strcpy(this->firstname, firstname);
	strcpy(this->lastname, lastname);
	this->pin = Id;
	this->postalCode = postalCode;
	this->vote = false;

	sprintf(this->m_fullname, "%s, %s", this->lastname, this->firstname);
}
Voter::~Voter()
{
	//cout << "Voter destructor for (" << lastname << ", " << firstname <<")"<< endl;
}




void Voter::setVoteStatus(bool status)
{
	this->vote = status;
}

void Voter::printVoter() const
{
	cout << pin << ", " << lastname << ", " << firstname << ", " << postalCode << ", ";
	cout << (this->vote ? "true" : "false") << endl;
}