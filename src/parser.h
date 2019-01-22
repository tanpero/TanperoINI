#ifndef _TANPERO_INI_PARSER_H_
#define _TANPERO_INI_PARSER_H_

#include "node.h"

namespace ini
{
    class Parser
    {
    public:
    	Parser();
	~Parser();

    public:
    	int read(TString path);
	TString getValue(TString root, TString key);
	TVector<Node>::size_type getSize(){
	    return mapINI.size();
	}
	int write(TString path);
	void clear();
	void travel();
    private:
    	TMap<TString, SubNode> mapINI;
    };
};

#endif // !_TANPERO_INI_PARSER_H_

