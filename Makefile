# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 13:45:26 by nali              #+#    #+#              #
#    Updated: 2023/04/06 23:50:25 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CONTAINERS	=	./containers/

SRC_DIR		=	tests
OBJ_DIR		=	output

CXX			=	c++
CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 
RM			=	rm -rf


# --------------------STACK--------------------
STK_TEST	=  capacity.cpp constructors.cpp push_pop.cpp relational.cpp 
STD_STK_OUT =  output/std_stack/
FT_STK_OUT  =  output/ft_stack/
STK_SRCS	=  tests/stack

STD_STK_OBJ	=	$(addprefix $(STD_STK_OUT), $(STK_TEST:%cpp=%o))
FT_STK_OBJ	=	$(addprefix $(FT_STK_OUT), $(STK_TEST:%cpp=%o))

$(STD_STK_OUT)%.o : $(STK_SRCS)/%.cpp
			@mkdir -p output && mkdir -p output/std_stack
			@$(CXX) $(CPPFLAGS) -D NAMESPACE=std -I$(CONTAINERS)  -c $< -o $@

$(FT_STK_OUT)%.o : $(STK_SRCS)/%.cpp
			@mkdir -p output && mkdir -p output/ft_stack
			@$(CXX) $(CPPFLAGS) -D NAMESPACE=ft -I$(CONTAINERS)  -c $< -o $@
			

# --------------------VECTOR--------------------
VEC_TEST	=  assign.cpp capacity.cpp constructors.cpp element_access.cpp \
			erase.cpp insert.cpp invalidation.cpp iterators.cpp push_pop.cpp \
			relational.cpp swap.cpp
			
STD_VEC_OUT =  output/std_vector/
FT_VEC_OUT  =  output/ft_vector/
VEC_SRCS	=  tests/vector

STD_VEC_OBJ	=	$(addprefix $(STD_VEC_OUT), $(VEC_TEST:%cpp=%o))
FT_VEC_OBJ	=	$(addprefix $(FT_VEC_OUT), $(VEC_TEST:%cpp=%o))

$(STD_VEC_OUT)%.o : $(VEC_SRCS)/%.cpp
			@mkdir -p output && mkdir -p output/std_vector
			@$(CXX) $(CPPFLAGS) -D NAMESPACE=std -I$(CONTAINERS)  -c $< -o $@

$(FT_VEC_OUT)%.o : $(VEC_SRCS)/%.cpp
			@mkdir -p output && mkdir -p output/ft_vector
			@$(CXX) $(CPPFLAGS) -D NAMESPACE=ft -I$(CONTAINERS)  -c $< -o $@
			

# --------------------MAP--------------------
MAP_TEST	=  capacity.cpp constructors.cpp element_access.cpp erase.cpp \
			insert.cpp iterators.cpp lookup.cpp pair.cpp relational.cpp swap.cpp
STD_MAP_OUT =  output/std_map/
FT_MAP_OUT  =  output/ft_map/
MAP_SRCS	=  tests/map

STD_MAP_OBJ	=	$(addprefix $(STD_MAP_OUT), $(MAP_TEST:%cpp=%o))
FT_MAP_OBJ	=	$(addprefix $(FT_MAP_OUT), $(MAP_TEST:%cpp=%o))

$(STD_MAP_OUT)%.o : $(MAP_SRCS)/%.cpp
			@mkdir -p output && mkdir -p output/std_map
			@$(CXX) $(CPPFLAGS) -D NAMESPACE=std -I$(CONTAINERS)  -c $< -o $@

$(FT_MAP_OUT)%.o : $(MAP_SRCS)/%.cpp
			@mkdir -p output && mkdir -p output/ft_map
			@$(CXX) $(CPPFLAGS) -D NAMESPACE=ft -I$(CONTAINERS)  -c $< -o $@
			

# --------------------RULES--------------------

stack:		$(STD_STK_OBJ) $(FT_STK_OBJ)

vector:		$(STD_VEC_OBJ) $(FT_VEC_OBJ)

map:		$(STD_MAP_OBJ) $(FT_MAP_OBJ)

clean:
			@$(RM) $(OBJ_DIR) *.log

fclean:		clean

.PHONY:		vector map stack clean
