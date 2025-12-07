#pragma once
#include <iterator>
#include <utility>  // Для std::move

template <class ArrayType>
class TArray final
{
private:
    ArrayType* first_element_ = nullptr;
    ArrayType* end_element_ = nullptr;
    ArrayType* dynamic_array_;

    long size_{0};
    long capacity_{8};

protected:
    static constexpr size_t base_capacity_multiplier = 2;
    bool resize();
    bool expand_if_necessary();

public:
    class TConstIterator
    {
    protected:
        ArrayType* begin_ptr_ = nullptr;
        ArrayType* end_ptr_ = nullptr;

        ArrayType* it_value_ = nullptr;
        bool is_reverse_{false};

    protected:
        TConstIterator() = delete;

        TConstIterator(ArrayType* begin_ptr, ArrayType* end_ptr, const bool is_reverse = false) : begin_ptr_(begin_ptr),
            end_ptr_(end_ptr), is_reverse_(is_reverse)
        {
            is_reverse_ ? it_value_ = end_ptr_ : it_value_ = begin_ptr_;
        }

    public:
        void next() { is_reverse_ ? --it_value_ : ++it_value_; }

        bool has_next()
        {
            if (is_reverse_)
            {
                return it_value_ >= begin_ptr_;
            }
            else
            {
                return it_value_ <= end_ptr_;
            }
        }

        const ArrayType& get() const { return *it_value_; }
    };

    class TIterator final : public TConstIterator
    {
    protected:
        TIterator() = delete;

        TIterator(ArrayType* begin_ptr, ArrayType* end_ptr, const bool is_reverse = false) : TConstIterator(
            begin_ptr, end_ptr, is_reverse)
        {
        };

    public:
        void set(const ArrayType& value) { *(this->it_value_) = value; }

        friend TArray;
    };

    TArray() : TArray(8)
    {
    }

    explicit TArray(const long capacity);
    ~TArray();

    TArray(const TArray& other);
    TArray(TArray&& other) noexcept;
    TArray& operator=(const TArray& other);
    TArray& operator=(TArray&& other) noexcept;

    ArrayType* begin()
    {
        return first_element_;
    }

    ArrayType* end()
    {
        return end_element_ + 1;
    }

    int insert(const ArrayType& value);
    int insert(int index, const ArrayType& value);

    void remove(int index);

    const ArrayType& operator[](int index) const;
    ArrayType& operator[](int index);

    int size() const;

    TIterator iterator() { return TIterator(begin(), end_element_); }
    TIterator reverse_iterator() { return TIterator(begin(), end_element_, true); }
    TConstIterator iterator() const { return TConstIterator(begin(), end_element_); }
    TConstIterator reverse_iterator() const { return TConstIterator(begin(), end_element_, true); }
};

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
    end_element_ = &dynamic_array_[size_ - 1];
    return true;
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
TArray<ArrayType>::TArray(const long capacity) : capacity_(capacity)
{
    dynamic_array_ = new ArrayType[capacity_];
    first_element_ = dynamic_array_;
    end_element_ = dynamic_array_;
}

template <class ArrayType>
TArray<ArrayType>::~TArray()
{
    delete[] dynamic_array_;
    first_element_ = nullptr;
    end_element_ = nullptr;
}

template <class ArrayType>
TArray<ArrayType>::TArray(const TArray& other) : size_(other.size_), capacity_(other.capacity_)
{
    dynamic_array_ = new ArrayType[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
        dynamic_array_[i] = other.dynamic_array_[i];
    }
}

template <class ArrayType>
TArray<ArrayType>::TArray(TArray&& other) noexcept : dynamic_array_(other.dynamic_array_), size_(other.size_),
                                                     capacity_(other.capacity_)
{
    other.dynamic_array_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class ArrayType>
TArray<ArrayType>& TArray<ArrayType>::operator=(const TArray& other)
{
    if (this != &other)
    {
        delete[] dynamic_array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        dynamic_array_ = new ArrayType[capacity_];
        for (size_t i = 0; i < size_; ++i)
        {
            dynamic_array_[i] = other.dynamic_array_[i];
        }
        first_element_ = other.begin();
        end_element_ = other.end();
    }
    return *this;
}

template <class ArrayType>
TArray<ArrayType>& TArray<ArrayType>::operator=(TArray&& other) noexcept
{
    if (this != &other)
    {
        delete[] dynamic_array_;
        dynamic_array_ = other.dynamic_array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        first_element_ = other.begin();
        end_element_ = other.end();

        other.dynamic_array_ = nullptr;
        other.first_element_ = nullptr;
        other.end_element_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <class ArrayType>
int TArray<ArrayType>::insert(const ArrayType& value)
{
    expand_if_necessary();
    dynamic_array_[size_++] = value;
    end_element_ = &dynamic_array_[size_ - 1];
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
    end_element_ = &dynamic_array_[size_ - 1];
    return size_;
}

template <class ArrayType>
void TArray<ArrayType>::remove(const int index)
{
    for (size_t i = index; i < size_ - 1; ++i)
    {
        dynamic_array_[i] = std::move(dynamic_array_[i + 1]);
    }
    --size_;
    end_element_ = &dynamic_array_[size_ - 1];
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
