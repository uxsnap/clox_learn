#include <stdlib.h>

#include "common.h"
#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  chunk->currentLine = 0;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCap = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCap);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
      oldCap, chunk->capacity);
    chunk->lines = GROW_ARRAY(Line, chunk->lines,
      oldCap, chunk->capacity);
  }
  
  chunk->code[chunk->count] = byte;
  chunk->count++;

  if (chunk->currentLine > -1 && chunk->lines[chunk->currentLine - 1].line == line)
  {
    chunk->lines[chunk->currentLine - 1].lineCount++;
  }
  else
  {
    chunk->lines[chunk->currentLine].line = line;
    chunk->lines[chunk->currentLine].lineCount = 1;
    chunk->currentLine++;
  }
}


int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}