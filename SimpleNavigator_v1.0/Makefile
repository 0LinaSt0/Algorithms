MAIN_EXE	=	SimpleNavigator.out
TEST_EXE	=	test.out
GRAPH_LIB	=	graph.a
ALGO_LIB	=	graph_algorithms.a

CC			=	g++
GCC			=	$(CC) -std=c++17 -Wall -Wextra -Werror -lgtest -MMD -g \
					-fsanitize=leak -fsanitize=undefined -fsanitize=address

TEST_DIR	=	tests
TMP_DIR		=	tmp

### HEADERS ###
HDRS_CONT	=	$(addprefix containers/, 									\
					$(addprefix stack/,										\
						$(addprefix includes/,								\
							stack.hpp										\
						)													\
					)														\
					$(addprefix queue/,										\
						$(addprefix includes/,								\
							queue.hpp										\
						)													\
					)														\
				)
HDRS_CLI	=	$(addprefix cli/,											\
					$(addprefix includes/,									\
						cli.hpp	timer.hpp									\
					)														\
				)
HDRS_GRAPH	=	$(addprefix graph/,											\
					$(addprefix includes/,									\
						graph.hpp											\
					)														\
				)
HDRS_ALGO	=	$(addprefix graph/,											\
					$(addprefix includes/,									\
						graphAlgorithms.hpp									\
					)														\
				)
HDRS_UTILS	=	$(addprefix utils/,											\
					$(addprefix includes/,									\
						ant.hpp												\
						antAlgorithmUtils.hpp								\
						branchBoundMethodAlgorithmUtils.hpp					\
						pathNodeMatrix.hpp									\
						utils.hpp											\
					)														\
				)
HDRS		=	$(HDRS_CONT) $(HDRS_CLI) $(HDRS_GRAPH) 						\
					$(HDRS_ALGO) $(HDRS_UTILS)

### SOURCES ###
SRCS_UTILS	=	$(addprefix utils/,											\
					$(addprefix srcs/,										\
						ant.cpp												\
						antAlgorithmUtils.cpp								\
						branchBoundMethodAlgorithmUtils.cpp					\
						pathNodeMatrix.cpp									\
						utils.cpp											\
					)														\
				)															
SRCS_CLI	=	$(addprefix cli/,											\
					$(addprefix srcs/,										\
						cli.cpp	timer.cpp									\
					)														\
				)															
SRCS_GRAPH	=	$(addprefix graph/,											\
					$(addprefix srcs/,										\
						graph.cpp											\
					)														\
				)
SRCS_ALGO	=	$(addprefix graph/,											\
					$(addprefix srcs/,										\
						graphAlgorithms.cpp									\
					)														\
				)
SRCS_MAIN	=	./main.cpp										
SRCS		=	$(SRCS_UTILS) $(SRCS_CLI) $(SRCS_GRAPH) \
					$(SRCS_ALGO) $(SRCS_MAIN)

### OBJECTS ###
OBJS_UTILS	=	$(addprefix $(TMP_DIR)/, $(SRCS_UTILS:.cpp=.o))
OBJS_CLI	=	$(addprefix $(TMP_DIR)/, $(SRCS_CLI:.cpp=.o))
OBJS_GRAPH	=	$(addprefix $(TMP_DIR)/, $(SRCS_GRAPH:.cpp=.o))
OBJS_ALGO	=	$(addprefix $(TMP_DIR)/, $(SRCS_ALGO:.cpp=.o))
OBJS_MAIN	=	$(addprefix $(TMP_DIR)/, $(SRCS_MAIN:.cpp=.o))
OBJS		=	$(OBJS_UTILS) $(OBJS_CLI) $(OBJS_GRAPH) \
					$(OBJS_ALGO) 

### DEPENDENCIES ###
DPNDS		=	$(addprefix $(TMP_DIR)/, $(SRCS:.cpp=.d))

TEST_HDRS	=	$(addprefix $(TEST_DIR)/,									\
					$(addprefix containers/,								\
						$(addprefix stack/,									\
							$(addprefix includes/,							\
								stack.hpp									\
							)												\
						)													\
						$(addprefix queue/,									\
							$(addprefix includes/,							\
								queue.hpp									\
							)												\
						)													\
					)														\
					$(addprefix graph/,										\
						$(addprefix includes/,								\
							graph.hpp graphAlgorithms.hpp					\
						)													\
					)														\
				)
TEST_SRCS	=	$(addprefix $(TEST_DIR)/, main.cpp							\
					$(addprefix containers/,								\
						$(addprefix stack/,									\
							$(addprefix srcs/,								\
								stack.cpp									\
							)												\
						)													\
						$(addprefix queue/,									\
							$(addprefix srcs/,								\
								queue.cpp									\
							)												\
						)													\
					)														\
					$(addprefix graph/,										\
						$(addprefix srcs/,									\
							graph.cpp graphAlgorithms.cpp					\
						)													\
					)														\
				)
TEST_OBJS	=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS:.cpp=.o))
TEST_DPNDS	=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS:.cpp=.d))

# $@			$<
$(TMP_DIR)/%.o:	%.cpp $(TEST_HDRS) $(HDRS)
				@mkdir -p $(dir $@)
				$(GCC) -c -o $@ $<

all:			algo_lib $(OBJS_CLI) $(OBJS_MAIN)
				$(GCC) $(OBJS_MAIN) $(OBJS_CLI) $(ALGO_LIB) -o $(MAIN_EXE)
	
graph_lib:		$(OBJS_GRAPH) $(OBJS_UTILS)
				@ar sr $(GRAPH_LIB) $(OBJS_GRAPH) $(OBJS_UTILS)

algo_lib:		$(OBJS_GRAPH) $(OBJS_UTILS) $(OBJS_ALGO)
				@ar sr $(ALGO_LIB) $(OBJS_GRAPH) $(OBJS_UTILS) $(OBJS_ALGO)

test:			$(OBJS_UTILS) $(OBJS_CLI) $(OBJS_GRAPH) $(OBJS_ALGO) $(TEST_OBJS)
				$(GCC) $(OBJS_UTILS) $(OBJS_GRAPH) $(OBJS_CLI) \
					$(OBJS_ALGO) $(TEST_OBJS) -o $(TEST_EXE)

test1:			$(OBJS)
				$(GCC) main_DELETEME.cpp $(OBJS) -o $(TEST_EXE)

clean:			
				@rm -rf $(TMP_DIR)

fclean:			clean
				@rm -f $(MAIN_EXE)
				@rm -f $(TEST_EXE)
				@rm -f $(GRAPH_LIB)
				@rm -f $(ALGO_LIB)

re:				fclean all

.PHONY: graph_lib algo_lib test clean fclean re
