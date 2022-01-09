# Monitor Architecture

## Parts of the Monitor
Each one of these classes can only have one class instance.
### State
The state class stores the current state of the monitor. For example, it might include the current temperature or the current pH of the nutrient solution.
### Commands
The commands class stores the operations that the monitor should do in one cycle.
### Outputs
The outputs class stores the outputs after calculation for each subsystem. These values can be used to write to state.

## Subsystems
Each subsystem has 3 functions and an initializer. These 3 functions are the read, calculate, and write functions. 

Each subsystem has their own variables organized in State, Commands, and Outputs. 

### Read
This function takes in the current State and initializes the subsystem. You can only read from the State and cannot write to it. For most subsystems, this function won't be used.

### Calculate
This function takes in the current State and Command and writes to Outputs. You can only read from the State and Command and cannot write to them. For example, the uploader subsystem uses the calculate function to generate the string to be uploaded. This string is stored in Outputs.

### Write 
This function reads the Outputs and applies them. For example, the uploader subsystem uses the write function to upload the data string to the database.

## Other things
### Control
The control class takes in user input and generates Commands. Control is the only way to write to Commands for now.

### robot.cpp
robot.cpp shouldn't be edited. Don't do it :)

## Monitor Cycle
Here is the layout for one cycle of the monitor:

 1. Control runs (uses user input to update Commands)
 2. Run subsystem functions
	 3. Read (state)
	 4. Calculate (state, commands, outputs)
	 5. Write (outputs)
