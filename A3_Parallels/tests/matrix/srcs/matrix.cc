#include "../includes/matrix.h"

namespace s21::test::mtrx{

void TEST_MTRX_LOAD_FROM_FILE(){
    std::cout << __FUNCTION__ << std::endl;
    
    {
        try {
            ::s21::Matrix<int> mtrx = ::s21::Matrix<int>::LoadFromFile(
                MATERIALS_ROOT + "00_empty_matrix"
            );
            s21::test::Assert(__FILE__, __LINE__, false);
        } catch (::s21::Exception&){
            
        }
    }

    {
        try {
            ::s21::Matrix<int> mtrx = ::s21::Matrix<int>::LoadFromFile(
                MATERIALS_ROOT + "01_with_solution"
            );
            std::cout << mtrx << std::endl;
        } catch (::s21::Exception&){
            s21::test::Assert(__FILE__, __LINE__, false);
        }
    }
}

void TEST_MTRX_COPY_CONSTRUCTOR(){
    std::cout << __FUNCTION__ << std::endl;

    {
        ::s21::Matrix<int> mtrx1 = ::s21::Matrix<int>::LoadFromFile(
            MATERIALS_ROOT + "01_with_solution"
        );
        std::cout 
            << "mtrx1" << std::endl
            << mtrx1 << std::endl;

        ::s21::Matrix<int> mtrx2(mtrx1);
        std::cout 
            << "mtrx1" << std::endl
            << mtrx1 << std::endl;
        std::cout 
            << "mtrx2" << std::endl
            << mtrx2 << std::endl;
    }
}

void TEST_MTRX_MOVE_CONSTRUCTOR(){
    std::cout << __FUNCTION__ << std::endl;

    {
        ::s21::Matrix<int> mtrx1 = ::s21::Matrix<int>::LoadFromFile(
            MATERIALS_ROOT + "01_with_solution"
        );
        std::cout 
            << "mtrx1" << std::endl
            << mtrx1 << std::endl;

        ::s21::Matrix<int> mtrx2(std::move(mtrx1));
        std::cout 
            << "mtrx1" << std::endl
            << mtrx1 << std::endl;
        std::cout 
            << "mtrx2" << std::endl
            << mtrx2 << std::endl;
    }
}

void RUN_ALL_TESTS(){
    TEST_MTRX_LOAD_FROM_FILE();
    TEST_MTRX_COPY_CONSTRUCTOR();
    TEST_MTRX_MOVE_CONSTRUCTOR();
}

}
