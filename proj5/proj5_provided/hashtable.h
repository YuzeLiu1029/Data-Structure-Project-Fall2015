#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdio.h>
#include <string.h>

namespace cop4530{
// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

  class HashTable
   {
    public:
      HashTable(size_t size =101);
      ~HashTable();
      bool contains(const K & k);
      bool match(const std::pair <K,V> & kv) const;
      bool insert(const std::pair<K,V> & kv);
      bool insert(std::pair<K,V> && kv);
      bool remove(const K & k);
      void clear();
      bool load(const char *filename);
      void dump();
      bool write_to_file(const char *filename);
    private:
      void makeEmpty();
      void rehash();
      size_t myhash(const K & k);
      unsigned long prime_below(unsigned long);
      void setPrimes(vector<unsigned long>&);





   };
}
#include "hashtable.hpp"
#endif
