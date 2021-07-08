#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum
{
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN
} OpCode;

typedef struct {
  int line;
  int lineCount;
} Line;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  ValueArray constants;
  Line* lines;
  int currentLine;
} Chunk;

void initChunk(Chunk*);
void freeChunk(Chunk*);
void writeChunk(Chunk*, uint8_t, int);
int addConstant(Chunk* chunk, Value value);

#endif