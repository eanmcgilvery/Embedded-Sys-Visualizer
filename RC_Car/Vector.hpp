// INCLUDE GUARDS
#ifndef VECTOR_H
#define VECTOR_H

template <typename DATA>
class Vector
{
  public:
    Vector();
    ~Vector();
    void push_back(DATA);
    void display_contents();

    int getSize() {return size_;}
  private:
    DATA* arr_;
    int size_;
    int capacity_;

    void resize();
};


// Constructor
template <typename DATA>
Vector<DATA>::Vector()
{
  capacity_ = 100;
  arr_ = new DATA[capacity_];
  size_ = 0;  
}

template <typename DATA>
Vector<DATA>::~Vector()
{
  delete [] arr_;
  arr_ = nullptr;
}

template <typename DATA>
void Vector<DATA>::push_back(DATA element)
{
  if(size_ == capacity_)
    resize();

  arr_[size_] = element;

  size_++;
}

template <typename DATA>
void Vector<DATA>::display_contents()
{
  Serial.println();
  for(int i = 0; i < size_; i++)
    Serial.print(arr_[i]);
  Serial.println();
}

template <typename DATA>
void Vector<DATA>::resize()
{
  // Double Capacity & create new array
  capacity_ *= 2;
  DATA* newArr = new DATA[capacity_];

  // copy old contents into new array
  for(int i =0; i < size_; i++)
    newArr[i] = arr_[i];

  // Free old memory
  delete [] arr_;

  // Assign our class variable to point to new array
  arr_ = newArr;
}
#endif // VECTOR_H
