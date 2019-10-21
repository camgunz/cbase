.PHONY: all clean debug test debugtest coverage help

all: release

clean:
	@rm -rf cbuild
	@rm -f *.gcno *.gcda *.info

debug:
	@mkdir -p cbuild
	@cd cbuild && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

release:
	@mkdir -p cbuild
	@cd cbuild && cmake -DCMAKE_BUILD_TYPE=Release .. && make

test: debug
	@cd cbuild && ./cbase_test

debugtest: debug
	@cd cbuild && gdb ./cbase_test --ex run

coverage: test
	@cd cbuild; \
	 mkdir -p coverage; \
	 lcov -q -c -i -d CMakeFiles/cbase_test.dir/src -o base_coverage.info; \
	 lcov -q -c -d CMakeFiles/cbase_test.dir/src -o test_coverage.info; \
	 lcov -q -a base_coverage.info -a test_coverage.info -o total_coverage.info; \
	 lcov -q --summary total_coverage.info; \
	 genhtml -q -o coverage total_coverage.info

help:
	@echo "Targets: all | clean | debug | release | test | debugtest | coverage"
