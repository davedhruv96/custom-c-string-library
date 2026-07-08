#ifndef GC_H
#define GC_H

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 10

typedef enum { OBG_INT, OBG_PAIR } ObjectType;

typedef struct sObject {
  struct sObject *next;
  ObjectType type;
  unsigned char marked;
  union {
    int value;
    struct {
      struct sObject *head;
      struct sObject *tail;
    };
  };
} Object;

typedef struct VM VM;

void assert(int condition, char *message);

VM *newVM();

void gc(VM *vm);

void push(VM *vm, Object *value);

Object *pop(VM *vm);

Object *newObject(VM *vm, ObjectType type);

void pushInt(VM *vm, int valToPush);

void markAll(VM *vm);

void sweep(VM *vm);

void freeVM(VM *vm);

void test1();

void test2();

void test3();

void test4();

void perftest();

#endif
