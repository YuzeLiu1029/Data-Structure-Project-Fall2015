///////COP4530 Data Structures,Algorithms, and Generic Programming/////////
/////////////////////////////Project 1/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////////////////////////////Yuze Liu///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//Thank you for checking my code. I am from Mechanical Engineering so I may
//not follow the proper format to write the code.I am sorry if it is hard//
//for you to read my code because of the format problem.///////////////////
//Thanks for your understangding.//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <locale>
#include <iomanip>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// This function will get all the words in the file and put them into a vector
////////////////////////////////////////////////////////////////////////////////////////
vector<string> getWords(string s)
{
    vector<string> parts;
    const char characters[]= "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
    string::size_type from=0;
    string::size_type to=s.length();

    while(from != s.length())
    {
       from = s.find_first_of(characters,from);
       if(from <s.length())
        { to = s.find_first_not_of(characters,from);

          if(to<s.length())
            { parts.push_back(s.substr(from,to-from));
             from = to;
            }
          else if(to == s.length())
             parts.push_back(s.substr(from,s.length()-from-1));
          else
            { parts.push_back(s.substr(from,s.length()-from));
              break;
            }
        } 
        else if(from == s.length())
          parts.push_back(s.substr(from));
        else
          from = s.length();
        
    }
    
    return parts;
}
////////////////////////////////////////////////////////////////////////////////////////
// This function will get all the digital numbers in the file and put them into vector
////////////////////////////////////////////////////////////////////////////////////////
vector<string> getNumber(string s)
{
    vector<string> parts;
    const char characters[]= "0123456789";
    string::size_type from=0;
    string::size_type to=s.length();

    while(from != s.length())
    {
       from = s.find_first_of(characters,from);
       if(from <s.length())
        { to = s.find_first_not_of(characters,from);

          if(to<s.length())
            { parts.push_back(s.substr(from,to-from));
             from = to;
            }
          else if(to == s.length())
             parts.push_back(s.substr(from,s.length()-from-1));
          else
            { parts.push_back(s.substr(from,s.length()-from));
              break;
            }
        }
        else if(from == s.length())
          parts.push_back(s.substr(from));
        else
          from = s.length();

    }
    
    return parts;
}
///////////////////////////////////////////////////////////////////////////////////////
// This function will count how many times a word or number appears in the file
///////////////////////////////////////////////////////////////////////////////////////
int countApperance(vector<string> v,vector<string> v2,int i)
{
  int countNumber;
  countNumber = count (v.begin(), v.end(), v2[i]);
  return countNumber;
}
///////////////////////////////////////////////////////////////////////////////////////
// This function will convert all the words to lowercase
// When I test my code with test3, this part will take a lot of time
///////////////////////////////////////////////////////////////////////////////////////
string conToLowercase(string s)
{
  locale loc;
  string newStr;
  vector<char> vec;
  //char array[s.length()];
  for (string::size_type i=0;i<s.length();++i)
      vec.push_back(tolower(s[i],loc));
  for (string::size_type i=0;i<s.length();++i)
      newStr=newStr+vec[i];
  return newStr;  
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//  Find Unique number or words, find out the array that only contain a word or number once
//  Then use this array and the original one to find how many times a word in the new array
//  appears in the old array 
////////////////////////////////////////////////////////////////////////////////////////
string  getUniString(vector<string> vec,string s)
{
   string UniString ="";
   bool same=true;
   for(string::size_type i=0;i<vec.size();++i)
      {
        if(s!=vec[i])
           same = false;
        else
          { same = true;
            break;
          }
      }
   if(same == false)
     UniString = s;
   else if(same == false)
     UniString = "";
   return UniString;
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
  string content;
  string whole;
  int countNewLine=0;
  ///////////////////////////////////////////////////////////////////////////////////////
  //get all the lines from the file,in the meantime count how many lines,beacuse new line
  //is also a character
  ///////////////////////////////////////////////////////////////////////////////////////
  while(getline(cin,content))
   {
       whole = whole+content;
       countNewLine++;
   }
  //Call the function to get all the words and numbers sequence and put them into vector
  vector<string> words  = getWords(whole);
  vector<string> number = getNumber(whole);
  ////////////////////////////////////////////////////////////////////////////////////////
  //get a vetor to put all the characters we want to check in the vector,except for new line
  //because I have already count it at the beginning of the main function I will add it later
  ////////////////////////////////////////////////////////////////////////////////////////
  vector<char> characters;
     for(int i=32;i<127;i++)
      {
        characters.push_back(i);
      }
   int counts[96]={0};
   for(string::size_type i=0;i<whole.size();i++)
        {
           counts[whole[i]-32]++;

        }
    //Count the unique characters in the whole string
    int uniqueChar =0;
    for(int i=0;i<96;i++)
        if(counts[i] !=0)
          uniqueChar++;
    //Count how many times each character appears in the whole string
    //Pick the top n characters and put them into a new vector
    //Also pick the numbers of its appearence and put this number in another vector
    vector<bool> newTracker(95, false);
    int newN = uniqueChar;
    if(uniqueChar >10)
       newN = 10;
    vector<int> topNChars;
    vector<char> sortedChars;
    for(int i = 0; i < newN; i++)
        {
          int unmarked_index = 0;
          for(; unmarked_index < 95; unmarked_index++)
             {
               if(!newTracker[unmarked_index])
                {
                  break;
                }
             }

          int max = counts[unmarked_index];
          int max_index = unmarked_index;
          for(int j = unmarked_index+1; j < 95; j++)
             {
              if(!newTracker[j] && counts[j] > max)
                {
                  max = counts[j];
                  max_index = j;
                }
             }
          newTracker[max_index] = true;
          topNChars.push_back(max);
          sortedChars.push_back(characters[max_index]);
        }
     //Add the newline character into the vector if it appears 
     //and the times of its appearence is more than the mimum one in the topNChars vector
     for(string::size_type i=0;i<topNChars.size();i++)
       {
          if(countNewLine == topNChars[i])
           {
              sortedChars.insert(sortedChars.begin()+i,10);
              topNChars.insert(topNChars.begin()+i,1);   
	      if(sortedChars.size()>10)
	        {
		  sortedChars.erase(sortedChars.end() - 1);
		  topNChars.erase(topNChars.end() - 1);
		}
	       break;	
       
           }
       }
      if(countNewLine < topNChars.back() && topNChars.size()<10)
	   {
              sortedChars.push_back(10);
	      topNChars.push_back(countNewLine);
	    }
     // Print out the different characters and most used charcters  
     if(countNewLine!=0)
        uniqueChar=uniqueChar+1;
     cout << '\n';
     cout << "Total " << uniqueChar<<" different characters, "<< topNChars.size() << " most used characters:" <<endl;
     for(string::size_type i = 0; i < topNChars.size(); i++)
        {
          if(sortedChars[i]==10)
            {
               cout << "No. " << i <<": " <<left << setw(20) << setfill(' ') <<"\\n" << topNChars[i]<<endl;
            }
          else
          cout << "No. " << i <<": " <<left << setw(20) << setfill(' ') << sortedChars[i] << topNChars[i]<<endl;
        }
  ///////////////////////////////////////////////////////////////////////////////////////
  //The following part will check the words in the file, is the words vector is not empty
  ///////////////////////////////////////////////////////////////////////////////////////
  if(words.size()!=0)  
  {
     //Because words are case insensitive, so I convert them all to lowercase
     //This is the most time consuming part when I test test3.
     vector<string> lowerWords;
     for(string::size_type i=0;i<words.size();i++)
       {
        string data = words[i];
        string lowercase = conToLowercase(data);
        lowerWords.push_back(lowercase);
       }
     vector<string>  uniLowerWords;
     uniLowerWords.push_back(lowerWords[0]);
     //Get all the unique words and put them into one vector
     for(string::size_type i=0;i<lowerWords.size();++i)
      {
         string compareData = lowerWords[i];
         string uniqueData  = getUniString(uniLowerWords,compareData);
         if(uniqueData !="")
            uniLowerWords.push_back(uniqueData);
      }
     //Count the appearence of the word,similar when count the characters
     vector<int> wordsCount;
     for(string::size_type i=0;i<uniLowerWords.size();i++)
       {
         int countNumber = countApperance(lowerWords,uniLowerWords,i);
         wordsCount.push_back(countNumber);
       } 
     vector<bool> tracker(wordsCount.size(), false);
     int n = uniLowerWords.size();
     if(uniLowerWords.size() >10)
       n = 10;
     vector<int> topNWords;
     vector<string> sortedWords;
     for(int i = 0; i < n; i++)
        { 
          string::size_type unmarked_index = 0;
          for(; unmarked_index < tracker.size(); unmarked_index++)
             {
               if(!tracker[unmarked_index])
                {
                  break;
                }
             }

          int max = wordsCount[unmarked_index];
          int max_index = unmarked_index;
          for(string::size_type j = unmarked_index+1; j < tracker.size(); j++)
             {
              if(!tracker[j] && wordsCount[j] > max)
                {
                  max = wordsCount[j];
                  max_index = j;
                }
             }
          tracker[max_index] = true;
          topNWords.push_back(max);
          sortedWords.push_back(uniLowerWords[max_index]);
        }
     //Print out the number of different words and the top 10 words
     cout << '\n';
     cout << "Total "<< uniLowerWords.size() <<" different words, "<<n<<" most used words:"<<endl;
     for(string::size_type i = 0; i < topNWords.size(); i++)
        {
          cout <<"No. " << i <<": " << left << setw(20) << setfill(' ') << sortedWords[i] << topNWords[i]<<endl;
        }

  }
  /////////////////////////////////////////////////////////////////////////////////////////
  //The following part will get the unique number sequence and count the appearence
  /////////////////////////////////////////////////////////////////////////////////////////
  if(number.size()!=0)
  {
      cout << "\n";
      //////////////////////////////////////////////
      vector<string>  uniNumber;
      uniNumber.push_back(number[0]);
      for(string::size_type i=0;i<number.size();++i)
        {
          string compareNumber = number[i];
          string uniqueNumber  = getUniString(uniNumber,compareNumber);
          if(uniqueNumber !="")
          uniNumber.push_back(uniqueNumber);
        }
     ///////////////////////////////////////////////
     vector<int> numberCount;
     for(string::size_type i=0;i<uniNumber.size();i++)
       {
         int countNumber = countApperance(number,uniNumber,i);
         numberCount.push_back(countNumber);
       }  
     //////////////////////////////////////////////
     vector<bool> tracker(uniNumber.size(), false);
     int n = uniNumber.size();
     if(uniNumber.size() >10)
       n = 10;
     vector<int> topNNumber;
     vector<string> sortedNumbers;
     for(int i = 0; i < n; i++)
        {
          string::size_type unmarked_index = 0;
          for(; unmarked_index < tracker.size(); unmarked_index++)
             {
               if(!tracker[unmarked_index])
                {
                  break;
                }
             }
          int max = numberCount[unmarked_index];
          int max_index = unmarked_index;
          for(string::size_type j = unmarked_index+1; j < tracker.size(); j++)
             {
              if(!tracker[j] && numberCount[j] > max)
                {
                  max = numberCount[j];
                  max_index = j;
                }
             }
          tracker[max_index] = true;
          topNNumber.push_back(max);
          sortedNumbers.push_back(uniNumber[max_index]);
        }
     cout << '\n';
     cout << "Total "<<uniNumber.size()<<" different numbers, "<<n<<" most used numbers:"<<endl;
     for(string::size_type i = 0; i < topNNumber.size(); i++)
        {
          cout <<"No. "<<i<<": "<< left << setw(20) << setfill(' ') << sortedNumbers[i] << topNNumber[i]<<endl;
        }
     cout <<'\n';
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  if(words.size() == 0)
  {
    cout <<'\n';
    cout << "Total 0 different words, 0 most used words:"<<endl;
  }
  ///////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////
  if(number.size() ==0)
  {
     cout <<'\n';
     cout << "Total 0 different numberss, 0 most used numbers:"<<endl;
     cout <<'\n';
  }
  return 0;
}
