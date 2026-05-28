# Bookstore - Project 3

## 1. Project Description

This project is a continuation of my Project 2 bookstore project.
The project is a small bookstore management system written in C++.
The bookstore stores different types of books, such as printed books, e-books, and audio books.
The program can load books from a CSV file, show all books, sell books, apply discounts, and show the orders that were created.

The main goal of the project is to show the object oriented programming concepts that I used and the new requirements for Project 3.
The project uses inheritance, polymorphism, smart pointers, custom exceptions, operator overloading, deep copy, templates, and two design patterns.
For Project 3, I added file input, a Factory Pattern for creating books, a Strategy Pattern for discounts, a template class, and a template function.

## 2. Problem Statement

A bookstore has different types of books.
The book data is stored in a CSV file.
Each book can be a printed book, an e-book, or an audio book.
All books have common information, such as title, author, base price, and stock.
Each book type also has extra data.
A printed book has pages and weight.
An e-book has file format and file size.
An audio book has duration and narrator.

The program must load the books from the file and create the correct object type.
After that, the books must be stored in the bookstore.
The program must calculate final prices using polymorphism, because each derived class has its own price logic.
The bookstore must be able to sell books and reduce stock.
It must also apply different discount rules when selling.
The program must store and display orders.
If the input data is wrong or an operation is invalid, the program must handle the problem with custom exceptions.

## 3. Solution Overview

The solution is based on an abstract base class named `Book`.
The classes `PrintedBook`, `EBook`, and `AudioBook` inherit from `Book`.
Each derived class implements its own final price calculation and its own clone method.
This allows the program to use polymorphism through `std::shared_ptr<Book>`.

The `Bookstore` class stores books and orders.
For Project 3, the storage was changed to use the template class `Repository<T>`.
Books are stored in `Repository<Book>`, and orders are stored in `Repository<Order>`.

The `BookFactory` class creates book objects from CSV lines.
It reads the first field from a line and decides which type of object to create.
This keeps the object creation code outside `main.cpp`.

The `DiscountStrategy` class is used for discounts.
It is an abstract base class for discount rules.
The project has `NoDiscountStrategy`, `PercentageDiscountStrategy`, and `FixedDiscountStrategy`.
The bookstore can sell a book using any discount strategy.

The `printCollection<T>` template function prints collections of shared pointers.
It is used for books and orders.
Custom exceptions are used for invalid book data, missing books, and not enough stock.

## 4. What Changed From Project 2

In Project 2, the project already had the basic bookstore classes and OOP structure.
It had the `Book` hierarchy with `PrintedBook`, `EBook`, and `AudioBook`.
It used polymorphism, smart pointers, custom exceptions, `operator<<`, `dynamic_pointer_cast`, and CMake.
It also used `clone()` for deep copy, so a copied bookstore does not share the same book objects.

In Project 3, I added new parts required for the next stage of the project.
I added `BookFactory` and file input from `data/books.csv`.
This is the first design pattern, the Factory Pattern.
I also added `DiscountStrategy` and the three discount classes.
This is the second design pattern, the Strategy Pattern.
After that, I added the template class `Repository<T>` and the template function `printCollection<T>`.
I also cleaned `main.cpp` so it shows a clear demo instead of a complex menu.
Finally, I added this README self-review section for the final submission.

## 5. Design Pattern 1: Factory Pattern

The Factory Pattern is used through the `BookFactory` class.
`BookFactory` is responsible for creating books.
This means that `main.cpp` does not need to know all the details about how to create each book type.
The first field from the CSV line decides the type.

- `printed` creates a `PrintedBook`
- `ebook` creates an `EBook`
- `audio` creates an `AudioBook`

Example:

```cpp
auto books = BookFactory::loadBooksFromFile("data/books.csv");

for (const auto& book : books) {
    store.addBook(book);
}
```

This makes object creation cleaner.
If I later add another book type, I can update the factory instead of putting a lot of creation logic in `main.cpp`.
The CSV parsing is simple on purpose.
It does not support quoted fields or commas inside titles, because this is enough for this project.

