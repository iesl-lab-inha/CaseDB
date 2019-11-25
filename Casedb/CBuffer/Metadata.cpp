// Copyright (c) 2019 The CaseDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "Metadata.h"

std::string generateCKey(int n){
    std::stringstream stream;
    stream << "c_key_" << n;
    return stream.str();
}

Metadata::Metadata(){
    list = new Meta[MAX_NUMBER_FILES];
    order = 0;
    index = 0;
};
void Metadata::add(std::string key, std::string url, int size){
    list[order].id = key;
    list[order].url = url;
    list[order].size = size;
    list[order].index = index;

    order++;
    index+=size;
    if(index >= THRESHOLD){
	index = 0;
    }
}

void Metadata::flush(){
std::cout<<"flushing"<<std::endl;
    std::ofstream log_file;        
    std::ifstream f_in;
    int ckey = 1;

    leveldb::DB* db;
    leveldb::WriteOptions wopt;
    leveldb::ReadOptions ropt;
    leveldb::WriteBatch batch;
    LevelDB ldb(db, wopt, ropt, batch);

    ldb.OpenDatabase(CLEVELDB_DIR);
    log_file.open("umeta.txt", std::ofstream::out | std::ofstream::app);

    if(!log_file.is_open()){
	std::cout << "Unable to open Log File. Flush failed!" << std::endl;
	exit(1);
    }

   //"dsdghdfsdhgfgsdjhfgdsjhfhgdsjhfsdjfgdsjhgfddsfdfg"+

    std::string value;
    for(int i = 0; i < order; i++){
//std::cout<<i<<" ";
	log_file << list[i].id << "," << generateCKey(ckey) << "," << list[i].index << "," << list[i].size << std::endl;

        f_in.open(list[i].url);
	if(!f_in.is_open()){
	    std::cout << "Unable to open the file! Flush Failed!" << std::endl;
	    f_in.close();
	    close_all();	
	    exit(1);
	}
	std::string v((std::istreambuf_iterator<char>(f_in)), (std::istreambuf_iterator<char>()));
	value.append(v);
	//std::cout << "ckey: " << generateCKey(ckey) << "\nurl: " << list[i].url << "\ndata: " << v << "\nvalue: " << value << std::endl;

	if((list[i].index + list[i].size) >= THRESHOLD){
	    if(value.compare("") == 0){
		std::cout<<"Value: " << value << std::endl;
	    }
	    //std::cout << "ckey: " << generateCKey(ckey) << "Value1: " << value << std::endl;
	    ldb.Put(generateCKey(ckey), value);
	    value = "";
	    ckey++;
	    //std::cout << "ckey: " << generateCKey(ckey) <<"Value2: " << value << "\n" << std::endl;
	}
	f_in.close();
    }
    ldb.Put(generateCKey(ckey), value);

    ldb.CloseDatabase();
    //log_file.close();
}

void Metadata::close_all(){
    delete[] list;

}
