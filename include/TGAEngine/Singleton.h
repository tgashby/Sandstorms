/**
 * @file Singleton.h
 *
 * @author Tag Ashby
 * @date 7/2012
 *
 * This template taken from http://www.yolinux.com/TUTORIALS/C++Singleton.html
 */

#ifndef SINGLETON
#define SINGLETON

#define NULL 0

namespace TGA
{
   /**
    * @class Singleton
    *
    * @brief Handles Singleton instances of classes.
    *
    * This is the Singleton template used to maintain Singletons.
    */
   template<class T> class Singleton
   {
   public:
      /**
      * GetSingletonPtr
      *
      * Gets the one and only Singleton pointer to the class.
      * @return T* - the single pointer to the class specified.
      */
      static T* GetSingletonPtr()
      {
         if (!m_Instance)
         {
            m_Instance = new T;
         }

         return m_Instance;
      }

   private:
      Singleton();
      ~Singleton();
      Singleton(Singleton const&);
      Singleton& operator=(Singleton const&);
      static T* m_Instance;
   };

   template<class T> T* Singleton<T>::m_Instance = NULL;
}

#endif
