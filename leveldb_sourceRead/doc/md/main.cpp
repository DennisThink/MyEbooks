#include <iostream>
#include <stdio.h>
int main(int argc,char * argv[])
{
    char buff[128]={0};
    for(int i = 0 ; i < 100000000; i+=100)
    {
        sprintf(buff,"%06llu",static_cast<unsigned long long>(i));
        std::cout<<buff<<std::endl;
    }
    return 0;
}