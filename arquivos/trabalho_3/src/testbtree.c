#include <stdio.h>

#include "btreebin.h"

int main()
{
    BTREE* a_btree;
    btree_err_t an_error;

    a_btree = openBTree("testbtr_0.btree", &an_error);

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


    //Time to insert values.

    //Pair 0: K=3,V=5
    an_error = insertKeyValBTree(a_btree, 3, 5);

    getValByKeyBTree(a_btree, 6);

    closeBTree(a_btree);
}

