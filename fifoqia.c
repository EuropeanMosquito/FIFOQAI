#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifoqai.h"

struct fifo {
  int size;
  int empty;
  int produce;
  int consume;
  char* contents[];
};

struct fifo* 
fifo_new (int size)
{
  struct fifo* fifo = malloc (sizeof (struct fifo) + sizeof (char*) * size);
  fifo->size = size;
  fifo->empty = 1;
  fifo->produce = 0;
  fifo->consume = 0;

  return fifo;
}

void 
fifo_free (struct fifo* fifo)
{
  fifo_dump (fifo);

  free (fifo);
}

int 
fifo_push (struct fifo* fifo, const char* str)
{
  if (!fifo->empty)
    return 0;

  fifo->contents[fifo->produce] = malloc (strlen (str) + 1);
  strcpy (fifo->contents[fifo->produce], str);
  fifo->produce = (fifo->produce + 1) % fifo->size;
  if (fifo->produce == fifo->consume)
    fifo->empty = 0;

  return 1;
}

char* 
fifo_pull (struct fifo* fifo)
{
  if (fifo->produce == fifo->consume && fifo->empty)
    return NULL;

  char* temp = fifo->contents[fifo->consume];
  fifo->consume = (fifo->consume + 1) % fifo->size;
  fifo->empty = 1;

  return temp;
}

void
fifo_dump (struct fifo* fifo)
{
  char* str;
  while ((str = fifo_pull (fifo)))
    free (str);

  fifo->consume = 0;
  fifo->produce = 0;
}
