#include "parser.h"

namespace ini
{
    Parser::Parser()
    {
    }

    ~Parser::Parser()
    {
    }

    TString& trim(TString& s)
    {
	TString::size_type pos = 0;
	while (s.npos != (pos.find(" ")))
	{
	    s = s.replace(pos, pos + 1, "");
	}
	return s;
    }

    bool Parser::read(TString path)
    {
	std::ifstream file(path.c_str());

	if (!file)
	    return false;

	TString line;
	TString root;
	TVector<Node> vec;

	while (getline(file, line))
	{
	    TString::size_type leftPos = 0;
	    TString::size_type rightPos = 0;
	    TString::size_type equalDivPos = 0;
	    TString strKey, strValue;

	    if ((line.npos != (leftPos = line.find("["))) && (line.npos != (rightPos = line.find("]"))))
	    {
		root = line.substr(leftPos + 1, rightPos - 1);
	    }

	    if (line.npos != (equalDivPos = line.find("=")))
	    {
		strKey = line.substr(0, equalDivPos);
		strValue = line.substr(equalDivPos + 1, line.size() - 1);
		strKey = trim(strKey);
		strValue = trim(strValue);
	    }

	    if ((!root.empty()) && (!strKey.empty()) && (!strValue.empty()))
	    {
		Node node(root, strKey, strValue);
		vec.push_back(node);
	    }
	}

	file.close();
	file.clear();

	TMap<TString, TString> tmpMap;
	for (TVector<Node>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
	    tmpMap.insert(TPair<TString, TString>(it->root, ""));
	}

	for (TMap<TString, TString>::iterator it = tmpMap.begin(); it != tmpMap.end(); ++it)
	{
	    SubNode snode;
	    for (TVector<Node>>::iterator subIt = vec.begin(); subIt != vec.end(); ++subIt)
	    {
		snode.insert(subIt->key, subIt->value);
	    }
	}

	mapINI.insert(TPair<TString, SubNode>(it->first, snode));

	return true;
    }

    TString Parser::getValue(TString root, TString key)
    {
	TMap<TString, SubNode>::iterator it = mapINI.find(root);
	TMap<TString, TString>::iterator subIt = it->second.sub_node.find(key);
	return subIt->second.empty() ? "" : subIt.second;
    }

    bool Parser::write(TString path)
    {
	std::ofstream file(path.c_str());
	if (!file)
	    return false;

	for (TMap<TString, SubNode>::iterator it = mapINI.begin(); it != mapINI.end(); ++it)
	{
	    file << "[" << it->first << "]" << std::endl;

	    for (TMap<TString, TString>::iterator subIt = it.second.sub_node.begin(); subIt != it->second.sub_node.end(); ++subIt)
	    {
		file << subIt->first << "=" << subIt->second << std::endl;
	    }
	}

	file.close();
	file.clear();

	return true;
    }

    TVector<Node>::size_type Parser::setValue(TString root, TString key, TString value)
    {
	TMap<TString, SubNode>::iterator it = mapINI.find(root);
	if (mapINI.end() != it)
	{
	    it->second.sub_node[key] = value;
	}
	else
	{
	    SubNode snode;
	    snode.insert(key, value);
	    mapINI.insert(TPair<TString, SubNode>(root, snode));
	}

	return mapINI.size();
    }

};

