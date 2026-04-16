# compile with g++
CC = g++
#name of file
FILE = voters50.csv
#enter bucket entries
BUCKET_ENTRIES = 2


program: 
	$(CC) -o mvote ./src/EnumerateFile.cpp ./src/LinearHash.cpp ./src/main.cpp ./src/PostalCodeList.cpp ./src/Voter.cpp ./src/actions.cpp

execute:
	./mvote -f $(FILE) -b $(BUCKET_ENTRIES)
