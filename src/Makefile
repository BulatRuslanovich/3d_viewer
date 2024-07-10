.PHONY : all install clean rebuild run style tests dvi

CXX := g++
CXX_FLAGS= -Wall -Wextra -Werror -std=c++17
GTEST_FLAGS= -lgtest_main -lgtest
GCOV=--coverage

OS := $(shell uname -s)
OPEN = open
MAKE = echo ".PHONY: all dvi \nall: dvi run\nrun:\n\tcd build && ./3dViewer\ndvi:\n\t:xopen dvi/dvi.html" >> 3dViewer/Makefile
ifeq ($(OS), Linux)
	OPEN = xdg-open
	MAKE = echo -e ".PHONY: all dvi \nall: dvi run\nrun:\n\tcd build && ./3dViewer\ndvi:\n\txdg-open dvi/dvi.html" >> 3dViewer/Makefile
endif

SRC_DIR := .
EXTENSIONS := cc cpp h
# Функция для обнаружения файлов с заданными расширениями в директории и ее поддиректориях
find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))

TEST_SRC := tests/unit_tests.cpp

all: install tests dvi run

install: uninstall clean
	mkdir ../build
	cd ../build && cmake .. && make 3dViewer
rebuild:
	cd ../build && make 3dViewer && ./3dViewer
run:
	cd ../build && ./3dViewer
dvi:
	cd ../dvi && $(OPEN) dvi.html
uninstall:
	rm -rf ../build
clean:
	clear
	rm -rf test
	rm -rf *.gcda *.gcno *.info report *.gcov coverage_report ../3dViewer.tgz ../3dViewer
	make style
style:
	clang-format -style=Google -n $(SRC_FILES)
	clang-format -style=Google -i $(SRC_FILES)
dist: install
	mkdir -p 3dViewer
	touch 3dViewer/Makefile
	$(MAKE)
	cp -R ../build ../dvi 3dViewer/
	tar cvzf 3dViewer.tgz 3dViewer/
	mv 3dViewer.tgz ../
	rm -rf 3dViewer/
gcov_report: clean
	$(CXX) $(CXXFLAGS) $(GCOV) $(GTEST_FLAGS) $(TEST_SRC) controller/controller.h model/*.cpp -o report
	./report
	gcov *.gcno *.gcda
	lcov --capture --directory . --output-file coverage.info --no-external --ignore-errors inconsistent --ignore-errors mismatch
	genhtml coverage.info --output-directory coverage_report
	$(OPEN) ./coverage_report/index.html
	rm -rf *.gcda *.gcno report *.gcov *.info

tests:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) model/*.cpp controller/controller.h $(GTEST_FLAGS) -o test
	./test
