#ifndef FIFOQAI_H
#define FIFOQAI_H

struct fifo* fifo_new (int size); //Creates a new fifo instance and sets it up in a way to not get screwed by built in functions.

void fifo_free (struct fifo* fifo); //Frees fifo stuct and its contents, but to free memory adresses pointed by pointers inside fifo->contents, it uses fifo_dump ().

int fifo_push (struct fifo* fifo, const char* str); //Pushes a element if fifo->empty is true and makes fifo->empty false if it wraps all the way around.

char* fifo_pull (struct fifo* fifo); //Pulls a element out of fifo, IT IS THE OWNER'S RESPONSIBILITY TO CALL free ().

void fifo_dump (struct fifo* fifo); //Frees contents of fifo->contents.

//YOU HAVE TO CALL fifo_free() to free the memory used!

#endif
