#ifndef _I_PLUGIN_H_
#define _I_PLUGIN_H_

#include <string>

class IPlugin
{
public:
	virtual std::string GetString() = 0;
};


#endif