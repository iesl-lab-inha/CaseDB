// Copyright (c) 2019 The CaseDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

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
