# uxdump

It was started as an open hardware project to create a device which measures changes in the state of a person while he/she works with software. Gradualy it permutates into a software shell with an additional hardware component,  intended for usability researches.

Hardware part measures galvanic skin responce and also carries out two measurements of the heartbeat rate (to estimate arterial pressure change). Electronics is highly based on Arduino, but was simplified to exclude unneeded parts. Measured values are transferred to computer via USB cable and received by driver written in Processing language. These data are to be further imported into the shell via CSV file in automatic or manual mode, so wide range of different hardware units can be successfully used in addition (particularly we have added NeuroSky Mindwave EEG for our own research project, paired with Puzzlebox Synapse software).



hardware:
------

* PCB - printed board 
* top, bottom - 3D model of the frame
* scheme - the schematics

driver:
------

A software module to get  GSR, pulse and pressure data from device (in processing 1.2.1)

frontend
------

A software shell created with QT Creator:

![screenshot](https://raw.githubusercontent.com/fiowro/uxdump/master/screenshot.jpg)
