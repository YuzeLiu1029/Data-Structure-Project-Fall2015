///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////proj5.cpp////////////////////////////////////////////
//////////////////////////////////////written by Yuze Liu//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include "passserver.h"
#include <crypt.h>
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace cop4530;

void Menu();
//sPair createPair();
pair<string,string> createPair();
string encryptPass(string);

int main()
{
  size_t userSize;
  char userChoice;
  cout << "Please Enter the size: ";
  cin >> userSize;
  PassServer userNPassHa(userSize);

  Menu();
  cin >> userChoice;

  while (userChoice != 'x')
    {
      switch(userChoice)

        {
          case 'l':
	    {char filename[255];
	     cout << "Enter pass word file name to write to:";
	     cin >> filename;
	     userNPassHa.load(filename);
	    }
	    break;
	  case 'a':
	    //sPair newUser = createPair();
	    {
	      pair<string,string> newUser = createPair();
	      userNPassHa.addUser(newUser);
	    }
	    break;
	  case 'r':
	    {string user;
	     cout << "Enter Username: ";
	     cin >> user;
	     userNPassHa.removeUser(user);
	    }
	    break;
	  case 'c':
	    {string newPass;
	     //sPair existingUser = createPair();
	     pair<string,string> existingUser = createPair();
	     cout <<"Please enter a new password:" << endl;
	     cin >> newPass;
	     newPass = encryptPass(newPass);	     
	     userNPassHa.changePassword(existingUser,newPass);
	    }
	    break;
	  case 'f':
	    {string username;
	     cout <<"Please enter the username: ";
	     cin >> username;
	     userNPassHa.find(username);
	    }
	    break;
	  case 'd':
	    {
	     userNPassHa.dump();
	    }
	    break;
	  case 's':
	    {
	     userNPassHa.size();
	    }
	    break;
	  case 'w':
	    {char filename[255];
	     cout <<"Enter password file name to write to: ";
	     cin >> filename;
	     userNPassHa.write_to_file(filename);
	    }
	    break;
	  case 'x':
            break;
	  default:
	    cerr << "*****Error: Invalid entry. Try again.\n";
	    break;
  
	}
  
    Menu();
    cin >>userChoice;

   }

  return(EXIT_SUCCESS);
}



void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

pair<string,string> createPair()
{
  string u;
  string p;

  cout << "Please enter a Username: " << endl;
  cin >> u;
  cout << "Please enter a password: " << endl;
  cin >> p;

  //sPair newPair;
  pair<string,string> newPair;

  newPair.first = u;
  newPair.second = encryptPass(p);

  return newPair;
}

string encryptPass(string clearText)
{
  char * password = new char [100];
  char salt[] = "$1$########";
  strcpy(password, crypt(clearText.c_str(),salt));
  string encryptedPass = password;
  return encryptedPass.substr(12,34);
}

