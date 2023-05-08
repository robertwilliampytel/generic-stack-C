#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


const long SIZE_OFFSET = 1L;


const union allValues {


  size_t      sizeT;
  ptrdiff_t   ptrDiffT;
  size_t    * sizeTPtr;
  ptrdiff_t * ptrDiffTPtr;


//_Float16     floatSixteen;  Float 16's not supported on Linux 22.04 Wayland/Jellyfish
  __float80    floatEighty;
  __float128   floatOneTwentyEight;
//_Float16   * floatSixteenPtr;
  __float80  * floatEightyPtr;
  __float128 * floatOneTwentyEightPtr;  


  int8_t          intEight;
  int16_t         intSixteen;
  int32_t         intThirtyTwo;
  int64_t         intSixtyFour;
  int_fast8_t     intFastEight;
  int_fast16_t    intFastSixteen;
  int_fast32_t    intFasthirtyTwo;
  int_fast64_t    intFastSixtyFour;
  int_least8_t    intLeastEight;
  int_least16_t   intLeastSixteen;
  int_least32_t   intLeastThirtyTwo;
  int_least64_t   intLeastSixtyFour;
  intmax_t 	      intMax;
  intptr_t 	      intPtrT;
  int8_t        * intEightPtr;
  int16_t       * intSixteenPtr;
  int32_t       * intThirtyTwoPtr;
  int64_t       * intSixtyFourPtr;
  int_fast8_t   * intFastEightPtr;
  int_fast16_t  * intFastSixteenPtr;
  int_fast32_t  * intFasthirtyTwoPtr;
  int_fast64_t  * intFastSixtyFourPtr;
  int_least8_t  * intLeastEightPtr;
  int_least16_t * intLeastSixteenPtr;
  int_least32_t * intLeastThirtyTwoPtr;
  int_least64_t * intLeastSixtyFourPtr;
  intmax_t 	    * intMaxPtr;
  intptr_t 	    * intPtrTPtr;


  uint8_t          uintEight;
  uint16_t         uintSixteen;
  uint32_t         uintThirtyTwo;
  uint64_t 	       uintSixtyFour;
  uint_fast8_t     uintFastEight;
  uint_fast16_t    uintFastSixteen;
  uint_fast32_t    uintFastThirtyTwo;
  uint_fast64_t    uintFastSixtyFour;
  uint_least8_t    uintLeastEight;
  uint_least16_t   uintLeastSixteen;
  uint_least32_t   uintLeastThirtyTwo;
  uint_least64_t   uintLeastSixtyFour;
  uintmax_t        uintMax;
  uintptr_t        uintPtrT;
  uint8_t        * uintEightPtr;
  uint16_t       * uintSixteenPtr;
  uint32_t       * uintThirtyTwoPtr;
  uint64_t 	     * uintSixtyFourPtr;
  uint_fast8_t   * uintFastEightPtr;
  uint_fast16_t  * uintFastSixteenPtr;
  uint_fast32_t  * uintFastThirtyTwoPtr;
  uint_fast64_t  * uintFastSixtyFourPtr;
  uint_least8_t  * uintLeastEightPtr;
  uint_least16_t * uintLeastSixteenPtr;
  uint_least32_t * uintLeastThirtyTwoPtr;
  uint_least64_t * uintLeastSixtyFourPtr;
  uintmax_t      * uintMaxPtr;
  uintptr_t      * uintPtrTPtr;


  bool     boolVal;
  short    shortVal;
  char     charVal;
  int      intVal;
  long     longVal;
  float    floatVal;
  double   doubleVal;
  void   * voidPtr;
  bool   * boolPtr;
  short  * shortPtr;
  char   * charPtr;
  int    * intPtr;
  long   * longPtr;
  float  * floatPtr;
  double * doublePtr;


} allValues;


typedef struct StackFrame {
  union allValues value;
} StackFrame;


typedef struct Stack {
  StackFrame * frames;
  int64_t size;
} Stack;


bool stackIsAlive(const Stack *);
bool framesAreAlive(const Stack *);
bool stackIsDead(const Stack *);
bool framesAreDead(const Stack *);


void push(Stack *, union allValues);
union allValues pop(Stack *);
union allValues peek(const Stack *);


void printStackFrames(const Stack *);


int main()
{
  Stack * stack = NULL;
  stack         = malloc(sizeof(Stack));


  if (stackIsDead(stack))
  {
    printf("Stack could not be malloc'ed. exit(1)...\n");
    exit(1);
  }


  stack->frames = NULL;


  for (int i = 0; i < 10000; ++i)
  {
    if (i % 2 == 0)
    {
      float j = (float) i;
      push(stack, (union allValues) j);
    }
    else 
    {
      push(stack, (union allValues) i);
    }
  }

  for (int i = 0; i < 10000; ++i)
  {
    printf("%f\n", peek(stack).floatVal);
    pop(stack);
  }
  
  /*
  push(stack, (union allValues) -5);
  push(stack, (union allValues) 5L);
  push(stack, (union allValues) ((float) 200.0) );
  push(stack, (union allValues) ((double) 200.0) );
  push(stack, (union allValues) 'A');
  push(stack, (union allValues) "what is going on?");
  */

  /*
  pop(stack);
  printStackFrames(stack);
  pop(stack);
  printStackFrames(stack);
  pop(stack);
  printStackFrames(stack);
  pop(stack);
  printStackFrames(stack);
  pop(stack);
  printStackFrames(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  */

  peek(stack); // Should display error message to confirm it works properly
  peek(stack);
  
  free(stack->frames);
  stack->frames = NULL;
  stack->size = 0L;
  free(stack);
  stack = NULL;
  


  return 0;
}


