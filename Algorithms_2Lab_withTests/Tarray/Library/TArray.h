#pragma once
#include <iterator>
#include <utility>  // Для std::move

template <class ArrayType>
class TArray final
{
private:
    ArrayType* first_element_ = nullptr;
    ArrayType* dynamic_array_;

    long size_{0};
    long capacity_{8};

protected:
    static constexpr size_t base_capacity_multiplier = 2;
    bool resize();
    bool expand_if_necessary();

public:
    
#pragma region Iterator
    
    class TConstIterator
    {
    protected:
        ArrayType* begin_ptr_{nullptr};
        ArrayType* end_ptr_{nullptr};

        ArrayType* it_value_{nullptr};
        bool is_reverse_{false};
        bool is_empty_{false};

    protected:
        TConstIterator() = delete;

        TConstIterator(ArrayType* begin_ptr, ArrayType* end_ptr, const bool is_empty, const bool is_reverse = false) :
            begin_ptr_(begin_ptr),
            end_ptr_(end_ptr), is_reverse_(is_reverse), is_empty_(is_empty)
        {
            is_reverse_ ? it_value_ = end_ptr_ : it_value_ = begin_ptr_;
        }

    public:
        void next()
        {
            if (is_empty_)
            {
                return;
            }
            is_reverse_ ? --it_value_ : ++it_value_;
        }

        bool has_next()
        {
            if (is_empty_)
            {
                return false;
            }
            return is_reverse_ ? it_value_ >= begin_ptr_ : it_value_ <= end_ptr_;
        }

        const ArrayType& get() const
        {
            return *it_value_;
        }
    };

    class TIterator final : public TConstIterator
    {
    protected:
        TIterator() = delete;

        TIterator(ArrayType* begin_ptr, ArrayType* end_ptr, const bool is_empty, const bool is_reverse = false) :
            TConstIterator(
                begin_ptr, end_ptr, is_empty, is_reverse) {}

    public:
        void set(const ArrayType& value) { *(this->it_value_) = value; }

        friend TArray;
    };
    
#pragma endregion
    
    TArray() : TArray(8){}
    explicit TArray(const long capacity);
    ~TArray();

    TArray(const TArray& other);
    TArray(TArray&& other) noexcept;
    TArray& operator=(const TArray& other);

    ArrayType* begin() {return first_element_; }
    ArrayType* end() {return dynamic_array_ + size_;; }

    int insert(const ArrayType& value);
    int insert(int index, const ArrayType& value);
    void remove(int index);

    const ArrayType& operator[](int index) const;
    ArrayType& operator[](int index);

    int size() const;
    int capacity() const;
    bool is_empty() const {return size_ == 0; }
    
    void swap(TArray& other) noexcept
    {
        std::swap(dynamic_array_, other.dynamic_array_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(first_element_, other.first_element_);
    }
    
    TIterator iterator()
    {
        return TIterator(begin(), end()-1, is_empty());
    }

    TIterator reverse_iterator()
    {
        return TIterator(begin(), end()-1, is_empty(), true);
    }

    TConstIterator iterator() const
    {
        return TConstIterator(begin(), end()-1, is_empty());
    }

    TConstIterator reverse_iterator() const
    {
        return TConstIterator(begin(), end()-1, is_empty(), true);
    }
};

template <class ArrayType>
TArray<ArrayType>::TArray(const long capacity) : capacity_(capacity)
{
    dynamic_array_ = new ArrayType[capacity_];
    first_element_ = dynamic_array_;
}

template <class ArrayType>
TArray<ArrayType>::~TArray()
{
    delete[] dynamic_array_;
    first_element_ = nullptr;
}

template <class ArrayType>
TArray<ArrayType>::TArray(const TArray& other) : TArray(other.capacity_)
{
    for(long i = 0; i < other.size_; ++i)
    {
        dynamic_array_[i] = other.dynamic_array_[i];
    }
    size_ = other.size_;
    first_element_ = dynamic_array_;
}

template <class ArrayType>
TArray<ArrayType>::TArray(TArray&& other) noexcept
    : first_element_(nullptr), dynamic_array_(nullptr),
      size_(0), capacity_(0)
{
    swap(other);
}

template <class ArrayType>
TArray<ArrayType>& TArray<ArrayType>::operator=(const TArray& other)
{
    TArray copy_array(other);
    swap(copy_array);
    return *this;
}

template <class ArrayType>
bool TArray<ArrayType>::expand_if_necessary()
{
    if (size_ == capacity_)
    {
        resize();
        return true;
    }
    return false;
}

template <class ArrayType>
bool TArray<ArrayType>::resize()
{
    capacity_ *= base_capacity_multiplier;
    ArrayType* new_array = new ArrayType[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
        new_array[i] = std::move(dynamic_array_[i]);
    }
    delete[] dynamic_array_;
    dynamic_array_ = new_array;

    first_element_ = dynamic_array_;
    return true;
}

template <class ArrayType>
int TArray<ArrayType>::insert(const ArrayType& value)
{
    expand_if_necessary();
    dynamic_array_[size_++] = value;
    return size_;
}

template <class ArrayType>
int TArray<ArrayType>::insert(const int index, const ArrayType& value)
{
    if (index > size_)
    {
        return insert(value);
    }
    expand_if_necessary();

    for (size_t i = size_; i > index; --i)
    {
        dynamic_array_[i] = std::move(dynamic_array_[i - 1]);
    }
    dynamic_array_[index] = value;
    ++size_;
    return size_;
}

template <class ArrayType>
void TArray<ArrayType>::remove(const int index)
{
    if(size_ == 0)
    {
        return;
    }
    for (size_t i = index; i < size_ - 1; ++i)
    {
        dynamic_array_[i] = std::move(dynamic_array_[i + 1]);
    }
    --size_;
}

template <class ArrayType>
const ArrayType& TArray<ArrayType>::operator[](int index) const
{
    return dynamic_array_[index];
}

template <class ArrayType>
ArrayType& TArray<ArrayType>::operator[](int index)
{
    return dynamic_array_[index];
}

template <class ArrayType>
int TArray<ArrayType>::size() const
{
    return size_;
}

template <class ArrayType>
int TArray<ArrayType>::capacity() const
{
    return capacity_;
}
