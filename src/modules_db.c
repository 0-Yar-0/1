#include <stdio.h>
#include <stdlib.h>
#include "database.h"

// Прототипы функций
int handle_select(FILE *db);
int handle_insert(FILE *db);
int handle_update(FILE *db);
int handle_delete(FILE *db);
int handle_get_active_modules(FILE *db);
int handle_delete_modules_by_ids(FILE *db);
int handle_set_protected_mode(FILE *db);
int handle_move_module(FILE *db);
int handle_set_level_protection(FILE *db);

void display_menu() {
    printf("Please choose one operation:\n");
    printf("1. SELECT\n");
    printf("2. INSERT\n");
    printf("3. UPDATE\n");
    printf("4. DELETE\n");
    printf("5. Get all active additional modules\n");
    printf("6. Delete modules by ids\n");
    printf("7. Set protected mode for module by id\n");
    printf("8. Move module by id to specified memory level and cell\n");
    printf("9. Set protection flag of the specified memory level\n");
    printf("> ");
}

int main() {
    int choice;
    display_menu();
    scanf("%d", &choice);

    FILE *modules_db = fopen("materials/master_modules.db", "rb+");
    FILE *levels_db = fopen("materials/master_levels.db", "rb+");
    FILE *status_events_db = fopen("materials/master_status_events.db", "rb+");

    if (!modules_db || !levels_db || !status_events_db) {
        printf("Error opening database files.\n");
        return -1;
    }

    switch (choice) {
        case 1:
            handle_select(modules_db);
            break;
        case 2:
            handle_insert(modules_db);
            break;
        case 3:
            handle_update(modules_db);
            break;
        case 4:
            handle_delete(modules_db);
            break;
        case 5:
            handle_get_active_modules(modules_db);
            break;
        case 6:
            handle_delete_modules_by_ids(modules_db);
            break;
        case 7:
            handle_set_protected_mode(status_events_db);
            break;
        case 8:
            handle_move_module(modules_db);
            break;
        case 9:
            handle_set_level_protection(levels_db);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    fclose(modules_db);
    fclose(levels_db);
    fclose(status_events_db);

    return 0;
}

int handle_select(FILE *db) {
    int id;
    printf("Enter the ID of the record to select: ");
    scanf("%d", &id);

    ENTITY *entity = select(db, id);
    if (entity) {
        // Пример вывода для модуля
        printf("ID: %d, Name: %s\n", entity->module_id, entity->module_name);
        free(entity);
    } else {
        printf("Record not found.\n");
    }

    return 0;
}

int handle_insert(FILE *db) {
    MODULE module;
    printf("Enter module ID: ");
    scanf("%d", &module.module_id);
    printf("Enter module name: ");
    scanf("%s", module.module_name);
    printf("Enter memory level: ");
    scanf("%d", &module.memory_level);
    printf("Enter memory cell: ");
    scanf("%d", &module.memory_cell);
    module.deleted = 0;

    insert(db, (ENTITY *)&module);
    printf("Module inserted.\n");
    return 0;
}

int handle_update(FILE *db) {
    int id;
    MODULE module;
    printf("Enter the ID of the module to update: ");
    scanf("%d", &id);

    printf("Enter new module name: ");
    scanf("%s", module.module_name);
    printf("Enter new memory level: ");
    scanf("%d", &module.memory_level);
    printf("Enter new memory cell: ");
    scanf("%d", &module.memory_cell);
    module.deleted = 0;

    update(db, id, (ENTITY *)&module);
    printf("Module updated.\n");
    return 0;
}

int handle_delete(FILE *db) {
    int id;
    printf("Enter the ID of the module to delete: ");
    scanf("%d", &id);

    if (delete(db, id) == 0) {
        printf("Module marked as deleted.\n");
    } else {
        printf("Module not found.\n");
    }

    return 0;
}

int handle_get_active_modules(FILE *db) {
    get_all_active_modules(db);
    return 0;
}

int handle_delete_modules_by_ids(FILE *db) {
    int ids[10], count, i;
    printf("Enter the number of modules to delete: ");
    scanf("%d", &count);

    printf("Enter module IDs to delete: ");
    for (i = 0; i < count; i++) {
        scanf("%d", &ids[i]);
        delete(db, ids[i]);
    }
    printf("Modules marked as deleted.\n");

    return 0;
}

int handle_set_protected_mode(FILE *db) {
    int id;
    printf("Enter the ID of the module to set to protected mode: ");
    scanf("%d", &id);

    if (set_protected_mode(db, id) == 0) {
        printf("Module set to protected mode.\n");
    } else {
        printf("Failed to set module to protected mode.\n");
    }

    return 0;
}

int handle_move_module(FILE *db) {
    int id, level, cell;
    printf("Enter the ID of the module to move: ");
    scanf("%d", &id);
    printf("Enter the new memory level: ");
    scanf("%d", &level);
    printf("Enter the new memory cell: ");
    scanf("%d", &cell);

    if (move_module(db, id, level, cell) == 0) {
        printf("Module moved.\n");
    } else {
        printf("Failed to move module.\n");
    }

    return 0;
}

int handle_set_level_protection(FILE *db) {
    int level, protection_flag;
    printf("Enter the level number: ");
    scanf("%d", &level);
    printf("Enter the protection flag (0 or 1): ");
    scanf("%d", &protection_flag);

    if (set_protection_flag(db, level, protection_flag) == 0) {
        printf("Protection flag set.\n");
    } else {
        printf("Failed to set protection flag.\n");
    }

    return 0;
}
