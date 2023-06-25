#include "../../common.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../commonSQLite.h"
#include <json-c/json.h>
const char *baseMsgPrefix  = "{\"error\":{\"msg\":\"Database error.  Please try again in a bit.\",\"id\":500,\"debugInfo\":{\"msg\":\"";
const char *baseMsgSuffix  = ", `id` is SQLite status, and errmsg is: ";
const char *baseMsgSuffix2 = "\",\"id\":";
const char *baseMsgSuffix3 = "}}}";

static void callback() {
	free(res->data);
}

// Register routine
static void registerUser() {
	sqlite3 *db;
	// open db, create if it doesn't exist
	int status = sqlite3_open("/usr/local/lib/seshcord/users.db", &db);
	ERR_START
		fprintf(stderr, "Cannot open database!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to open SQLite database";
	ERR_END

	// create users table if it doesn't exist
	const char *createTableQuery = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT, name TEXT, pass BLOB, rsrvd BLOB);";
	status = sqlite3_exec(db, createTableQuery, 0, 0, 0);
	
	ERR_START
		fprintf(stderr, "Failed to create `users` table in db!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to create `users` table if it doesn't already exist in db";
	ERR_END

	// prepare statement to write info into db
	sqlite3_stmt *statement;
	status = sqlite3_prepare_v2(db, "INSERT INTO users (email, name, pass, rsrvd) VALUES (?, ?, ?, ?)", -1, &statement, NULL);
	ERR_START
		fprintf(stderr, "Failed to prepare db statement!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to prepare statement to write user details into db";
	ERR_END


	uint8_t sha256passwd[32];
	uint8_t reserved[128];
	memset(reserved, '\0', 128);
	json_object *jsonData = json_tokener_parse(req->data);
	json_object *nameObj  = json_object_object_get(jsonData, "name");
	json_object *passObj  = json_object_object_get(jsonData, "pass");
	json_object *emailObj = json_object_object_get(jsonData, "email");

	const char *name = json_object_get_string(nameObj);
	const char *passStr = json_object_get_string(passObj);
	const char *email = json_object_get_string(emailObj);


	size_t hashLength = strlen(passStr);
    for (size_t i = 0; i < hashLength; i += 2) {
        sscanf(&passStr[i], "%2hhx", &sha256passwd[i / 2]);
    }
	// bind the params
	sqlite3_bind_text(statement, 1, email, -1, SQLITE_STATIC);
	sqlite3_bind_text(statement, 2, name, -1, SQLITE_STATIC);
	sqlite3_bind_blob(statement, 3, sha256passwd, 32, SQLITE_STATIC);
	sqlite3_bind_blob(statement, 4, reserved, 128, SQLITE_STATIC);

	// execute
	status = sqlite3_step(statement);
	ERR_START
		fprintf(stderr, "Failed to execute db statement!  Status: %d  Err: %s\r\n", status, sqliteErr);
		const char *baseMsg = "Failed to write user details into db, `id` is SQLite status, and errmsg is: ";
	ERR_END

	sqlite3_finalize(statement);
	sqlite3_close(db);

	json_object_put(jsonData);

	res->status = RES_200;
	res->data = "Account created";
}