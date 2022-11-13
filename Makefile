slide-fsm-simulation:
	gcc -o slide-fsm-simulation ./fsm/slide_fsm_simulation.c ./fsm/slide_fsm.c

debounce-fsm-simulation:
	gcc -o debounce-fsm-simulation ./fsm/debounce_fsm_simulation.c ./fsm/debounce_fsm.c

rising-edge-fsm-simulation:
	gcc -o rising-edge-fsm-simulation ./fsm/rising_edge_fsm_simulation.c ./fsm/rising_edge_fsm.c


all: 
	$(MAKE) slide-fsm-simulation
	$(MAKE) rising-edge-fsm-simulation
	$(MAKE) debounce-fsm-simulation

clean:
	del *.exe

clean-sim:
	del *.csv