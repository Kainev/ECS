#pragma once

#include <iostream>
#include <array>
#include <deque>

namespace ECS
{
	class IObjectPool
	{

	};

	template <class T, size_t MAX_OBJECTS>
	class ObjectPool : public IObjectPool
	{
	public:
		ObjectPool()
		{
			for (unsigned int i = 0; i < MAX_OBJECTS; i++)
			{
				mFreeIndexList.push_front(i);
			}
		}
		~ObjectPool()
		{
			//delete[] mObjects;
		}

		std::shared_ptr<T> GetObject()
		{
			size_t index = mFreeIndexList.back();
			mFreeIndexList.pop_back();
			mObjects[index] = std::make_shared<T>();
			return mObjects[index];
		}


	private:
		//std::array <T, MAX_OBJECTS> mObjects;
		std::shared_ptr<T> mObjects[MAX_OBJECTS];
		std::deque<unsigned int> mFreeIndexList;
		
	};
}
