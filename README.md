# Sorting Encrypted Vector using Obligious Programming 
## Summary
This projcet is an example of obligious programming at work: sort a vector of encrypted objects without revealing sensetive information. The sorting algorith in the code uses only the interface of Secret class. Once the vector is sorterd, decrypt function is used to decrypt the message and output. 

### Installation
IDE : Xcode Version 10.2.1 (10E1001) \
Complier: Clang C++ frontend with LLVM as backend \
OS: macOS Catalina version 10.15.7 (19H2) 
### Directory structure
/Selection-sort-rk3660/main.cpp has main function of the program and functions used inside main()
/Selection-sort-rk3660/secret.h has the declaration and definition of Secret class
### Usage 
Automated run in Xcode
### Description of modules
There is one class - Secret that creates Secret objects. It has encrypt and decrypt functions that perform their obvious functions, import_vec function that loads values into vector of type Secret, and printArray functions that ouyputs the content of the vector. 