bool stackIsAlive(const Stack * stack)
{
  return stack != NULL;
}


bool framesAreAlive(const Stack * stack)
{
  if (stack == NULL)
  {
    return false;
  }

  return stack->frames != NULL;
}


bool stackIsDead(const Stack * stack)
{
  return stack == NULL;
}


bool framesAreDead(const Stack * stack)
{
  if (stack == NULL)
  {
    return true;
  }

  return stack->frames == NULL;
}


void push(Stack * stack, union allValues value)
{
  if (stackIsDead(stack))
  {
    printf("Stack is Dead == NULL. Could not push a value to a Stack Frame...\n");
    return;
  }


  if (framesAreDead(stack))
  {
    stack->frames = malloc( ++stack->size * sizeof(StackFrame) );


    if (framesAreDead(stack))
    {
      printf("StackFrames could not be malloc'ed. exit(1)...\n");
      exit(1);
    }


    stack->frames[stack->size - SIZE_OFFSET].value = value;
    return;
  }


  StackFrame * newFrames = realloc( stack->frames, ++stack->size * sizeof(StackFrame) );


  if (newFrames == NULL)
  {
    printf("StackFrames could not be realloc'ed. exit(1)...\n");
    exit(1);
  }
  else
  {
    stack->frames = newFrames;
    stack->frames[stack->size - SIZE_OFFSET].value = value;
    return;
  }
}


union allValues pop(Stack * stack)
{
  if (stackIsDead(stack))
  {
    printf("Stack is Dead == NULL. Could not POP a value from a StackFrame. returning -1...\n");
    return (union allValues) -1;
  }

  if (framesAreDead(stack))
  {
    printf("StackFrames == NULL. Could not POP a value from a StackFrame. returning -1...\n");
    return (union allValues) -1;
  }


  union allValues value = stack->frames[stack->size - SIZE_OFFSET].value;


  StackFrame * newFrames = NULL;


  if (stack->size - SIZE_OFFSET == 0L)
  {
    --stack->size;
    newFrames = realloc( stack->frames, 0 * sizeof(StackFrame) );
    stack->frames = newFrames;
    return value;
  }
  else if (stack->size - SIZE_OFFSET < 0L)
  {
    printf("StackFrames == NULL. Could not POP a value from a StackFrame. returning -1...\n");
    return (union allValues) -1;
  }
  else
  {
    newFrames = realloc( stack->frames, --stack->size * sizeof(StackFrame) );
  }


  stack->frames = newFrames;
  return value;
}


union allValues peek(const Stack * stack)
{
  if (stackIsDead(stack))
  {
    printf("Stack is Dead == NULL. Could not PEEK a value from a StackFrame. returning -1...\n");
    return (union allValues) -1;
  }


  if (framesAreDead(stack))
  {
    printf("StackFrames == NULL. Could not PEEK a value from a StackFrame. returning -1...\n");
    return (union allValues) -1;
  }


  return stack->frames[stack->size - SIZE_OFFSET].value;
}


void printStackFrames(const Stack * stack)
{
  if (stack == NULL)
  {
    printf("Stack is Dead == NULL. Cannot print...\n");
    return;
  }


  if (stack->frames == NULL)
  {
    printf("StackFrames are Dead == NULL. Cannot print...\n");
    return;
  }


  for (long i = 0L; i < stack->size; ++i)
  {
    if (i == stack->size - SIZE_OFFSET)
    {
      printf("\n");      
      printf("Stack Frame %ld ->\n", i + SIZE_OFFSET);
      printf("                  integer: %d\n",          stack->frames[i].value.intThirtyTwo);
      printf("                  long: %ld\n",            stack->frames[i].value.intSixtyFour);
      printf("                  unsigned integer: %u\n", stack->frames[i].value.uintThirtyTwo);
      printf("                  unsigned long: %lu\n",   stack->frames[i].value.uintSixtyFour);
      printf("                  float: %f\n",            stack->frames[i].value.floatVal);
      printf("                  double: %f\n",           stack->frames[i].value.doubleVal);
      printf("                  pointer: %p\n",          stack->frames[i].value.voidPtr);
      printf("                  char: %c\n",             stack->frames[i].value.charVal);
      printf("                  char *: %p\n",           stack->frames[i].value.charPtr);
      printf("\n");
      continue;
    }

    printf("\n");
    printf("Stack Frame %ld ->\n", i + SIZE_OFFSET);
    printf("                  integer: %d\n",          stack->frames[i].value.intThirtyTwo);
    printf("                  long: %ld\n",            stack->frames[i].value.intSixtyFour);
    printf("                  unsigned integer: %u\n", stack->frames[i].value.uintThirtyTwo);
    printf("                  unsigned long: %lu\n",   stack->frames[i].value.uintSixtyFour);
    printf("                  float: %f\n",            stack->frames[i].value.floatVal);
    printf("                  double: %f\n",           stack->frames[i].value.doubleVal);
    printf("                  pointer: %p\n",          stack->frames[i].value.voidPtr);
    printf("                  char: %c\n",             stack->frames[i].value.charVal);
    printf("                  char *: %p\n",           stack->frames[i].value.charPtr);
  }
}