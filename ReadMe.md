# mvote – Linear Hashing Voting System

## About

This repository contains coursework developed for the *Operating Systems* course at the Department of Informatics and Telecommunications, National and Kapodistrian University of Athens (NKUA).

The project implements a command-line application (`mvote`) that simulates the management of a voting process, focusing on efficient data access and dynamic data structures.

## Main Idea

The goal of this project is to manage a dynamic set of voters and support efficient queries on voting activity.

The system is designed using a combination of data structures:

- **Linear Hashing Table**
  - stores voters indexed by their unique PIN
  - provides expected **O(1)** access time
  - dynamically expands as new records are inserted

- **Inverted List by Postal Code**
  - tracks voters who have voted per postal code
  - allows efficient group-based queries

Each voter is represented by:

- PIN (unique identifier)
- name and surname
- postal code
- voting status (Y/N)

## Functionality

The application supports interactive commands through a CLI interface:

- `l <pin>` → lookup voter by PIN  
- `i <pin> <lname> <fname> <zip>` → insert new voter  
- `m <pin>` → mark voter as having voted  
- `bv <file>` → bulk voting update from file  
- `v` → count voters who have voted  
- `perc` → percentage of voters who have voted  
- `z <zipcode>` → show voters who voted in a specific area  
- `o` → display postal codes sorted by participation  
- `exit` → terminate program and free memory  

The system ensures:

- no duplicate PIN entries  
- dynamic updates across all structures  
- proper memory management  

## Design Notes

- The hash table is implemented using **linear hashing**, allowing dynamic resizing without full rehashing.
- Buckets have a configurable capacity (`-b` flag).
- Overflow buckets are used when collisions occur.
- The inverted list maintains **real-time consistency** with the main hash structure.

The overall structure combines fast individual access with efficient group queries.

## Design & Implementation

The system is structured using multiple cooperating classes, each responsible for a specific part of the application:

### Linear Hashing

The core data structure is implemented in the `LinearHash` class, which manages voters using **linear hashing**.

- Each voter is stored in a `HashNode`
- The structure provides expected **O(1)** access time
- Buckets are dynamically expanded when needed

To handle bucket splitting:

- a new set of buckets is created
- existing elements are rehashed into the updated structure
- temporary storage is used during redistribution
- memory is properly deallocated after reorganization

### File Processing

Input data is handled by the `EnumerateFile` class.

- It reads the input file and parses voter records
- It separates parsing logic from the core data structure
- This design improves modularity and code clarity

### Postal Code Tracking

To support queries per postal code, a custom structure is implemented via the `PostalCodeList` class.

- Each node (`PostalCodeNode`) represents a postal code
- It stores:
  - the postal code
  - the number of voters who have voted
  - a list of voters associated with it

Each postal code node maintains a linked list of voters (`ListNode`), where:

- each node references a `Voter` object
- allows efficient grouping of voters by region

### Command Interface

The system provides an interactive command-line interface.

- A prompt (`printInstructions`) displays available commands
- After each operation, the prompt is shown again
- Commands update both the hash structure and the postal code structure consistently

### Memory Management

Dynamic memory is used throughout the implementation.

- Temporary structures are properly deallocated after use
- All allocated memory is released before program termination

## Usage

The project includes a [`Makefile`](Makefile).

### Compile

```make program```

### Run

```make execute```

or manually:

```./mvote -f voters50.csv -b 2```

#### Parameters:
- ```-f``` → input file containing voters
- ```-b``` → maximum number of entries per bucket

## Input Format
The input file contains voter records in text format, one per line:

```PIN LastName FirstName ZipCode```

## Technologies
- C++
- Linear Hashing
- Dynamic memory management
- Command-line interface (CLI)
