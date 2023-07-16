##############################
### ~~ Common variables ~~ ###
##############################

MAIN_EXE	=	Parallels.out
TEST_EXE	=	test.out

TEST_DIR	=	tests
TMP_DIR		=	tmp_handlers

CC			=	g++
GCC			=	$(CC) -std=c++17 -Wall -Wextra -Werror -lgtest -MMD -g		\
					-fsanitize=leak -fsanitize=undefined -fsanitize=address

###########################
### ~~ Project files ~~ ###
###########################

### HEADERS ###
PRJ_HDRS_ALGO	=	$(addprefix algorithms/,								\
						$(addprefix ACO/,									\
							$(addprefix includes/,							\
								aco.h										\
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
PRJ_HDRS_CLI	=	$(addprefix cli/,										\
						$(addprefix includes/,								\
							cli.h  cli_aco.h  cli_sle.h						\
								cli_winograd.h  timer.h						\
						)													\
					)
PRJ_HDRS_MTRX	=	$(addprefix matrix/,									\
						$(addprefix includes/,								\
							matrix.h s21_graph.h							\
						)													\
					)
PRJ_HDRS_UTIL	=	$(addprefix utils/,										\
						$(addprefix includes/,								\
							exception.h utils.h								\
						)													\
					)
PRJ_HDRS		=	$(PRJ_HDRS_ALGO) $(PRJ_HDRS_CLI) $(PRJ_HDRS_MTRX)		\
						$(PRJ_HDRS_UTIL)

### SOURCES ###
PRJ_SRCS_ALGO	=	$(addprefix algorithms/,								\
						$(addprefix ACO/,									\
							$(addprefix srcs/,								\
								aco.cc										\
							)												\
						)													\
						$(addprefix SLE/,									\
							$(addprefix srcs/,								\
								sle_gaussian.cc								\
							)												\
						)													\
						$(addprefix Winograd/,								\
							$(addprefix srcs/,								\
								winograd.cc									\
							)												\
						)													\
					)
PRJ_SRCS_CLI	=	$(addprefix cli/,										\
						$(addprefix srcs/,									\
							cli.cc cli_aco.cc cli_sle.cc					\
								cli_winograd.cc timer.cc					\
						)													\
					)
PRJ_SRCS_MTRX	=	
PRJ_SRCS_UTIL	=	$(addprefix utils/,										\
						$(addprefix srcs/,									\
							exception.cc utils.cc							\
						)													\
					)
PRJ_SRCS_MAIN	=	main.cc
PRJ_SRCS		=	$(PRJ_SRCS_ALGO) $(PRJ_SRCS_CLI) $(PRJ_SRCS_MTRX)		\
						$(PRJ_SRCS_UTIL) $(PRJ_SRCS_MAIN)

### OBJECTS ###
PRJ_OBJS_ALGO	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_ALGO:.cc=.o))
PRJ_OBJS_CLI	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_CLI:.cc=.o))
PRJ_OBJS_MTRX	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_MTRX:.cc=.o))
PRJ_OBJS_UTIL	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_UTIL:.cc=.o))
PRJ_OBJS_MAIN	=	$(addprefix $(TMP_DIR)/, $(PRJ_SRCS_MAIN:.cc=.o))
PRJ_OBJS		=	$(PRJ_OBJS_ALGO) $(PRJ_OBJS_CLI) $(PRJ_OBJS_MTRX)		\
						$(PRJ_OBJS_UTIL) $(PRJ_OBJS_MAIN)

### DEPENDENCIES ###
DPNDS		=	$(PRJ_OBJS:.o=.d)


########################
### ~~ Test files ~~ ###
########################

### HEADERS ###
TEST_HDRS_GRAPH	=	$(addprefix $(TEST_DIR)/,								\
						$(addprefix graph/,									\
							$(addprefix includes/,							\
								graph.h										\
							)												\
						)													\
					)
TEST_HDRS		=	$(TEST_HDRS_GRAPH)

### SOURCES ###
TEST_SRCS_GRAPH	=	$(addprefix $(TEST_DIR)/,								\
						$(addprefix graph/,									\
							$(addprefix srcs/,								\
								graph.cc									\
							)												\
						)													\
					)
TEST_SRCS_MAIN	=	$(addprefix $(TEST_DIR)/, 								\
						main.cc												\
					)
TEST_SRCS		=	$(TEST_SRCS_GRAPH) $(TEST_SRCS_MAIN)

### OBJECTS ###
TEST_OBJS_GRAPH	=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS_GRAPH:.cc=.o))
TEST_OBJS_MAIN	=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS_MAIN:.cc=.o))
TEST_OBJS		=	$(TEST_OBJS_GRAPH) $(TEST_OBJS_MAIN)

### DEPENDENCIES ###
TEST_DPNDS		=	$(TEST_OBJS:.o=.d)


###################
### ~~ Rules ~~ ###
###################

# $@						$<
$(TMP_DIR)/%.o:				%.cc $(TEST_HDRS) $(HDRS)
							@mkdir -p $(dir $@)
							$(GCC) -c -o $@ $<

all:						$(PRJ_OBJS)
							$(GCC) $(PRJ_OBJS) -o $(MAIN_EXE)

test:						$(PRJ_OBJS) $(TEST_OBJS)
							$(GCC) $(PRJ_OBJS) $(TEST_OBJS) -o $(TEST_EXE)

clean:						
							@rm -rf $(TMP_DIR)

fclean:						clean
							@rm -f $(MAIN_EXE)
							@rm -f $(TEST_EXE)

re:							fclean all

-include $(DPNDS) $(TEST_DPNDS)

.PHONY: test clean fclean re