## 6. Design Pattern 2: Strategy Pattern

The Strategy Pattern is used for discount rules.
`DiscountStrategy` is the base class.
It has a virtual function for applying a discount.
The derived classes are `NoDiscountStrategy`, `PercentageDiscountStrategy`, and `FixedDiscountStrategy`.

The bookstore can sell a book using any discount strategy.
This made the discount part easier to separate from the normal selling code.
A new discount can be added later without changing the whole selling logic too much.

Example:

```cpp
NoDiscountStrategy noDiscount;
PercentageDiscountStrategy studentDiscount(10);
FixedDiscountStrategy couponDiscount(20);

Order order = store.sellBook(2, 1, studentDiscount);
```

`NoDiscountStrategy` keeps the price unchanged.
`PercentageDiscountStrategy` subtracts a percent from the price.
`FixedDiscountStrategy` subtracts a fixed amount, but it does not allow the final price to become negative.

## 7. Template Class: Repository<T>

`Repository<T>` is a template class.
It stores objects in a `std::vector<std::shared_ptr<T>>`.
It has simple functions such as `add`, `getAll`, `empty`, `size`, and `clear`.
It also checks if the added pointer is `nullptr`.
If the pointer is empty, it throws a custom exception.

The project uses this template class with at least two types:

- `Repository<Book>`
- `Repository<Order>`

This is useful in my project because the bookstore needs similar collection logic for both books and orders.
Books and orders are different types, but the basic storage operations are similar.
Using a template avoids writing almost the same repository code twice.

The implementation is in the header file because C++ templates usually need to be visible to the compiler when they are used.
For this reason, there is no `Repository.cpp` file.

## 8. Template Function: printCollection<T>

`printCollection<T>` is a template function.
It prints a collection of shared pointers.
It works with different types that have `operator<<`.
In this project, both `Book` and `Order` can be printed with `operator<<`.

The function is used for:

- printing books
- printing orders

This is a simple example of generic programming in C++.
The function does not need to know if it prints books or orders.
It only needs a collection and a title.

## 9. OOP Concepts Used

- Encapsulation: class data is kept private or protected, and access is done through public methods.
- Composition: a `Bookstore` contains repositories for books and orders.
- Inheritance: `PrintedBook`, `EBook`, and `AudioBook` inherit from `Book`.
- Polymorphism: books are stored as `std::shared_ptr<Book>`, but the correct derived functions are called.
- Abstract class: `Book` is abstract because it has pure virtual functions.
- Pure virtual functions: `calculateFinalPrice()` and `clone()` must be implemented by derived classes.
- Virtual destructor: `Book` has a virtual destructor so derived objects can be deleted safely.
- Smart pointers: the project uses `std::shared_ptr` to manage book and order objects.
- Deep copy with `clone()`: when a bookstore is copied, the books are cloned, so the copy is independent.
- Custom exceptions: invalid data, missing books, and not enough stock are handled with custom exception classes.
- Static fields: book ids and order ids are generated with static fields.
- Const correctness: methods that do not modify objects are marked with `const`.
- Operator overloading: `operator<<` is used to print books and orders.
- `dynamic_pointer_cast`: used to find printed books and show shipping information.
- Templates: `Repository<T>` and `printCollection<T>` are used for generic code.
- Design patterns: Factory Pattern and Strategy Pattern are used in simple ways.

## 10. File Structure

```text
bookstore-project-3/
|-- include/
|   |-- AudioBook.h
|   |-- Book.h
|   |-- BookFactory.h
|   |-- Bookstore.h
|   |-- BookstoreException.h
|   |-- DiscountStrategy.h
|   |-- EBook.h
|   |-- Order.h
|   |-- PrintedBook.h
|   |-- Repository.h
|   |-- TemplateUtils.h
|
|-- src/
|   |-- AudioBook.cpp
|   |-- Book.cpp
|   |-- BookFactory.cpp
|   |-- Bookstore.cpp
|   |-- BookstoreException.cpp
|   |-- DiscountStrategy.cpp
|   |-- EBook.cpp
|   |-- Order.cpp
|   |-- PrintedBook.cpp
|
|-- data/
|   |-- books.csv
|   |-- discounts.csv
|
|-- main.cpp
|-- CMakeLists.txt
|-- README.md
```

