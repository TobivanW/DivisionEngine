#ifndef DIVISION_RESOURCEMANAGER_H
#define DIVISION_RESOURCEMANAGER_H

#include "Resource.h"

#include <map>

namespace Division
{
	class ResourceManager
	{
	private:
		std::map<std::string, Resource*> resources_;

	public:
		ResourceManager();
		~ResourceManager();

		void addResource(std::string, Resource*);
		void getResource(std::string, Resource*);
		void destroyResource(std::string);
	};
}
#endif