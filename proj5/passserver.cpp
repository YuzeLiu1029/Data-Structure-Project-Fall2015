////////////////////////////////////////////////////////////////////////////////
////////////////////////////////passserver.cpp//////////////////////////////////
///////////////////////////////written by Yuze Liu//////////////////////////////
#ifndef PASSSERVER_CPP
#define PASSSERVER_CPP

#include "passserver.h"
using namespace cop4530;

PassServer::PassServer():userNPass(){
}

PassServer::PassServer(size_t size):userNPass(size)
{
  //userNPass.HashTable(size);
  //HashTable(size);
  //userNPass(size);
  //HashTable(size);

}

PassServer::~PassServer()
{
  //userNPass.~HashTable();
  //~userNPass();
  //~HashTable();
}

bool PassServer::load(const char *filename)
{
  return userNPass.load(filename);
}

bool PassServer::addUser(std::pair<string,string> &kv)
{
  //if(currentSize >= size
  //encrypt(kv.second);
  if(userNPass.contains(kv.first) == true)
   {
    cout <<"\n ****Error: User already exist. Could not add user." << endl;
    return false;
   }
  ++currentSize;
  return userNPass.insert(kv);
  //cout << "New user added." << endl;
  //++currentSize;
}

bool PassServer::addUser(std::pair<string,string> &&kv)
{
 // encrypt(kv.second);
 if(userNPass.contains(kv.first) == true)
   {
    cout <<"\n****Error:User already exists.Could not add user." <<endl;
    return false;
   }
  ++currentSize;
  return userNPass.insert(kv);
  //cout << "New user added." << endl;
  //++currentSize;
}

bool PassServer::removeUser(const string &k)
{
 //if(userNPass.contains(k) == true)
   //{
    --currentSize;
    return userNPass.remove(k);
    //--currentSize;
    //cout << "\n User" << k << "deleted" << endl;
    //return true;
   //}
 
 
}

bool PassServer::changePassword(const pair<string,string> &p, const string &newpassword)
{
  if(userNPass.contains(p.first) == false)
   {
     cout << "User doesn't exist." << endl;
     return false;
   }
  else if(userNPass.match(p) == false)
   {
     cout << "Password is wrong. Couldn't update the password." << endl;
     return false;
   }
  else if(p.second == newpassword)
   {
     //userNPass.insert(p);
     cout << "The new password is same as the old one. Couldn't update the password."<<endl;
     return false;
   }
  else
   {
     //p.second = newpassword;
     pair<string, string> newPair;
     newPair.first = p.first;
     newPair.second = newpassword;
     //cout << newPair.second << endl;
     //cout << p.second << endl;
     //cout << &newPair << endl;
     //cout << &p << endl;
     return userNPass.insert(newPair);
   }

}

bool PassServer::find(const string & user)
{
  if(userNPass.contains(user)==true)
   {
    cout << "Find user" << endl;
    return true;
   }

  else
   {
    cout << "Couldn't find the user."<<endl;
    return false;
   }
}

void PassServer::dump()
{
  userNPass.dump();
}

size_t PassServer::size()
{
  cout << currentSize << endl;
  return currentSize;
}

bool PassServer::write_to_file(const char *filename)
{
  return userNPass.write_to_file(filename);
}

//string PassServer::encrypt(const string & str)
//{
//  char * password = new char[100];
//  char salt[] = "$1$########";

//  strcpy(password, crypt(str.c_str(),salt);
//  string encryptedPass = password;
//  return encryptedPass.substr(12,34);
//}

#endif
