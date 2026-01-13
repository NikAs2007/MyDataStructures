#ifndef LIST_H
#define LIST_H

namespace MyDataStructures {
    template <typename T>
    class list {
        struct node {
            T data_;
            node* next;
            node* pre;
            node() : next(nullptr), pre(nullptr) {}
            node(T data_, node* pre = nullptr, node* next = nullptr) : data_(data_), next(next), pre(pre) {}
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

        list(const list& other) : size_(other.size_) {
            head_ = new node;
            head_->data_ = other.head_->data_;
            node *temp = head_, *temp_other = other.head_;
            while (temp_other->next != nullptr) {
                temp_other = temp_other->next;            
                temp->next = new node(temp_other->data_, temp, nullptr);
                temp = temp->next;
            }
            tail_ = temp;
        }

        void operator =(const list& right) {
            clear();
            size_ = right.size_;
            head_ = new node;
            head_->data_ = right.head_->data_;
            node* temp = head_, * temp_right = right.head_;
            while (temp_right->next != nullptr) {
                temp_right = temp_right->next;
                temp->next = new node(temp_right->data_, temp, nullptr);
                temp = temp->next;
            }
            tail_ = temp;
        }

        list(list&& other) noexcept : size_(other.size_){
            head_ = other.head_;
            tail_ = other.tail_;
            other.size_ = 0;
            other.head_ = nullptr;
            other.tail_ = nullptr;
        }

        void operator =(list&& right) noexcept {
            clear();
            size_ = right.size_;
            head_ = right.head_;
            tail_ = right.tail_;
            right.size_ = 0;
            right.head_ = nullptr;
            right.tail_ = nullptr;
        }

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

namespace mds = MyDataStructures;

#endif //LIST_H
