PROJ_NAME = employee
TEST_PROJ_NAME = Test_$(PROJ_NAME)

BUILD_DIR = Build
# All source code files
SRC = src\add.c\
src\delete.c\
src\modify.c\
src\list.c

# All test source files
TEST_SRC = test\test.c\
unity\unity.c

INC = -Iinc\
-Iunity
#Library Inlcudes
#if working with math.h 
#INCLUDE_LIBS = -lm
#To check if the OS is Windows or Linux and set the executable file extension and delete command accordingly
ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif

# Makefile will not run target command if the name with file already exists. To override, use .PHONY
.PHONY : all test coverage run clean 

all:$(BUILD_DIR)
	gcc test\test.c $(SRC) $(INC) -lm 

# Call `make run` to run the application
run: $(BUILD_DIR)
	$(call FixPath,$(BUILD_DIR)/$(PROJ_NAME).$(EXEC))

#Coverage	
coverage:$(BUILD_DIR)
	gcc $(TEST_SRC) $(SRC) $(INC) -fprofile-arcs -ftest-coverage -lm -o $(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
	$(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
   #perform gcov -a *.gcno to check coverage

# Remove all the built files, invoke by `make clean`
clean:
	$(RM) $(call FixPath,$(BUILD_DIR)/*)
	$(RM) *.gcda *.gcov *gcno  

#cppcheck static code analysis	
cppcheck:
	cppcheck --enable=all --check-config --suppress=missingIncludeSystem main.c $(SRC) -Iinc 
	
valgrind:
	gcc $(TEST_SRC) $(SRC) $(INC) -lm -o $(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
	valgrind $(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
 
# Build and run the unit tests	
test:$(BUILD_DIR)
	gcc $(TEST_SRC) $(SRC) $(INC) -lm -o $(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
		$(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
doc:
	make -C document	

$(BUILD_DIR):
	mkdir $(BUILD_DIR)