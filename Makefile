CXX = g++
src = $(wildcard *.cc)
obj = $(src:.cc=.o)
bin = metric_clock

CXXFLAGS = -Wall -std=c++11
LDFLAGS = -l sfml-graphics -l sfml-window -l sfml-system

$(bin): $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)
	rm -f $(obj)

.PHONY: clean
clean:
	rm -f $(obj) $(bin)
