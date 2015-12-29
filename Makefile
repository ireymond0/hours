all: hours
hours: hours.cpp
	g++ hours.cpp -o hours

clean:
	rm -rf hours
