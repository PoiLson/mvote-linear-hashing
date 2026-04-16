#include "../include/main.h"


EnumerateFile::EnumerateFile(const char* path):m_cfPtr(NULL)
{
	this->m_filepath = path;

	this->m_cfPtr = fopen(path, "r");
	if (this->m_cfPtr == NULL)
	{
		fprintf(stderr, "Could not open input file!\n");
		exit(-1);
	}
}
EnumerateFile::~EnumerateFile()
{
	if (this->m_cfPtr != NULL)
	{
		fclose(this->m_cfPtr);
		this->m_cfPtr = NULL;
	}
}

/*
* Åìðéóôåõïìáóôå ôï áñ÷åéï åéóïäïõ ïôé å÷åé 
* óõãêåêñéìåíç ãñáììïãñáöçóç
*/
bool EnumerateFile::MoveNext()
{
	int linecounter = 0;
	char lineBuffer[256] = { 0 };
	const char* separator = " ";
	char* token = NULL;

	/*
	* äéáâáæïõìå ôçí åðïìåíç ãñáììç áðï ôï áñ÷åßï:
	*/
	if (fgets((char*)lineBuffer, sizeof(lineBuffer) - 1, this->m_cfPtr) == NULL)
		return false;
	/*
	* ôé ìéíéìèì ìçêïò ðïõ êáíïõìå äåêôï åéíáé 8 ÷áñáêôçñås:
	*/
	size_t line_lentgh = strlen(lineBuffer);
	if (line_lentgh < 8)
		return false;
	/*
	* Ðåôáìå áðï ôï lineBuffer ôïí ôåëåõôáéï ÷áñáêôçñá '\n'
	*/
	//lineBuffer[line_lentgh - 1] = 0;


	linecounter++;
	// m_pin
	if ((token = strtok(lineBuffer, separator)) == NULL)
	{
		fprintf(stderr, "line #%d, PIN error\n", linecounter);
		exit(-1);
	}
	m_pin = atoi(token);
	
	//m_firstname
	if ((token = strtok(NULL, separator)) == NULL)
	{
		fprintf(stderr, "line #%d, FirstName error\n", linecounter);
		exit(-1);
	}
	strcpy(this->m_firstname, token);

	//m_lastname
	if ((token = strtok(NULL, separator)) == NULL)
	{
		fprintf(stderr, "line #%d, LastName error\n", linecounter);
		exit(-1);
	}
	strcpy(this->m_lastname, token);

	//m_postalCode
	if ((token = strtok(NULL, separator)) == NULL)
	{
		fprintf(stderr, "line #%d, PostalCode error\n", linecounter);
		exit(-1);
	}
	m_postalCode = atoi(token);

	return true;
}
