#include "PluginRegistry.h"

#include "IPlugin.h"

class ConcretePlugin : public IPlugin
{
public:
	virtual std::string GetString()
	{
		return "OMG! Bear is driving car!";
	}
};

FLAKED_TUNA_EXPORTS_BEGIN
FLAKED_TUNA_PLUGIN(ConcretePlugin, IPlugin)
FLAKED_TUNA_EXPORTS_END