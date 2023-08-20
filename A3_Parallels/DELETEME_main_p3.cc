#include <iostream>
#include <functional>
#include <utility>
#include <array>
#include <map>

#include "matrix/includes/matrix.h"
#include "algorithms/Winograd/includes/winograd.h"

using vec_type = std::vector<std::vector<double>>;
using pair_vec_type = std::pair<vec_type, vec_type>;

size_t PARALLEL_COUNT = 20;

std::array<pair_vec_type, 5> tasks_array = {
    /*0*/pair_vec_type{
        vec_type{std::vector<double>{}}, 
        vec_type{std::vector<double>{}}
    },
    /*1*/pair_vec_type{
        vec_type{
            std::vector<double>{0,	1,	2,	3,	4,	5}
        }, vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6},
            std::vector<double>{1,	2,	3,	5,	6,	7},
            std::vector<double>{4,	5,	6,	8,	9,	10},
            std::vector<double>{5,	6,	7,	9,	10,	11},
            std::vector<double>{8,	9,	10,	12,	13,	14},
            std::vector<double>{9,	10,	11,	13,	14,	15}
        }
    },
    /*2*/pair_vec_type{
        vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6,	4}
        }, vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6,	1,	4,	5,	6},
            std::vector<double>{1,	2,	3,	5,	6,	7,	2,	5,	6,	7},
            std::vector<double>{2,	5,	6,	8,	9,	10,	5,	8,	9,	10},
            std::vector<double>{3,	6,	7,	9,	10,	11,	6,	9,	10,	11}
        }
    },
    /*3*/pair_vec_type{
        vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6,	4},
            std::vector<double>{1,	2,	3,	5,	6,	7,	3},
            std::vector<double>{4,	5,	6,	8,	9,	10,	4},
            std::vector<double>{5,	6,	7,	9,	10,	11,	2},
            std::vector<double>{8,	9,	10,	12,	13,	14,	1}
        }, vec_type{
            std::vector<double>{0,	1,	2,	4,	5,	6,	1,	4,	5,	6},
            std::vector<double>{1,	2,	3,	5,	6,	7,	2,	5,	6,	7},
            std::vector<double>{2,	5,	6,	8,	9,	10,	5,	8,	9,	10},
            std::vector<double>{3,	6,	7,	9,	10,	11,	6,	9,	10,	11},
            std::vector<double>{4,	9,	10,	12,	13,	14,	9,	12,	13,	14},
            std::vector<double>{5,	0,	5,	76,	23,	56,	0,	76,	23,	56},
            std::vector<double>{6,	3,	4,	89,	99,	77,	3,	89,	99,	77}
        }
    },
    /*4*/pair_vec_type{
        vec_type{
            std::vector<double>{0, 582, 0, 385, 0, 416, 675, 833, 27, 823, 317, 244, 0, 127, 0, 0, 806, 0, 954, 109},
            std::vector<double>{433, 0, 225, 446, 972, 158, 730, 425, 997, 308, 323, 144, 80, 656, 895, 118, 687, 0, 544, 816},
            std::vector<double>{378, 489, 0, 0, 16, 0, 412, 121, 268, 676, 76, 307, 616, 512, 690, 697, 109, 976, 0, 819},
            std::vector<double>{513, 0, 831, 0, 135, 32, 495, 841, 143, 0, 744, 0, 86, 302, 470, 0, 718, 838, 0, 958},
            std::vector<double>{641, 611, 871, 876, 0, 0, 80, 980, 291, 243, 336, 340, 0, 248, 498, 160, 965, 722, 908, 237},
            std::vector<double>{502, 633, 690, 362, 0, 0, 0, 0, 0, 283, 878, 899, 659, 666, 479, 871, 345, 718, 878, 632},
            std::vector<double>{797, 569, 0, 133, 133, 33, 0, 777, 72, 22, 176, 540, 0, 918, 549, 263, 320, 884, 154, 593},
            std::vector<double>{250, 365, 588, 73, 229, 258, 223, 0, 0, 790, 852, 500, 8, 155, 397, 77, 520, 581, 922, 120},
            std::vector<double>{844, 812, 0, 83, 546, 951, 15, 70, 0, 37, 998, 849, 369, 700, 453, 147, 34, 0, 768, 913},
            std::vector<double>{858, 92, 105, 426, 436, 435, 258, 804, 811, 0, 559, 341, 82, 588, 404, 0, 505, 264, 0, 310},
            std::vector<double>{826, 879, 731, 924, 390, 700, 128, 502, 583, 42, 0, 784, 147, 811, 826, 9, 287, 192, 671, 407},
            std::vector<double>{446, 878, 769, 206, 535, 318, 309, 0, 710, 398, 836, 0, 154, 0, 0, 303, 274, 0, 890, 910},
            std::vector<double>{52, 717, 703, 401, 573, 35, 313, 621, 708, 0, 752, 0, 0, 552, 552, 149, 834, 358, 963, 406},
            std::vector<double>{388, 910, 899, 231, 296, 595, 209, 403, 949, 834, 538, 906, 256, 0, 705, 514, 823, 449, 993, 303},
            std::vector<double>{708, 150, 335, 541, 343, 716, 0, 0, 0, 621, 594, 863, 906, 917, 0, 27, 990, 42, 927, 540},
            std::vector<double>{989, 801, 660, 185, 25, 834, 969, 239, 465, 366, 50, 770, 343, 292, 852, 0, 562, 617, 513, 998},
            std::vector<double>{95, 305, 114, 355, 71, 525, 930, 755, 0, 200, 293, 582, 889, 166, 562, 826, 0, 0, 846, 134},
            std::vector<double>{926, 550, 666, 388, 729, 895, 172, 434, 420, 436, 653, 435, 648, 0, 937, 711, 545, 0, 902, 401},
            std::vector<double>{247, 721, 101, 967, 456, 753, 974, 0, 575, 693, 0, 951, 830, 647, 514, 959, 173, 135, 0, 376}
        }, vec_type{
            std::vector<double>{0, 223, 776, 526, 88, 806, 6, 572, 238, 54, 42, 651, 154, 707, 253, 191, 967, 27, 0, 167, 660, 685, 307, 176, 463, 794, 958, 0, 0, 86, 286, 877, 806, 116, 752, 0, 504, 703, 194, 0, 469, 855, 421},
            std::vector<double>{809, 0, 44, 362, 451, 181, 149, 371, 458, 0, 0, 773, 0, 298, 0, 10, 573, 706, 130, 452, 616, 673, 475, 544, 850, 905, 663, 79, 637, 855, 484, 246, 74, 273, 0, 462, 441, 938, 447, 453, 380, 335, 730},
            std::vector<double>{147, 831, 0, 814, 44, 690, 165, 869, 245, 864, 367, 266, 782, 108, 0, 850, 684, 855, 383, 939, 125, 31, 915, 369, 419, 606, 272, 386, 841, 952, 0, 575, 168, 821, 750, 603, 787, 132, 52, 3, 650, 542, 465},
            std::vector<double>{961, 802, 742, 0, 862, 0, 98, 436, 400, 80, 577, 936, 258, 988, 349, 527, 30, 494, 43, 124, 58, 466, 989, 0, 378, 0, 980, 677, 965, 297, 696, 825, 0, 594, 615, 101, 28, 245, 0, 386, 0, 804, 340},
            std::vector<double>{630, 275, 957, 836, 0, 490, 689, 0, 914, 603, 12, 0, 177, 366, 992, 647, 581, 37, 675, 223, 839, 0, 719, 546, 466, 96, 0, 297, 490, 760, 764, 794, 690, 0, 252, 28, 213, 46, 644, 834, 285, 0, 404},
            std::vector<double>{35, 73, 911, 27, 838, 0, 0, 444, 146, 441, 548, 968, 244, 666, 642, 430, 117, 466, 332, 687, 949, 306, 529, 94, 112, 0, 128, 954, 31, 783, 238, 885, 970, 356, 19, 302, 445, 177, 0, 478, 59, 823, 130},
            std::vector<double>{533, 128, 989, 649, 292, 396, 0, 775, 260, 368, 76, 342, 106, 660, 762, 312, 352, 0, 484, 471, 889, 574, 0, 0, 0, 410, 259, 621, 0, 744, 132, 906, 718, 785, 156, 225, 544, 257, 0, 909, 864, 983, 822},
            std::vector<double>{956, 532, 533, 188, 50, 113, 369, 0, 992, 0, 691, 628, 359, 176, 294, 661, 930, 386, 573, 746, 337, 410, 442, 257, 128, 971, 0, 341, 138, 558, 55, 42, 336, 558, 559, 736, 39, 306, 708, 528, 556, 711, 403},
            std::vector<double>{903, 575, 7, 691, 488, 594, 710, 551, 0, 119, 739, 90, 913, 352, 731, 126, 441, 227, 565, 622, 814, 331, 199, 997, 791, 828, 223, 16, 74, 932, 0, 51, 657, 535, 699, 771, 0, 643, 403, 675, 702, 476, 876},
            std::vector<double>{130, 788, 0, 153, 28, 824, 544, 667, 565, 0, 352, 759, 554, 0, 935, 0, 160, 470, 695, 0, 184, 0, 169, 0, 867, 659, 271, 202, 0, 134, 124, 675, 514, 525, 786, 360, 0, 49, 331, 431, 781, 767, 994},
            std::vector<double>{446, 623, 199, 16, 312, 223, 402, 0, 0, 314, 0, 515, 953, 793, 274, 911, 0, 624, 809, 972, 744, 63, 739, 668, 793, 0, 815, 887, 464, 644, 785, 690, 256, 706, 470, 0, 635, 0, 570, 455, 70, 389, 73},
            std::vector<double>{508, 876, 618, 759, 911, 252, 137, 224, 426, 634, 837, 0, 665, 0, 478, 238, 403, 998, 183, 0, 896, 0, 481, 333, 899, 969, 526, 737, 388, 866, 439, 297, 226, 379, 734, 239, 819, 12, 751, 449, 286, 0, 89},
            std::vector<double>{791, 895, 174, 495, 340, 0, 32, 612, 0, 491, 556, 62, 0, 95, 543, 105, 600, 553, 716, 0, 573, 505, 882, 762, 2, 104, 715, 128, 739, 0, 878, 604, 503, 107, 623, 966, 177, 745, 0, 688, 734, 813, 635},
            std::vector<double>{822, 991, 32, 979, 510, 0, 452, 438, 839, 322, 155, 499, 27, 0, 140, 115, 130, 796, 163, 886, 874, 0, 370, 599, 17, 285, 23, 529, 0, 949, 660, 707, 201, 396, 321, 0, 488, 854, 475, 218, 227, 318, 581},
            std::vector<double>{931, 861, 281, 620, 368, 284, 286, 620, 639, 972, 482, 515, 426, 723, 0, 551, 346, 332, 556, 720, 932, 676, 330, 319, 438, 669, 151, 55, 232, 967, 349, 21, 576, 803, 595, 478, 542, 815, 950, 154, 179, 905, 977},
            std::vector<double>{0, 785, 0, 438, 656, 332, 511, 112, 592, 992, 991, 257, 905, 839, 196, 0, 903, 0, 139, 704, 447, 432, 291, 226, 691, 901, 800, 577, 137, 559, 224, 0, 374, 277, 665, 749, 495, 0, 675, 192, 5, 161, 102},
            std::vector<double>{342, 718, 152, 769, 836, 656, 0, 589, 953, 682, 508, 812, 494, 78, 0, 660, 0, 185, 886, 304, 0, 0, 739, 106, 174, 94, 689, 79, 755, 74, 669, 310, 691, 926, 0, 295, 935, 734, 962, 449, 214, 0, 596},
            std::vector<double>{322, 0, 891, 299, 32, 183, 86, 581, 0, 343, 729, 666, 0, 0, 207, 544, 200, 0, 695, 983, 336, 291, 0, 214, 613, 0, 637, 119, 869, 0, 648, 949, 978, 0, 853, 407, 430, 101, 0, 371, 579, 82, 976},
            std::vector<double>{0, 868, 28, 907, 770, 280, 0, 727, 333, 504, 971, 221, 976, 0, 321, 343, 427, 575, 0, 243, 352, 832, 4, 169, 381, 499, 0, 334, 316, 616, 343, 112, 573, 0, 295, 645, 199, 498, 671, 927, 0, 104, 171},
            std::vector<double>{129, 191, 764, 959, 725, 119, 593, 975, 795, 611, 0, 249, 0, 868, 0, 364, 371, 0, 762, 0, 654, 697, 47, 310, 791, 553, 411, 271, 472, 0, 667, 0, 505, 13, 994, 903, 540, 678, 355, 0, 591, 758, 280}
        }
    }
};

