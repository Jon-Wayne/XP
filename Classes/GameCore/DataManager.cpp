#include "DataManager.h"

#include "type.h"
#include "../../cocos2d/external/json/document.h"

const unsigned int NameRow = 0;
const unsigned int TypeRow = 1;
const unsigned int DataRow = 2;

static DataManager *s_DataManager = nullptr;

DataManager::DataManager():
_tables(nullptr)
{
    
}

DataManager::~DataManager()
{
    CCLOG("~DataManager");
    
    delete _tables;
}

DataManager *DataManager::getInstance()
{
    if (!s_DataManager)
    {
        s_DataManager = new DataManager();
        if (s_DataManager->init())
        {
            s_DataManager->retain();
        }
        else
        {
            CC_SAFE_DELETE(s_DataManager);
        }
    }
    
    return s_DataManager;
}

bool DataManager::init()
{
    _tables = new std::map<std::string, std::map<int, std::vector<Value>>>();
    
    return true;
}

void DataManager::readTableFromDataFile(std::string &tableName, std::string &fileName)
{
    if(!FileUtils::getInstance()->isFileExist(fileName))
    {
        CCLOG("json file is not find [%s]",fileName.c_str());
        return;
    }
    
    auto fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto jsonString = FileUtils::getInstance()->getStringFromFile(fileName);
    //CCLOG("%s", jsonString.c_str());
    
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(jsonString.c_str());
    
    if (doc.HasParseError() || !doc.IsArray())
    {
        CCLOG("get json data err!");
        return;
    }
    
    rapidjson::Value &name = doc[NameRow];
    rapidjson::Value &type = doc[TypeRow];
    
    if (!name.IsArray())
    {
        CCLOG("namerow is not a array.");
        return;
    }
    
    if (_tables->find(tableName) != _tables->end())
    {
        CCLOG("The table [%s] has existed!", tableName.c_str());
    }
    
    std::map<int, std::vector<Value>> newtable;
    
    auto colNum = name.Size();
    std::vector<std::string> typeName;
    //CCLOG("colNum : %d", colNum);
    
    for(int i=0; i<colNum; i++)
    {
        std::string typeNameStr(type[i].GetString());
        typeName.push_back(typeNameStr);
    }
    
    /*
    int xxx = 0;
    for (auto s : typeName)
    {
        printf("%d-%s ", ++xxx, s.c_str());
    }
    printf("\n");
     */
    
    for(int i=DataRow; i<doc.Size(); i++)
    {
        rapidjson::Value &row=doc[i];
        int dataId = row[(unsigned int)0].GetInt();
        //printf("row [%d] dataId : %d\n", i, dataId);
        
        std::vector<Value> item;
        for (int j=1; j<colNum; j++)
        {
            std::string &typeNameStr = typeName[j];
            //printf("col [%d], typeName [%s]\n", j, typeNameStr.c_str());
            if (typeNameStr == "U8")
            {
                U8 u8 = row[j].GetInt();
                Value v(u8);
                item.push_back(v);
            }
            else if (typeNameStr == "S8")
            {
                int s8 = row[j].GetInt();
                Value v(s8);
                item.push_back(v);
            }
            else if (typeNameStr == "U16")
            {
                int u16 = row[j].GetInt();
                Value v(u16);
                item.push_back(v);
            }
            else if (typeNameStr == "S16")
            {
                int s16 = row[j].GetInt();
                Value v(s16);
                item.push_back(v);
            }
            else if (typeNameStr == "U32")
            {
                int u32 = row[j].GetUint();
                Value v(u32);
                item.push_back(v);
            }
            else if (typeNameStr == "S32")
            {
                S32 s32 = row[j].GetInt();
                Value v(s32);
                item.push_back(v);
            }
            else if (typeNameStr == "U64")
            {
                int u64 = row[j].GetUint64();
                Value v(u64);
                item.push_back(v);
            }
            else if (typeNameStr == "S64")
            {
                int s64 = row[j].GetInt64();
                Value v(s64);
                item.push_back(v);
            }
            else if (typeNameStr == "F32")
            {
                F64 f32 = row[j].GetDouble();
                Value v(f32);
                item.push_back(v);
            }
            else if (typeNameStr == "F64")
            {
                F64 f64 = row[j].GetDouble();
                Value v(f64);
                item.push_back(v);
            }
            else if (typeNameStr == "B8")
            {
                B8 b8 = (B8)row[j].GetInt();
                Value v(b8);
                item.push_back(v);
            }
            else if (typeNameStr == "STR")
            {
                // @todo number string is not supported
                STR str = row[j].GetString();
                Value v(str);
                item.push_back(v);
            }
        }
        //printf("\n");
        newtable.insert(std::pair<int, std::vector<Value>>(dataId, item));
    }
    
    _tables->insert(std::pair<std::string, std::map<int, std::vector<Value>>>(tableName, newtable));
}

std::vector<Value> *DataManager::getDataItem(const std::string &tableName, int dataId) const
{
    char *name = (char *)tableName.c_str();
    
    if (_tables->find(tableName) == _tables->end())
    {
        CCLOG("There is not the table named %s", name);
        return nullptr;
    }
    
    auto &table = _tables->at(name);
    
    if (table.find(dataId) == table.end())
    {
        CCLOG("There is not the item ID : %d in table : %s", dataId, name);
        return nullptr;
    }
    
    auto &item = table.at(dataId);
    
    return &item;
}

void DataManager::printTable(std::string &tableName)
{
    CCLOG("==========  print table : [%s] ===========", tableName.c_str());
    if (_tables->find(tableName) == _tables->end())
    {
        CCLOG("There is not the table named %s", tableName.c_str());
        return;
    }
    
    auto &table = _tables->at(tableName);
    for (auto &v : table)
    {
        auto dataId = v.first;
        printf("[%d]", dataId);
        auto vector = v.second;
        for (auto v2 : vector)
        {
            switch (v2.getType())
            {
                case Value::Type::BYTE:
                    printf("\t%d", v2.asByte());
                    break;
                case Value::Type::INTEGER:
                    printf("\t%d", v2.asInt());
                    break;
                case Value::Type::FLOAT:
                    printf("\t%f", v2.asFloat());
                    break;
                case Value::Type::DOUBLE:
                    printf("\t%f", v2.asDouble());
                    break;
                case Value::Type::BOOLEAN:
                    printf("\t%d", v2.asBool());
                    break;
                case Value::Type::STRING:
                    printf("\t%s", v2.asString().c_str());
                    break;
                default:
                    printf("\tnew type");
                    break;
            }
        }
        printf("\n");
    }
}