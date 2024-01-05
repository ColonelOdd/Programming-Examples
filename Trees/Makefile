#
# Makefile for Pset 5: Trees
#
# CPSC 223
# Fall 2023
#

CXX      = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -pedantic
LDFLAGS  = -g

all: bst avlt rbt

bst: main_bst.o BSTree.o BSTNode.o pretty_print.o
	${CXX} ${LDFLAGS} -o $@ $^

avlt: main_avlt.o AVLTree.o BSTNode.o pretty_print.o
	${CXX} ${LDFLAGS} -o $@ $^

rbt: main_rbt.o RBTree.o BSTNode.o pretty_print.o
	${CXX} ${LDFLAGS} -o $@ $^

clean:
	${RM} bst avlt rbt *.o *.dSYM

.PHONY: all clean
