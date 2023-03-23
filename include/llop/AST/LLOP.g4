grammar LLOP;

program: (classDecl | staticDecl | interfaceDecl)*
;


classDecl: CLASS IDENTIFIER '(' IDENTIFIER ')' '[' IDENTIFIER* ']'
BEGIN
    (fieldDecl)*
    (funcDecl)*
END
;

staticDecl: STATIC IDENTIFIER
BEGIN
    (fieldDecl)*
    (funcDecl)*
END
;

interfaceDecl: INTERFACE
BEGIN
    (funcHeader)*
END
;

fieldDecl: VAR IDENTIFIER ':' type
;

funcDecl: funcHeader blockStatement
;


funcHeader: FUNC IDENTIFIER paramList '->' type
;

stmt: blockStatement
    | ifStatement
    | whileStatement
    | assignStatement
    | variableDeclStatement
    | returnStatement
;

expr: IDENTIFIER argumentList   	#funCallExpr
    | expr '.' expr 			#accessExpr
    | SUB expr                      #negExpr
    | expr op=(MUL | DIV) expr 		#multiplicativeExpr
    | expr op=(ADD | SUB) expr 		#additiveExpr
    | expr op=(EQ | NE | GT) expr 	#relationalExpr
    | expr op= expr 		        #equalityExpr
    | expr '[' expr ']'             #arrayRefExpr
    | IDENTIFIER				    #varExpr
    | NUMBER					    #numExpr
    | NEW type argumentList         #newExpr
    | NULL                          #nullExpr
    | '(' expr ')'				    #parenExpr
;

blockStatement: BEGIN (stmt)* END
;

ifStatement: IF '(' expr ')' THEN stmt (ELSE stmt)
;

whileStatement: WHILE '(' expr ')' stmt
;

returnStatement: RETURN expr
;

argumentList : '(' (expr (',' expr)*)? ')'
;

paramList : '(' (param (',' param)*)? ')'
;

param: IDENTIFIER ':' type
;

assignStatement: expr '=' expr
;

variableDeclStatement: VAR IDENTIFIER ':' type
;

type: valueType | referenceType
;

valueType : INT
;

referenceType :
    IDENTIFIER #simpleType
    | ARRAY '<' referenceType '>' #arrayType
;




MUL : '*' ;
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;
GT  : '>' ;
EQ  : '==' ;
NE  : '!=' ;

NUMBER : [0-9]+ ;

NEW: 'NEW' ;
BEGIN : 'BEGIN' ;
END   : 'END' ;
CLSSS : 'CLASS' ;
INTERFACE: 'INTERFACE' ;
STATIC: 'STATIC';
FIELD: 'FIELD';
FUNC: 'FUNC';
NULL: 'NULL';

IF: 'IF' ;
THEN: 'THEN' ;
ELSE: 'ELSE' ;

WHILE: 'WHILE';
ARRAY: 'ARRAY';


RETURN: 'RETURN' ;
VAR: 'VAR' ;
INT: 'INT' ;

IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]* ;


// Ignore whitespace
WS : [ \t\n\r]+ -> skip ;

// This does not handle nested block comments.
BLOCKCOMMENT: '/*' .*? '*/' -> skip ;

COMMENT : '//' ~[\n\r]* -> skip ;