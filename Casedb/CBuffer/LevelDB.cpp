#include "LevelDB.h"

LevelDB::LevelDB(){
}

LevelDB::LevelDB(leveldb::DB *db, leveldb::WriteOptions wop, leveldb::ReadOptions rop, leveldb::WriteBatch b){
    ldb = db;
    wopt = wop;
    ropt = rop;
    batch = b;
}

void LevelDB::OpenDatabase(const char *path){
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, path, &ldb);
    assert(status.ok());
    std::cout << "Database Opened " << path << std::endl;
}

void LevelDB::CloseDatabase(){
    delete ldb;
}

void LevelDB::Put(std::string key, std::string value){
    assert(ldb->Put(wopt, key, value).ok());
}

std::string LevelDB::Get(std::string key){
    std::string value;
    leveldb::Status s = ldb->Get(leveldb::ReadOptions(), key, &value);
    if(s.ok()){
	return value;
	//cout << key << " => " << value << endl;
    }else{
	std::cout << "failed: " << s.ToString() << " " << key << std::endl;
	return NULL;
    }
}

void LevelDB::Delete(std::string key){

}


