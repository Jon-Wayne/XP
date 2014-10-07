//
//  DataManager.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__DataManager__
#define __XP__DataManager__

#include "cocos2d.h"
using namespace cocos2d;

class DataManager : public Ref
{
public:
    DataManager();
	~DataManager();

	static DataManager *getInstance();
	bool init();
    
    void readTableFromDataFile(std::string &tableName, std::string &fileName);
    std::vector<Value> *getDataItem(const std::string &tableName, int dataId) const;
    void printTable(std::string &tableName);
private:
    void readData();
private:
    std::map<std::string, std::map<int, std::vector<Value>>>  *_tables;
};

#endif /* defined(__XP__DataManager__) */
