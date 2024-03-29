##############################
### ~~ Common variables ~~ ###
##############################

OS_NAME 			=	$(shell uname)

GTEST				=	true
GTEST_LIB			=	/usr/lib/libgtest.a /usr/lib/libgtest_main.a

ANT_EXE				=	ant.out
SLE_EXE				=	gauss.out
WIN_EXE				=	winograd.out
TEST_EXE			=	test.out

TEST_DIR			=	tests
TMP_DIR				=	tmp_handlers

CC					=	g++
ifeq ($(GTEST), true)
	GCC				=	$(CC) -std=c++17 -lgtest -Wall -Wextra -Werror -MMD -g	\
							-fsanitize=leak -fsanitize=undefined -fsanitize=address
else		
	GCC				=	$(CC) -std=c++17 -Wall -Wextra -Werror -MMD -g			\
							-fsanitize=leak -fsanitize=undefined -fsanitize=address
endif

###########################
### ~~ Project files ~~ ###
###########################

### HEADERS ###
PRJ_HDRS_ALGO		=	$(addprefix algorithms/,								\
							$(addprefix ACO/,									\
								$(addprefix includes/,							\
									aco_abs.h aco_single.h aco_multi.h			\
									ant.h edge.h								\
								)												\
							)													\
							$(addprefix SLE/,									\
								$(addprefix includes/,							\
									sle_gaussian.h								\
								)												\
							)													\
							$(addprefix Winograd/,								\
								$(addprefix includes/,							\
									winograd.h									\
								)												\
							)													\
						)
PRJ_HDRS_CLI		=	$(addprefix cli/,										\
							$(addprefix includes/,								\
								cli.h  cli_aco.h  cli_sle.h						\
									cli_winograd.h  timer.h						\
							)													\
						)
PRJ_HDRS_MTRX		=	$(addprefix matrix/,									\
							$(addprefix includes/,								\
								matrix.h s21_graph.h sle.h						\
							)													\
							$(addprefix srcs/,									\
								matrix.h s21_graph.h sle_impl.h					\
							)													\
						)
PRJ_HDRS_UTIL		=	$(addprefix utils/,										\
							$(addprefix includes/,								\
								exception.h utils.h								\
							)													\
						)
PRJ_HDRS			=	$(PRJ_HDRS_ALGO) $(PRJ_HDRS_CLI) $(PRJ_HDRS_MTRX)		\
							$(PRJ_HDRS_UTIL)

### SOURCES ###
PRJ_SRCS_ALGO_ACO	=	$(addprefix algorithms/,								\
							$(addprefix ACO/,									\
								$(addprefix srcs/,								\
									aco_abs.cc aco_single.cc aco_multi.cc		\
									ant.cc edge.cc								\
								)												\
							)													\
						)										
PRJ_SRCS_ALGO_SLE	=	$(addprefix algorithms/,								\
							$(addprefix SLE/,									\
								$(addprefix srcs/,								\
									sle_gaussian.cc								\
								)												\
							)													\
						)
PRJ_SRCS_ALGO_WIN	=	$(addprefix algorithms/,								\
							$(addprefix Winograd/,								\
								$(addprefix srcs/,								\
									winograd.cc									\
								)												\
							)													\
						)

PRJ_SRCS_CLI_ACO	=	$(addprefix cli/,										\
							$(addprefix srcs/,									\
								cli.cc cli_aco.cc timer.cc						\
							)													\
						)
PRJ_SRCS_CLI_SLE	=	$(addprefix cli/,										\
							$(addprefix srcs/,									\
								cli.cc cli_sle.cc timer.cc						\
							)													\
						)
PRJ_SRCS_CLI_WIN	=	$(addprefix cli/,										\
							$(addprefix srcs/,									\
								cli.cc cli_winograd.cc timer.cc					\
							)													\
						)

PRJ_SRCS_MTRX		=	$(addprefix matrix/,									\
							$(addprefix srcs/,									\
																				\
							)													\
						)
PRJ_SRCS_UTIL		=	$(addprefix utils/,										\
							$(addprefix srcs/,									\
								exception.cc utils.cc							\
							)													\
						)
PRJ_SRCS			=	$(PRJ_SRCS_ALGO) $(PRJ_SRCS_CLI) $(PRJ_SRCS_MTRX)		\
							$(PRJ_SRCS_UTIL)

### OBJECTS ###
PRJ_OBJS_ALGO_ACO	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_ALGO_ACO:.cc=.o))
PRJ_OBJS_ALGO_SLE	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_ALGO_SLE:.cc=.o))
PRJ_OBJS_ALGO_WIN	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_ALGO_WIN:.cc=.o))
PRJ_OBJS_CLI_ACO	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_CLI_ACO:.cc=.o))
PRJ_OBJS_CLI_SLE	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_CLI_SLE:.cc=.o))
PRJ_OBJS_CLI_WIN	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_CLI_WIN:.cc=.o))
PRJ_OBJS_MTRX		=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_MTRX:.cc=.o))
PRJ_OBJS_UTIL		=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_UTIL:.cc=.o))
PRJ_OBJS			=	$(PRJ_OBJS_ALGO_ACO) $(PRJ_OBJS_ALGO_SLE) $(PRJ_OBJS_ALGO_WIN) \
							$(PRJ_OBJS_CLI_ACO) $(PRJ_OBJS_CLI_SLE) $(PRJ_OBJS_CLI_WIN) \
							$(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL)

