#ifndef BTREE_BIN_H
#define BTREE_BIN_H

typedef struct _btree_handle BTREE;

typedef enum _btree_err
{
    BTR_OK,
    BTR_ERROR,
    BTR_NEW_FILE, //Created new file.
    BTR_CORRUPTED //First byte not equal to '1'.
} btree_err_t;

/* Opens B-Tree.
- In case of file existing, opens the file and checks for consistency.
- In case of file not existing, creates file and returns error type NEW_FILE.
*/
BTREE* openBTree(const char* filename, btree_err_t* err);
void closeBTree(BTREE*);

btree_err_t insertKeyValBTree(BTREE*, int key, int value);
int getValByKeyBTree(BTREE*, int key);

#endif

