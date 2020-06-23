#ifndef DEBUG_LS_HPP_
#define  DEBUG_LS_HPP_

#include "constants.hpp"

void debug_header(){
    DebugSERIAL.print(F("[ DEBUG ] $ "));
}

//not in use yet
template<typename T, typename L, size_t N>
void debug_print(T& field_ref, std::string& label){
    
    if(std::is_same<T, lin::Vector<L, N>>::value)
        debug_lin_vec(label, field_ref);
    else{
        assert(false);
        // other debug statements dont exist yet!
    }
}

template<typename T, size_t N>
void debug_lin_vec(std::string& label, lin::Vector<T, N>& lin_vec){
    // for(int i = 0; i < N; i++){

    // }
}

void debug_terminator(){
    DebugSERIAL.print(F("\n"));
}
#endif