### DEPENDENCIES ###
DPNDS				=	$(PRJ_OBJS:.o=.d)


########################
### ~~ Test files ~~ ###
########################

### HEADERS ###
TEST_HDRS_MTRX		=	$(addprefix $(TEST_DIR)/,								\
							$(addprefix matrix/,								\
								$(addprefix includes/,							\
									matrix.h graph.h sle.h						\
								)												\
							)													\
						)
TEST_HDRS_WIN		=	$(addprefix $(TEST_DIR)/,								\
							$(addprefix algorithms/,							\
								$(addprefix includes/,							\
									winograd.h									\
								)												\
							)													\
						)
TEST_HDRS_UTILS		=	$(addprefix $(TEST_DIR)/,								\
							$(addprefix test_utils/,							\
								$(addprefix includes/,							\
									assert.h									\
								)												\
							)													\
						)
TEST_HDRS			=	$(TEST_HDRS_MTRX) $(TEST_HDRS_WIN) $(TEST_HDRS_UTILS)

### SOURCES ###	
TEST_SRCS_MTRX		=	$(addprefix $(TEST_DIR)/,								\
							$(addprefix matrix/,								\
								$(addprefix srcs/,								\
									matrix.cc graph.cc sle.cc					\
								)												\
							)													\
						)
TEST_SRCS_WIN		=	$(addprefix $(TEST_DIR)/,								\
							$(addprefix algorithms/,							\
								$(addprefix srcs/,								\
									winograd.cc									\
								)												\
							)													\
						)
TEST_SRCS_UTILS		=	$(addprefix $(TEST_DIR)/,								\
							$(addprefix test_utils/,							\
								$(addprefix srcs/,								\
									assert.cc									\
								)												\
							)													\
						)					
TEST_SRCS_MAIN		=	$(addprefix $(TEST_DIR)/, 								\
							main.cc												\
						)
TEST_SRCS			=	$(TEST_SRCS_MTRX) $(TEST_SRCS_WIN) $(TEST_SRCS_UTILS) $(TEST_SRCS_MAIN)

### OBJECTS ###	
TEST_OBJS_MTRX		=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS_MTRX:.cc=.o))
TEST_OBJS_WIN		=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS_WIN:.cc=.o))
TEST_OBJS_UTILS		=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS_UTILS:.cc=.o))
TEST_OBJS_MAIN		=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS_MAIN:.cc=.o))
TEST_OBJS			=	$(TEST_OBJS_MTRX) $(TEST_OBJS_WIN) $(TEST_OBJS_MAIN) $(TEST_OBJS_UTILS)

### DEPENDENCIES ###
TEST_DPNDS			=	$(TEST_OBJS:.o=.d)


###################
### ~~ Rules ~~ ###
###################

# $@						$<
$(TMP_DIR)/%.o:				%.cc $(TEST_HDRS) $(HDRS)
							@mkdir -p $(dir $@)
							$(GCC) -c -o $@ $<

all:						ant gauss winograd
							
ant:						$(PRJ_OBJS_ALGO_ACO) $(PRJ_OBJS_CLI_ACO) $(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL)
							$(GCC) $(PRJ_OBJS_ALGO_ACO) $(PRJ_OBJS_CLI_ACO) \
								$(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL) \
								-o $(ANT_EXE)

gauss:						$(PRJ_OBJS_ALGO_SLE) $(PRJ_OBJS_CLI_SLE) $(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL)
							$(GCC) $(PRJ_OBJS_ALGO_SLE) $(PRJ_OBJS_CLI_SLE) \
								$(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL) \
								-o $(SLE_EXE)

winograd:					$(PRJ_OBJS_ALGO_WIN) $(PRJ_OBJS_CLI_WIN) $(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL)
							$(GCC) $(PRJ_OBJS_ALGO_WIN) $(PRJ_OBJS_CLI_WIN) \
								$(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL) \
								-o $(WIN_EXE)

test:						$(PRJ_SRCS_ALGO_WIN) $(PRJ_OBJS_CLI) $(PRJ_OBJS_MTRX) \
								$(PRJ_OBJS_UTIL) $(TEST_OBJS)
							if [ $(OS_NAME) = "Linux" ]; then \
								$(GCC) $(PRJ_SRCS_ALGO_WIN) $(PRJ_OBJS_CLI) \
									$(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL) $(TEST_OBJS) \
									$(GTEST_LIB) \
									-o $(TEST_EXE); \
							else \
								$(GCC) $(PRJ_SRCS_ALGO_WIN) $(PRJ_OBJS_CLI) \
									$(PRJ_OBJS_MTRX) $(PRJ_OBJS_UTIL) $(TEST_OBJS) \
									-o $(TEST_EXE); \
							fi
							./$(TEST_EXE) 2> /dev/null

check-style:
							@clang-format -style=Google -Werror --dry-run *.h *.cc

set-style:
							@find . -name "*.h" -or -name "*.cc" -type f | xargs clang-format -i -style=Google

clean:						
							@rm -rf $(TMP_DIR)

fclean:						clean
							@rm -f $(ANT_EXE)
							@rm -f $(SLE_EXE)
							@rm -f $(WIN_EXE)
							@rm -f $(TEST_EXE)

re:							fclean all

-include $(DPNDS) $(TEST_DPNDS)

.PHONY: ant gauss winograd test clean check-style set-style fclean re
