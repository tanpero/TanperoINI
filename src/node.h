#ifndef _TANPERO_INI_NODE_H_
#define _TANPERO_INI_NODE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>

namespace ini
{
    using TString = std::string;
    using TVector = std::vector;
    using TMap    = std::map;
    using TPair   = std::pair;

    class Node
    {
    public:
    	Node(TString root, TString key, TString value)
		: root(root), key(key), value(value) {}
	TString root;
	TString key;
	TString value;
    };

    class SubNode
    {
    public:
    	void insert(TString key, TString value)
	{
	    subNode.insert(TPair<TString, TString>(key, value));
	}
	TMap<TString, TString> subNode;
    };
}

#endif // !_TANPERO_INI_NODE_H_

