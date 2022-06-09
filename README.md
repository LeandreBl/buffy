# buffy
A lightweight C library to manipulate buffers

This library is a simple byte buffer manager.
It is intended to be used for operations over streaming devices, keyboard, network, etc.

An example of getdelim with a buffy:
```c
/* For malloc and free */
#include <stdlib.h>

/* For printf */
#include <stdio.h>

/* For read and ssize_t */
#include <unistd.h>

#include <buffy.h>

ssize_t buffy_getdelim(char **line, struct buffy *buffy, int delim)
{
	uint8_t temp_buffer[256];
	char c = delim;
	ssize_t lf_offset = buffy_find(buffy, &c, sizeof(c));
	ssize_t rd;
	ssize_t wr;

	while(lf_offset == -1) {

		/* Read from STDIN file descriptor */
		rd = read(STDIN_FILENO, temp_buffer, sizeof(temp_buffer));

		/* EOF and error case, use will need to check errno, the same way it goes with getdelim */
		if (rd <= 0) {
			return -1;
		}
		
		/* Append what was read to the buffy */
		wr = buffy_write(buffy, temp_buffer, rd);

		/* Verify if there was an error or if the wrong number of bytes was written */
		if (wr != rd) {
			return -1;
		}

		/* Update the line feed offset */
		lf_offset = buffy_find(buffy, &c, sizeof(c));
	}
	/* 
	* Allocate enough memory to store the line
	* +1 to include the delimitor and +1 again for the NIL byte
	*/
	*line = malloc(lf_offset + 2);
	if (*line == NULL) {
		return -1;
	}

	/* Copy the line from the buffy to the line pointer, still +1 to contain the delimitor */
	rd = buffy_read(buffy, *line, lf_offset + 1);

	/* Add a NIL byte at the end of the delimited line */
	(*line)[lf_offset + 1] = '\0';
	return rd;
}

int main(void)
{
	/* Our buffy struct */
	struct buffy buffer;

	/* Our line buffer, same usage as getdelim */
	char *line;

	/* Create the buffer, the allocation will be dynamic and the original capacity will be 0 */
	if (buffy_create(&buffer, 0, BUFFY_DYNAMIC_SIZE_STRATEGY) == -1) {
		perror("buffy");
		return 1;
	}

	/* Read from STDIN until a '\n' is found, and fill the given pointer with the content of the line, same usage as getdelim */
	if (buffy_getdelim(&line, &buffer, '\n') == -1) {
		perror("buffy getdelim");
		return 1;
	}

	/* Print the line */
	printf("<%s>\n", line);

	/* Free the line */
	free(line);

	/* Destroy the buffy */
	buffy_destroy(&buffer);
	return 0;
}
```