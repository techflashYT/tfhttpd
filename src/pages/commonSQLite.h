#include <sqlite3.h>

#define ERR_START \
	if (status != SQLITE_OK && status != SQLITE_DONE && status != SQLITE_ROW) {\
		const char *sqliteErr = sqlite3_errmsg(db);

#define ERR_END \
		res->status = RES_500;\
		res->data = malloc(strlen(baseMsgPrefix) + strlen(baseMsg) + strlen(baseMsgSuffix) + strlen(sqliteErr) + strlen(baseMsgSuffix2) + strlen(baseMsgSuffix3) + 5);\
		sprintf(res->data, "%s%s%s%s%s%d%s", baseMsgPrefix, baseMsg, baseMsgSuffix, sqliteErr, baseMsgSuffix2, status, baseMsgSuffix3);\
		sqlite3_close(db);\
		res->callback = callback;\
		return;\
	}
