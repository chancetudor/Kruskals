OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o da-0-4.o integer.o
CDAOBJS = cda.o cda-0-0.o integer.o
QOBJS = queue.o cda.o queue-0-0.o integer.o
SETOBJS = set.o da.o set-0-2.o integer.o real.o string.o
BSTOBJS = bst.o queue.o cda.o bst-0-4.o integer.o real.o tnode.o
RBTOBJS = bst.o queue.o cda.o rbt-0-0.o integer.o real.o rbt.o tnode.o gst.o
KOBJS = kruskal2.o set.o da.o string.o integer.o scanner.o queue.o cda.o bst.o rbt.o gst.o tnode.o

all : da cda queue bst rbt set kruskal

set : $(SETOBJS)
	gcc $(LOPTS) $(SETOBJS) -o set
da : $(DAOBJS)
	gcc $(LOPTS) $(DAOBJS) -o da
cda : $(CDAOBJS)
	gcc $(LOPTS) $(CDAOBJS) -o cda
queue : $(QOBJS)
	gcc $(LOPTS) $(QOBJS) -o queue
bst : $(BSTOBJS)
	gcc $(LOPTS) $(BSTOBJS) -o bst
rbt : $(RBTOBJS)
	gcc $(LOPTS) $(RBTOBJS) -o rbt
kruskal : $(KOBJS)
	gcc $(LOPTS) $(KOBJS) -o kruskal

set.o: set.c set.h
	gcc $(OOPTS) set.c
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c
real.o : real.c real.h
	gcc $(OOPTS) real.c
string.o : string.c string.h
	gcc $(OOPTS) string.c
scanner.o:	scanner.c scanner.h
	gcc $(OOPTS) scanner.c
da.o: da.c
	gcc $(OOPTS) da.c
tnode.o : tnode.c tnode.h
	gcc $(OOPTS) tnode.c
cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c
queue.o : queue.c queue.h cda.h
	gcc $(OOPTS) queue.c
bst.o : bst.c bst.h queue.h
	gcc $(OOPTS) bst.c
gst.o : gst.c gst.h bst.h tnode.h queue.h
	gcc $(OOPTS) gst.c
rbt.o : rbt.c rbt.h
	gcc $(OOPTS) rbt.c
kruskal2.o: kruskal2.c set.h da.h string.h integer.h
	gcc $(OOPTS) kruskal2.c


set-0-2.o : set-0-2.c set.h da.h integer.h real.h string.h
	gcc $(OOPTS) set-0-2.c
da-0-4.o : da-0-4.c da.h
	gcc $(OOPTS) da-0-4.c
cda-0-0.o : cda-0-0.c cda.h
	gcc $(OOPTS) cda-0-0.c
queue-0-0.o : queue-0-0.c queue.h cda.h
	gcc $(OOPTS) queue-0-0.c
test-bst.o : test-bst.c integer.h string.h queue.h bst.h real.h
	gcc $(OOPTS) test-bst.c
bst-0-4.o : bst-0-4.c integer.h string.h queue.h bst.h real.h
	gcc $(OOPTS) bst-0-4.c
rbt-0-0.o : rbt-0-0.c rbt.h integer.h real.h string.h
	gcc $(OOPTS) rbt-0-0.c


test : kruskal #set bst rbt cda queue
	#./da
	#./cda
	#./queue
	#./bst
	#./rbt
	#./set
	./kruskal g-0-0
	#./kruskal g-0-4

valgrind : set #kruskal bst rbt cda queue
	#valgrind --leak-check=full ./da
	#valgrind --leak-check=full ./cda
	#valgrind --leak-check=full ./queue
	#valgrind --leak-check=full bst
	#valgrind --leak-check=full rbt
	valgrind --leak-check=full set
	valgrind --leak-check=full kruskal

clean :
	rm -f $(BSTOBJS) $(RBTOBJS) $(QOBJS) $(DAOBJS) $(CDAOBJS) $(KOBJS) $(SETOBJS) \ #$(OKRUSH) $(NKRUSK)  \
	bst da cda queue rbt set kruskal