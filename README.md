# duh
dumb user handset

The prebuilt binary is in the [cmake-build-default-mingw] folder, along with the needed dll s for running on Windows. I will try to make a build for OSX soon.

## Configuration
The serial port can be configured using environmental variables

variable | description
---|---
SERIAL_PORT|The location of the serial port (COM1 for example)
BAUD_RATE|The baud rate for the serial port

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
* switches behind a I2C port expander

# Protocol Design
* All messages are ASCII and are terminated by a semicolon.
    - A newline between messages will be ignored.
* All IDs must be 3 characters. 
* **All Checksums are calculated by XOR ing all the bytes of a message before the slash**
* Checksums are optional (in case you're running it from a serial monitor) but highly suggested

## Switch
### Format
`SW-<switch array id>:<switch states in hex ascii>/<checksum>;`
### Notes
Sent every time a switch in a particular array is modified. Switch states are sent as the ASCII representation of the hex number representing the switch states (1 for on and 0 for off) rounded to the nearest nibble (padded switches will be set to 0). Sent in big-endian order so that the first letter represents the state of switches 0-3, the second represents 4-7, etc
### Example
`SW-0:FF/24;`

Sent when any switch in switch array 0 has been toggled so that every switch in the array is now on
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