make -C libft/ fclean && make -C libft/
clang -Wall -Wextra -Werror -I libft/ -o get_next_line.o -c get_next_line.c
clang -Wall -Wextra -Werror -I libft/ -o main.o -c main.c
clang -o test_gnl main.o get_next_line.o -I libft/ -L libft/ -lft
./test_gnl