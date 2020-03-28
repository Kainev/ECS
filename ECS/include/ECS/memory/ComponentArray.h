#pragma once

#include <iostream>
#include <cstddef>
#include <utility>
#include <unordered_map>


template <typename Arg, typename... Args>
void Print(Arg&& arg, Args&&... args)
{
	std::cout << std::forward<Arg>(arg);
	((std::cout << std::forward<Args>(args)), ...);
	std::cout << std::endl;
}


template <typename T, typename ... Args>
inline void Construct_T(T* object, Args&&... params)
{
	new (object)T{ std::forward<Args>(params)... };
}

template <typename T>
inline void Destroy_T(void* element)
{
	static_cast<T*>(element)->T::~T();
}

template <typename T>
struct Handle
{
	T* component;
};


class ComponentAllocator
{
	using VoidFunction = void(*)(void*);

public:
	ComponentAllocator() : mSize(0), mStride(0), mCount(0), mData(nullptr), mHandles(nullptr) { }
	~ComponentAllocator() { Clear(); }

	void Clear()
	{
		char* ptr = mData;
		std::size_t count = mCount;
		for (; count > 0; --count, ptr += mStride)
		{
			mDestructorT(ptr);
		}

		free(mData);
	}

	template <typename T>
	Handle<T>* Get()
	{
		T* element = (T*)mData + mCount;
		Construct_T<T>(element);

		Handle<T>* handle = (Handle<T>*)mHandles + mCount;
		handle->component = element;

		++mCount;

		return handle;
	}

	//int remove(std::size_t index)
	//{
	//	if (mCount == 0)
	//		return;

	//	--mCount;

	//	char* dest = mData + mStride * index;
	//	char* src = mData + mStride * mCount;

	//	mDestructorT(dest);

	//	if (dest >= src)
	//		return -1;

	//	memmove(dest, src, mStride);

	//	return mCount - 1;
	//}


protected:
	std::size_t mSize;
	std::size_t mStride;
	std::size_t mCount;

	VoidFunction mConstructorT = nullptr;
	VoidFunction mDestructorT = nullptr;

	char* mData = nullptr;
	char* mHandles = nullptr;

	template <typename T, std::size_t MAX_ELEMENTS>
	void Initialize()
	{
		mStride = sizeof(T);
		mSize = mStride * MAX_ELEMENTS;

		mData = (char*)malloc(mSize);
		mHandles = (char*)malloc(MAX_ELEMENTS * sizeof(Handle<T>));

		mDestructorT = Destroy_T<T>;
	}
};


template <typename T, std::size_t MAX_ELEMENTS>
class ComponentArray : public ComponentAllocator
{
public:
	ComponentArray() { Initialize<T, MAX_ELEMENTS>(); }
	T* Data() { return (T*)mData; }
	const T* Data() const { return (T*)mData; }

	inline const T& operator[](int i) const { return ((T*)mData)[i]; }
	inline T& operator[](int i) { return ((T*)mData)[i]; }

	inline T* begin() { return(T*)mData; }
	inline const T* begin() const { return(T*)mData; }
	inline T* end() { return (T*)mData + mCount; }
	inline const T* end() const { return (T*)mData + mCount; }
};