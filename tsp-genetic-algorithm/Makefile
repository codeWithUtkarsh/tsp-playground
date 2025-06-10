# Makefile for TSP Genetic Algorithm Project

# Compiler settings
CXX       := g++
CXX_FLAGS := -O3 -ffast-math -std=c++11
CC        := gcc
CFLAGS    := -O3 -ffast-math -std=c99
DEBUG_FLAGS := -g -DDEBUG -O0 -Wall -Wextra
LIBS      := -lm

# Directories
BIN     := bin
SRC     := src
INCLUDE := include
INSTANCES_DIR := instances
RESULTS_DIR   := results

# Files
EXECUTABLE  := main
C_SOURCE    := GA_TSP_Serial_Random.c

# Default target
all: $(BIN)/$(EXECUTABLE)

# Ensure bin directory exists
$(BIN):
	@mkdir -p $(BIN)

# For C++ version (if needed later)
$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBS)

# For current C version (optimized, no debug prints)
c_version: | $(BIN)
	$(CC) $(CFLAGS) $(C_SOURCE) -o $(BIN)/$(EXECUTABLE) $(LIBS)
	@echo "Build complete! Executable: $(BIN)/$(EXECUTABLE) (optimized, no debug prints)"

# Build parallel version (optimized)
parallel: | $(BIN)
	$(CC) $(CFLAGS) -fopenmp GA_TSP_Parallel.c -o $(BIN)/$(EXECUTABLE)_parallel $(LIBS)
	@echo "Build complete! Executable: $(BIN)/$(EXECUTABLE)_parallel (optimized, no debug prints)"

# Build serial version (optimized)
serial: | $(BIN)
	$(CC) $(CFLAGS) GA_TSP_Serial.c -o $(BIN)/$(EXECUTABLE)_serial $(LIBS)
	@echo "Build complete! Executable: $(BIN)/$(EXECUTABLE)_serial (optimized, no debug prints)"

# Debug builds
gdb: CXX_FLAGS = -ggdb -DDEBUG
gdb: all

valgrind: CXX_FLAGS = -Wall -pedantic -g -DDEBUG
valgrind: all

debug: CFLAGS = $(DEBUG_FLAGS) -std=c99
debug: clean c_version
	@echo "Debug version built with symbols and DEBUG prints enabled"

debug_parallel: CFLAGS = $(DEBUG_FLAGS) -std=c99 -fopenmp
debug_parallel: clean
	$(CC) $(CFLAGS) GA_TSP_Parallel.c -o $(BIN)/$(EXECUTABLE)_parallel $(LIBS)
	@echo "Debug parallel version built with symbols and DEBUG prints enabled"

debug_serial: CFLAGS = $(DEBUG_FLAGS) -std=c99
debug_serial: clean
	$(CC) $(CFLAGS) GA_TSP_Serial.c -o $(BIN)/$(EXECUTABLE)_serial $(LIBS)
	@echo "Debug serial version built with symbols and DEBUG prints enabled"

# Run targets
run: clean all
	./$(BIN)/$(EXECUTABLE)

run_c: clean c_version
	./$(BIN)/$(EXECUTABLE)

# Test targets
test-random: c_version
	@echo "=== Testing Random Mode ==="
	./$(BIN)/$(EXECUTABLE)

test-instance: c_version
	@echo "=== Testing Instance Mode ==="
	./$(BIN)/$(EXECUTABLE) instance_mode

test-both: test-random test-instance

# Create necessary directories
dirs:
	@mkdir -p $(BIN) $(INSTANCES_DIR) $(RESULTS_DIR)
	@echo "Created directories: $(BIN), $(INSTANCES_DIR), $(RESULTS_DIR)"

# Clean targets
clean:
	@rm -rf $(BIN)
	@rm -f *.o core
	@echo "Cleaned executable and object files"

clean-results:
	@rm -rf $(RESULTS_DIR)/*
	@echo "Cleaned results directory"

clean-all: clean clean-results
	@echo "Full cleanup completed"

# Install target
install: c_version
	@echo "Installing $(EXECUTABLE) to /usr/local/bin..."
	@sudo cp $(BIN)/$(EXECUTABLE) /usr/local/bin/
	@echo "Installation complete"

uninstall:
	@echo "Removing $(EXECUTABLE) from /usr/local/bin..."
	@sudo rm -f /usr/local/bin/$(EXECUTABLE)
	@echo "Uninstallation complete"

# Help
help:
	@echo "=== TSP Genetic Algorithm Makefile ==="
	@echo ""
	@echo "BUILD TARGETS:"
	@echo "  all          - Build the executable (default, C++)"
	@echo "  c_version    - Build C version (optimized, no debug prints)"
	@echo "  parallel     - Build parallel version (optimized)"
	@echo "  serial       - Build serial version (optimized)"
	@echo "  debug        - Build debug version with DEBUG prints"
	@echo "  debug_parallel - Build parallel debug version with DEBUG prints"
	@echo "  debug_serial - Build serial debug version with DEBUG prints"
	@echo "  gdb          - Build with gdb symbols and DEBUG prints"
	@echo "  valgrind     - Build for valgrind analysis with DEBUG prints"
	@echo ""
	@echo "RUN TARGETS:"
	@echo "  run          - Clean, build and run C++ version"
	@echo "  run_c        - Clean, build and run C version"
	@echo ""
	@echo "TEST TARGETS:"
	@echo "  test-random  - Run in random mode"
	@echo "  test-instance- Run in instance mode"
	@echo "  test-both    - Run both modes"
	@echo ""
	@echo "UTILITY TARGETS:"
	@echo "  dirs         - Create necessary directories"
	@echo "  clean        - Remove executable"
	@echo "  clean-all    - Remove executable and results"
	@echo "  install      - Install to /usr/local/bin"
	@echo "  uninstall    - Remove from /usr/local/bin"

# Phony targets
.PHONY: all c_version parallel serial debug debug_parallel debug_serial gdb valgrind run run_c test-random test-instance test-both dirs clean clean-results clean-all install uninstall help

# Default goal
.DEFAULT_GOAL := all