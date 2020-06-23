#ifndef DEBUG_LS_HPP_
#define DEBUG_LS_HPP_
#pragma once

#include "constants.hpp"

// #define debug_print(x) DebugSERIAL.print(x);
// #define debug_println(x) DebugSERIAL.println(x)
// #define debug_printF(x) DebugSERIAL.print(F(x))
// #define debug_printlnF(x) DebugSERIAL.println(F(x))

void debug_header1(void){
    DebugSERIAL.print(F("[ DEBUG ] $ "));
} // macro this

// //not in use yet
// template<typename T, typename L, size_t N>
// void debug_print(String label, T& field_ref){
    
//     if(std::is_same<T, lin::Vector<L, N>>::value)
//         debug_lin_vec(label, field_ref);
//     else{
//         assert(false);
//         // other debug statements dont exist yet!
//     }
// }

template<typename T, size_t N, size_t M>
void debug_lin_vec(String label, lin::Vector<T, N, M> lin_vec){
    DebugSERIAL.print(label);
    DebugSERIAL.print(": (");
    for(unsigned int i = 0; i < N-1; i++){
        DebugSERIAL.print(lin_vec(i));
    }
    DebugSERIAL.print(", ");
    DebugSERIAL.print(lin_vec(N-1));
    DebugSERIAL.print(")");
}

// void debug_terminator(){
//     DebugSERIAL.print(F("\n"));
// }

#endif