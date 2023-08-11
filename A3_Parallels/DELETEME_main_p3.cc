#include <iostream>
#include <functional>
#include <utility>
#include <map>

#include "matrix/includes/matrix.h"
#include "algorithms/Winograd/includes/winograd.h"

using vec_type = std::vector<std::vector<double>>;


std::pair<vec_type, vec_type> vectors(void){
    std::pair<vec_type, vec_type> vec_pair;

    {
        vec_pair.first = vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6,	4},
            std::vector<double>{1,	2,	3,	5,	6,	7,	3},
            std::vector<double>{4,	5,	6,	8,	9,	10,	4},
            std::vector<double>{5,	6,	7,	9,	10,	11,	2},
            std::vector<double>{8,	9,	10,	12,	13,	14,	1}
        };

        vec_pair.second = vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6,	1,	4,	5,	6},
            std::vector<double>{1,	2,	3,	5,	6,	7,	2,	5,	6,	7},
            std::vector<double>{2,	5,	6,	8,	9,	10,	5,	8,	9,	10},
            std::vector<double>{3,	6,	7,	9,	10,	11,	6,	9,	10,	11},
            std::vector<double>{4,	9,	10,	12,	13,	14,	9,	12,	13,	14},
            std::vector<double>{5,	0,	5,	76,	23,	56,	0,	76,	23,	56},
            std::vector<double>{6,	3,	4,	89,	99,	77,	3,	89,	99,	77}
        };
    }
    {
        // vec_pair.first = vec_type{
        //     std::vector<double>{0,	1,	2,	3,	4,	5}
        // };

        // vec_pair.second = vec_type{
        //     std::vector<double>{0,	1,	2,	4,	5,	6},
        //     std::vector<double>{1,	2,	3,	5,	6,	7},
        //     std::vector<double>{4,	5,	6,	8,	9,	10},
        //     std::vector<double>{5,	6,	7,	9,	10,	11},
        //     std::vector<double>{8,	9,	10,	12,	13,	14},
        //     std::vector<double>{9,	10,	11,	13,	14,	15}
        // };
    }
    {
        // vec_pair.first = vec_type{
        //     std::vector<double>{0,	1,	2,	4,	5,	6,	4}
        // };

        // vec_pair.second = vec_type{
        //     std::vector<double>{0,	1,	2,	4,	5,	6,	1,	4,	5,	6},
        //     std::vector<double>{1,	2,	3,	5,	6,	7,	2,	5,	6,	7},
        //     std::vector<double>{2,	5,	6,	8,	9,	10,	5,	8,	9,	10},
        //     std::vector<double>{3,	6,	7,	9,	10,	11,	6,	9,	10,	11}
        // };

    }
    {
        // vec_pair.first = vec_type{};

        // vec_pair.second = vec_type{};
    }
    {
        // vec_pair.first = vec_type{std::vector<double>{}};

        // vec_pair.second = vec_type{std::vector<double>{}};

    }

    return vec_pair;
}



void check(vec_type& av, vec_type& bv){
    s21::Matrix<double> a(av);
    s21::Matrix<double> b(bv);

    // s21::WinogradUsual alg;
    s21::WinogradParallel alg;

    std::cout << alg.WinogradMultiplication(a, b).matrix_array << std::endl;
}

int main(){
    std::pair<vec_type, vec_type> vecs = vectors();

    check(vecs.first, vecs.second);
}
