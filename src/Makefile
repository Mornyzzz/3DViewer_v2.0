CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wswitch -Wunused -std=c++17
TFLAGS = $(shell pkg-config --libs gtest)
QMAKE = qmake

SOURCE_DEC = tests/test.cc model/obj.cc
TARGET := 3DViewer

ifeq ($(shell uname), Linux)
	QMAKE = qmake6
	TST_LIBS := -lgtest -lm
    LSTDC := -lstdc++ --coverage
    OPEN_CMD := xdg-open
endif

all: clean install valgrind_check gcov_report

tests: clean
	@echo "┏=========================================┓"
	@echo "┃                 Tests                   ┃"
	@echo "┗=========================================┛"
	@$(CC) $(CFLAGS) $(SOURCE_DEC) $(TFLAGS) -o test $(TST_LIBS) $(LSTDC) \
	-lcheck $(shell pkg-config --cflags --libs check) \
	$(TST_LIBS) --coverage
	@./test

valgrind_check: tests
	@CK_FORK=no valgrind --leak-check=full \
	--show-leak-kinds=all --track-origins=yes -s ./test
	@echo "┏=========================================┓"
	@echo "┃        Valgrind check is over           ┃"
	@echo "┗=========================================┛"

install:
	@echo "Start installation"
	@mkdir -p ../build
	@cd view && $(QMAKE) && make && make clean && rm Makefile && mv 3DViewer ../../build/$(TARGET).exe
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃              build folder.              ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ../build
	@echo "Uninstall completed successfully"

dvi:
	@open ../README_RUS.md

dist: install
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).exe ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "The build was successfully archived"

clean:
	@echo "Deleting unnecessary files..."
	@rm -rf test *.gcov *.css gcov*.html view/Makefile view/ui_mainwindow.h
	@rm -rf *.o *.a *.out view/*.o view/*.a
	@rm -rf *.gcda *.gcno *.info *.gch **/.qmake.stash
	@rm -rf unit-test
	@rm -rf view/*.o view/Makefile view/moc_predefs.h view/moc_mainwindow.cpp view/moc_myopenglwidget.cpp view/ui_mainwindow.h
	@rm -rf build

gcov_report: tests
	@echo "┏=========================================┓"
	@echo "┃               HTML Report               ┃"
	@echo "┗=========================================┛"
	@lcov --no-external -t "test" -o test.info -c -d .
	@genhtml -o report test.info

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n **/*.h **/*.cc **/**/*.h **/**/*.cc
	@rm ./.clang-format

style_fix:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i **/*.h **/*.cc **/**/*.h **/**/*.cc
	@rm ./.clang-format

.PHONY: all install uninstall dvi dist test gcov_report valgrind_check style_check format_style fonts clean fclean

