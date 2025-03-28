CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

cmake:
	@mkdir -p build && cd build && cmake ..

install: uninstall cmake
	@echo "\033[46mInstallation\033[0m"
	@cd build && make
	@echo "\033[46mApplication installed\033[0m"
	@make dvi
	@cd build && open 3DViewer.app

uninstall: clean
	@rm -rf build
	@rm -rf ../dist
	@echo "\033[46mApplication removed\033[0m"

dvi:
	@open ./../dvi_report/html/index.html

dist:
	@mkdir -p ../dist
	@cp -R build/3DViewer.app ../dist
	@cd ../dist && tar cvzf 3DViwer.tar *
	@cd ../dist && rm -rf 3DViwer.app README.md

test: clean
	$(CC) $(CFLAGS) --coverage Model/tests/tests.cc Model/object.cc Model/Transformations/*.cc Controller/controller.cc  -lgtest -lgtest_main -pthread -o test
	./test

gcov_report: test
	@lcov -t "test_model" -o model.info -c -d . --ignore-errors mismatch,inconsistent
	@lcov -e model.info '*/src/Model/*.cc' -o model_filtered.info --ignore-errors mismatch,inconsistent
	@genhtml -o ../gcov_report model_filtered.info --ignore-errors mismatch,inconsistent
	@open ./../gcov_report/index.html

clean:
	@rm -rf test *.gcda *.gcno *.o *.info *.a ../gcov_report
	@echo "\033[46mCleaned\033[0m"

check_style:
	clang-format -style=Google -n View/*.cc View/*.h
	clang-format -style=Google -n Controller/*.h
	clang-format -style=Google -n Model/*.cc Model/*.h
	clang-format -style=Google -n Model/tests/*.cc
	clang-format -style=Google -n Model/Transformations/*.cc
	clang-format -style=Google -n main.cc

fix_style:
	@clang-format -style=Google -i View/*.cc View/*.h
	@clang-format -style=Google -i Controller/*.h
	@clang-format -style=Google -i Model/*.cc Model/*.h
	@clang-format -style=Google -i Model/tests/*.cc
	@clang-format -style=Google -i Model/Transformations/*.cc
	@clang-format -style=Google -i main.cc