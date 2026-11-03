# Smart College Campus Canteen Management System using C++

A menu-driven C++ mini project based on the CIET Software Engineering Laboratory PDF.

## Features
- Add and display canteen menu items
- Register students
- Place orders after validating student, item, and stock
- Calculate bills and reduce available stock
- Search orders and update order status (Pending, Preparing, Ready)
- View order history
- Save and load records using text files

## C++ concepts
Classes and objects, encapsulation, STL vectors, file handling, input validation, functions, conditional statements, and loops.

## Compile and run (C++17)

**Windows:**
```bash
g++ -std=c++17 CanteenManagementSystem.cpp -o CanteenManagementSystem.exe
CanteenManagementSystem.exe
```

**Linux / macOS:**
```bash
g++ -std=c++17 CanteenManagementSystem.cpp -o CanteenManagementSystem
./CanteenManagementSystem
```

## Menu
1. Add Menu Item
2. Display Menu
3. Register Student
4. Place Order
5. Search Order
6. Update Order Status
7. View Order History
8. Exit

## Data files
The program creates `menu.txt`, `students.txt`, and `orders.txt` in its working directory to retain records between runs.

## Example test
1. Add item: ID `1`, name `Veg Sandwich`, price `50`, quantity `20`.
2. Register student: ID `101`, name `Arun Kumar`.
3. Place order: student ID `101`, item ID `1`, quantity `2`.
4. Expected bill: Rs.100.00; remaining stock: 18.
5. Search order ID `1` and update its status to `Ready`.

This is an educational mini project, not a production canteen payment system.
