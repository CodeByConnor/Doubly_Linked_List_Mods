#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
    int value;
    string name;
    Data(int value, string name) {
        this->value = value;
        this->name = name;
    }
    void print() {

        cout << value << " " << endl;
        cout << name << " " << endl;

    }
    bool compareData(const Data & other) {
        return this->value < other.value;
    }
    bool compareEqualData(const Data & other) {
        return this->value == other.value;
    }
};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
    T *value;
    Node<T> *next;
    Node<T> *prev;
    Node(T *value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
    void print() { value->print(); }
};

// LinkedList Class : Container for Nodes
template <typename T> class DoubleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
    // Constructor
    DoubleLinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    // Destructor
    ~DoubleLinkedList() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            temp->print();
            temp = temp->next;
        }
        cout<<endl;
    }

    // get and set
    Node<T> *getHead() {
        if (head == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << head->value << endl;
        }
        return head;
    }

    Node<T> *getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() {
        cout << "Length: " << length << endl;
        return length;
    }

    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }
    // All insert methods
    // Insert at end
    void append(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }
    // Insert at beginning
    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }
    // Insert at Index
    bool insert(int index, T *value) {
        if (index < 0 || index > length)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *prev1 = get(index - 1);
        Node<T> *next1 = prev1->next;
        newNode->prev = prev1;
        newNode->next = next1;
        prev1->next = newNode;
        next1->prev = newNode;
        length++;
        return true;
    }
    // All delete Methods
    // Write DeleteHead, DeleteTail & DeleteAtIndex here
    void deleteAtHead() {
//        getHead();
        Data *deletedValue = head->value;
        Node<T> *newHead = head->next;
        newHead->prev = nullptr;
        delete deletedValue;
        delete head;
        head = newHead;
        length--;
        cout << "The list with deleted head: "<< endl;
        printList();
    }
    void deleteAtTail() {
        //getTail();
        Data *deleteValue = tail->value;
        Node<T> *newTail = tail->prev;
        newTail->next = nullptr;
        delete deleteValue;
        delete tail;
        tail = newTail;
        length--;
        cout << "The list with deleted tail: "<< endl;
        printList();
    }

    void deleteAtIndex(int index) {
        Node<T> *temp = get(index);
        int theindex = index;
        Data *tempVal = temp->value;
        if (temp->prev) {
            temp->prev->next = temp->next;
            //tempVal;
        } else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;
        }
        delete tempVal;
        delete temp;
        length--;
        cout <<"The list after deleted @index: "<<endl;
        printList();
    }

    // Method that sorts the DL
    void sortList() {
        Node<T> *current;
        Node<T> *temp = nullptr;
        bool swap = true;
        do {
            swap = false;
            current = head;
            while (current->next != temp) {
                Data *currentVal = current->value;
                Data *currentNextVal = current->next->value;
                //if (currentNextVal > currentVal) {}
                if (currentNextVal->compareData(*currentVal)) {
                    Data *tempVal = currentVal;
                    current->value = currentNextVal;
                    current->next->value = tempVal;
                    swap = true;
                } current = current->next;
            }
            temp = current;
        } while (swap);
        cout << "Sorted List: "<<endl;
        printList();
    }
    //Method that removes duplicate nodes
    void removeMultiples() {
        sortList();
        Node<T> *current = head;
        Node<T> *temp;
        while (current != nullptr) {
            temp = current->next;
            if (temp != nullptr) {
                Data *currVal = current->value;
                Data *tempVal = temp->value;
/*              if (currVal->compareData(*tempVal)) {
                    if(temp->next != nullptr){
                        temp->next-> = current->prev;
                    }
                    delete tempVal;
                    length--;
                }*/
                if (currVal->compareEqualData(*tempVal)) {
                    current->next = temp->next;
                    length--;
                    if(temp->next != nullptr){
                        temp->next->prev = current->next;
                    }
                    delete temp;
                    length--;
                } else{
                    current = current->next;
                }
            }else{break;}
        }
        cout <<"List without duplicates: "<< endl;
        printList();
    }
        //Method that counts how many nodes have the value matching to T value passed in the argument
        int countMultiples(T value) {
            sortList();
            int numOfMult = 0;
            Node<T> *current = head;
            while (current != nullptr) {
                Data *currVal = current->value;
                if (currVal->compareEqualData(value)) {
                    numOfMult++;
                }
                current = current->next;
            }
            cout <<"The number of multiples are: ";
            return numOfMult;
        }
        //Method that splits list into two: head and tail
        void headTailSplit() {
        int preLength = length;
        int headLength = 0;
        int tailLength = 0;
        int mid = length/2;
        Node<T> *current = head;
        Node<T> *middleNode = nullptr;
        int count =0;
        while(count<mid){
            middleNode = current;
            current = current->next;
            count++;
        }
        if(middleNode){
            middleNode->next = nullptr;
            current->prev = nullptr;
        }
        if (preLength % 2 ==0 ){
            headLength = preLength/2;
            tailLength = preLength/2;
        }
        else{
            headLength = preLength/2;
            tailLength = (preLength/2) + 1;
        }

        DoubleLinkedList<T> *listA = new DoubleLinkedList<T>(head->value);
        listA->head = head;
        listA->tail = middleNode;
        listA->length = headLength;

        DoubleLinkedList<T> *listB = new DoubleLinkedList<T>(current->value);
        listB->head = current;
        listB->tail = tail;
        listB->length = tailLength;



        cout<<"Head list: "<<endl;
        listA->printList();

        cout<<"Tail list: "<<endl;
        listB->printList();
        cout<<endl;

        while(head){
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        }
        //Method that reverses the DL
        void reverseList() {
/*          Node<T> *temp = NULL;
            Node<T> *current;
            current = tail;

            while (current != NULL) {
                cout << current->value << endl;
                current = current->prev;
            }*/
        Node<T> *current = head;
        Node<T> *temp = nullptr;
        Node<T> *nextNode;
        while(current != nullptr){
            nextNode = current->next;
            current->next = temp;
            current->prev = nextNode;
            temp = current;
            current = nextNode;
        }
        head = temp;
        printList();
        }
    };

