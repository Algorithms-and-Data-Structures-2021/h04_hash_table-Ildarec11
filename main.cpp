#include <iostream>
#include "hash_table.hpp"
using namespace itis;

int main(int argc, char **argv) {
  std::cout << "Hello, stranger!" << std::endl;
  auto t = new HashTable(5, 0.1);
  t->Put(4, "result");
  std::cout << t->ContainsKey(4);
  t->Remove(4);
  std::cout << t->ContainsKey(4);
  t->Put(4, "value 2");
  t->Put(3, "4");
 std::vector<std::string> rslt = t->values();
 std::cout << rslt.size();
  return 0;
}