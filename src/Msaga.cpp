#include <iostream>
#include <fstream>
#include "SyntaxTree.hpp"

int main() {
    std::ifstream inputStream("test/examples2/28_lista_deklaracija/test.in");

    SyntaxTree st;
    st.load(std::cin);
    //st.print();
    st.check();
    return 0;
}