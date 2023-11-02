#include "../includes/sle.h"

namespace s21::test::sle{

TEST(TEST_SUITE_NAME_SLE, TEST_LOAD_VALID_FILE){
    for (const std::string& file : ::s21::test::valid_sle_files){
        try {
            ::s21::Sle<int> mtrx = ::s21::Sle<int>::LoadFromFile(file);
        } catch (::s21::Exception& e){
            ASSERT_TRUE(false);
        }
    }
}

TEST(TEST_SUITE_NAME_SLE, TEST_LOAD_INVALID_FILE){
    for (const std::string& file : ::s21::test::invalid_graph_files){
        try {
            ::s21::Sle<int> mtrx = ::s21::Sle<int>::LoadFromFile(file);
            ASSERT_TRUE(false);
        } catch (::s21::Exception&){
            
        }
    }
}

TEST(TEST_SUITE_NAME_SLE, TEST_COPY_CONSTRUCTOR){
    for (const std::string& file : ::s21::test::valid_sle_files){
        try {            
            ::s21::Sle<int> mtrx1 = ::s21::Sle<int>::LoadFromFile(file);
            ::s21::Sle<int> mtrx2(mtrx1);

            ASSERT_EQ(mtrx1.RowsSize(), mtrx2.RowsSize());
            ASSERT_EQ(mtrx1.ColumnsSize(), mtrx2.ColumnsSize());

            for (size_t i = 0; i < mtrx1.RowsSize(); i++){
            for (size_t j = 0; j < mtrx1.ColumnsSize(); j++){
                ASSERT_EQ(mtrx1[i][j], mtrx2[i][j]);
            }
            }
        } catch (::s21::Exception&){
            ASSERT_TRUE(false);
        }
    }
}

TEST(TEST_SUITE_NAME_SLE, TEST_MOVE_CONSTRUCTOR){
    for (const std::string& file : ::s21::test::valid_sle_files){
        try {
            ::s21::Sle<int> mtrx = ::s21::Sle<int>::LoadFromFile(file);
            ::s21::Sle<int> mtrx_cpy(mtrx);
            ::s21::Sle<int> mtrx_mv(std::move(mtrx));

            ASSERT_EQ(mtrx.RowsSize(), 0);
            ASSERT_EQ(mtrx.ColumnsSize(), 0);
            ASSERT_EQ(mtrx_cpy.RowsSize(), mtrx_mv.RowsSize());
            ASSERT_EQ(mtrx_cpy.ColumnsSize(), mtrx_mv.ColumnsSize());

            for (size_t i = 0; i < mtrx_cpy.RowsSize(); i++){
            for (size_t j = 0; j < mtrx_cpy.ColumnsSize(); j++){
                ASSERT_EQ(mtrx_cpy[i][j], mtrx_mv[i][j]);
            }
            }
        } catch (::s21::Exception&){
            ASSERT_TRUE(false);
        }
    }
}

}
