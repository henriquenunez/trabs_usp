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
    an_error = insertKeyValBTree(a_btree, 3, 13);
    an_error = insertKeyValBTree(a_btree, 4, 14);
    an_error = insertKeyValBTree(a_btree, 1, 11);
    an_error = insertKeyValBTree(a_btree, 2, 12);
    an_error = insertKeyValBTree(a_btree, 5, 15);
    an_error = insertKeyValBTree(a_btree, 99, 109);

    //getValByKeyBTree(a_btree, 6);

    closeBTree(a_btree);
}

