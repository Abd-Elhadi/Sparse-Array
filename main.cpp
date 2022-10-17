#include <iostream>
#include <cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
    int data { };
    int index;
    Node* next { };
    Node* prev { };	 // Previous node!

    Node (int data, int index) : data(data), index(index) {}

    ~Node() {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList {
private:
    Node *head { };
    Node *tail { };
    int length = 0;
    int capacity = 0;

public:

    // Below 2 deletes prevent copy and assign to avoid this mistake
    LinkedList(int length) : capacity(length) {
    }
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;

    void link(Node* first, Node*second) {
        if(first)
            first->next = second;
        if(second)
            second->prev = first;
    }

    void insert_end(int value, int index) {
        Node* item = new Node(value, index);

        if (!head)
            head = tail = item;
        else {
            link(tail, item);
            tail = item;
        }
    }

    void insert_front(int value, int index) {
        Node* item = new Node(value, index);

        if (!head)
            head = tail = item;
        else {
            link(item, head);
            head = item;
        }
    }

    void set_value (int key, int index) {
        if (index < 0 || index > capacity) {
            cout << "Out of range index: " << index << "\n";
            return;
        }
        --index;
        if (!head) {
            insert_front(key, index);
            return;
        }
        Node* item = new Node(key, index);
        Node* cur = head;

        while (cur) {
            if (cur->index == index){
                cur->data = key;
                return;
            }
            cur = cur->next;
        }
        insert_end(key, index);
    }

    int get_value(int index) const {
        --index;
        Node* cur = head;
        while (cur) {
            if (cur->index == index) return cur->data;
            cur = cur->next;
        }
        return -1;
    }

    void add_array(const LinkedList &list) {
        int n = max(capacity, list.capacity);
        for (int i = 0; i < n; i++){
            int first = get_value(i), second = list.get_value(i);
            if (first != -1 && second != -1){
                int key = first + second;
                set_value(key, i);
            } else if (second != -1) set_value(second, i);
        }
    }

    void print_array() {
        for (int i = 0; i < capacity; i++) {
            int val = get_value(i);
            if (val == -1) cout << 0 << " ";
            else cout << val << " ";
        }
        cout << "\n";
    }

    void print_non_zero() {
        for (int i = 0; i < capacity; i++) {
            int val = get_value(i);
            if (val == -1) continue;
            else cout << val << " ";
        }
        cout << "\n";
    }

    void print_reversed()  {
        for (Node* cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }
};

void test1() {
    LinkedList list(10);
    list.set_value(50, 5);
    list.set_value(20, 2);
    list.set_value(70, 7);
    list.set_value(40, 4);
    list.print_array();
    list.print_non_zero();

    LinkedList list2(10);
    list2.set_value(1, 4);
    list2.set_value(3, 7);
    list2.set_value(4, 6);

    list.add_array(list2);
//    list.set_value(100, 1);
//    list.set_value(100, 100);
    list.print_array();
    list.print_reversed();
}


int main() {
    test1();
    // must see it, otherwise RTE
    cout << "\nNO RTE\n";
}