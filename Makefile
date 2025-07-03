.PHONY: all build clean run test \
	clean_build clean_build_run clean_build_test clean_build_test_run \
	build_run build_test build_test_run test_run

build:
	./scripts/build.sh

clean:
	./scripts/clean.sh

run:
	./scripts/run.sh

test:
	./scripts/test.sh

clean_build: clean build

clean_build_run: clean build run

clean_build_test: clean build test

clean_build_test_run: clean build test run

build_run: build run

build_test: build test

build_test_run: build test run

test_run: test run

