#include <iostream>

using namespace std ;

// global variable :
int global_a = 1 ;
int global_b = 2 ;

// global const variable :
const int global_const_a = 1 ;
const int global_const_b = 2 ; 

int main()
{
    // local variable :
    int local_a = 1 ;
    int local_b = 2 ;
    int local_c = 3 ;

    // const variable :
    const int const_a = 1 ;
    const int const_b = 2 ;

    // static variable :
    static int static_a = 1 ;
    static int static_b = 2 ;
    static int static_c = 3 ;



    // local --------------------> reverse allocate !
    cout << "\nLOCAL variable address : " << endl ;
    // a
    cout << "address of 'a' (local) : " << &local_a << endl ;
    cout << "int vertion :    " << (int)&local_a << endl ;
    // b
    cout << "address of 'b' (local) : " << &local_b << endl ;
    cout << "int version :    " << (int)&local_b << endl ;
    // c 
    cout << "address of 'c' (local) : " << &local_c << endl ;
    cout << "int version :    " << (int)&local_c << "\n" << endl ;

    // const --------------------> reverse allocate ! (next to local )
    cout << "CONST variable address : " << endl ;
    // a
    cout << "address of 'a' (const) : " << &const_a << endl ;
    cout << "int version :    " << (int)&const_a << endl ;
    // b 
    cout << "address of 'b' (const) : " << &const_b << endl ;
    cout << "int version :    " << (int)&const_b << endl ;

cout << "\n---------------------------------------------------------------\n" << endl ;


    // global
    cout << "GLOBAL variable address : " << endl ;
    // a
    cout << "address of 'a' (global) : " << &global_a << endl ;
    cout << "int vertion :    " << (int)&global_a << endl ;
    // b
    cout << "address of 'b' (global) : " << &global_b << endl ;
    cout << "int version :    " << (int)&global_b << "\n" << endl ;
    // static (next to global )
    cout << "STATIC variable address : " << endl ;
    // a
    cout << "address of 'a' (static) : " << &static_a << endl ;
    cout << "int vertion :    " << (int)&static_a << endl ;
    // b
    cout << "address of 'b' (static) : " << &static_b << endl ;
    cout << "int version :    " << (int)&static_b << endl ;
    // c 
    cout << "address of 'c' (static) : " << &static_c << endl ;
    cout << "int version :    " << (int)&static_c << "\n" << endl ;


    // global const
    cout << "GLOBAL CONST variable address : " << endl ;
    // a
    cout << "address of 'a' (global_const) : " << &global_const_a << endl ;
    cout << "int version :    " << (int)&global_const_a << endl ;
    // b 
    cout << "address of 'b' (global_const) : " << &global_const_b << endl ;
    cout << "int version :    " << (int)&global_const_b << "\n" << endl ;


    // string
    cout << "String variable address : " << endl ;
    cout << "address of string : " << &"hello world !!!" << endl ;
    cout << "int version :    " << (int)&"hello world !!!" << "\n" << endl ;




    system("pause") ;
    system("cls") ;

}