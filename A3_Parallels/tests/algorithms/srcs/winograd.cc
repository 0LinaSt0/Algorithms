#include "../includes/winograd.h"

namespace s21::test::winograd{

TEST(TEST_SUITE_NAME_WIN, TEST_MULTIPLICATION){
    std::vector<MultiplicatorInfo> info{
        { 
            WINOGRAD_MTRX_DIR + "00.0", 
            WINOGRAD_MTRX_DIR + "00.1", 
            "",
            false
        },
        { 
            WINOGRAD_MTRX_DIR + "01.0", 
            WINOGRAD_MTRX_DIR + "01.1", 
            "1 6 101 116 131 161 176 191",
            true
        },
        { 
            WINOGRAD_MTRX_DIR + "02.0", 
            WINOGRAD_MTRX_DIR + "02.1", 
            "",
            true
        },
        { 
            WINOGRAD_MTRX_DIR + "03.0", 
            WINOGRAD_MTRX_DIR + "03.1", 
            "5 10 91 93 139 929 663 785 93 929 663 785 100 113 168 954 630 812 113 954 630 812 151 185 271 1385 927 1201 185 1385 927 1201 154 202 296 1321 795 1151 202 1321 795 1151 193 268 391 1574 894 1386 268 1574 894 1386",
            true
        },
        { 
            WINOGRAD_MTRX_DIR + "04.0", 
            WINOGRAD_MTRX_DIR + "04.1",
            "19 43 "
            "2802318 3497434 2252446 2865395 3091309 2101967 1181610 3040278 3331075 1858104 2946360 3713070 2849082 1841345 2477435 2412532 2112224 2749487 2740556 2450225 2802396 2325981 2393115 1246245 2591177 3061734 2210046 2513432 2075309 3223426 2264543 2770090 2972343 3091224 2240006 2525304 2317672 2451918 3011672 3565170 2311475 3092296 3134777 " 
            "4808477 5089187 3879312 5724614 3879730 3265412 3034188 4560733 4771547 3968051 3342941 3623347 3658817 3911303 3519226 3682672 3452936 2717826 4384482 3908890 5566206 3221146 3499805 3255542 3886766 4141098 2877728 2828940 2797632 5269709 3721618 3797084 4736508 4010511 4407549 3530551 3490906 4169265 4375661 4135602 3504626 4614728 4888383 "
            "3268400 3643508 2838201 3902523 2731101 2163307 2135683 3921157 3106508 3171009 3035993 3187925 2036321 2728211 2201374 1876785 3065982 2132549 3486023 3246272 4263982 2901104 2067037 2420592 3806815 3758239 3406849 1911526 2538043 3042782 3223652 3164997 3815064 2363956 4468714 3547356 2979847 3269576 2758302 2504481 3367942 3754781 4530298 "
            "3129925 3380354 3387704 4001130 2274860 2466769 1857993 3812339 3416295 3232754 2366919 3457199 2517593 2873733 1479530 3892775 2942585 2142426 4144862 4238712 3638864 2382837 2900164 2278125 3070525 3068543 3049688 2260459 3132951 3207076 3054319 3360851 3773849 3396299 4137866 3080827 3696391 2924917 2927567 2290091 3289692 3743557 3789799 "
            "4321212 5293300 3199121 4635632 3876682 3146502 1745439 4507112 4302724 3473218 4455718 4913138 4039319 2964261 2018489 4157263 3804856 3797022 3595221 4500724 3666323 3387229 4124887 2473548 4127431 4527525 4149817 2744295 4303897 4524949 3552644 3833132 3983289 4174663 4637831 3764436 3867627 3888637 4101802 3518729 3138637 4048743 4579086 "
            "3791863 6009673 2886499 5333664 4529936 2754789 2217445 4633983 3770195 4675755 4450160 3958908 4339284 3387155 2240500 3452514 3925745 4429580 3687689 4488332 5098390 3428084 4100605 3358448 5105135 4630837 4918627 3602735 4266670 4879163 4620083 4120845 3970632 3409562 5400833 4110761 4658869 3792677 4190214 3428432 3052123 3815421 4138491 "
            "3572883 3443746 3160220 3922206 2777562 1863177 1822783 3079066 3747508 2606133 2803805 3555573 1877399 2394033 1421654 2508613 3166706 2545330 2764016 3652061 4137046 2637881 2373189 2311792 3332229 3813101 3066559 2040803 2462484 3473685 3217713 3032370 3367531 2332346 3881477 2602771 3189591 3464490 3343701 2176237 2535114 3047308 3655563 "
            "2344472 4064196 2249628 3559905 2828807 2698954 1502935 3506207 2691532 3053866 3005182 3378944 3626133 1996720 2319920 3070124 2211165 3219849 3172157 3360031 3472759 2055258 2776544 1959912 3768221 2958972 2883751 2641626 2861040 3725015 2936823 3527776 3441943 3012856 3388695 2417054 3301837 2214604 3176589 3083895 2362043 2744280 3430354 "
            "3488488 4302947 3854673 4720426 4430004 2099063 2148139 3767221 3677549 3618825 2824873 3834444 3154250 3848567 2714259 3124491 3399392 3974437 3205680 3569508 6148168 3385898 3653466 3239786 4402334 3943293 3688439 3775240 2793724 5044340 4374349 4089697 4107068 2568571 3960131 2970063 4068082 3874376 3880816 3443309 2367993 4052316 3052073 "
            "4072197 3771688 3506267 3724374 2981531 2410851 2112732 3029511 3393596 2455706 2804359 3601073 2760831 3164431 2601001 3140815 3038057 2531701 3313936 3726334 4550170 2373325 3272942 2770605 3108656 3423683 3043987 2574279 2259111 4088683 3006595 3594760 3803006 3265387 3687236 2457674 2933483 3242662 3223566 2963399 2741567 3826472 3606267 "
            "5219455 5549358 4087009 5534248 4778032 2903530 2215202 4895094 4529593 3901085 4234629 4849539 3626353 3819148 2903313 3695987 4193781 4633251 3177088 4460150 5824603 3831409 4565450 3317778 4439238 5135789 3897972 3485465 3784935 6248683 3935883 4506245 4336294 4019386 4781459 3719492 4109136 4758188 4082200 3790933 3258027 5028783 4781406 "
            "2932826 3875049 2604812 4499235 3447044 3007468 2405261 4200120 3080023 3196157 2678050 3309621 3871872 3468051 2703970 3120047 3383800 3076648 3476431 3469373 4373888 3162007 3313401 3075589 4523684 3905055 3403999 2753161 3190204 4459135 3225338 3364765 3687808 2945895 3894463 3613701 3279317 3301467 3146259 3501984 3059652 3748098 3545399 "
            "4586725 4975064 2700512 5119359 3763381 2856706 2446429 4125596 4241956 3725894 3612739 3959915 4127135 3058565 2378380 4085094 3321675 3544617 4008515 4807309 4512724 3079422 3866996 3336597 3993189 3933052 3150480 2836032 3788979 5388126 3734274 3415615 3901329 4012188 3800069 3650573 3703451 3982851 4369573 4042710 2935093 3531977 4427271 "
            "4783849 6466861 3460060 5967161 5113051 4277319 2820195 5564061 4601131 4911972 5557814 5080631 5771678 3637451 3837582 4227030 4613384 4925636 4837661 5138299 5947082 3824938 4705706 3804613 6089089 6096938 4607188 3726969 4340641 6576031 4023359 4453042 5449516 4940179 5586495 5074806 4857377 4374188 5232599 4929748 4182394 4890592 5722740 "
            "3607888 5991550 3402903 5255568 4927649 2848570 1847166 4680123 4139028 3880833 3908528 4334554 3673012 2844043 3255657 3374268 3037920 4495967 3830105 3112411 4955883 2733999 4621516 2952324 3839874 3413475 4218286 3736509 3705069 4232769 4780638 4934239 4414684 3438142 4339950 3271697 4218447 4015240 3854855 3979338 2948816 4110468 3767968 "
            "4417819 4867114 5018915 6050117 4772033 3589433 2044081 6212715 4295633 4490948 4083629 5080823 3448753 4200190 3267060 3762752 4372983 3910877 4417145 4495121 6453176 4440809 3753473 3055981 4877600 5463823 4416757 3427658 3716066 5619526 3989248 5025088 5761693 4314008 5344814 4495111 5048367 4982380 3872113 4090503 4597531 5953945 5749746 "
            "3717726 4681525 3080924 3757868 3717581 1762289 1499209 3442379 3201098 3573459 4120064 3123305 3299839 3175879 2970949 2532572 3660254 3183897 2879056 3306153 4633598 3444742 3103224 2223707 2852526 3993744 3019519 3422577 2380858 4464515 2926472 3182955 3572889 3112114 3565934 3794829 2921418 2812172 3196785 3987746 2726357 4287752 3350474 "
            "4484087 6158470 4137326 5587566 4804858 3803752 2645164 5056878 4652733 5090411 4816536 4918244 5013758 4718429 3808402 4300703 4989449 4216736 4484810 4714942 6255725 4234376 5090011 3589314 5095274 5313044 4659002 3880669 3912017 6070715 4371937 4771941 5532462 4338696 5265817 4639518 4559334 4382970 4891307 4593551 3532683 5538534 4838589 "
            "5270661 5704798 4361717 5048945 5118666 2807952 2640690 4763784 4279978 4275621 4508569 4499353 3465296 4464360 4357977 2640597 3986096 4029506 3836190 3821046 6326645 3570259 4447914 3247182 4653226 4910081 4667558 4221069 3425097 5794115 4256196 5091583 4606409 4135834 4939260 4082361 3928734 3905198 3587286 4542721 3878558 5463505 5209086 ",
            true
        }
    };

    auto str_to_mtrx = [](const std::string& str){
        int rows, columns;
        std::stringstream stream(str);
        std::vector<std::vector<double>> new_mtrx;
        
        stream >> rows;
        stream >> columns;
        new_mtrx.reserve(rows);

        for (int row = 0; row < rows; row++){
            std::vector<double> new_row;
            new_row.reserve(columns);
            for (int col = 0; col < columns; col++){
                double val;
                stream >> val;
                new_row.push_back(val);
            }
            new_mtrx.push_back(std::move(new_row));
        }

        return ::s21::Matrix<double>(new_mtrx);
    };

    for (const MultiplicatorInfo& mi : info){
        ::s21::WinogradUsual usual;
        ::s21::WinogradParallel parallel;
        ::s21::WinograPipelineParallel pipeline;

        ::s21::MatrixResult<double> usual_res;
        ::s21::MatrixResult<double> parallel_res;
        ::s21::MatrixResult<double> pipeline_res;

        try {            
            ::s21::Matrix<double> A = ::s21::Matrix<double>::LoadFromFile(mi.A);
            ::s21::Matrix<double> B = ::s21::Matrix<double>::LoadFromFile(mi.B);

            usual_res = usual.WinogradMultiplication(A, B);
            parallel_res = parallel.WinogradMultiplication(A, B);
            pipeline_res = pipeline.WinogradMultiplication(A, B);
            
            ASSERT_TRUE(usual_res.matrix_array == parallel_res.matrix_array);
            ASSERT_TRUE(usual_res.matrix_array == pipeline_res.matrix_array);
            ASSERT_TRUE(parallel_res.matrix_array == pipeline_res.matrix_array);
            if (!usual_res.matrix_array.size()) {
                ASSERT_FALSE(mi.C.size());
                continue;
            }

            ::s21::Matrix<double> res_mtrx_1 = str_to_mtrx(mi.C);
            ::s21::Matrix<double> res_mtrx_2(usual_res.matrix_array);

            ASSERT_EQ(res_mtrx_1.RowsSize(), res_mtrx_2.RowsSize());
            ASSERT_EQ(res_mtrx_1.ColumnsSize(), res_mtrx_2.ColumnsSize());
            for (size_t i = 0; i < res_mtrx_1.RowsSize(); i++){
            for (size_t j = 0; j < res_mtrx_1.ColumnsSize(); j++){
                ASSERT_TRUE(::s21::DoubleCompare(
                    res_mtrx_1[i][j], 
                    res_mtrx_2[i][j])
                );
            }
            }
        } catch (std::exception&) {
            ASSERT_FALSE(mi.mtrx_valid);
        }
    }
}

}