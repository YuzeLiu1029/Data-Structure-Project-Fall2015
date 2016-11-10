////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////passserver.h/////////////////////////////////////
////////////////////////////////////written by Yuze Liu/////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"

namespace cop4530{

  class PassServer{
    public:
     PassServer();
     PassServer(size_t size);
     ~PassServer();
     bool load(const char *filename);
     bool addUser(std::pair<string, string> & kv);
     bool addUser(std::pair<string, string> && kv);
     bool removeUser(const string & k);
     bool changePassword(const pair<string, string> &p, const string &newpassword);
     bool find(const string & user);
     void dump();
     size_t size();
     bool write_to_file(const char *filename);
    private:
     HashTable<string, string> userNPass;
     //string encrypt(const string & str);
     size_t currentSize = 0;
  };
}

#include "passserver.cpp"
#endif
