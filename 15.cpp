#include <iostream>
#include <stdexcept>

template<typename T, int Capacity>
class Stack {
private:
    T data[Capacity];    
    int topIndex;   
public:
    Stack() : topIndex(-1) {}

    void push(const T& value) {
        if (full()) {
            throw std::overflow_error("Stack is full");
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex--];
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }

    bool empty() const {
        return topIndex == -1;
    }

    bool full() const {
        return topIndex == Capacity - 1;
    }

    int size() const {
        return topIndex + 1;
    }
};

// Пример использования
int main() {
    try {
        Stack<int, 5> intStack;

        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        
        std::cout << "Size: " << intStack.size() << std::endl;      
        std::cout << "Empty: " << intStack.empty() << std::endl;  
        std::cout << "Full: " << intStack.full() << std::endl;      
        
        std::cout << "Top: " << intStack.top() << std::endl;        
        std::cout << "Pop: " << intStack.pop() << std::endl;        
        std::cout << "Top: " << intStack.top() << std::endl;        
        
        Stack<std::string, 3> strStack;
        strStack.push("Hello");
        strStack.push("World");
        
        std::cout << "String stack top: " << strStack.top() << std::endl;  
        
        Stack<int, 2> smallStack;
        smallStack.push(1);
        smallStack.push(2);
        smallStack.push(3); 
        
        Stack<int, 2> emptyStack;
        emptyStack.pop();  
        emptyStack.top();   
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}