CC = g++ -Wall -Wextra -Werror -std=c++11
CC_S = g++ -shared -Wall -Wextra -Werror -std=c++11
LINK_FLAGS = -Wl,--out-implib,engine.dll -L"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib" \
				-lWinMM -L"C:\glfw-3.0.4.bin.WIN32\lib-mingw" -lglfw3  \
				-L"C:\glew-1.11.0\lib\Release\Win32" -lglew32s -L"C:\glew-1.5.4-mingw32\lib" -llibglew32 -lgdi32 -lglu32 -lopengl32
ENG_LINK = -L"C:\Users\jgelderl\Documents\Engine" -lengine
INC_DIRS = -isystem"C:\glfw-3.0.4.bin.WIN32\include" -isystem"C:\glew-1.5.4-mingw32\include" \
 				-I"C:\Users\jgelderl\Documents\Engine\lib" -I"C:\Users\jgelderl\Documents\Engine\src"
CFLAGS = -c $(INC_DIRS)

all: engine.dll Tetris.exe Pong.exe

Tetris: engine.dll Tetris.exe

Pong: engine.dll Pong.exe

engine.dll: engine.o game.o PhysSpace2D.o PhysObj2D.o Shape2D.o HitBox2D.o CollisionData2D.o Vec2D.o Point2D.o Box.o Circle.o 
		$(CC_S) -o engine.dll $(INC_DIRS) engine.o game.o PhysSpace2D.o PhysObj2D.o Shape2D.o HitBox2D.o CollisionData2D.o Vec2D.o Point2D.o Box.o Circle.o $(LINK_FLAGS)

engine.o: src/engine.cpp src/engine.h
		$(CC) $(CFLAGS) src/engine.cpp src/engine.h
        
game.o: src/game.cpp src/game.h
		$(CC) $(CFLAGS) src/game.cpp src/game.h

PhysSpace2D.o: src/PhysSpace2D.cpp src/PhysSpace2D.h
		$(CC) $(CFLAGS) src/PhysSpace2D.cpp

PhysObj2D.o: src/PhysObj2D.cpp src/PhysObj2D.h
		$(CC) $(CFLAGS) src/PhysObj2D.cpp

Shape2D.o: src/Shape2D.cpp src/Shape2D.h
		$(CC) $(CFLAGS) src/Shape2D.cpp
		
HitBox2D.o: src/HitBox2D.cpp src/HitBox2D.h
		$(CC) $(CFLAGS) src/HitBox2D.cpp

CollisionData2D.o: src/CollisionData2D.cpp src/CollisionData2D.h
		$(CC) $(CFLAGS) src/CollisionData2D.cpp

Vec2D.o: src/Vec2D.cpp src/Vec2D.h
		$(CC) $(CFLAGS) src/Vec2D.cpp

Point2D.o: src/Point2D.cpp src/Point2D.h
		$(CC) $(CFLAGS) src/Point2D.cpp

Box.o: src/Box.cpp src/Box.h
		$(CC) $(CFLAGS) src/Box.cpp

Circle.o: src/Circle.cpp src/Circle.h
		$(CC) $(CFLAGS) src/Circle.cpp

Tetris.exe: TetrisMain.o Tetris.o Menu.o Block.o Board.o
		$(CC) -o Tetris.exe $(INC_DIRS) TetrisMain.o Tetris.o Menu.o Block.o Board.o $(LINK_FLAGS) $(ENG_LINK)
		
TetrisMain.o: examples/Tetris/TetrisMain.cpp
		$(CC) $(CFLAGS) examples/Tetris/TetrisMain.cpp

Tetris.o: examples/Tetris/Tetris.cpp examples/Tetris/Tetris.h
		$(CC) $(CFLAGS) examples/Tetris/Tetris.cpp

Menu.o: examples/Tetris/Menu.cpp examples/Tetris/Menu.h
		$(CC) $(CFLAGS) examples/Tetris/Menu.cpp
		
Block.o: examples/Tetris/Block.cpp examples/Tetris/Block.h
		$(CC) $(CFLAGS) examples/Tetris/Block.cpp
        
Board.o: examples/Tetris/Board.cpp examples/Tetris/Board.h
		$(CC) $(CFLAGS) examples/Tetris/Board.cpp

Pong.exe: PongMain.o Table.o Paddle.o Ball.o
		$(CC) -o Pong.exe $(INC_DIRS) PongMain.o Table.o Paddle.o Ball.o $(LINK_FLAGS) $(ENG_LINK)

PongMain.o: examples/Pong/PongMain.cpp
		$(CC) $(CFLAGS) examples/Pong/PongMain.cpp

Table.o: examples/Pong/Table.cpp examples/Pong/Table.h
		$(CC) $(CFLAGS) examples/Pong/Table.cpp

Paddle.o: examples/Pong/Paddle.cpp examples/Pong/Paddle.h
		$(CC) $(CFLAGS) examples/Pong/Paddle.cpp
		
Ball.o: examples/Pong/Ball.cpp examples/Pong/Ball.h
		$(CC) $(CFLAGS) examples/Pong/Ball.cpp

clean:
		-del engine.dll Tetris.exe Pong.exe *.o
		
rebuild: clean all
