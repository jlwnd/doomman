BUILD := build

.PHONY: all configure build server client run-server run-client clean rebuild fmt test generate-docs

all: build

configure:
	cmake -S . -B $(BUILD) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure generate-docs
	cmake --build $(BUILD) -j

client: configure
	cmake --build $(BUILD) -j --target DoomManClient

run: client
	$(BUILD)/DoomManClient

fmt:
	find src include \( -name '*.cpp' -o -name '*.h' \) | xargs clang-format -i

clean:
	rm -rf $(BUILD)

rebuild: clean build

test:
	ctest --test-dir $(BUILD) --output-on-failure

generate-docs:
	mkdir -p docs/doxygen
	doxygen Doxyfile
