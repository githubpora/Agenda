CC := g++-4.8
FLAGS := -std=c++11 -w
bin/Agenda: build/AgendaUI.o build/AgendaService.o build/Storage.o build/Date.o build/Meeting.o build/User.o build/Agenda.o 
	@mkdir -p bin
	$(CC) $(FLAGS) -I./include build/AgendaUI.o build/AgendaService.o build/Storage.o build/Date.o build/Meeting.o build/User.o build/Agenda.o -o $@

build/AgendaUI.o: src/AgendaUI.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -c -o $@ src/AgendaUI.cpp

build/AgendaService.o: src/AgendaService.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -c -o $@ src/AgendaService.cpp

build/Storage.o: src/Storage.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -I./data -c -o $@ src/Storage.cpp

build/Date.o: src/Date.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -c -o $@ src/Date.cpp

build/Meeting.o: src/Meeting.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -c -o $@ src/Meeting.cpp

build/User.o: src/User.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -c -o $@ src/User.cpp

build/Agenda.o: src/Agenda.cpp
	@mkdir -p build
	$(CC) $(FLAGS) -I./include -c -o $@ src/Agenda.cpp

clean:
	@rm -rf bin
	@rm -rf build

