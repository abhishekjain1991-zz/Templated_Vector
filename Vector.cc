// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// Abhishek Jain

#include <iostream> // debugging
#include "Vector.h"

// Your implementation here
// Fill in all the necessary functions below
using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector():elements(0),count(0),reserved(0)
{
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{elements = (T*)malloc(rhs.Size()* sizeof(T));
for (size_t i = 0; i < rhs.Size(); ++i)
	{ new (&elements[i]) T(rhs.elements[i]);
	}
count=rhs.Size();
reserved=count;

}

#ifdef GRAD_STUDENT
// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
elements = (T*)malloc(nReserved * sizeof(T));
count=nReserved;
reserved=nReserved;

}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
elements = (T*)malloc(n* sizeof(T));
for (size_t i = 0; i < n; ++i)
        { new (&elements[i]) T(t);
        }
count=n;
reserved=n;

}
#endif

// Destructor
template <typename T>
Vector<T>::~Vector()
{Clear();
free(elements);//check
}

// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{if (reserved > count)
    { 
      new (&elements[count]) T(rhs);
    }
  else
    { 
      T* newelements = (T*)malloc((count + 1) * sizeof(T));
      reserved = count + 1;
     
      for (size_t i = 0; i < count; ++i)
      {
      new (&newelements[i]) T(elements[i]);
       
      elements[i].~T();
       }
      
      new (&newelements[count]) T(rhs);
      
       free(elements);
       elements = newelements;
       }
       count++;
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{//Remove first element
  if (reserved>count)
	{
         T* newelements = (T*)malloc(reserved * sizeof(T));
	 new (&newelements[0]) T(rhs);
        for (size_t i = 0; i < count; ++i)
        {
          new (&newelements[i+1]) T(elements[i]);
          
          elements[i].~T();
        }
	free (elements);
	elements = newelements;
	}
  else 
   {	 reserved=count+1;
	 T* newelements = (T*)malloc((reserved) * sizeof(T));
     	 new (&newelements[0]) T(rhs);
         for (size_t i = 0; i < count; ++i)
         {
          new (&newelements[i+1]) T(elements[i]);
          
          elements[i].~T();
         }
	 free (elements);
	 elements = newelements;
  }
  count++;  
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
count--;
elements[count].~T();

}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
 T* newelements = (T*)malloc(reserved * sizeof(T));
       
        for (size_t i = 1; i < count; ++i)
        {
          new (&newelements[i-1]) T(elements[i]);

          elements[i].~T();
        }
	elements[0].~T();
        free (elements);
        elements = newelements;
	count--;
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{return elements[0];
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{return elements[count-1];
}

template <typename T>
T& Vector<T>::operator[](size_t i) 
{return elements[i];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{return elements[i];
}

template <typename T>
size_t Vector<T>::Size() const
{return count;
}

template <typename T>
bool Vector<T>::Empty() const
{if(count==0)
return true;
else
return false;
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{while(count)
Pop_Back();
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin()
{
//  cout << "Hello from NonConst Begin" << endl;
  return VectorIterator<T>(elements);
}

template <typename T>
ConstVectorIterator<T> Vector<T>::Begin() const
{
 // cout << "Hello from Const Begin" << endl;
  return ConstVectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End()
{
 // cout << "Hello from NonConst End" << endl;
return VectorIterator<T>(elements+count);

}

template <typename T>
ConstVectorIterator<T> Vector<T>::End() const
{
 // cout << "Hello from Const End" << endl;
return ConstVectorIterator<T>(elements+count);
}

#ifdef GRAD_STUDENT
// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
VectorIterator<T> i(elements);
size_t j=0,k;
for(;i!=it;++i)
                j++;
 T* newelements = (T*)malloc(reserved * sizeof(T));
  for ( k = 0; k< j; ++k)
        {
          new (&newelements[k]) T(elements[k]);

          elements[k].~T();
        }

 elements[k].~T();
 for ( size_t l = k+1; l< count; ++l)
        {
          new (&newelements[l-1]) T(elements[l]);

          elements[l].~T();
        }

 free (elements);
        elements = newelements;

count--;
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{VectorIterator<T> i(elements);
size_t j=0,k=0; 
if(reserved>count)
	{for(;i!=it;++i)
		j++;

	T* newelements = (T*)malloc(reserved * sizeof(T));
        for ( k = 0; k< j; ++k)
        {
          new (&newelements[k]) T(elements[k]);

          elements[k].~T();
        }
	 new (&newelements[k]) T(rhs);
	for ( size_t l = k; l< count; ++l)
        {
          new (&newelements[l+1]) T(elements[l]);

          elements[l].~T();
        }
        free (elements);
        elements = newelements;
	
	}
else	
	{for(;i!=it;++i)
                j++;
	 reserved=count+1;
	  T* newelements = (T*)malloc(reserved * sizeof(T));
        for ( k = 0; k< j; ++k)
        {
          new (&newelements[k]) T(elements[k]);

          elements[k].~T();
        }
         new (&newelements[k]) T(rhs);
        for ( size_t l = k; l< count; ++l)
        {
          new (&newelements[l+1]) T(elements[l]);

          elements[l].~T();
        }
        free (elements);
        elements = newelements;

	}
count++;
}
#endif

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator():current(0)
{
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c):current(c)
{
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{current=rhs.current;
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{return *current;
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{if(current) VectorIterator(++current);
return *this;
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{VectorIterator tmp(*this);
if(current) VectorIterator(++current);
return tmp;

}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
return (current!=rhs.current);
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
return(current==rhs.current);
}
//Constant vector iterators
template <typename T>
ConstVectorIterator<T>::ConstVectorIterator():current(0)
{
}

template <typename T>
ConstVectorIterator<T>::ConstVectorIterator(T* c):current(c)
{
}

//Copy constructor
 template <typename T>
 ConstVectorIterator<T>::ConstVectorIterator(const ConstVectorIterator<T>& rhs)
 {current=rhs.current;
 }

 // Iterator defeferencing operator
 template <typename T>
 T& ConstVectorIterator<T>::operator*() const
 {return *current;
 }
 // Prefix increment
 template <typename T>
 ConstVectorIterator<T>  ConstVectorIterator<T>::operator++()
 {if(current) ConstVectorIterator(++current);
 return *this;
 }

 // Postfix increment
 template <typename T>
 ConstVectorIterator<T> ConstVectorIterator<T>::operator++(int)
 {ConstVectorIterator tmp(*this);
 if(current) ConstVectorIterator(++current);
 return tmp;

 }
 //comparison operators
 template <typename T>
bool ConstVectorIterator<T>::operator !=(const ConstVectorIterator<T>& rhs) const
{
return (current!=rhs.current);
}

template <typename T>
bool ConstVectorIterator<T>::operator ==(const ConstVectorIterator<T>& rhs) const
{
return(current==rhs.current);

}


