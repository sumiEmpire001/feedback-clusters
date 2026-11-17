#pragma once
#include <cstddef>
#include <cstring>
#include <cctype>
namespace embedded_feedback {
enum Status { Ok, InvalidInput, CapacityExceeded };
struct Topic { const char* name; const char* keyword; unsigned count; };
inline bool containsIgnoreCase(const char* text,const char* key){
 if(!text||!key||!*key)return false;
 for(const char* p=text;*p;++p){const char* a=p;const char* b=key;
  while(*a&&*b&&std::tolower((unsigned char)*a)==std::tolower((unsigned char)*b)){++a;++b;}
  if(!*b)return true;
 }return false;
}
inline Status classify(const char* message,Topic* topics,std::size_t n,std::size_t maxMessage=512){
 if(!message||!topics||!n||n>32||!maxMessage||maxMessage>4096)return InvalidInput;
 const std::size_t length=std::strlen(message);
 if(!length)return InvalidInput;
 if(length>maxMessage)return CapacityExceeded;
 for(std::size_t i=0;i<length;++i){const unsigned char ch=(unsigned char)message[i];if(ch<32||ch==127)return InvalidInput;}
 for(std::size_t i=0;i<n;++i){
  if(!topics[i].name||!topics[i].keyword||!topics[i].keyword[0])return InvalidInput;
  if(std::strlen(topics[i].keyword)>64)return CapacityExceeded;
 }
 for(std::size_t i=0;i<n;++i){
  if(containsIgnoreCase(message,topics[i].keyword)){
   if(topics[i].count==~0u)return CapacityExceeded;
  }
 }
 for(std::size_t i=0;i<n;++i)if(containsIgnoreCase(message,topics[i].keyword))++topics[i].count;
 return Ok;
}
}