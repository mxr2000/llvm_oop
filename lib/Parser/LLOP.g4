grammar LLOP;

program: (classDecl | staticDecl | interfaceDecl)+
;


classDecl: 'CLASS' IDENTIFIER '(' IDENTIFIER ')' '[' (IDENTIFIER)* ']'
BEGIN
    (fieldDecl | funcDecl)*
END
;

staticDecl: STATIC IDENTIFIER
BEGIN
    (fieldDecl)*
    (funcDecl)*
END
;

interfaceDecl: INTERFACE IDENTIFIER // ('(' IDENTIFIER ')')? not time to implement this
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
    | outputStatement
    | expr
;

expr: referenceType '::' expr       #staticAccessExpr
    | IDENTIFIER argumentList   	#funCallExpr
    | expr'.' '[' referenceType ']' #typeCoercionExpr
    | expr '[' expr ']'             #arrayIndexExpr
    | expr '.' expr 			    #accessExpr
    | SUB expr                      #negExpr
    | expr op=(MUL | DIV) expr 		#multiplicativeExpr
    | expr op=(ADD | SUB) expr 		#additiveExpr
    | expr op=(EQ | NE | GT | LT | LE |GE) expr 	#relationalExpr
    | NOT expr                      #notExpr
    | expr AND expr                 #andExpr
    | expr OR expr                  #orExpr
    | expr IS referenceType         #isExpr
    | IDENTIFIER				    #varExpr
    | NUMBER					    #numExpr
    | val=(TRUE | FALSE)            #boolLiteralExpr
    | NEW referenceType argumentList#newExpr
    | NEW arrayType '(' expr ')'    #newArrayExpr
    | NIL                           #nullExpr
    | SUPER                         #superExpr
    | SELF                          #selfExpr
    | '(' expr ')'				    #parenExpr
;

outputStatement: OUTPUT expr
;

blockStatement: BEGIN (stmt)* END
;

ifStatement: IF '(' expr ')' THEN stmt (ELSE stmt)?
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

type: valueType | referenceType | voidType | arrayType
;

valueType : INT | LONG | CHAR | BOOL
;

referenceType :
    IDENTIFIER
    // | ARRAY '<' referenceType '>' #arrayType
;

voidType : VOID
;

arrayType : '[' type ']'
;




MUL : '*' ;
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;
GT  : '>' ;
LT  : '<' ;
GE  : '>=' ;
LE  : '<=' ;
EQ  : '==' ;
NE  : '!=' ;

AND : 'AND' ;
OR  : 'OR'  ;
NOT : 'NOT' ;

NUMBER : [0-9]+ ;

NEW: 'NEW' ;
BEGIN : 'BEGIN' ;
END   : 'END' ;
CLSSS : 'CLASS' ;
INTERFACE: 'INTERFACE' ;
STATIC: 'STATIC';
FIELD: 'FIELD';
FUNC: 'FUNC';
NIL: 'NIL';
IS: 'IS' ;
SUPER: 'SUPER';
SELF: 'SELF';
OUTPUT: 'OUTPUT';

IF: 'IF' ;
THEN: 'THEN' ;
ELSE: 'ELSE' ;

WHILE: 'WHILE';
ARRAY: 'ARRAY';


RETURN: 'RETURN' ;
VAR: 'VAR' ;
INT: 'Int' ;
BOOL: 'Bool' ;
LONG: 'Long' ;
CHAR: 'Char' ;
VOID: 'Void';

TRUE: 'TRUE' ;
FALSE: 'FALSE' ;

IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]* ;


// Ignore whitespace
WS : [ \t\n\r]+ -> skip ;

// This does not handle nested block comments.
BLOCKCOMMENT: '/*' .*? '*/' -> skip ;

COMMENT : '//' ~[\n\r]* -> skip ;
