###############################################################################
#
# Simple Makefile to help development of Verilog modules using Icarus Verilog
# and GTKWave.
#
# Part of the DeWille DAC project
#
# Supported targets:
# 	"make" 			- Compile the module and the testbench
# 	"make test" 	- Compile and execute the testbench
# 	"make display" 	- Compile, execute the test and display the waveforms
#
###############################################################################

# Per-module sources. Change these 
SOURCES = spi_slave.v
OUTPUT = spi_slave
TESTBENCH = spi_slave_tb.v
WAVEFORMS = spi_slave.lxt2	# adjust in spi_slave_tb.v

# Tools - probably should not be changed
COMPILER = iverilog
SIMULATOR = vvp
VIEWER = gtkwave

# Options
COFLAGS = -o			# COmpiler flags
SIMFLAGS = 				# Simulator flags - before the simulated file
SIMARGS = -lxt2			# Simulator arguments - after the simulated file 

# Rules
build : $(TESTBENCH) $(SOURCES)
	$(COMPILER) $(COFLAGS) $(OUTPUT) $(TESTBENCH) $(SOURCES)

test: $(OUTPUT)
	$(SIMULATOR) $(SIMFLAGS) $(OUTPUT) $(SIMARGS) 

display: $(WAVEFORMS)
	$(VIEWER) $(WAVEFORMS) 1>/dev/null 2>/dev/null &

clean:
	rm -f $(OUTPUT) $(WAVEFORMS)

# Dependancies
$(WAVEFORMS): $(OUTPUT)
	$(SIMULATOR) $(SIMFLAGS) $(OUTPUT) $(SIMARGS)

$(OUTPUT): $(TESTBENCH) $(SOURCES)
	$(COMPILER) $(COFLAGS) $(OUTPUT) $(TESTBENCH) $(SOURCES)

