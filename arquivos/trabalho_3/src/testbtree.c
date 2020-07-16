#include <stdio.h>

#include "btreebin.c"

int main()
{
    BTREE* a_btree;
    btree_err_t an_error;

    a_btree = openBTree("index0.bin", &an_error);

    //Error checking.
    if(an_error == BTR_CORRUPTED)
    {
	fprintf(stderr, "Btree index corrupted!");
	return 1;
    }

    if(an_error == BTR_NEW_FILE)
    {
	fprintf(stdout, "New file created!");
    }

    int key_number = 10000;
    //int val;

    printf("inserting...\n");
    //Inserting keys
    for(int i = 1 ; i <= key_number ; i++)
    {
	an_error = insertKeyValBTree(a_btree, i, i+100);
    }

    //Retrieving keys
    for(int i = 1 ; i <= key_number ; i++)
    {
	int count, val = getValByKeyBTree(a_btree, i, &count);
	if(val != (i+100))
	{
	    printf("Got %d, expected %d!!\n", val, i+100);
	}
    }

    closeBTree(a_btree);
}

