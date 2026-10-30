#pragma once
// 第4章 队列（教材 §4.5）—— 第 10 天
//
// 以列表的首端为队头、末端为队尾。size()、empty() 从 List 继承。

#include "dsa/list.h"

namespace dsa {

template <typename T>
class Queue : public List<T> {
public:
    void enqueue(T const& e);  // 入队（插到队尾）
    T dequeue();               // 出队（删除队头，返回它），队列非空
    T& front();                // 取队头，队列非空
};

template <typename T>
void Queue<T>::enqueue(T const& e) {
    DSA_TODO();
}

template <typename T>
T Queue<T>::dequeue() {
    DSA_TODO();
}

template <typename T>
T& Queue<T>::front() {
    DSA_TODO();
}

}  // namespace dsa
