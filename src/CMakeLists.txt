file(GLOB SOURCES queue.c rbtree.c stack.c)
add_library(rbtree STATIC ${SOURCES})