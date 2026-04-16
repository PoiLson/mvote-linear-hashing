# compile with g++
CC = g++
#name of file
FILE = voters50.csv
#enter bucket entries
BUCKET_ENTRIES = 2


program: 
	$(CC) -o mvote EnumerateFile.cpp LinearHash.cpp main.cpp PostalCodeList.cpp Voter.cpp actions.cpp

execute:
	./mvote -f $(FILE) -b $(BUCKET_ENTRIES)
