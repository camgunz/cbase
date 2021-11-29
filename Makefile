.PHONY: all clean debug release debugtest test coverage

all: release

clean:
	@rm -f *.gcno *.gcda *.info
	@rm -rf build releasebuild

build:
	@meson setup --default-library=both build
	@compdb -p build/ list > compile_commands.json
	@mv compile_commands.json build/compile_commands.json

releasebuild:
	@meson setup --buildtype=release --default-library=both \
		--buildtype=release --optimization=3 releasebuild

debug: build
	@meson compile -v -C build

release: releasebuild
	@meson compile -C releasebuild

test: build
	@meson compile -C build cbase_test
	@cd build && ./cbase_test

releasetest: releasebuild
	@meson compile -C releasebuild cbase_test
	@cd releasebuild && ./cbase_test

coverage: test
	@cd build; \
	 mkdir -p coverage; \
	 lcov -q -c -i -d CMakeFiles/cbase_test.dir/src -o base_coverage.info; \
	 lcov -q -c -d CMakeFiles/cbase_test.dir/src -o test_coverage.info; \
	 lcov -q -a base_coverage.info -a test_coverage.info -o total_coverage.info; \
	 lcov -q --summary total_coverage.info; \
	 genhtml -q -o coverage total_coverage.info

help:
	@echo "Targets: all | clean | build | releasebuild | debug | release | test | releasetest | coverage"
