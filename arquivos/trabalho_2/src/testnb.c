#include <stdio.h>
#include "newborns.h"

int main() {

    NEWBORNS* bb;

    bb = NBCreateInstance("gen_file.bin");
    NBImportCSV(bb, "little.csv");
    NBPrintAllNewborns(bb);
    NBDeleteInstance(bb);

    return 0;
}
