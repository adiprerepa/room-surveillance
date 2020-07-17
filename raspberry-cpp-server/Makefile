CXX := g++
CXX_FLAGS := 

BIN := bin
SRC := src
LIB := lib
LIBRARIES :=
EXECUTABLE := main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cc
	@echo "🚧 Building...";
	@protoc proto/activity_interface.proto --cpp_out=.;
	$(CXX) $(CXX_FLAGS) -L$(LIB) $^ -o $@ $(LIBRARIES) `pkg-config --cflags --libs protobuf`

clean:
	@echo "🧹 Clearing..."
	-rm $(BIN)/*
