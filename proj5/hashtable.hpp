//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////hashtable.hpp//////////////////////////
//////////////////////////////////////written by Yuze Liu/////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "hashtable.h"
using namespace cop4530;
using namespace std;

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n

template <typename K, typename V>
HashTable<K,V>::HashTable()
  {
    theList.resize(default_capacity);
  }

template <typename K, typename V>
HashTable<K,V>::HashTable(size_t size)
  {
      theList.resize(prime_below(size));
  }
 
template <typename K, typename V>
HashTable<K,V>::~HashTable()
  {
    //for (size_t i=0;i<theList.size();i++)
     //{
       //theList[i].clear();
     //}
    for(list < pair <K,V> > p:theList)
     {
       p.clear();
     }
    theList.clear();
  }

template <typename K, typename V>
bool HashTable<K,V>::contains(const K &k)
  {
    auto & whichList = theList[myhash(k)];
    auto itr = whichList.begin();

    for(; itr != whichList.end();++itr)
      {
         if(itr -> first == k)
	 //cout << "Find User." << endl;
	 return true;
      }
    return false;
    //return find(begin(element),end(element),k) != end(element);
  }

template <typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> &kv) const
  {
    auto & whichList = theList[myhash(kv.first)];
    auto itr = whichList.begin();

    for(;itr != whichList.end();itr++)
     {
       if( (itr -> first == kv.first) && (itr -> second == kv.second))
         {
           return true;
	 }

     }
    return false;
    
  }
//////////////////////////////////////////////////////////////////////
template<typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> &kv)
  {
    if(currentSize >= theList.size())
     {
        rehash();
     }
      
    auto & whichList = theList[myhash(kv.first)];
    auto itr = whichList.begin();
    
    if(match(kv) == true){
      //cerr <<"\n ****Error: User already exist. Could not add user." <<endl;
      //cout << "test" << endl;
      //cout << kv.first << ":" << kv.second << endl;
      //cout << &kv << endl;
      return false;
     }
    else if(contains(kv.first) == true){
      itr -> second = kv.second;
      cout << "Password updated successfully." <<endl;
      return true;
     }
    else{
      //itr -> first = kv.first;
      //itr -> second = kv.second;
      whichList.push_back(kv);
      cout <<"New user add successfully." <<endl;
      //cout << kv.first << ":" << kv.second << endl;
      ++currentSize;
      return true;
     }
    

  }
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
template<typename K, typename V>
bool HashTable<K,V>::insert(std::pair<K,V> &&kv)
  {
    auto & whichList = theList[myhash(kv.first)];
    auto  itr = whichList.begin();

    if(match(kv) == true){
      cerr << "\n ****Error: User already exists. Could not add user."<<endl;
      return false;
     }
    else if(contains(kv.first) == true){
      itr -> second = kv.second;
      cout << " Password update successfully."<<endl;
      return true;
     }
    else{
      //itr -> first = kv.first;
      //itr -> second = kv.second;
      whichList.push_back(kv);
      cout << "New user add successfully."<<endl;
      ++currentSize;
      return true;
     }

  }
//////////////////////////////////////////////////////////////////////

template<typename K, typename V>
bool HashTable<K,V>::remove(const K &k)
  {
    auto & whichList = theList[myhash(k)];
    auto itr = whichList.begin();
    //auto itr = find(begin(whichList),end(whichList),k);
    for(;itr != whichList.end();++itr)
     {
       if(itr -> first == k)
        {
	  whichList.erase(itr);
	  cout << "\n User: " << k << " deleted " << endl;
	  --currentSize;
	  return true;
	}
     }
    cerr << "\n****Error: User not found.Could not delete user" <<endl;
    return false;

    //if(contains(k) == true)
     //{
      //cerr << "\n ****Erroe:User not found. Could not delete user."<<endl;
      //return false;
     //}
    //whichList.erase(itr);
    //--currentSize;
    //--theList.size();
    //cout << "User deleted successfully." << endl;
    //return true;
  }
    
template<typename K, typename V>
void HashTable<K,V>::clear()
  {
    makeEmpty();
  }

template<typename K, typename V>
bool HashTable<K,V>::load(const char *filename)
  {
    ifstream f(filename);
    if(f)
     {
        while(!f.eof())
	 {
           string line, username, password;
	   getline(f, line);
	   stringstream ss(line);
	   getline(ss, username,':');
	   getline(ss, password,' ');

	   pair<string,string> p;
	   p.first = username;
	   p.second = password;
	   (*this).insert(p);
	 }
	return true;
     }
     else
     {
       cout << "****Error:Unable to open file "<< filename << endl;
       return false;
     }
  }

template<typename K, typename V>
void HashTable<K,V>::dump()
  {
    //int index = 0;
    //for(list<pair<K,V>> l : theList)
     //{
       //cout << "v[" << index++ << "]:";
       //for (pair <K,V> p : l)
        //{
	  //cout << setw(32) << left << p.first + ':' + p.second;
	//}
	//cout << endl;
     //}
    

    for(size_t i=0;i<theList.size();++i)
     {
       std::cout << "V[" << i << "]:";
       auto itr = theList[i].begin();
       for(; itr != theList[i].end();++itr)
        {
          std::cout << itr ->first <<':'<< itr -> second << " ";
	}
       std::cout << endl;

     }
  }

template<typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename)
  {
    ofstream f(filename);
    for(list<pair<K,V>> l : theList)
     {
       for(pair<K,V> p: l)
        {
          f << p.first << ':' << p.second <<endl;
	}
     }
    f.close();
    return true;
  }

template<typename K, typename V>
void HashTable<K,V>::makeEmpty()
  {
    for(auto & thisList:theList)
     {
      thisList.clear();
     }
     currentSize = 0;
  }

template<typename K, typename V>
void HashTable<K,V>::rehash()
  {
   vector<list<pair<K,V>>> oldList = theList;
   theList.resize(prime_below(2*theList.size()));
   for(auto &thisList : theList)
         thisList.clear();
   currentSize = 0;
   for(auto & thisList : oldList)
     for(auto & x : thisList)
       insert(move(x));
  }
template<typename K, typename V>
size_t HashTable<K,V>::myhash(const K &k) const
  {
    static hash<K> hf;
    return hf(k) % theList.size();
  }

template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

// now: 2 <= n < max_prime
std::vector <unsigned long> v (n+1);
setPrimes(v);
while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

