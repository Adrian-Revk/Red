#ifndef SINGLETON_HPP
#define SINGLETON_HPP


namespace blue {
	/// Classic Singleton class to store an object pointer in its only instance
    template<class T>
	class Singleton{
        private:
            static T *mSingleton;	///< Pointer on object stored by singleton

            /// Copy Ctor, forbidden
            Singleton( Singleton & ) {}

            /// Copy Op, forbidden
            void operator=( Singleton & ){}

        protected:
			/// Default Ctor/Dtor, forbidden
            Singleton(){}
            ~Singleton(){}

        public:
            /// Returns a pointer on stored object
            static T* Get(){
                if( mSingleton == 0 )
                    mSingleton = new T;
                return ( static_cast<T*> ( mSingleton ) );
            }

            /// Returns the reference of stored object
            static T& Call(){
                if( mSingleton == 0 )
                    mSingleton = new T;
                return *mSingleton;
            }

            /// Destroy the stored object
            static void Kill(){
                if( mSingleton != 0 ){
                    delete mSingleton;
                    mSingleton = 0;
                }
            }
	};

    /// Initialisation
    template<class T> T *Singleton<T>::mSingleton = 0;

}
#endif