std::pair<vec_type, vec_type> vectors(void){
    std::pair<vec_type, vec_type> vec_pair;

    {
        // vec_pair.first = vec_type{
        //     std::vector<double>{0,	1,	2,	4,	5,	6,	4},
        //     std::vector<double>{1,	2,	3,	5,	6,	7,	3},
        //     std::vector<double>{4,	5,	6,	8,	9,	10,	4},
        //     std::vector<double>{5,	6,	7,	9,	10,	11,	2},
        //     std::vector<double>{8,	9,	10,	12,	13,	14,	1}
        // };

        // vec_pair.second = vec_type{
        //     std::vector<double>{0,	1,	2,	4,	5,	6,	1,	4,	5,	6},
        //     std::vector<double>{1,	2,	3,	5,	6,	7,	2,	5,	6,	7},
        //     std::vector<double>{2,	5,	6,	8,	9,	10,	5,	8,	9,	10},
        //     std::vector<double>{3,	6,	7,	9,	10,	11,	6,	9,	10,	11},
        //     std::vector<double>{4,	9,	10,	12,	13,	14,	9,	12,	13,	14},
        //     std::vector<double>{5,	0,	5,	76,	23,	56,	0,	76,	23,	56},
        //     std::vector<double>{6,	3,	4,	89,	99,	77,	3,	89,	99,	77}
        // };
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

s21::WinogradParallel::result_matrix_type::matrix_type check_usuall(s21::Matrix<double>& a, s21::Matrix<double>& b){
    s21::WinogradUsual alg;
    s21::WinogradParallel::result_matrix_type::matrix_type r;

    r = alg.WinogradMultiplication(a, b).matrix_array;

    // std::cout << "USUAL:" << std::endl
    //         << r << std::endl << std::endl;
    return r;
}

s21::WinogradParallel::result_matrix_type::matrix_type check_parallel(s21::Matrix<double>& a, s21::Matrix<double>& b){
    s21::WinogradParallel alg(PARALLEL_COUNT);
    s21::WinogradParallel::result_matrix_type::matrix_type r;

    r = alg.WinogradMultiplication(a, b).matrix_array;

    // std::cout << "PARALLEL:" << std::endl
    //         << r << std::endl << std::endl;
    return r;
}


void check_is_equal(
    s21::WinogradParallel::result_matrix_type::matrix_type a, 
    s21::WinogradParallel::result_matrix_type::matrix_type b){
    std::cout << "IS EQUAL? -> " << (a == b) << std::endl;
}

int main(){
    // s21::Matrix<double> a(tasks_array[0].first); s21::Matrix<double> b(tasks_array[0].second);
    // s21::Matrix<double> a(tasks_array[1].first); s21::Matrix<double> b(tasks_array[1].second);
    // s21::Matrix<double> a(tasks_array[2].first); s21::Matrix<double> b(tasks_array[2].second);
    // s21::Matrix<double> a(tasks_array[3].first); s21::Matrix<double> b(tasks_array[3].second);
    s21::Matrix<double> a(tasks_array[4].first); s21::Matrix<double> b(tasks_array[4].second);

    check_is_equal(check_usuall(a, b), check_parallel(a, b));
}