Important files:

- `BookFactory.h` / `BookFactory.cpp`: creates books from CSV lines.
- `DiscountStrategy.h` / `DiscountStrategy.cpp`: contains the discount strategy classes.
- `Repository.h`: header-only template class for storing shared objects.
- `TemplateUtils.h`: contains the `printCollection<T>` template function.
- `data/books.csv`: contains example book data.
- `data/discounts.csv`: contains example discount data.

## 11. Build and Run

Run these commands from the project root:

```bash
cmake -S . -B build
cmake --build build
./build/bookstore
```

The program should be run from the project root because it loads the file `data/books.csv`.

## 12. Self-Review

This project started from my Project 2 bookstore project. I did not want to change the whole idea, because the bookstore example already worked well for OOP. The project has different types of books, and this fits inheritance quite naturally. A `PrintedBook`, an `EBook`, and an `AudioBook` are all books, but they also have their own extra information. For example, a printed book has pages and weight, an e-book has file format and file size, and an audio book has duration and narrator. Because of this, the `Book` base class made sense for this project.

The `Book` hierarchy is still one of the most important parts of my project. The base class `Book` stores common data like title, author, base price, and stock. The derived classes `PrintedBook`, `EBook`, and `AudioBook` add their own data and their own price calculation. I used pure virtual functions for `calculateFinalPrice()` and `clone()`. This means that every book type must say how its final price is calculated and how it can be copied. I think this helped me understand why abstract classes are useful, because `Book` gives the common interface, but the derived classes do the specific work.

Polymorphism is used when the bookstore stores books as `std::shared_ptr<Book>`. The `Bookstore` does not need to store three separate lists for printed books, e-books, and audio books. It can store them together and call virtual functions through the base pointer. In the demo from `main.cpp`, the program prints all books and sells books without checking the exact derived type in most places. The correct `calculateFinalPrice()` function is called automatically. This is a simple example, but it is useful and not only written for the requirement.

I also kept the deep copy idea from Project 2. The `Bookstore` copy constructor uses `clone()` when copying books. This is important because books are polymorphic objects. If I copied only the shared pointers, then two bookstores would point to the same book objects. That would be wrong for my demo, because selling a book from the copied store would also change the original store. In `main.cpp`, I create `Bookstore copyStore = store;`, then I sell a book from the copied store. After that, I print both stores. The original store keeps its old stock, while the copied store has one less copy for that book. This part helped me check that the clone logic really works.

For Project 3, I first added file input. In Project 2, the books were created directly in `main.cpp`, which made the file longer and mixed data with program logic. Now the books are loaded from `data/books.csv`. I think this made the project cleaner, because the book examples are outside the code. The CSV file has simple lines such as type, title, author, base price, stock, and two extra fields. The parser is basic. It splits by comma and trims simple spaces. It does not support quoted text or commas inside titles and authors. This is a weakness, but I think it is acceptable for this project because I was not trying to build a complete CSV parser.

The Factory Pattern is implemented with `BookFactory`. I used this pattern because it made the creation of books easier to organize. `main.cpp` does not create every book with `std::make_shared` anymore. Instead, it calls `BookFactory::loadBooksFromFile("data/books.csv")`. The factory reads every line and checks the first field. If the type is `printed`, it creates a `PrintedBook`. If the type is `ebook`, it creates an `EBook`. If the type is `audio`, it creates an `AudioBook`. In my opinion, the project became clearer after moving book creation to `BookFactory`, because `main.cpp` now shows the demo instead of containing all object creation details.

