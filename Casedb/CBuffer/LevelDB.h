#ifndef LEVELDB_H
#define LEVELDB_H

#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "Basic.h"

class LevelDB{
    private:
	leveldb::DB *ldb;
	leveldb::WriteOptions wopt;
	leveldb::ReadOptions ropt;
	leveldb::WriteBatch batch;
    public:
	LevelDB();
	LevelDB(leveldb::DB *db, leveldb::WriteOptions wop, leveldb::ReadOptions rop, leveldb::WriteBatch b);
	void OpenDatabase(const char *path);
	void CloseDatabase();
	void Put(std::string key, std::string value);
	std::string Get(std::string key);
	void Delete(std::string key);
};


#endif
