#pragma once
// 第4章 栈（教材 §4.1）—— 第 8 天
//
// Stack：以向量的末端为栈顶；ListStack：以列表的末端为栈顶。
// size()、empty() 从基类继承。push、pop、top 现在都是 DSA_TODO();。

#include "dsa/list.h"
#include "dsa/vector.h"

namespace dsa {

template <typename T>
class Stack : public Vector<T> {
public:
    void push(T const& e);  // 入栈
    T pop();                // 出栈，返回原来的栈顶（栈非空）
    T& top();               // 取栈顶（栈非空）
};

template <typename T>
class ListStack : public List<T> {
public:
    void push(T const& e);
    T pop();
    T& top();
};

template <typename T>
void Stack<T>::push(T const& e) {
    DSA_TODO();
}

template <typename T>
T Stack<T>::pop() {
    DSA_TODO();
}

template <typename T>
T& Stack<T>::top() {
    DSA_TODO();
}

template <typename T>
void ListStack<T>::push(T const& e) {
    DSA_TODO();
}

template <typename T>
T ListStack<T>::pop() {
    DSA_TODO();
}

template <typename T>
T& ListStack<T>::top() {
    DSA_TODO();
}

}  // namespace dsa
