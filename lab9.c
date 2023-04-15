#include <stdio.h>
#include  <stdlib.h>

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
    struct RecordType *record;
    struct HashType *next;
};

// Compute the hash function
int hash(int x, int hashSz)
{
    return x % hashSz;

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
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
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
	struct HashType *pTemp;


	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		        pTemp = pHashArray + i;
        if (pTemp->record != NULL)
        {
            printf("index %d -> ", i);
            while (pTemp != NULL)
            {
                printf("%d, %c, %d -> ", pTemp->record->id, pTemp->record->name, pTemp->record->order);
                pTemp = pTemp->next;
            }
            printf("\n");
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int hashSz = 10;
    int i;
    int index;
	struct HashType *pHashArray = (struct HashType*) calloc(hashSz, sizeof(struct HashType));
    struct HashType *pTemp;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	    for (i = 0; i < recordSz; ++i)
    {
        index = hash(pRecords[i].id, hashSz);
        pTemp = pHashArray + index;
        if (pTemp->record == NULL)
        {
            pTemp->record = pRecords + i;
        }
        else
        {
            while (pTemp->next != NULL)
            {
                pTemp = pTemp->next;
            }
            pTemp->next = (struct HashType*) malloc(sizeof(struct HashType));
            pTemp->next->record = pRecords + i;
        }
    }

    displayRecordsInHash(pHashArray, hashSz);

    return 0;
}