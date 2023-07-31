#include <stdio.h>


// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
	
};

// Fill out this structure
struct HashType
{
	struct RecordType* pData;
	int hashSz;
	
};



// Compute the hash function
int hash(int x)
{
	return x % 30;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\tID->%d NAME->%c ORDER->%d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	int r;
	struct RecordType* pRecord;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		pRecord = (pHashArray + i)->pData;

		if(pRecord != NULL){
			printf("index %d ->", i);
			for(r = 0; r < (pHashArray + i)->hashSz; ++r){
				printf("ID->%d NAME->%c ORDER->%d", pRecord[r].id, pRecord[r].name, pRecord[r].order);
			}
			printf("\n");
		}
		
	}
	
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0, i, hashpx;
	struct HashType hashArray[30];

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Your hash implementation

	for(i = 0; i < 10; i++){
		hashArray[i].pData = NULL;
		hashArray[i].hashSz = 0;
	}

	for(i = 0; i < recordSz; i++){
		hashpx = hash(pRecords[i].id) % hashSz;
		while (hashArray[hashpx].recordSz.id != 0)
		{
			hashpx = (hashpx + 1) % hashSz;
		}
		hashArray[hashpx].recordSz = pRecords[i];
		
	}

	displayRecordsInHash(hashArray, hashSz);

	free(pRecords);
	return 0;




}