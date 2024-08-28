#include <stdio.h>
#include "database.h"
#include "master_modules.h"

int get_all_active_modules(FILE *db) {
    MODULE module;
    fseek(db, 0, SEEK_SET);
    while (fread(&module, sizeof(MODULE), 1, db)) {
        if (module.deleted == 0) {
            printf("Module ID: %d, Name: %s, Level: %d, Cell: %d\n",
                   module.module_id, module.module_name, module.memory_level, module.memory_cell);
        }
    }
    return 0;
}

int move_module(FILE *db, int module_id, int new_level, int new_cell) {
    MODULE module;
    fseek(db, module_id * sizeof(MODULE), SEEK_SET);
    if (fread(&module, sizeof(MODULE), 1, db) == 1) {
        if (module.deleted == 0) {
            module.memory_level = new_level;
            module.memory_cell = new_cell;
            fseek(db, module_id * sizeof(MODULE), SEEK_SET);
            fwrite(&module, sizeof(MODULE), 1, db);
            return 0;
        }
    }
    return -1;  // Module not found or deleted
}
