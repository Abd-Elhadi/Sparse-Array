#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

class Stack {
private:
    int size { };
    int top { 0 } ;
    int* arr;
public:
    Stack(int size) : size(size), top(-1) {
        arr = new int [size];
    }

    bool push(int value) {
        if (is_full()) return false;
        arr[++top] = value;
        return true;
    }

    int pop () {
        assert(!is_empty());
        return arr[top--];
    }

    int peek() {
        assert(!is_empty());
        return arr[top];
    }

    bool is_full() const {
        return top == size - 1;
    }

    bool is_empty () {
        return top == -1;
    }

    void display() {
        if (top == -1){
            cout << "Stack is empty\n";
            return;
        }
        for (int i = top; i >= 0; --i) cout << arr[i] << " ";
        cout << "\n";
    }

    void display_reversed() {
        for (int i = 0; i <= top; i++) cout << arr[i] << " ";
        cout << "\n";
    }
    // recursively without using a new stack or array
    // Assume stack is [4, 3, 2, 1] and x = 10 [1 is top, 4 is last]
    // Now is: [10, 4, 3, 2, 1]

    void insert_at_bottom(int x) {
        if (is_empty()) push(x);
        else {
            int cur_top = pop();
            insert_at_bottom(x);
            push(cur_top);
        }
    }

    void reverse() {
        if (is_empty()){
            return;
        } else {
            int cur_top = pop();
            reverse();
            insert_at_bottom(cur_top);
        }
    }

    void asteroids(int arr[], int len) {
        Stack st(len);

        for (int i = 0; i < len; i++){
            int cur_asteroid = arr[i];
            bool exploded  = false;
            while (!st.is_empty() && cur_asteroid < 0 && st.peek() > 0){
                if (st.peek() < -cur_asteroid) {
                    st.pop();
                    continue;
                }
                else if (st.peek() == -cur_asteroid) st.pop();
                exploded = true;
                break;
            }
            if (!exploded) st.push(cur_asteroid);
        }
        st.display_reversed();
    }

    ~Stack(){
        delete[] arr;
    }
};

string reverse_subwords(string s) {
    Stack st(s.size());
    s += ' ';
    string str;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' '){
            while (!st.is_empty())
                str += st.pop();
            str += ' ';
        } else st.push(s[i]);
    }
    return str;
}

void test1() {
    Stack stk(5);
    stk.push(4);
    stk.push(3);
    stk.push(2);
    stk.push(1);
    stk.insert_at_bottom(10);
//    stk.reverse();

    cout << "Display\n";
    stk.display();
//    stk.pop();
//    stk.display();
//    stk.pop();
//    stk.display();
//    stk.pop();
//    stk.display();
}

// asteroid collision
void test2() {
    Stack stk(4);

}

void test3() {
    Stack st(4);
    // -2 -1 1 2
    st.push(-2);
    st.push(-1);
    st.push(1);
    st.push(2);

    int arr[] = {-2, -1, 1, 2};
    st.asteroids(arr, 4);
}


int main () {
    test1();
//    test3();
//    cout << reverse_subwords("abcdefgh xyz df a rare");
}