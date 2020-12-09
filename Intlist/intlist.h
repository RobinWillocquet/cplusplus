#include <iostream>

class IntCell {

friend class IntList;

private:
    IntCell () : PrevCell(NULL), NextCell(NULL), val(0) {

     }
    IntCell *PrevCell;
    IntCell *NextCell;
    int val;

};

class IntList {
public:
    IntList () : FirstCell(NULL), LastCell(NULL) {

     }

    ~IntList () {
        FirstCell = NULL;
        LastCell = NULL;
    }

    void add_front(int a) {
        IntCell *front = new IntCell;
        front -> val = a;
        if(FirstCell != NULL) {
            FirstCell -> PrevCell = front;
            front -> NextCell = FirstCell;
        }
        FirstCell = front;
        if(LastCell == NULL) {
            LastCell = front;
        }
    }

    void add_back(int a) {
        IntCell *back = new IntCell;
        back -> val = a;
        if(LastCell != NULL) {
            LastCell -> NextCell = back;
            back -> PrevCell = LastCell;
        }
        LastCell = back;
        if(FirstCell == NULL) {
            FirstCell = back;
        }
    }

    void remove_front() {
        if(FirstCell != NULL) {
            if(FirstCell == LastCell){
                FirstCell = NULL;
                LastCell = NULL;
            }
            else {
                IntCell* first = FirstCell;
                FirstCell = first -> NextCell;
                FirstCell -> PrevCell = NULL;
                first -> NextCell = NULL;
            }
        }
    }
    
    void remove_back() {
        if(LastCell != NULL) {
            if(FirstCell == LastCell){
                FirstCell = NULL;
                LastCell = NULL;
            }
            else {
                IntCell* last = LastCell;
                LastCell = last -> PrevCell;
                LastCell -> NextCell = NULL;
                last -> PrevCell = NULL;
            }
        }
    }

    void remove(int a) {
        if(search(a)) {
            IntCell* top = FirstCell;
            if(top -> val == a) {
                remove_front();
            }
            else {
                while(top -> NextCell != NULL) {
                    top = top -> NextCell;
                    if(top -> val == a) {
                        if(top -> NextCell != NULL) {
                            IntCell* prev = top -> PrevCell;
                            IntCell* next = top -> NextCell;
                            prev -> NextCell = next;
                            next -> PrevCell = prev;
                            top -> NextCell = NULL;
                            top -> PrevCell = NULL;
                        }
                        else {
                            remove_back();
                        }

                    }
                }
            }
        }

    }

    bool search(int a) {
        IntCell* top = FirstCell;
        if(top -> val == a) {
            return true;
        }
        while(top -> NextCell != NULL) {
            top = top -> NextCell;
            if(top -> val == a) {
                return true;
            }
        }
        return false;
    }

    void print() {
        std::cout << '{';
        IntCell* top = FirstCell;
        std::cout << top -> val << ' ';
        while(top -> NextCell != NULL) {
            top = top -> NextCell;
            std::cout << top -> val << ' ';
        }
        std::cout << '}' << std::endl;
    }

    

private:
    IntCell *FirstCell;
    IntCell *LastCell;

};

