#include"structHeader.h"
#include"SerilizationBindName.h"
#include"SerilizationChatInfo.h"

#include<cstdlib>
#include<cstring>

#include<iostream>

#include <cstring>
template <typename T>std::string seriliaze(const T &obj){
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa & obj;
    return ss.str();
}

bool parseMessage(const std::string &input,int *type,std::string &outbuffer){
    auto pos=input.find_first_of(" ");
    if(pos==std::string::npos||pos==0){
        std::cout<<"输入格式错误"<<"\n";
        return false;
    }
    auto command=input.substr(0,pos);
    if(command=="BindName"){
        std::string name=input.substr(pos+1);
        if(name.size()>32){
            std::cout<<"你的名字太长了！"<<"\n";
            return false;
        }
        *type=MT_BIND_NAME;
        outbuffer=seriliaze(SBindName(std::move(name)));       
        return true;
    }
    else if(command=="Chat"){
        std::string chat=input.substr(pos+1);
        if(chat.size()>256){
            std::cout<<"你发送的消息太长了！"<<"\n";
            return false;
        }
        *type=MT_CHAT_INFO;
        outbuffer=seriliaze(SChatInfo(std::move(chat)));    
        return true;
    }
    else{
        std::cout<<"没有这个指令！"<<"\n";
        return false;
    }

}