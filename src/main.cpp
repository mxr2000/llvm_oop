#include <iostream>
#include <fstream>
#include "llop/Parser/ASTBuilder.h"
#include "LLOPLexer.h"
#include "llop/CodeGen/Context.h"


int main(int argc, char *argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
    antlr4::ANTLRInputStream input(stream);
    LLOPLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LLOPParser parser(&tokens);
    ASTBuilder builder(parser.program());
    Program* program = builder.build();
    Context context(program);
    context.output("a");
    return 0;
}


// 1. return type of main
// 2. return type of init function
// 3. child call super init
// 4. assign left pointer
