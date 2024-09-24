#include <queue>

template <class T>
struct max_queue {
    std::deque<T> all;
    std::deque<T> max_q;
    
    void add(T elem) {
        all.push_back(elem);
        while (!max_q.empty() and elem > max_q.back()) {
            max_q.pop_back();
        }

        max_q.push_back(elem);
    }
    
    void pop() {
        if (all.front() == max_q.front()) {
            max_q.pop_front();
        }

        all.pop_front();
    }
    
    T get_max() const {
        return max_q.front();
    }
};
