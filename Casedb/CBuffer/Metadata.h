#ifndef METADATA_H
#define METADATA_H

#include "Basic.h"
#include "LevelDB.h"

struct Meta{
    std::string id;
    std::string url;
    int index;
    int size;

    //Meta *next;
};

class Metadata{
    private:
	Meta *list;
	int order;
	int index;

    public:
	Metadata();
	void add(std::string key, std::string value, int size);
	void flush();
	void close_all();
};

#endif
