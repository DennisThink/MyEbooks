#include <iostream>
#include "leveldb/db.h"
#include "leveldb/options.h"
using namespace leveldb;
int main(int argc,char * argv[])
{
	Options option;
	option.create_if_missing = true;
	std::string strFileName = "dennis1";
	DB * pDB = nullptr;
	Status rt = DB::Open(option,strFileName,&pDB);
	if(rt.ok())
	{
		std::cout<<"Open Succeed"<<std::endl;
	}
	else
	{
		std::cout<<"Open Failed"<<rt.ToString()<<std::endl;
		return 1;
	}
	{
		WriteOptions wtOption;
		pDB->Put(wtOption,std::to_string(1),std::to_string(100));
		pDB->Put(wtOption,std::to_string(1),std::to_string(200));
		ReadOptions rdOption;
		std::string strResult;
		Status stRead = pDB->Get(rdOption,"1",&strResult);
		if(stRead.ok())
		{
			std::cout<<"Read 1   "<<strResult<<std::endl;
		}
	}
	ReadOptions rdOption;
	std::string strResult;
	Status stRead = pDB->Get(rdOption,"1",&strResult);
	if(stRead.ok())
	{
		std::cout<<"Read 1   "<<strResult<<std::endl;
	}
	WriteOptions wtOption;
	pDB->Put(wtOption,"1","10");
	pDB->Put(wtOption,"2","20");
	pDB->Delete(wtOption,"1");
	
	if(nullptr != pDB)
	{
		delete pDB;
		pDB=nullptr;
	}
	return 0;
}