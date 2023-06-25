#include "../../common.h"
#include "../../commonSQLite.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Login routine
static void login() {
	sqlite3 *db;
	// open the db
	int status = sqlite3_open("/usr/local/lib/seshcord/users.db", &db);
	ERR_START
		fprintf(stderr, "Cannot open database!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to open SQLite database";
	ERR_END

	// prepare statement
	sqlite3_stmt *statement;
	status = sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE name = ? AND pass = ?", -1, &statement, NULL);
	ERR_START
		fprintf(stderr, "Cannot prepare statement!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to prepare statement for db";
	ERR_END

	// parse JSON
	json_object *jsonData = json_tokener_parse(req->data);
	json_object *nameObj  = json_object_object_get(jsonData, "name");
	json_object *passObj  = json_object_object_get(jsonData, "pass");

	const char *name = json_object_get_string(nameObj);
	const char *passStr = json_object_get_string(passObj);

	// bind data to sqlite statement
	sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
	sqlite3_bind_blob(statement, 2, passStr, 32, SQLITE_STATIC);

	// execute
	status = sqlite3_step(statement);
	ERR_START
		fprintf(stderr, "Cannot execute statement!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to execute statement for db";
	ERR_END
		
	int id = sqlite3_column_int(statement, 0);
	// we're done with the db, shut it down
	sqlite3_finalize(statement);
	sqlite3_close(db);
	if (id < 0) {
		// invalid creds
		res->status = RES_401;
		res->data = "{\"error\":{\"msg\":\"Unauthorized (Bad Credentials)\",\"id\":401}}";
		return;
	}
	// VALID credentials!  Let the user log in.
	res->status = RES_200;

	int fd = open("/dev/urandom", O_RDONLY);
	uint32_t token1;
	uint32_t token2;
	read(fd, &token1, 4);
	read(fd, &token2, 4);
	close(fd);

	uint_fast8_t len = 0;
	if (id > 9)     {len = 1;}
	if (id > 99)    {len = 2;}
	if (id > 999)   {len = 3;}
	if (id > 9999)  {len = 4;}
	if (id > 99999) {len = 5;}
	char *str = malloc(strlen("{\"token\":\"-\",\"id\":}") + 16 + len +1 +1); // FIXME: Why do I need an extra byte on top of the null terminator?

	sprintf(str, "{\"token\":\"%8x-%8x\",\"id\":%d}", token1, token2, id);
	res->data = str;
	res->callback = callback;
}