// Main Program

    int main() {
        // creating data object
        Data *d1 = new Data(10, "ab");
        Data *d2 = new Data(11, "abc");
        Data *d3 = new Data(12, "abcd");
        Data *d4 = new Data(14, "APHI");
        Data *d5 = new Data(10, "ab");
        Data *d6 = new Data(14, "APHI");
        Data *d7 = new Data(20, "GPHI");
        Data *d8 = new Data(19, "topG");
        Data *d9 = new Data(18, "SigEp");
        Data *d10= new Data(17, "DCHI");

        //extra data to be used for modification
        Data *d11 = new Data(15, "DG");
        Data *d12 = new Data(1, "AXO");
        Data *d13= new Data(1869, "KSIG");
        Data *d14 = new Data(10000, "ZBT");
        Data *d15 = new Data(21, "SigChi");

        // Creating Linked List
        DoubleLinkedList<Data> *ll1 = new DoubleLinkedList<Data>(d1);
        ll1->append(d2);
        ll1->append(d3);
        ll1->append(d4);
        ll1->append(d5);
        ll1->append(d6);
        ll1->append(d7);
        ll1->append(d8);
        ll1->append(d9);
        ll1->append(d10);

        // Calling operations on Linked List

      int input  = 0 ;
      cout<<"Here is the original list: "<<endl;
        ll1->printList();
      cout<<"Hello, the list is already preloaded with 10 elements. Please enter 0 to start."<<endl;
      cout<<"Type one of the following integers for desired function call."<<endl;

      cout<<"You may modify the current list with the following five options into the list: "<<endl;
      d11->print();
      d12->print();
      d13->print();
      d14->print();
      d15->print();

      cout<<"1 -> Delete a List"<<endl;
      cout<<"2 -> Insert at Head"<<endl;
      cout<<"3 -> Insert at Tail"<<endl;
      cout<<"4 -> Insert at Index"<<endl;
      cout<<"5 -> Delete at Head"<<endl;
      cout<<"6 -> Delete at Tail"<<endl;
      cout<<"7 -> Delete at Index"<<endl;
      cout<<"8 -> Reverse List"<<endl;
      cout<<"9 -> Sort List"<<endl;
      cout<<"10 -> Count Multiples"<<endl;
      cout<<"11 -> Remove Multiples"<<endl;
      cout<<"12 -> Head Tail Split"<<endl;
      cout<<"13 -> Exit the Program"<<endl;
      cout<<endl;

      bool condition = true;
      int dataIndex = 0;
      int i = 0;
      int j = 0;
      while(condition) {
          cin >> input;
          switch (input) {
              case 1:
                  delete ll1;
                  cout<<"The list has been deleted."<<endl;
                  condition = false;
                  break;
              case 2:
                  cout<<"Enter a number between 1-5 to insert some data into the head position."<<endl;
                  cin >> dataIndex;
                  cout<< dataIndex;
                  if(dataIndex == 1){
                      ll1->insert(0, d11);
                      cout<<endl;
                      cout<<"New list with an insert at head:"<<endl;
                      ll1->printList();
                  }else if( dataIndex == 2){
                      ll1->insert(0, d12);
                      cout<<endl;
                      cout<<"New list with an insert at head:"<<endl;
                      ll1->printList();
                  } else if(dataIndex == 3){
                      ll1->insert(0, d13);
                      cout<<endl;
                      cout<<"New list with an insert at head:"<<endl;
                      ll1->printList();
                  } else if(dataIndex ==4){
                      ll1->insert(0, d14);
                      cout<<endl;
                      cout<<"New list with an insert at head:"<<endl;
                      ll1->printList();
                  } else if(dataIndex ==5){
                      ll1->insert(0, d15);
                      cout<<endl;
                      cout<<"New list with an insert at head:"<<endl;
                      ll1->printList();
                  }else{
                      cout<<"You did not enter a number between 1-5."<<endl;
                  }
                  break;
              case 3:
                  cout<<"Enter a number between 1-5 to insert some data into the tail position."<<endl;
                  cin >> dataIndex;
                  if(dataIndex == 1){
                      int lengthIndex = ll1->getLength();
                      cout<<"New list with an insert at tail: "<<endl;
                      ll1->insert(lengthIndex, d11);
                      ll1->printList();
                  }else if( dataIndex == 2){
                      int lengthIndex = ll1->getLength();
                      cout<<"New list with an insert at tail: "<<endl;
                      ll1->insert(lengthIndex, d12);
                      ll1->printList();
                  } else if(dataIndex == 3){
                      int lengthIndex = ll1->getLength();
                      cout<<"New list with an insert at tail: "<<endl;
                      ll1->insert(lengthIndex, d13);
                      ll1->printList();
                  } else if(dataIndex ==4){
                      int lengthIndex = ll1->getLength();
                      cout<<"New list with an insert at tail: "<<endl;
                      ll1->insert(lengthIndex, d14);
                      ll1->printList();
                  } else if(dataIndex ==5){
                      int lengthIndex = ll1->getLength();
                      cout<<"New list with an insert at tail: "<<endl;
                      ll1->insert(lengthIndex, d15);
                      ll1->printList();
                  }else{
                      cout<<"You did not enter a number between 1-5."<<endl;
                  }
                  break;
              case 4:
                  cout << "Enter desired index to insert (0-9) at: " << endl;
                  cin >> i;
                  cout<< "Then choose a number between 1-5, to insert some data into the list."<<endl;
                  cin >> dataIndex;
                  if(dataIndex == 1){
                      cout<<"New list with an insert at index: "<<endl;
                      ll1->insert(i, d11);
                      ll1->printList();
                  }else if( dataIndex == 2){
                      cout<<"New list with an insert at index: "<<endl;
                      ll1->insert(i, d12);
                      ll1->printList();
                  } else if(dataIndex == 3){
                      cout<<"New list with an insert at index: "<<endl;
                      ll1->insert(i, d13);
                      ll1->printList();
                  } else if(dataIndex ==4){
                      cout<<"New list with an insert at index: "<<endl;
                      ll1->insert(i, d14);
                      ll1->printList();
                  } else if(dataIndex ==5){
                      cout<<"New list with an insert at index: "<<endl;
                      ll1->insert(i, d15);
                      ll1->printList();
                  }else{
                      cout<<"You did not enter a number between 1-5."<<endl;
                  }
                  break;
              case 5:
                  ll1->deleteAtHead();
                  break;
              case 6:
                  ll1->deleteAtTail();
                  break;
              case 7:
                  cout << "Enter desired index (0-9) to delete at: " << endl;
                  cin >> j;
                  ll1->deleteAtIndex(j);
                  break;
              case 8:
                  ll1->reverseList();
                  break;
              case 9:
                  ll1->sortList();
                  break;
              case 10:
                  cout<<"Enter a number between 1-10 to search for duplicates of dX"<<endl;
                  cin >> dataIndex;
                  if(dataIndex == 1){
                      cout<<ll1->countMultiples(*d1);
                  }else if(dataIndex == 2){
                      cout<<ll1->countMultiples(*d2);
                  } else if(dataIndex == 3){
                      cout<<ll1->countMultiples(*d3);
                  } else if(dataIndex ==4){
                      cout<<ll1->countMultiples(*d4);
                  } else if(dataIndex ==5) {
                      cout << ll1->countMultiples(*d5);
                  }else if(dataIndex == 6){
                          cout<<ll1->countMultiples(*d6);
                  }else if(dataIndex == 7){
                      cout << ll1->countMultiples(*d7);
                  }else if(dataIndex == 8){
                      cout<<ll1->countMultiples(*d8);
                  }else if( dataIndex == 9){
                      cout<<ll1->countMultiples(*d9);
                  }else if( dataIndex == 10){
                      cout<<ll1->countMultiples(*d10);
                  }
                  else{
                      cout<<"You did not enter a number between 1-5."<<endl;
                  }
                  cout<<endl;
                  break;
              case 11:
                  ll1->removeMultiples();
                  break;
              case 12:
                  ll1->headTailSplit();
                  condition = false;
                  break;
              case 13:
                  condition = false;
                  break;
              default:
                  cout<<"Enter a valid number within the range."<< endl;
                  break;
          }
      }
        return 0;
}