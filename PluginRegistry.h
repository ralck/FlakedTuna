/*
* Copyright (c) 2014 Clark Cianfarini
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _PLUGIN_REGISTRY_H_
#define _PLUGIN_REGISTRY_H_

#include <map>
#include <functional>
#include <memory>

// TODO: Look at supporting constructors with parameters

namespace FlakedTuna
{
	class PluginRegistry
	{
	private:
		std::map<std::string, std::function<std::shared_ptr<void>()>> _plugins;

	public:
		template <class T, class BaseT>
		void RegisterPlugin()
		{
			// Should think about asserting here if the key already exists.
			_plugins[typeid(BaseT).name()] = [this]() -> std::shared_ptr<T> { return std::shared_ptr<T>(new T()); };
		}

		template <class BaseT>
		std::shared_ptr<BaseT> ResolvePlugin()
		{
			if (_plugins.find(typeid(BaseT).name()) != _plugins.end())
			{
				return std::static_pointer_cast<BaseT>(_plugins[typeid(BaseT).name()]());
			}
			return std::shared_ptr<BaseT>(nullptr);
		}
	};
}


#define FLAKED_TUNA_DERRIVED( concrete, base )		static_assert(std::is_base_of< base , concrete>::value, "ERROR: FLAKED_TUNA_PLUGIN: Registered concrete type must be of base type.");

#define FLAKED_TUNA_EXPORTS_BEGIN					FlakedTuna::PluginRegistry* pr = nullptr; extern "C" __declspec(dllexport) FlakedTuna::PluginRegistry* GetPluginRegistry() { pr = new FlakedTuna::PluginRegistry();
#define FLAKED_TUNA_PLUGIN( concrete, base )		FLAKED_TUNA_DERRIVED( concrete, base ) pr->RegisterPlugin< concrete , base >();
#define FLAKED_TUNA_EXPORTS_END						return pr; } extern "C" __declspec(dllexport) void ClosePluginRegistry() { if(pr != nullptr) { delete pr; } }

#define FLAKED_TUNA_PLUGIN_VERSION( version )		extern "C" __declspec(dllexport) int GetVersion() { return version ; }

#endif