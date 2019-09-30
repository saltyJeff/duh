//
// Created by Jefferson on 7/18/2019.
//

#include "DuhRead.h"
#include "checksum.h"

DuhInputCache input;
char readBuffer[MAX_MESSAGE_SIZE + 1] = "";

// finite state machine states for the parsing
char *currentField = input.prefix;
byte currentMaxLen = MAX_PREFIX_LEN;
byte currentIndex = 0;
byte fieldsWritten = 0;

bool transitionChar(char c);

byte readDuh(char c) {
	if(c < 32) {
		return WARNING_DISCARDED; //ignore non-printable characters
	}
	if(transitionChar(c) && c != ';') {
		return SEND_NOTHING;
	}
	//printf("STATE: %c field: %s\n", c, currentField);
	if(c == ';') {
		if (fieldsWritten < 2) {
			//not valid condition
			fieldsWritten = 0;
			input.hasChecksum = false;
			return WARNING_DISCARDED; //received incomplete message, disposing
		}
		fieldsWritten = 0;
		if (input.hasChecksum) {
			input.hasChecksum = false;
			// parse the checksum value from the checksum field
			uint16_t challenge = strtol(input.checksum, NULL, 16);
			if (challenge == 0 && errno != 0) {
				return SEND_NAK;
			}
			byte bytesToHash = sprintf(readBuffer, PACKET_NO_CHECKSUM, input.prefix, input.id,
			                           input.data);
			uint16_t sum = checksum(readBuffer, bytesToHash);
			if (sum != challenge) {
				return SEND_NAK;
			}
		}
		return SEND_ACK;
	}
	if(currentIndex < currentMaxLen) {
		currentField[currentIndex++] = c;
		return SEND_NOTHING;
	}
	//WARNING STATE: current field is full but we haven't transitioned yet. will throwaway but give warning
	fieldsWritten = 0;
	return WARNING_DISCARDED;
}
bool transitionChar(char c) {
	char *previousField = currentField;
	byte previousIndex = currentIndex;
	byte previousMaxLen = currentMaxLen;
	switch(c) {
		default:
			return false;
		case '-':
			currentField = input.id;
			currentMaxLen = MAX_ID_LEN;
			fieldsWritten++;
			break;
		case ':':
			currentField = input.data;
			currentMaxLen = MAX_DATA_LEN;
			fieldsWritten++;
			break;
		case '/':
			currentField = input.checksum;
			currentMaxLen = CHECKSUM_LENGTH;
			input.hasChecksum = true;
			break;
		case ';':
			currentField = input.prefix;
			currentMaxLen = MAX_PREFIX_LEN;
			break;
	}
	currentIndex = 0;
	if(previousIndex <= previousMaxLen) {
		previousField[previousIndex] = '\0'; // add null terminator to the previous field so we don't over scan
	}
	return true;
}