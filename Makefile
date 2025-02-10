CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lncurses
TARGET = TextForge
SRC = main.c write.c loadconfig.c fhexedit.c
OBJ = $(SRC:.c=.o)
PREFIX = /usr/local/bin

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
debug: CFLAGS += -g
debug: $(TARGET)
install: $(TARGET)
	install -m 755 $(TARGET) $(PREFIX)

ver:
	@echo "TextForge version 1.0.0"
.PHONY: all clean debug install ver
