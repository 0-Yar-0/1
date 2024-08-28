#include <stdio.h>
#include "database.h"
#include "master_levels.h"



int get_level_info(FILE *db, int level_number) {
    LEVEL level;
    fseek(db, level_number * sizeof(LEVEL), SEEK_SET);
    if (fread(&level, sizeof(LEVEL), 1, db) == 1) {
        printf("Level %d: Cells: %d, Protection: %d\n", level.level_number, level.cell_count, level.protection_flag);
        return 0;
    }
    return -1;  // Level not found
}

int set_protection_flag(FILE *db, int level_number, int protection_flag) {
    LEVEL level;
    fseek(db, level_number * sizeof(LEVEL), SEEK_SET);
    if (fread(&level, sizeof(LEVEL), 1, db) == 1) {
        level.protection_flag = protection_flag;
        fseek(db, level_number * sizeof(LEVEL), SEEK_SET);
        fwrite(&level, sizeof(LEVEL), 1, db);
        return 0;
    }
    return -1;  // Level not found
}
