TEST_EXE	=	test.out

CC			=	g++
GCC			=	$(CC) -std=c++17 -Wall -Wextra -Werror -lgtest -MMD -g \
					-fsanitize=leak -fsanitize=undefined -fsanitize=address

TEST_DIR	=	tests
TMP_DIR		=	tmp

HDRS		=	$(addprefix containers/, 			\
					$(addprefix stack/,				\
						$(addprefix includes/,		\
							stack.hpp				\
						)							\
					)								\
				)
SRCS		=
OBJS		=	$(addprefix $(TMP_DIR)/, $(SRCS:.cpp=.o))
DPNDS		=	$(addprefix $(TMP_DIR)/, $(SRCS:.cpp=.d))

TEST_HDRS	=	$(addprefix $(TEST_DIR)/,			\
					$(addprefix containers/,		\
						$(addprefix stack/,			\
							$(addprefix includes/,	\
								stack.hpp			\
							)						\
						)							\
					)								\
				)
TEST_SRCS	=	$(addprefix $(TEST_DIR)/, main.cpp	\
					$(addprefix containers/,		\
						$(addprefix stack/,			\
							$(addprefix srcs/,		\
								stack.cpp			\
							)						\
						)							\
					)								\
				)
TEST_OBJS	=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS:.cpp=.o))
TEST_DPNDS	=	$(addprefix $(TMP_DIR)/, $(TEST_SRCS:.cpp=.d))

all:

# $@			$<
$(TMP_DIR)/%.o:	%.cpp $(TEST_HDRS) $(HDRS)
				@mkdir -p $(dir $@)
				$(GCC) -c -o $@ $<

test:			$(OBJS) $(TEST_OBJS)
				$(GCC) $(OBJS) $(TEST_OBJS) -o $(TEST_EXE)

clean:			
				@rm -rf $(TMP_DIR)

fclean:			clean
				@rm -f $(TEST_EXE)

.PHONY: test clean fclean
