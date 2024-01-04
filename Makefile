CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99
LIBS = -lGL -lGLU -lglut -lm

SRCS = main.c ball.c panel.c tunnel.c
OBJS = $(SRCS:.c=.o)

EXECUTABLE = PONG3D

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
