#ifndef HANDLEMANAGER_HPP
#define HANDLEMANAGER_HPP

#include "Shared.hpp"
#include "Logger.hpp"

#include <vector>

namespace red {

	/// Single Entry in the HandleManager. Store the actual data and the index
	/// of the next possible index for the HM to use
	template<class T>
	class HandleEntry {
	public:
		HandleEntry() : mData( NULL ), mNextFreeIndex( 0 ) {}

		T* 		mData;				///< Pointer to a T object. Actual Data
		u32 	mNextFreeIndex;		///< Next index that will be usable by the HM
	};


	/// Container using indices and dynamic directing to store single entries 
	/// containing a unique sort of data. The user of the HM provides the Data he wants
	/// to store and the HM returns him a handle(u32) directing him to it.
	/// The HM automatically destroy all Data stored when deleted.
	template<class T>
	class HandleManager {
	public:
		HandleManager() : mEntryCount( 0 ), mCapacity( 0 ), mFirstFreeIndex( 0 ) { }
		~HandleManager();
		
		/// Add a new entry to the HM at the FirstFreeIndex, storing the pointer in it
		/// @param pData : pointer to the data to store in it
		/// @return : the handle to the location where the data was stored
		u32 AddEntry( T* pData );

		/// Remove an existing entry. Delete the Data if present
		/// @param pHandle : Index where the removal must occur
		void RemoveEntry( u32 pHandle );

		/// Returns the data present at a given Index
		/// @param pHandle : Index of the wanted data
		T* GetEntry( u32 pHandle );


	private:
		std::vector<HandleEntry<T>> mEntries;			///< Array of Entries of data
		u32							mEntryCount;		///< Number of active entries
		u32							mCapacity;			///< Size of mEntries
		u32							mFirstFreeIndex;	///< First allocatable index

	};

	template<class T>
	HandleManager<T>::~HandleManager() {
		for( u32 i = 0; i < mEntries.size(); ++i )
			delete mEntries[i].mData;
	}

	template<class T>
	u32 HandleManager<T>::AddEntry( T* pData ) {
		u32 handle = mFirstFreeIndex;

		if( handle == mCapacity ) {
			mEntries.push_back( HandleEntry<T>() );
			mEntries[handle].mNextFreeIndex = ++mCapacity;	
		}
			
		mEntries[handle].mData = pData;

		mFirstFreeIndex = mEntries[handle].mNextFreeIndex;

		++mEntryCount;

		return handle;
	}

	template<class T>
	void HandleManager<T>::RemoveEntry( u32 pHandle ) {
		if( pHandle >= 0 && pHandle < mCapacity ) {
			// Replace the next free handles availables
			u32 nextFree = mFirstFreeIndex;
			mFirstFreeIndex = pHandle;
			mEntries[pHandle].mNextFreeIndex = nextFree;

			// Destroy the actual data
			delete mEntries[pHandle].mData;
			mEntries[pHandle].mData = NULL;

			--mEntryCount;
		}
	}

	template<class T>
	T* HandleManager<T>::GetEntry( u32 pHandle ) {
		T* ret = NULL;
		
		if( pHandle >= 0 && pHandle < mCapacity ) 
			ret = mEntries[pHandle].mData;

		return ret;
	}
}

#endif
