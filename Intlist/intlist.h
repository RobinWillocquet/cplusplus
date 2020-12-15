#include <iostream>

class IntCell {

friend class IntList;

private:
    IntCell () : PrevCell(nullptr), NextCell(nullptr), val(0) {

     }
    IntCell *PrevCell;
    IntCell *NextCell;
    int val;

};

class IntList {
public:
    IntList () : FirstCell(nullptr), LastCell(nullptr) {

     }

    ~IntList () {
        while(LastCell != nullptr) {
            remove_front();
        }
    }

    void add_front(int a) {
        IntCell *front = new IntCell;
        front -> val = a;
        if(FirstCell != nullptr) {
            FirstCell -> PrevCell = front;
            front -> NextCell = FirstCell;
        }
        FirstCell = front;
        if(LastCell == nullptr) {
            LastCell = front;
        }
    }

    void add_back(int a) {
        IntCell *back = new IntCell;
        back -> val = a;
        if(LastCell != nullptr) {
            LastCell -> NextCell = back;
            back -> PrevCell = LastCell;
        }
        LastCell = back;
        if(FirstCell == nullptr) {
            FirstCell = back;
        }
    }

    void remove_front() {
        if(FirstCell != nullptr) {
            if(FirstCell == LastCell){
                IntCell* cellule = FirstCell;
                FirstCell = nullptr;
                LastCell = nullptr;
                delete cellule;
            }
            else {
                IntCell* first = FirstCell;
                FirstCell = first -> NextCell;
                FirstCell -> PrevCell = nullptr;
                first -> NextCell = nullptr;
                delete first;
            }
        }
    }
    
    void remove_back() {
        if(LastCell != nullptr) {
            if(FirstCell == LastCell){
                IntCell* cellule = FirstCell;
                FirstCell = nullptr;
                LastCell = nullptr;
                delete cellule;
            }
            else {
                IntCell* last = LastCell;
                LastCell = last -> PrevCell;
                LastCell -> NextCell = nullptr;
                last -> PrevCell = nullptr;
                delete last;
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
                while(top -> NextCell != nullptr) {
                    top = top -> NextCell;
                    if(top -> val == a) {
                        if(top -> NextCell != NULL) {
                            IntCell* prev = top -> PrevCell;
                            IntCell* next = top -> NextCell;
                            prev -> NextCell = next;
                            next -> PrevCell = prev;
                            top -> NextCell = nullptr;
                            top -> PrevCell = nullptr;
                            delete top;
                            return;
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
        while(top -> NextCell != nullptr) {
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
        while(top -> NextCell != nullptr) {
            top = top -> NextCell;
            std::cout << top -> val << ' ';
        }
        std::cout << '}' << std::endl;
    }

    int size() {
        if(FirstCell==nullptr and LastCell==nullptr) {
            return 0;
        }
        IntCell* top = FirstCell;
        int c = 1;
        while(top -> NextCell !=nullptr) {
            top = top -> NextCell;
            c++;
        }
        return c;
    }

    bool is_empty() {
        return size()==0;
    }

    int get_element_at(int s) {
        if(s>size()-1) {
            return 0;
        }
        else {
            IntCell* top = FirstCell;
            int c = 0;
            while(c != s) {
                top = top -> NextCell;
                c++;
            }
            return(top -> val);
        }
    }

    

private:
    IntCell *FirstCell;
    IntCell *LastCell;

};

