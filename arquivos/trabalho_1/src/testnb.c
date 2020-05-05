#include <stdio.h>
#include "newborns.h"

int main() {

    NEWBORNS* bb;

    bb = NBCreateInstance("gen_file.bin");
    NBImportCSV(bb, "arquivoEntrada.csv");
    NBPrintAllNewborns(bb);
    NBDeleteInstance(bb);

    return 0;
}