The second design pattern is the Strategy Pattern. I used it for discounts because discounts are easy to change. The base class is `DiscountStrategy`, and the derived classes are `NoDiscountStrategy`, `PercentageDiscountStrategy`, and `FixedDiscountStrategy`. The `Bookstore` has a selling function that receives a discount strategy. This means the selling logic does not need one large `if` block for every discount type. This part is still simple, but it helped me understand how Strategy works. If I later want to add a discount for loyal customers or a discount for large quantities, I can add another class derived from `DiscountStrategy`.

I also added `data/discounts.csv`, but right now it is mostly example data. The program does not fully parse discounts from this file. I wrote this clearly because I do not want the README to claim something that is not true. In the current code, the discount objects are created directly in `main.cpp`: `NoDiscountStrategy`, `PercentageDiscountStrategy`, and `FixedDiscountStrategy`. A future improvement could be to load discount rules from `data/discounts.csv`, but I kept this step simple because the main requirement was to show the Strategy Pattern.

The template class `Repository<T>` is used for storing objects. It stores `std::shared_ptr<T>` values in a vector. In this project, I use it as `Repository<Book>` and `Repository<Order>`. This makes sense because the bookstore needs to store both books and orders. Both collections need similar actions, such as adding an item and getting all items. The repository also checks if an added pointer is null. I kept this class small because the project does not need a real database or complicated storage layer.

The template function `printCollection<T>` is in `TemplateUtils.h`. It prints a title and then prints every object from a collection of shared pointers. It works for types that have `operator<<`. In my project, it is used for books and orders, so the two instantiations are meaningful. `Bookstore::showBooks()` uses it for `Book`, and `Bookstore::showOrders()` uses it for `Order`. This was a simple way to use a template function without making the code too advanced.

I also cleaned `main.cpp` for the final demo. Earlier I had a menu, but for the final version I changed it to a fixed demo. I did this because it is easier to present. The program prints the title, loads the books from `data/books.csv`, shows all loaded books, shows printed book shipping information, sells books with three discount strategies, prints orders, shows books again after selling, demonstrates deep copy, and then demonstrates exceptions. There is no real menu or graphical interface now. The program is more like a presentation demo, and I think that is fine for this assignment.

The project uses exceptions for invalid actions. For example, if the file has invalid book data, `BookFactory` can throw an exception. If a book id does not exist, `Bookstore` throws `BookNotFoundException`. If the quantity is too large, it throws `NotEnoughStockException`. In the final demo, I try to sell too many copies and I try to find book id 999. These examples show that the program handles errors instead of ignoring them.

There are still things that could be improved. The project is still small. The CSV parser is simple and would not be enough for real book data with commas inside fields. The user interaction is also very limited because there is no menu in the final version. More filters could be added later, for example search by author, search by book type, or show only books that are in stock. The discount data file could also be used in the code instead of being only example data. I could also add more tests, because right now the checking is done mainly through the demo output.

Overall, I think my project meets the Project 3 requirements. It has the old Project 2 OOP parts, plus `BookFactory`, `DiscountStrategy`, `Repository<T>`, and `printCollection<T>`. The code is not perfect, but I can explain the main parts and why I added them. The new features are connected to the bookstore idea, not added as separate examples. `BookFactory` creates the books, `DiscountStrategy` changes the selling price, `Repository<T>` stores books and orders, and `printCollection<T>` prints both collections. I think the project is clearer now than it was in Project 2, and it is still simple enough for me to understand and present.

## 13. Bibliography / Resources

- OOP course, seminar, and laboratory materials.
- C++ reference for `std::shared_ptr`, `std::vector`, `std::runtime_error`, file streams, and templates: https://en.cppreference.com/
- OOP project template: https://github.com/mcmarius/oop-template
- Tema 3 examples: https://github.com/mcmarius/poo/tree/master/tema-3
- OOP course repository: https://github.com/GFA03/oop
- Design pattern ideas: Factory Pattern and Strategy Pattern from general OOP theory.
- Previous Project 2 bookstore code used as the base for this project.
