#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  int curLineCount = chunk->lines[0].lineCount;
  int curLine = chunk->lines[0].line;
  int curOffset = 0;
  
  for (int offset = 0, lineNum = 0; offset < chunk->count && curLine != 0;)
    {
      curOffset = disassembleInstructionByLine(chunk, offset, curOffset, curLine);
      if (curOffset > curLineCount)
      {
        lineNum++;
        curOffset = 0;
        curLineCount = chunk->lines[curLine].lineCount;
        curLine = chunk->lines[lineNum].line;
      } else curLineCount -= curOffset;
      offset += curOffset;
    }
}

static int simpleInstruction(const char *name, int offset)
{
  printf("%s\n", name);
  return 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return 2;
}

int disassembleInstructionByLine(Chunk *chunk, int offset, int curOffset, int line)
{
  printf("%04d ", offset);

  // printf("\n%d %d %d", curOffset, line);
  if (curOffset > 0)
  {
    printf("   | ");
  }
  else
  {
    printf("%4d ", line);
  }

  return disassembleInstruction(chunk, offset);
}

int disassembleInstruction(Chunk* chunk, int offset) {
  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}
