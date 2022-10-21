all: clean compile link


link:
	cc=g++ -o bin/main bin/main.o bin/Customer.o bin/Action.o bin/Studio.o bin/Trainer.o bin/Workout.o




compile: src/main.cpp src/Customer.cpp src/Action.cpp src/Studio.cpp src/Trainer.cpp src/Workout.cpp
		cc=g++ -g -Wall  -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
		g++ -g -Wall  -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp
		g++ -g -Wall  -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp
		g++ -g -Wall  -std=c++11 -c -Iinclude -o bin/Studio.o src/Studio.cpp
		g++ -g -Wall  -std=c++11 -c -Iinclude -o bin/Trainer.o src/Trainer.cpp
		g++ -g -Wall  -std=c++11 -c -Iinclude -o bin/Workout.o src/Workout.cpp



clean:
		@echo 'Cleaning'
		rm -f bin/*