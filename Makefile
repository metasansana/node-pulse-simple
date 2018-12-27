
bin: bin/pulse
	touch bin

bin/pulse: src/node_pulse_simple.cc
	g++ -Wall $? -lpulse -lpulse-simple -o $@
	chmod +x $@
