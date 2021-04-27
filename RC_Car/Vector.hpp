// INCLUDE GUARDS
#ifndef VECTOR_H
#define VECTOR_H

template <typename DATA>
class Vector
{
  public:
    // Constructor
    Vector();
    ~Vector();
    Vector(const Vector<DATA>&);
    
    void push_back(DATA);
    void display_contents();
    int size() {return size_;}
    void clear();

    // Operator Overloads
    DATA operator[](int);
    bool operator>(const Vector<DATA>&);
    void operator=(const Vector<DATA>&);
    
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
Vector<DATA>::Vector(const Vector<DATA>& rhs)
{
  this->capacity_ = rhs.capacity_;
  this->size_ = rhs.size_;

  this->arr_ = new DATA[capacity_];

  for (int i = 0; i < size_; i++)
  {
    this->arr_[i] = rhs.arr_[i];
  }
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

template <typename DATA>
void Vector<DATA>::clear()
{
  delete [] arr_;
  Vector();
}

template <typename DATA>
DATA Vector<DATA>::operator[](int index)
{
  return arr_[index];
}


template <typename DATA>
bool Vector<DATA>::operator>(const Vector<DATA>& rhs)
{
  for (int i = 0; i < size_; i++)
  {
    int l = this->arr_[i] - '0';
    int r = rhs.arr_[i] - '0';
    if(l > r)
      return true;
  }
  return false;
}

template <typename DATA>
void Vector<DATA>::operator=(const Vector<DATA>& rhs)
{
  delete [] arr_;

  this->capacity_ = rhs.capacity_;
  this->size_ = rhs.size_;

  this->arr_ = new DATA[capacity_];

  for (int i = 0; i < size_; i++)
  {
    this->arr_[i] = rhs.arr_[i];
  }
}
#endif // VECTOR_H
