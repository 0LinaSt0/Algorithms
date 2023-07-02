#include "../includes/stack.hpp"

namespace s21::tests {

TEST(TEST_SUITE_NAME, EMPTY_CONSTRUCTOR) {
    s21::Stack<int> stack;

    ASSERT_EQ(stack.size(), 0);
    ASSERT_TRUE(stack.empty());
}

TEST(TEST_SUITE_NAME, COPY_CONSTRUCTOR){
    s21::Stack<int> stack1;

    for (int i = 0; i < max_size; i++){
        stack1.push(i);
    }

    ASSERT_EQ(stack1.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack1.empty());

    s21::Stack<int> stack2(stack1);
    ASSERT_EQ(stack2.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack2.empty());

    while (!stack1.empty()){
        ASSERT_EQ(stack1.pop(), stack2.pop());
        ASSERT_EQ(stack1.size(), stack2.size());
    }
    ASSERT_EQ(stack1.empty(), stack2.empty());
}

TEST(TEST_SUITE_NAME, MOVE_CONSTRUCTOR){
    s21::Stack<int> stack1;

    for (int i = 0; i < max_size; i++){
        stack1.push(i);
    }

    ASSERT_EQ(stack1.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack1.empty());

    s21::Stack<int> stack2(std::move(stack1));
    ASSERT_EQ(stack2.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack2.empty());
    ASSERT_EQ(stack1.size(), 0);
    ASSERT_TRUE(stack1.empty());
}

TEST(TEST_SUITE_NAME, COPY_OPERATOR){
    s21::Stack<int> stack1;

    for (int i = 0; i < max_size; i++){
        stack1.push(i);
    }

    ASSERT_EQ(stack1.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack1.empty());

    s21::Stack<int> stack2;
    stack2 = stack1;
    ASSERT_EQ(stack2.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack2.empty());

    while (!stack1.empty()){
        ASSERT_EQ(stack1.pop(), stack2.pop());
        ASSERT_EQ(stack1.size(), stack2.size());
    }
    ASSERT_EQ(stack1.empty(), stack2.empty());
}

TEST(TEST_SUITE_NAME, MOVE_OPERATOR){
    s21::Stack<int> stack1;

    for (int i = 0; i < max_size; i++){
        stack1.push(i);
    }

    ASSERT_EQ(stack1.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack1.empty());

    s21::Stack<int> stack2;
    stack2 = std::move(stack1);
    ASSERT_EQ(stack2.size(), static_cast<s21::Stack<int>::size_type>(max_size));
    ASSERT_FALSE(stack2.empty());
    ASSERT_EQ(stack1.size(), 0);
    ASSERT_TRUE(stack1.empty());
}

TEST(TEST_SUITE_NAME, PUSH_CPY){
    srand(time(nullptr));
    s21::Stack<std::vector<int>> stack;
    s21::Stack<std::vector<int>>::size_type size = 0;

    for (int i = 0; i < max_iters; i++){
        std::vector<int> v(rand() % max_rand, rand() % max_rand);

        stack.push(v);
        size++;
        ASSERT_EQ(stack.size(), size);
        ASSERT_EQ(stack.top(), v);
    }
}

TEST(TEST_SUITE_NAME, PUSH_MOVE){
    srand(time(nullptr));
    s21::Stack<std::vector<int>> stack;
    s21::Stack<std::vector<int>>::size_type size = 0;

    for (int i = 0; i < max_iters; i++){
        std::vector<int> v(rand() % max_rand, rand() % max_rand);
        std::vector<int> v_cpy(v);
        ASSERT_EQ(v, v_cpy);

        stack.push(std::move(v));
        size++;
        ASSERT_EQ(stack.size(), size);
        ASSERT_EQ(stack.top(), v_cpy);
        ASSERT_TRUE(v.empty());
    }
}

TEST(TEST_SUITE_NAME, TOP_POP){
    srand(time(nullptr));
    s21::Stack<int> stack;

    for (int i = 0; i < max_rand; i++){
        stack.push(i);
    }
    s21::Stack<int>::size_type size = stack.size();

    int iters = 0;
    while (!stack.empty()){
        int f = stack.top();
        int s = stack.pop();
        ASSERT_EQ(f, s);
        iters++;
    }
    ASSERT_EQ(size, iters);
}

}
