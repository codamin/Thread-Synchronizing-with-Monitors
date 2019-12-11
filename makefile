BUILD_DIR = build

all: $(BUILD_DIR) program.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp defs.h EdgeMonitor.h EmmisionMonitor.h
	g++ -c main.cpp -o $(BUILD_DIR)/main.o 

$(BUILD_DIR)/EdgeMonitor.o: EdgeMonitor.cpp EdgeMonitor.h
	g++ -c EdgeMonitor.cpp -o $(BUILD_DIR)/EdgeMonitor.o

$(BUILD_DIR)/EmmisionMonitor.o: EmmisionMonitor.cpp EmmisionMonitor.h
	g++ -c EmmisionMonitor.cpp -o $(BUILD_DIR)/EmmisionMonitor.o

program.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/EdgeMonitor.o $(BUILD_DIR)/EmmisionMonitor.o
	g++ -o program.out $(BUILD_DIR)/main.o $(BUILD_DIR)/EdgeMonitor.o $(BUILD_DIR)/EmmisionMonitor.o -pthread