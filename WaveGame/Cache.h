#pragma once

#include <map>
#include <exception>

using namespace std;

namespace Engine::Core
{
	///<summary>
	///The cache stores data in a map which uses a string as the key.
	///The map stores data of type T.
	///</summary>
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
		///Adds Item into the storage, if it isn't already in the storage.
		///</summary>
		///<param name = "ID">The string ID of the item to be added.</param>
		///<param name = "Item">The item to be added.</param>
		///<returns>The item which was added.</returns>
		T Add(string ID, T Item)
		{
			if (this->Storage.find(ID) == this->Storage.end())
				this->Storage[ID] = Item;
			return Item;
		}

		T operator()(string ID)
		{
			return this->Access(ID);
		}

	private:
		map<string, T> Storage;
	};
}