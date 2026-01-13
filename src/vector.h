#ifndef VECTOR_H
#define VECTOR_H

namespace MyDataStructures {
    template <typename T>
    class vector {
        T* first_;
        size_t size_;
        size_t capacity_;

    public:
        vector() : size_(0) {
            capacity_ = 1;
            first_ = (T*)malloc(sizeof(T)*capacity_);
        }
        vector(size_t new_capacity_) {
            first_ = (T*)malloc(sizeof(T) * new_capacity_);
            size_ = 0;
            capacity_ = new_capacity_;
        }
        vector(const vector& other) {
            first_ = (T*)malloc(sizeof(T) * other.capacity_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            for (int i = 0; i < size_; i++) {
                first_[i] = other.first_[i];
            }
        }
        vector(vector&& other) noexcept : first_(other.first_), size_(other.size_), capacity_(capacity_) {
            for (int i = 0; i < size_; i++) {
                first_[i] = other.first_[i];
            }
            other.first_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 1;
        }

        T& operator [](size_t index) {
            return *(first_ + index);
        }

        void operator =(const vector& right) {
            clear();
            reserve(right.capacity_);
            size_ = right.size_;
            for (int i = 0; i < size_; i++) {
                this->first_[i] = right.first_[i];
            }

        }

        void operator =(vector&& right) noexcept {
            clear();
            reserve(right.capacity_);
            size_ = right.size_;
            first_ = right.first_;
            right.first_ = nullptr;
            right.size_ = 0;
            right.capacity_ = 1;
        }

        void reserve(size_t new_capacity_) {
            if (new_capacity_ == 0) new_capacity_ = 1;
            //T* new_first_ = new T[new_capacity_];
            T* new_first_ = (T*)malloc(sizeof(T) * new_capacity_);
            for (size_t i = 0; i < size_; i++) {
                new_first_[i] = first_[i];
            }
            //
            if (size_) free(first_);
            first_ = new_first_;
            capacity_ = new_capacity_;
            //delete[] new_first_;
        }

        void push_back(T val) {
            if (size_ >= capacity_) {
                reserve(capacity_ * 2);
            }
            first_[size_++] = val;
        }

        void pop_back() {
            size_--;
            if (size_ * 2 < capacity_) {
                reserve(capacity_ / 2);
            }
        }

        void clear() {
            if (size_) free(first_);
            size_ = 0;
        }

        bool empty() {
            return size_ == 0;
        }

        T front() {
            return *first_;
        }

        T back() {
            return *(first_ + size_ - 1);
        }

        size_t size() {
            return size_;
        }

        T* begin() {
            return first_;
        }

        T* end() {
            return first_ + size_;
        }

        ~vector() {
            if (size_) free(first_);
        }
    };
}

namespace mds = MyDataStructures;

#endif VECTOR_H