#include "../includes/queue.hpp"

namespace s21::tests{

TEST(TEST_SUITE_NAME, EMPTY_CONSTRUCTOR) {
    s21::Queue<int> queue;

    ASSERT_EQ(queue.size(), 0);
}

TEST(TEST_SUITE_NAME, COPY_CONSTRUCTOR){
    s21::Queue<int> queue1;

    for (int i = 0; i < max_size; i++){
        queue1.push(i);
    }

    ASSERT_EQ(queue1.size(), static_cast<s21::Queue<int>::size_type>(max_size));

    s21::Queue<int> queue2(queue1);
    ASSERT_EQ(queue2.size(), static_cast<s21::Queue<int>::size_type>(max_size));

    while (queue1.size()){
        int v1 = queue1.front();
        int v2 = queue2.front();
        queue1.pop();
        queue2.pop();
        ASSERT_EQ(v1, v2);
        ASSERT_EQ(queue1.size(), queue2.size());
    }
}

TEST(TEST_SUITE_NAME, MOVE_CONSTRUCTOR){
    s21::Queue<int> queue1;

    for (int i = 0; i < max_size; i++){
        queue1.push(i);
    }

    ASSERT_EQ(queue1.size(), static_cast<s21::Queue<int>::size_type>(max_size));
    
    s21::Queue<int> queue2(std::move(queue1));
    ASSERT_EQ(queue2.size(), static_cast<s21::Queue<int>::size_type>(max_size));
    ASSERT_FALSE(!queue2.size());
    ASSERT_EQ(queue1.size(), 0);
    ASSERT_TRUE(!queue1.size());
}

TEST(TEST_SUITE_NAME, COPY_OPERATOR){
    s21::Queue<int> queue1;

    for (int i = 0; i < max_size; i++){
        queue1.push(i);
    }

    ASSERT_EQ(queue1.size(), static_cast<s21::Queue<int>::size_type>(max_size));
    
    s21::Queue<int> queue2;
    queue2 = queue1;
    ASSERT_EQ(queue2.size(), static_cast<s21::Queue<int>::size_type>(max_size));

    while (queue1.size()){
        int v1 = queue1.front();
        int v2 = queue2.front();
        queue1.pop();
        queue2.pop();
        ASSERT_EQ(v1, v2);
        ASSERT_EQ(queue1.size(), queue2.size());
    }
}

TEST(TEST_SUITE_NAME, MOVE_OPERATOR){
    s21::Queue<int> queue1;

    for (int i = 0; i < max_size; i++){
        queue1.push(i);
    }

    ASSERT_EQ(queue1.size(), static_cast<s21::Queue<int>::size_type>(max_size));

    s21::Queue<int> queue2;
    queue2 = std::move(queue1);
    ASSERT_EQ(queue2.size(), static_cast<s21::Queue<int>::size_type>(max_size));
    ASSERT_EQ(queue1.size(), 0);
}

TEST(TEST_SUITE_NAME, PUSH_CPY){
    srand(time(nullptr));
    s21::Queue<std::vector<int>> queue1;
    std::queue<std::vector<int>> queue2;
    s21::Queue<std::vector<int>>::size_type size = 0;

    for (int i = 0; i < max_iters; i++){
        std::vector<int> v(rand() % max_rand, rand() % max_rand);

        queue1.push(v);
        queue2.push(v);
        size++;
        ASSERT_EQ(queue1.size(), size);
        ASSERT_EQ(queue1.front(), queue2.front());
    }
}

TEST(TEST_SUITE_NAME, PUSH_MOVE){
    srand(time(nullptr));
    s21::Queue<std::vector<int>> queue1;
    std::queue<std::vector<int>> queue2;
    s21::Queue<std::vector<int>>::size_type size = 0;

    for (int i = 0; i < max_iters; i++){
        std::vector<int> v(rand() % max_rand, rand() % max_rand);
        std::vector<int> v_cpy(v);
        ASSERT_EQ(v, v_cpy);

        queue1.push(std::move(v));
        queue2.push(std::move(v_cpy));
        size++;
        ASSERT_EQ(queue1.front(), queue2.front());
        ASSERT_TRUE(v.empty());
    }
}

}