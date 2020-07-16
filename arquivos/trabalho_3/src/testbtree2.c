#include <stdio.h>

#include "btreebin.c"

int main()
{
    BTREE* a_btree;
    btree_err_t an_error;

    a_btree = openBTree("btr_1.btree", &an_error);

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

    int key_number = 1000000;
    //int val;

    //Inserting keys
    for(int i = 1 ; i < key_number ; i++)
    {
	an_error = insertKeyValBTree(a_btree, i, i+100);
    }

    //Retrieving keys
    for(int i = 1 ; i < key_number ; i++)
    {
	int* val = getValByKeyBTree(a_btree, i);
	if(val[0] != (i+100))
	{
	    printf("Got %d, expected %d!!\n", val[0], i+100);
	}
	free(val);
    }

    closeBTree(a_btree);
}

