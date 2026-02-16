#ifndef MACRO_H
#define MACRO_H

#define QUOTE(S) #S
#define CAT(A,B) A##B
#define FOREACH(TYPE,ITER,LLIST) for (TYPE ITER = LLIST; ITER != NULL; ITER=ITER->next)

#endif /* MACRO_H */