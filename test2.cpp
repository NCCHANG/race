

// C++ program to demonstrate how to access local variable 
// inside another function using pointers 
#include <iostream> 
  
using namespace std; 
  
// Function to modify the value pointed to by a pointer 
void modifyValue(int* ptr) 
{ 
    // Dereferencing the pointer to modify the value 
    (*ptr) += 10; 
} 
  
int main() 
{ 
    int localVar = 5; 
    int* ptr = &localVar; // Getting the address of the 
                          // local variable 
  
    // Passing the pointer to another function 
    modifyValue(ptr); 
  
    // Output the modified value 
    cout << "Modified Value: " << localVar << endl; 
  
    return 0; 
}