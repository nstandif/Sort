CC = g++
OPTS = -Wall

SOURCE_DIR = source
OUTPUT_DIR = binaries

$(OUTPUT_DIR)/sort240: $(SOURCE_DIR)/sort240.cpp
	$(CC) $(OPTS) $(SOURCE_DIR)/sort240.cpp -o $(OUTPUT_DIR)/sort240
$(OUTPUT_DIR)/sort240-debug: $(SOURCE_DIR)/sort240.cpp
	$(CC) $(OPTS) -g $(SOURCE_DIR)/sort240.cpp -o $(OUTPUT_DIR)/sort240-debug