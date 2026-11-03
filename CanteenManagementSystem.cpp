#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

class MenuItem {
public:
    int id, quantity; string name; double price; bool available;
    MenuItem(int i=0, string n="", double p=0, int q=0): id(i), quantity(q), name(n), price(p), available(q>0) {}
    void display() const {
        cout << "ID: " << id << " | Item: " << name << " | Price: Rs." << fixed << setprecision(2) << price
             << " | Stock: " << quantity << " | Status: " << (available ? "Available" : "Unavailable") << '\n';
    }
};
class Student {
public:
    int id; string name;
    Student(int i=0, string n=""): id(i), name(n) {}
};
class Order {
public:
    int id, studentId, itemId, quantity; double total; string status;
    Order(int i=0,int s=0,int item=0,int q=0,double t=0,string st="Pending"):
        id(i),studentId(s),itemId(item),quantity(q),total(t),status(st) {}
};
class CanteenSystem {
    vector<MenuItem> menuItems; vector<Student> students; vector<Order> orders;
    const string menuFile="menu.txt", studentFile="students.txt", orderFile="orders.txt";
    int readInt(const string& msg) {
        int x; while (true) { cout << msg; if (cin >> x) { cin.ignore(numeric_limits<streamsize>::max(),'\n'); return x; }
            cout << "Invalid input. Enter a number.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
    }
    double readPrice(const string& msg) {
        double x; while (true) { cout << msg; if (cin >> x && x >= 0) { cin.ignore(numeric_limits<streamsize>::max(),'\n'); return x; }
            cout << "Invalid price. Enter zero or a positive value.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
    }
    string readText(const string& msg) {
        string s; do { cout << msg; getline(cin,s); if (s.empty()) cout << "Input cannot be empty.\n"; } while(s.empty()); return s;
    }
    MenuItem* findItem(int id) { for (auto& x:menuItems) if(x.id==id) return &x; return nullptr; }
    Student* findStudent(int id) { for (auto& x:students) if(x.id==id) return &x; return nullptr; }
    Order* findOrder(int id) { for (auto& x:orders) if(x.id==id) return &x; return nullptr; }
    void saveMenu() const { ofstream out(menuFile); if(!out){cout<<"Error saving menu.\n";return;}
        for(const auto& x:menuItems) out<<x.id<<'|'<<x.name<<'|'<<x.price<<'|'<<x.quantity<<'\n'; }
    void saveStudents() const { ofstream out(studentFile); if(!out){cout<<"Error saving students.\n";return;}
        for(const auto& x:students) out<<x.id<<'|'<<x.name<<'\n'; }
    void saveOrders() const { ofstream out(orderFile); if(!out){cout<<"Error saving orders.\n";return;}
        for(const auto& x:orders) out<<x.id<<'|'<<x.studentId<<'|'<<x.itemId<<'|'<<x.quantity<<'|'<<x.total<<'|'<<x.status<<'\n'; }
    void loadRecords() {
        string line;
        ifstream mi(menuFile); while(getline(mi,line)){ stringstream ss(line); string a,b,c,d;
            if(getline(ss,a,'|')&&getline(ss,b,'|')&&getline(ss,c,'|')&&getline(ss,d,'|')) try{menuItems.emplace_back(stoi(a),b,stod(c),stoi(d));}catch(...){} }
        ifstream si(studentFile); while(getline(si,line)){ stringstream ss(line); string a,b;
            if(getline(ss,a,'|')&&getline(ss,b,'|')) try{students.emplace_back(stoi(a),b);}catch(...){} }
        ifstream oi(orderFile); while(getline(oi,line)){ stringstream ss(line); string a,b,c,d,e,f;
            if(getline(ss,a,'|')&&getline(ss,b,'|')&&getline(ss,c,'|')&&getline(ss,d,'|')&&getline(ss,e,'|')&&getline(ss,f,'|'))
                try{orders.emplace_back(stoi(a),stoi(b),stoi(c),stoi(d),stod(e),f);}catch(...){} }
    }
public:
    CanteenSystem(){loadRecords();}
    void addMenuItem(){ int id=readInt("Enter item ID: "); if(findItem(id)){cout<<"Item ID already exists.\n";return;}
        string name=readText("Enter item name: "); double price=readPrice("Enter price: Rs."); int qty=readInt("Enter available quantity: ");
        if(qty<0){cout<<"Quantity cannot be negative.\n";return;} menuItems.emplace_back(id,name,price,qty); saveMenu(); cout<<"Menu item added successfully.\n"; }
    void displayMenu() const { if(menuItems.empty()){cout<<"No menu items available.\n";return;} cout<<"\n--- CANTEEN MENU ---\n"; for(const auto& x:menuItems)x.display(); }
    void registerStudent(){ int id=readInt("Enter student ID: "); if(findStudent(id)){cout<<"Student ID already exists.\n";return;}
        string name=readText("Enter student name: "); students.emplace_back(id,name); saveStudents(); cout<<"Student registered successfully.\n"; }
    void placeOrder(){ int sid=readInt("Enter student ID: "); if(!findStudent(sid)){cout<<"Student not found. Register first.\n";return;}
        int iid=readInt("Enter item ID: "); MenuItem* item=findItem(iid); if(!item||!item->available){cout<<"Item unavailable or not found.\n";return;}
        int qty=readInt("Enter quantity: "); if(qty<=0||qty>item->quantity){cout<<"Invalid quantity or insufficient stock.\n";return;}
        int oid=1; for(const auto& o:orders) if(o.id>=oid) oid=o.id+1; double total=item->price*qty;
        orders.emplace_back(oid,sid,iid,qty,total,"Pending"); item->quantity-=qty; item->available=item->quantity>0; saveOrders(); saveMenu();
        cout<<"Order placed successfully. Order ID: "<<oid<<'\n'<<"Total amount: Rs."<<fixed<<setprecision(2)<<total<<'\n'; }
    void searchOrder(){ int id=readInt("Enter order ID: "); Order* o=findOrder(id); if(!o){cout<<"Order not found.\n";return;}
        Student* s=findStudent(o->studentId); MenuItem* x=findItem(o->itemId);
        cout<<"Order ID: "<<o->id<<" | Student: "<<(s?s->name:"Unknown")<<'\n';
        cout<<"Item: "<<(x?x->name:"Unknown")<<" | Quantity: "<<o->quantity<<" | Total: Rs."<<fixed<<setprecision(2)<<o->total<<" | Status: "<<o->status<<'\n'; }
    void updateStatus(){ int id=readInt("Enter order ID: "); Order* o=findOrder(id); if(!o){cout<<"Order not found.\n";return;}
        cout<<"1. Pending\n2. Preparing\n3. Ready\n"; int c=readInt("Select status: "); if(c<1||c>3){cout<<"Invalid status.\n";return;}
        o->status=(c==1?"Pending":c==2?"Preparing":"Ready"); saveOrders(); cout<<"Order status updated successfully.\n"; }
    void orderHistory() const { if(orders.empty()){cout<<"No orders recorded.\n";return;} cout<<"\n--- ORDER HISTORY ---\n";
        for(const auto& o:orders){ string sn="Unknown",in="Unknown"; for(const auto& s:students)if(s.id==o.studentId)sn=s.name;
            for(const auto& x:menuItems)if(x.id==o.itemId)in=x.name;
            cout<<"Order ID: "<<o.id<<" | Student ID: "<<o.studentId<<" | Student: "<<sn<<'\n';
            cout<<in<<" x "<<o.quantity<<" | Total: Rs."<<fixed<<setprecision(2)<<o.total<<" | Status: "<<o.status<<'\n'; } }
    void menu(){ int c; do { cout<<"\n=== SMART COLLEGE CAMPUS CANTEEN MANAGEMENT SYSTEM ===\n"
        <<"1. Add Menu Item\n2. Display Menu\n3. Register Student\n4. Place Order\n5. Search Order\n6. Update Order Status\n7. View Order History\n8. Exit\n";
        c=readInt("Enter your choice: "); switch(c){case 1:addMenuItem();break;case 2:displayMenu();break;case 3:registerStudent();break;
        case 4:placeOrder();break;case 5:searchOrder();break;case 6:updateStatus();break;case 7:orderHistory();break;
        case 8:cout<<"Thank you for using the system.\n";break;default:cout<<"Invalid menu choice.\n";} }while(c!=8); }
};
int main(){ CanteenSystem system; system.menu(); return 0; }
