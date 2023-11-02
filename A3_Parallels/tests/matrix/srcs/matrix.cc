#include "../includes/matrix.h"

namespace s21::test::mtrx{

TEST(TEST_SUITE_NAME_MTRX, TEST_LOAD_VALID_FILE){
    for (const std::string& file : ::s21::test::valid_graph_files){
        try {
            ::s21::Matrix<int> mtrx = ::s21::Matrix<int>::LoadFromFile(file);
        } catch (::s21::Exception&){
            ASSERT_TRUE(false);
        }
    }
}

TEST(TEST_SUITE_NAME_MTRX, TEST_LOAD_INVALID_FILE){
    for (const std::string& file : ::s21::test::invalid_graph_files){
        try {
            ::s21::Matrix<int> mtrx = ::s21::Matrix<int>::LoadFromFile(file);
            ASSERT_TRUE(false);
        } catch (::s21::Exception&){
            
        }
    }
}

TEST(TEST_SUITE_NAME_MTRX, TEST_COPY_CONSTRUCTOR){
    for (const std::string& file : ::s21::test::valid_graph_files){
        try {
            ::s21::Matrix<int> mtrx1 = ::s21::Matrix<int>::LoadFromFile(file);
            ::s21::Matrix<int> mtrx2(mtrx1);

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

TEST(TEST_SUITE_NAME_MTRX, TEST_MOVE_CONSTRUCTOR){
    for (const std::string& file : ::s21::test::valid_graph_files){
        try {
            ::s21::Matrix<int> mtrx = ::s21::Matrix<int>::LoadFromFile(file);
            ::s21::Matrix<int> mtrx_cpy(mtrx);
            ::s21::Matrix<int> mtrx_mv(std::move(mtrx));

            ASSERT_EQ(mtrx.RowsSize(), 0);
            ASSERT_EQ(mtrx.ColumnsSize(), 0);
            ASSERT_EQ(mtrx_cpy.RowsSize(), mtrx_mv.RowsSize());
            ASSERT_EQ(mtrx_cpy.ColumnsSize(), mtrx_mv.ColumnsSize());

            for (size_t i = 0; i < mtrx.RowsSize(); i++){
            for (size_t j = 0; j < mtrx.ColumnsSize(); j++){
                ASSERT_EQ(mtrx_cpy[i][j], mtrx_mv[i][j]);
            }
            }
        } catch (::s21::Exception&){
            ASSERT_TRUE(false);
        }
    }
}

}
