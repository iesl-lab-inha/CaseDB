// Copyright (c) 2019 The CaseDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "CLevel.h"
#include "LevelDB.h"
#include "Metadata.h"

leveldb::DB* db;
leveldb::WriteOptions wopt;
leveldb::ReadOptions ropt;
leveldb::WriteBatch batch;

CLevel::CLevel(){}

std::string generateKey(int n){
    std::stringstream stream;
    stream << "key_" << n;
    return stream.str();
}

unsigned long CLevel::Put(const char *dir_name){
    system("rm -rf /home/nemo/Desktop/db/leveldb/clevel");
    system("rm -rf /home/nemo/Desktop/db/leveldb/level");

    leveldb::DB* db;
    leveldb::WriteOptions wopt;
    leveldb::ReadOptions ropt;
    leveldb::WriteBatch batch;
    LevelDB ldb(db, wopt, ropt, batch);

    DIR *dr;
    struct dirent *de;
    //char f_url[FILE_URL_SIZE];
    std::string f_url;

    std::ifstream f_in;
    int key = 1, size;
    unsigned long total_size = 0;
 
    Metadata metadata;
    //ldb.OpenDatabase(LEVELDB_DIR);

    dr = opendir(dir_name);
    if(dr == NULL){
        std::cout << "Could not open current directory" << std::endl;
	return 0;
    }

    //read all files from directory
    while((de = readdir(dr)) != NULL){
	// - - - - - Preprocessing part starts - - - - - 
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
	    //std::cout << "Skipping this file. file_name: " << de->d_name << std::endl;
	    continue;
	}
        //strcat(strcat(strcpy(f_url, dir_name), "/"), de->d_name);
	f_url = "";
	f_url.append(dir_name);
	f_url.append("/");
	f_url.append(de->d_name);
        f_in.open(f_url);
	if(!f_in.is_open()){
	    std::cout << "Unable to open the file!" << std::endl;
	    f_in.close();	
	    continue;
	}
	std::string v((std::istreambuf_iterator<char>(f_in)), (std::istreambuf_iterator<char>()));
	size = v.length();
	total_size += size;
	// - - - - - Preprocessing part ends - - - - - 

	if(size >= THRESHOLD){
	    // - - - - - leveldb part starts - - - - - - -

            ldb.Put(generateKey(key), v);
//std::cout<<"key: "<<generateKey(key)<<" value: "<<v<<std::endl;
	    // - - - - - leveldb part ends - - - - - - - -
	}else{
	    // - - - - - clevel part starts - - - - - - -
	    metadata.add(generateKey(key), f_url, size);
	    // - - - - - clevel part ends - - - - - - - -
	}

	key++;
	f_in.close();
    }

    metadata.flush();
    metadata.close_all();

    ldb.CloseDatabase();

    return total_size;

}

std::string CLevel::Get(std::string key){
    leveldb::DB* db;
    leveldb::WriteOptions wopt;
    leveldb::ReadOptions ropt;
    leveldb::WriteBatch batch;
    LevelDB ldb(db, wopt, ropt, batch);
 
    Metadata metadata;
    ldb.OpenDatabase(LEVELDB_DIR);

    std::string lkey, ckey;  
    int index, size;
    std::ifstream umeta("umeta.txt", std::ios::in);
    if(!umeta){
	std::cerr << "Can't open UMeta file!" << std::endl;
    }
    while(umeta >> lkey >> ckey >> index >> size){
	if(lkey.compare(key) == 0){
    	    ldb.OpenDatabase(CLEVELDB_DIR);
    	    std::string group = ldb.Get(key);	
	    return group.substr(index, size);    
	}
    }
    umeta.close();

    ldb.OpenDatabase(LEVELDB_DIR);
    return ldb.Get(key);
}

void CLevel::Delete(std::string key){}
