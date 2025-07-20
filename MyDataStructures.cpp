//Кратко о проекте: написание своих аналогов структурам данных STL для того, чтобы лучше разобраться как они работают "под капотом"
//На данный момент готов vector, list (без глубокого тестирования)


#include <iostream>
#include <algorithm>

namespace mds {
    template <typename T>
    class vector {
        T* first_;
        size_t size_;
        size_t capacity_;

    public:
        vector() : size_(0){
            capacity_ = 1;
            first_ = new T[capacity_];
        }
        vector(size_t new_capacity_) {
            first_ = new T[new_capacity_];
            size_ = 0;
            capacity_ = new_capacity_;
        }
        vector(const vector& other) {
            first_ = new T[other.capacity_];
            size_ = other.size_;
            capacity_ = other.capacity_;
            for (int i = 0; i < size_; i++) {
                first_[i] = other.first_[i];
            }
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

        void reserve(size_t new_capacity_) {
            if (new_capacity_ == 0) new_capacity_ = 1;
            T* new_first_ = new T[new_capacity_];
            for (size_t i = 0; i < size_; i++) {
                new_first_[i] = first_[i];
            }
            if (size_) delete[] first_;
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
            if (size_) delete[] first_;
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
            if (size_) delete[] first_;
        }
    };

    template <typename T>
    class list {
        struct node {
            T data_;
            node* next;
            node* pre;
            node() : next(nullptr), pre(nullptr) {}
            node(T data_, node* pre, node* next) {
                this->data_ = data_;
                this->next = next;
                this->pre = pre;
            }
            ~node() {
                if (next) delete next;
                //if (pre) delete pre;
            }
        };

        node* head_;
        node* tail_;
        size_t size_;

    public:

        class iterator {
            node* current;
        public:
            iterator(node* cur_node) : current(cur_node) {}

            T& operator*() {
                return current->data_;
            }

            iterator& operator++() {
                current = current->next;
                return *this;
            }

            iterator& operator++(int) {
                node& ret = current;
                current = current->next;
                return ret;
            }

            bool operator !=(const iterator& right) {
                return current != right.current;
            }

            iterator operator +(size_t index) {
                iterator it(this->get_node());
                for (size_t i = 0; i < index; i++) {
                    ++it;
                }
                return it;
            }

            node* get_node() {
                return current;
            }
        };

        list() : head_(nullptr), tail_(nullptr), size_(0) {}

        iterator begin() {
            return iterator(head_);
        }

        iterator end() {
            return iterator(nullptr);
        }

        T& operator [](size_t index) {
            iterator it(head_);
            for (int i = 0; i < index; i++) {
                ++it;
            }
            return *it;
        }

        void push_back(T data_) {
            if (tail_) {
                tail_->next = new node;
                node* extra = tail_;
                tail_ = tail_->next;
                tail_->pre = extra;
                tail_->data_ = data_;
                size_++;
            }
            else {
                if (head_) {
                    head_->next = new node(data_, head_, nullptr);
                    tail_ = head_->next;
                    size_++;
                }
                else {
                    head_ = new node(data_, nullptr, nullptr);
                    size_++;
                }
            }
        }

        void push_front(T data_) {
            if (head_) {
                head_->pre = new node;
                node* extra = head_;
                head_ = head_->pre;
                head_->next = extra;
                head_->data_ = data_;
                size_++;
            }
            else {
                if (tail_) {
                    tail_->pre = new node(data_, nullptr, tail_);
                    head_ = head_->pre;
                    size_++;
                }
                else {
                    tail_ = new node(data_, nullptr, nullptr);
                    size_++;
                }
            }
        }

        void pop_back() {
            if (tail_) {
                if (tail_->pre != head_) {
                    node* extra = tail_;
                    tail_ = extra->pre;
                    tail_->next = nullptr;
                    delete extra;
                    size_--;
                }
                else {
                    //подозрение на delete
                    tail_ = nullptr;
                    size_--;
                }
            }
            else {
                delete head_;
                head_ = nullptr;
                size_--;
            }
        }

        void pop_front() {
            if (head_) {
                if (head_->next != tail_) {
                    node* extra = head_;
                    head_ = extra->next;
                    head_->pre = nullptr;
                    extra->next = nullptr; //тут опасно с деструктором node
                    delete extra;
                    size_--;
                }
                else {
                    //подозрение на delete
                    head_ = nullptr;
                    size_--;
                }
            }
            else {
                delete tail_;
                tail_ = nullptr;
                size_--;
            }
        }

        T front() {
            return head_->data_;
        }

        T back() {
            return tail_->data_;
        }

        size_t size() {
            return size_;
        }

        bool empty() {
            return size_ == 0;
        }

        void clear() {
            if (head_) delete head_;
            head_ = nullptr;
            //if (head_) head_->next = nullptr;
            size_ = 0;
        }

        void erase(iterator it) {
            node* del = it.get_node();
            if (del->next && del->pre) {
                del->pre->next = del->next;
                del->next->pre = del->pre;
                del->next = nullptr;
                delete del;
            }
            else if (del->next) {
                head_ = del->next;
                del->next->pre = nullptr;
                del->next = nullptr;
                delete del;
            }
            else if (del->pre) {
                tail_ = del->pre;
                del->pre->next = nullptr;
                delete del;
            }
            else {
                throw("Error from erase");
                return;
            }
            size_--;
        }

        void insert(T data_insert, iterator next_it) {
            node* ins = new node(data_insert, nullptr, nullptr);
            node* nex = next_it.get_node();
            if (head_ != nex) {
                ins->pre = nex->pre;
                ins->next = nex;
                ins->pre = ins;
                nex->pre = ins;
            }
            else {
                ins->next = nex;
                nex->pre = ins;
                head_ = ins;
            }
        }

        ~list() {
            if (head_) delete head_;
            //if (tail_) delete tail_;
        }
    };

    
}

int main()
{
    //mds::list<int> li;
    //li.push_back(5);
    //li.push_back(8);
    //li.push_front(3);
    //li.push_front(9);
    //li.push_front(2);
    //li.clear();

    //std::cout << li[0] << std::endl << li[1];
    //li.erase(li.begin() + 1);

    //li.insert(7, li.begin());
    //std::cout << li.size() << std::endl;
    //std::cout << li[0] << std::endl;
    //std::cout << li.back() << std::endl;
    //mds::vector<int> vec;
    //vec.push_back(16);
    //vec.push_back(15);
    //for (int i = 10; i > 0; i--) {
    //    vec.push_back(i);
    //}
    //std::sort(vec.begin(), vec.end());
    //std::cout << vec.front() << std::endl << vec.back();
    return 0;
}