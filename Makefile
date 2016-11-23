CCC = g++
LEX = flex
YACC = bison
CFLAGS = -Wall -std=c++11
LEXFLAGS = -Wno-unused

YACCDEBUG = -vtd

OBJS = main.o ast.o parse.tab.o lex.yy.o manager.o

run: $(OBJS)
	$(CCC) $(CFLAGS) -o run $(OBJS)

main.o: main.cpp parse.y scan.l parse.tab.cpp lex.yy.cpp
	$(CCC) $(CFLAGS) -c main.cpp

parse.tab.cpp: parse.y model/ast.h
	$(YACC) $(YACCDEBUG) -oparse.tab.cpp -d parse.y

manager.o: controller/manager.cpp controller/manager.h
	$(CCC) $(CFLAGS) -c controller/manager.cpp

ast.o: model/ast.cpp model/ast.h
	$(CCC) $(CFLAGS) -c model/ast.cpp

parse.tab.o: parse.tab.cpp
	$(CCC) $(CFLAGS) -c parse.tab.cpp

lex.yy.cpp: scan.l parse.tab.o
	$(LEX) -olex.yy.cpp scan.l

lex.yy.o: lex.yy.cpp
	$(CCC) $(CFLAGS) $(LEXFLAGS) -c lex.yy.cpp
	
clean:
	rm -f run *.o parse.tab.cpp lex.yy.cpp *.gch
	rm -f parse.tab.* parse.output
