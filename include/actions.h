#pragma once




void FetchVoters(LinearHash& linearHash, const char* _filename);
void multiplePINs(LinearHash& linearhash, PostalCodeList& listPostalCode, const char* filename);
void ChangeVoteStatus(LinearHash& linearhash, PostalCodeList& listPostalCode, int pin);
void findPIN(LinearHash& linearHash, int pin);
void insertVoter(LinearHash& linearHash, char* buffer);
void zipcodePINs(PostalCodeList& postalList, int postalCode);
void findPercentage(LinearHash& linearHash, PostalCodeList& postalList);


