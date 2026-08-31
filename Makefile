BUILD := build

.PHONY: all configure build server client run-server run-client clean rebuild fmt

all: build

configure:
	cmake -S . -B $(BUILD) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure
	cmake --build $(BUILD) -j

server: configure
	cmake --build $(BUILD) -j --target DoomManServer

client: configure
	cmake --build $(BUILD) -j --target DoomManClient

run-server: server
	$(BUILD)/DoomManServer

run-client: client
	$(BUILD)/DoomManClient

fmt:
	find src include \( -name '*.cpp' -o -name '*.h' \) | xargs clang-format -i

clean:
	rm -rf $(BUILD)

rebuild: clean build
