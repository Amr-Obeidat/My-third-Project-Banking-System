Simple Bank System in C++

A console-based bank management system in C++ using structs, vectors, and text files. Designed as a practice project .

Features

Add, delete, search, and update clients.

Deposit, withdraw, and transfer money between clients.

Display all clients and total balances.

Validates pin codes, account numbers, and balances.

How It Works

Client data is stored in Client.txt.

All operations check if a client exists before proceeding.

Functions read and write to the file as needed.

Notes

Existence checks prevent actions on non-existent clients.

Some functions read the file multiple times — can be optimized by loading all clients once.

Input is validated via the Amr library.

 I could have used maps/sets for faster searches and uniqueness, but this project is kept simple for practice purposes.

