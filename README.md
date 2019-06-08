# duh
dumb user handset

## Summary
Declares a simple protocol to communicate between a dumb client
and a remote system.

The protocol is designed to be fully ASCII, so any PC with a serial port
monitor can be used if no user handset is available

### Diagram
This library is for the local box

```
local box
------          -----
|   🕹️         |
|   🕹️ <====>  |   remote box
|   🕹️         |
------          ------

```

## Operation mode

1. The local will send deltas of the input in the format specified below (**event mode**)
2. The remote box can also send a request for the local box to sample
an input immediately (**rpc mode**)

## Supported inputs
* push button
* switches behind a shift register

# Protocol Design
* All messages are ASCII should end with a LF (not shown). 
* All IDs are capped at 3 characters. 
* Unless otherwise noted all timestamps are in seconds and are relative to when the local machine was turned on. 
* All messages are semicolon terminated right before the LF
* Timestamps are optional (in case you're running it from a serial monitor) but highly suggested

## Switch
### Format
`SW-<switch array id>:<switch states in hex ascii>;/<timestamp>;`
### Notes
Sent every time a switch in a particular array is modified. Switch states are sent as the ASCII representation of the hex number representing the switch states (1 for on and 0 for off) rounded to the nearest nibble (padded switches will be set to 0). Sent in big-endian order so that the first letter represents the state of switches 0-3, the second represents 4-7, etc
### Example
`SW-0:FF/24;`

Sent when any switch in switch array 0 has been toggled so that every switch in the array is now on
## Pushbutton
### Format
`PB-*pushbutton id*:<P/R for pressed/released>/<timestamp>;`

### Example
`PB-3:P/38;`

Sent when push button 3 is pressed down. When push button 3 is released, 

`PB-3:R/39;`

will be sent.

## RPC Request from the remote machine
### Format
`RQ-<request id>:<id of the input to sample>;`

### Notes
The &lt;id of the input to sample&gt; is specified as:

`SW/PB-<id>`

### Example
`RQ-420:SW-3;`

Sends a request to sample switch array 3. The corresponding reply (see below) will use 420 to distinguish the reply

## RPC response from the remote machine
### Format
`RS-<request id>:<value that was requested>/<timestamp when the requested data was last updated>;`

### Notes
The &lt;request id&gt; will be the same as the request id used when requesting the sample (see above).
Note that the response doesn't include which location the data sample came from (the remote box is responsible for keeping track of the mapping between request id and requested sample).

### Example
`RS-420:0F/220;`

Sends a response to the example request above. The state of the switches is 0F from left to right, and the data was valid as of time stamp 220.