#include <stdio.h>

#include "btreebin.c"

int main()
{
    BTREE* a_btree;
    btree_err_t an_error;

    a_btree = openBTree("btr_0.btree", &an_error);

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
/*    an_error = insertKeyValBTree(a_btree, 30, 13);
    an_error = insertKeyValBTree(a_btree, 40, 14);
    an_error = insertKeyValBTree(a_btree, 10, 11);
    an_error = insertKeyValBTree(a_btree, 20, 12);
    an_error = insertKeyValBTree(a_btree, 50, 15);
    an_error = insertKeyValBTree(a_btree, 99, 109);
*/


an_error = insertKeyValBTree(a_btree, 2, 102);
an_error = insertKeyValBTree(a_btree, 3, 103);
an_error = insertKeyValBTree(a_btree, 4, 104);
an_error = insertKeyValBTree(a_btree, 5, 105);
an_error = insertKeyValBTree(a_btree, 6, 106);
an_error = insertKeyValBTree(a_btree, 7, 107);
an_error = insertKeyValBTree(a_btree, 8, 108);
an_error = insertKeyValBTree(a_btree, 9, 109);
an_error = insertKeyValBTree(a_btree, 10, 110);
an_error = insertKeyValBTree(a_btree, 11, 111);
an_error = insertKeyValBTree(a_btree, 12, 112);
an_error = insertKeyValBTree(a_btree, 13, 113);
an_error = insertKeyValBTree(a_btree, 14, 114);
an_error = insertKeyValBTree(a_btree, 15, 115);
an_error = insertKeyValBTree(a_btree, 16, 116);
an_error = insertKeyValBTree(a_btree, 17, 117);
an_error = insertKeyValBTree(a_btree, 18, 118);
an_error = insertKeyValBTree(a_btree, 19, 119);
an_error = insertKeyValBTree(a_btree, 20, 120);
an_error = insertKeyValBTree(a_btree, 21, 121);
an_error = insertKeyValBTree(a_btree, 22, 122);
an_error = insertKeyValBTree(a_btree, 23, 123);
an_error = insertKeyValBTree(a_btree, 24, 124);
an_error = insertKeyValBTree(a_btree, 25, 125);
an_error = insertKeyValBTree(a_btree, 26, 126);
an_error = insertKeyValBTree(a_btree, 27, 127);
an_error = insertKeyValBTree(a_btree, 28, 128);
an_error = insertKeyValBTree(a_btree, 29, 129);
an_error = insertKeyValBTree(a_btree, 30, 130);
an_error = insertKeyValBTree(a_btree, 31, 131);
an_error = insertKeyValBTree(a_btree, 32, 132);
an_error = insertKeyValBTree(a_btree, 33, 133);
an_error = insertKeyValBTree(a_btree, 34, 134);
an_error = insertKeyValBTree(a_btree, 35, 135);
an_error = insertKeyValBTree(a_btree, 36, 136);
an_error = insertKeyValBTree(a_btree, 37, 137);
an_error = insertKeyValBTree(a_btree, 38, 138);
an_error = insertKeyValBTree(a_btree, 39, 139);
an_error = insertKeyValBTree(a_btree, 40, 140);
an_error = insertKeyValBTree(a_btree, 41, 141);
an_error = insertKeyValBTree(a_btree, 42, 142);
an_error = insertKeyValBTree(a_btree, 43, 143);
an_error = insertKeyValBTree(a_btree, 44, 144);
an_error = insertKeyValBTree(a_btree, 45, 145);
an_error = insertKeyValBTree(a_btree, 46, 146);
an_error = insertKeyValBTree(a_btree, 47, 147);
an_error = insertKeyValBTree(a_btree, 48, 148);
an_error = insertKeyValBTree(a_btree, 49, 149);
an_error = insertKeyValBTree(a_btree, 50, 150);
an_error = insertKeyValBTree(a_btree, 51, 151);
an_error = insertKeyValBTree(a_btree, 52, 152);
an_error = insertKeyValBTree(a_btree, 53, 153);
an_error = insertKeyValBTree(a_btree, 54, 154);
an_error = insertKeyValBTree(a_btree, 55, 155);
an_error = insertKeyValBTree(a_btree, 56, 156);
an_error = insertKeyValBTree(a_btree, 57, 157);
an_error = insertKeyValBTree(a_btree, 58, 158);
an_error = insertKeyValBTree(a_btree, 59, 159);
an_error = insertKeyValBTree(a_btree, 60, 160);
an_error = insertKeyValBTree(a_btree, 61, 161);
an_error = insertKeyValBTree(a_btree, 62, 162);
an_error = insertKeyValBTree(a_btree, 63, 163);
an_error = insertKeyValBTree(a_btree, 64, 164);
an_error = insertKeyValBTree(a_btree, 65, 165);
an_error = insertKeyValBTree(a_btree, 66, 166);
an_error = insertKeyValBTree(a_btree, 67, 167);
an_error = insertKeyValBTree(a_btree, 68, 168);
an_error = insertKeyValBTree(a_btree, 69, 169);
an_error = insertKeyValBTree(a_btree, 70, 170);
an_error = insertKeyValBTree(a_btree, 71, 171);
an_error = insertKeyValBTree(a_btree, 72, 172);
an_error = insertKeyValBTree(a_btree, 73, 173);
an_error = insertKeyValBTree(a_btree, 74, 174);
an_error = insertKeyValBTree(a_btree, 75, 175);
an_error = insertKeyValBTree(a_btree, 76, 176);
an_error = insertKeyValBTree(a_btree, 77, 177);
an_error = insertKeyValBTree(a_btree, 78, 178);
an_error = insertKeyValBTree(a_btree, 79, 179);
an_error = insertKeyValBTree(a_btree, 80, 180);
an_error = insertKeyValBTree(a_btree, 81, 181);
an_error = insertKeyValBTree(a_btree, 82, 182);
an_error = insertKeyValBTree(a_btree, 83, 183);
an_error = insertKeyValBTree(a_btree, 84, 184);
an_error = insertKeyValBTree(a_btree, 85, 185);
an_error = insertKeyValBTree(a_btree, 86, 186);
an_error = insertKeyValBTree(a_btree, 87, 187);
an_error = insertKeyValBTree(a_btree, 88, 188);
an_error = insertKeyValBTree(a_btree, 89, 189);
an_error = insertKeyValBTree(a_btree, 90, 190);
an_error = insertKeyValBTree(a_btree, 91, 191);
an_error = insertKeyValBTree(a_btree, 92, 192);
an_error = insertKeyValBTree(a_btree, 93, 193);
an_error = insertKeyValBTree(a_btree, 94, 194);
an_error = insertKeyValBTree(a_btree, 95, 195);
an_error = insertKeyValBTree(a_btree, 96, 196);
an_error = insertKeyValBTree(a_btree, 97, 197);
an_error = insertKeyValBTree(a_btree, 98, 198);
an_error = insertKeyValBTree(a_btree, 99, 199);
an_error = insertKeyValBTree(a_btree, 100, 200);
an_error = insertKeyValBTree(a_btree, 101, 201);
an_error = insertKeyValBTree(a_btree, 102, 202);
an_error = insertKeyValBTree(a_btree, 103, 203);
an_error = insertKeyValBTree(a_btree, 104, 204);
an_error = insertKeyValBTree(a_btree, 105, 205);
an_error = insertKeyValBTree(a_btree, 106, 206);
an_error = insertKeyValBTree(a_btree, 107, 207);
an_error = insertKeyValBTree(a_btree, 108, 208);
an_error = insertKeyValBTree(a_btree, 109, 209);
an_error = insertKeyValBTree(a_btree, 110, 210);
an_error = insertKeyValBTree(a_btree, 111, 211);
an_error = insertKeyValBTree(a_btree, 112, 212);
an_error = insertKeyValBTree(a_btree, 113, 213);
an_error = insertKeyValBTree(a_btree, 114, 214);
an_error = insertKeyValBTree(a_btree, 115, 215);
an_error = insertKeyValBTree(a_btree, 116, 216);
an_error = insertKeyValBTree(a_btree, 117, 217);
an_error = insertKeyValBTree(a_btree, 118, 218);
an_error = insertKeyValBTree(a_btree, 119, 219);
an_error = insertKeyValBTree(a_btree, 120, 220);
an_error = insertKeyValBTree(a_btree, 121, 221);
an_error = insertKeyValBTree(a_btree, 122, 222);
an_error = insertKeyValBTree(a_btree, 123, 223);
an_error = insertKeyValBTree(a_btree, 124, 224);
an_error = insertKeyValBTree(a_btree, 125, 225);
an_error = insertKeyValBTree(a_btree, 126, 226);
an_error = insertKeyValBTree(a_btree, 127, 227);
an_error = insertKeyValBTree(a_btree, 128, 228);
an_error = insertKeyValBTree(a_btree, 129, 229);
an_error = insertKeyValBTree(a_btree, 130, 230);
an_error = insertKeyValBTree(a_btree, 131, 231);
an_error = insertKeyValBTree(a_btree, 132, 232);
an_error = insertKeyValBTree(a_btree, 133, 233);
an_error = insertKeyValBTree(a_btree, 134, 234);
an_error = insertKeyValBTree(a_btree, 135, 235);
an_error = insertKeyValBTree(a_btree, 136, 236);
an_error = insertKeyValBTree(a_btree, 137, 237);
an_error = insertKeyValBTree(a_btree, 138, 238);
an_error = insertKeyValBTree(a_btree, 139, 239);
an_error = insertKeyValBTree(a_btree, 140, 240);
an_error = insertKeyValBTree(a_btree, 141, 241);
an_error = insertKeyValBTree(a_btree, 142, 242);
an_error = insertKeyValBTree(a_btree, 143, 243);
an_error = insertKeyValBTree(a_btree, 144, 244);
an_error = insertKeyValBTree(a_btree, 145, 245);
an_error = insertKeyValBTree(a_btree, 146, 246);
an_error = insertKeyValBTree(a_btree, 147, 247);
an_error = insertKeyValBTree(a_btree, 148, 248);
an_error = insertKeyValBTree(a_btree, 149, 249);

    int key;

    printf("Getting values now...\n");

    key = 90;
    printf("Looking for %d", key);
    getValByKeyBTree(a_btree, key);

    key = 99;
    printf("Looking for %d", key);
    getValByKeyBTree(a_btree, key);

    key = 40;
    printf("Looking for %d", key);
    getValByKeyBTree(a_btree, key);

    closeBTree(a_btree);
}

