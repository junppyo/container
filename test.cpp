#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"

# if !defined(USING_STD)
using namespace ft;
#define TEST ft
# else
using namespace std;
#define TEST std
#include <vector>
#include <map>
#include <stack>

# endif

template <class T1, class T2>
void print_map(map<T1, T2> m) {
	std::cout << "size: " << m.size() << std::endl;
	for (typename map<T1, T2>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << "key: " << it->first << " | value: " << it->second << std::endl;
}

int main() {
	TEST::map<int, std::string> mp;
	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	print_map(mp);
}
