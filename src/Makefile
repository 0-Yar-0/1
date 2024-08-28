CC = gcc
CFLAGS = -Wall -Werror -Wextra

build_db: modules_db.c shared.c master_levels.c master_modules.c master_status_events.c
	$(CC) $(CFLAGS) -o build_db modules_db.c shared.c master_levels.c master_modules.c master_status_events.c

clean:
	rm -f build_db
