#pragma once



/*
* Περπαταει γραμμη γραμμη το αρχειο εισοδου!
*/
class EnumerateFile
{
	const char* m_filepath;
	FILE* m_cfPtr;

	int m_pin;
	char m_firstname[64];
	char m_lastname[64];
	int m_postalCode;
public:
	EnumerateFile(const char* filepath);
	~EnumerateFile();
	bool MoveNext();

	const char* get_FirstName() const
	{
		return this->m_firstname;
	}
	const char* get_LastName() const
	{
		return this->m_lastname;
	}
	int get_PostalCode() const
	{
		return this->m_postalCode;
	}
	int get_PIN() const
	{
		return this->m_pin;
	}
};

