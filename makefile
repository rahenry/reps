NAME = reps
CC = g++
CFLAGS = -std=c++0x -MMD -MP -O3
LDFLAGS = -DNDEBUG -msse2
FC = gfortran
FCFLAGS = -g -fbounds-check -O2 -I/usr/include
LIBS = -lgfortran -llapack -lblas -lgsl

SRC_DIR = src
OBJDIR_CPP = build/cpp
OBJDIR_F = build/f
SRCS_CPP := $(wildcard src/*.cpp) 
SRCS_F := $(wildcard src/*.f)
SRCS := $(SRCS_CPP) $(SRCS_F)
OBJS_CPP := $(SRCS_CPP:$(SRC_DIR)/%.cpp=$(OBJDIR_CPP)/%.o) 
OBJS_F :=$(SRCS_F:$(SRC_DIR)/%.f=$(OBJDIR_F)/%.o)
OBJS = $(OBJS_CPP) $(OBJS_F)

all: $(SRCS) $(NAME)
  
$(NAME): $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJDIR_CPP)/%.o: $(SRC_DIR)/%.cpp | $(OBJDIR_CPP)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_F)/%.o: $(SRC_DIR)/%.f | $(OBJDIR_F)
	$(FC) $(FCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR_CPP)/* $(OBJDIR_F)/* $(NAME)

$(OBJDIR_CPP):
	mkdir -p $(OBJDIR_CPP)

$(OBJDIR_F):
	mkdir -p $(OBJDIR_F)

-include $(SRCS_CPP:.cpp=.d)

# ....
