#ifndef CLEVEL_H
#define CLEVEL_H
#include "Basic.h"
class CLevel{
    
    public:
	CLevel();
	unsigned long Put(const char *dir_name);
	std::string Get(std::string Key);
	void Delete(std::string key);
};


#endif
