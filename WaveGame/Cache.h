#pragma once

#include <map>
#include <exception>
#include "GameTexture.h"

using namespace std;

namespace Engine::Core
{
	template<class T>
	class Cache
	{
	public:
		Cache<T>()
		{}

		///<summary>
		///Accesses the item if it is found in the storage.
		///</summary>
		///<param name = "ID">A string which is the identifier for accessing the item.</param>
		///<returns>The item required of type T.</returns>
		///<exception cref = "std::runtime_error">Throws when the object isn't found.</exception>
		T Access(string ID)
		{
			if (Storage.find(ID) != Storage.end())
			{
				return this->Storage.at(ID);
			}

			string ErrorMessage = string("Failed to find item with cache ID of: ") + ID;
			throw runtime_error(ErrorMessage);
		}

		///<summary>
		///Adds Item into the storage.
		///</summary>
		///<param name = "ID">The string ID of the item to be added.</param>
		///<param name = "Item">The item to be added.</param>
		///<returns>The item which was added.</returns>
		///<exception cref = "std::runtime_error">Throws if there is already an item in the storage with the ID</exception>
		T Add(string ID, T Item)
		{
			if (this->Storage.find(ID) != this->Storage.end())
			{
				this->Storage.insert(ID, Item);
				return Item;
			}
			
			string ErrorMessage = string("There is already an item with the ID of: ") + ID;
			throw runtime_error(ErrorMessage);
		}

	private:
		map<string, T> Storage;
	};
}