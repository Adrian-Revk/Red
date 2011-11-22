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
		HandleEntry() : mNextFreeIndex( 0 ), mUsed( false ) {}

		T 		mData;				///< Pointer to a T object. Actual Data
		u32 	mNextFreeIndex;		///< Next index that will be usable by the HM
        bool    mUsed;              ///< True if the Entry is in use
	};


	/// Container using indices and dynamic directing to store single entries 
	/// containing a unique sort of data. The user of the HM provides the Data he wants
	/// to store and the HM returns him a handle(u32) directing him to it.
	/// The HM does not care about memory managment and this should be done elsewhere.
    /// It is just a dynamic storage. Nothing is new'ed or delete'd.
	template<class T>
	class HandleManager {
	public:
		HandleManager() : mEntryCount( 0 ), mCapacity( 0 ), mFirstFreeIndex( 0 ) { }
		
		/// Add a new entry to the HM at the FirstFreeIndex, storing the pointer in it
		/// @param pData : pointer to the data to store in it
		/// @return : the handle to the location where the data was stored
		u32 AddEntry( T pData );

		/// Remove an existing entry. Delete the Data if present
		/// @param pHandle : Index where the removal must occur
		void RemoveEntry( u32 pHandle );

		/// Returns the entry present at a given Index
		/// @param pHandle : Index of the wanted entry
		HandleEntry<T> GetEntry( u32 pHandle );

		/// Returns the data present at a given Index
		/// @param pHandle : Index of the wanted data
        T& operator[]( u32 pHandle); 

        /// Sets the value of the Data at a given Index
        /// @param pHandle : Index of the data changed
        void Set( u32 pHandle, const T& pVal );

        /// Returns the number of slots in mEntries, occupied or not
        u32 Size() const { return mCapacity; }

	private:
		std::vector<HandleEntry<T>> mEntries;			///< Array of Entries of data
		u32							mEntryCount;		///< Number of active entries
		u32							mCapacity;			///< Size of mEntries
		u32							mFirstFreeIndex;	///< First allocatable index

	};


	template<class T>
	u32 HandleManager<T>::AddEntry( T pData ) {
		u32 handle = mFirstFreeIndex;

		if( handle == mCapacity ) {
			mEntries.push_back( HandleEntry<T>() );
			mEntries[handle].mNextFreeIndex = ++mCapacity;	
		}
			
		mEntries[handle].mData = pData;
        mEntries[handle].mUsed = true;

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

            mEntries[pHandle].mUsed = false;

			--mEntryCount;
		}
	}

	template<class T>
	HandleEntry<T> HandleManager<T>::GetEntry( u32 pHandle ) {
		return mEntries[pHandle];
	}

    template<class T>
    T& HandleManager<T>::operator[]( u32 pHandle ) {
        return mEntries[pHandle].mData;
    }

    template<class T>
    void HandleManager<T>::Set( u32 pHandle, const T& pVal ) {
        mEntries[pHandle].mData = pVal;
    }
}

#endif
