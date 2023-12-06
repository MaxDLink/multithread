grammar FlowscriptGrammar;

// Parser rules
flowscript             : DIGRAPH ID '{' graph_content '}';
graph_content          : (node_definition | edge_definition)* ;
node_definition        : ID node_attrs ';' ;
node_attrs             : '[' attr_list ']' ;
attr_list              : attr (',' attr)* ;
attr                   : 'shape' '=' STRING {System.out.println($STRING.text); } | ID ;
edge_definition        : ID '->' ID edge_attrs? ';' ;
edge_attrs             : '[' a_list ']' ;
a_list                 : a_list_item (',' a_list_item)* ;
a_list_item            : ID '=' STRING ;
cluster_id             : 'cluster_' ID | ID ;

// Lexer rules
DIGRAPH                : 'digraph';
ID                     : [a-zA-Z_][a-zA-Z_0-9]* ;
STRING                 : '"' (~["\r\n\\] | '\\' .)* '"';
WS                     : [ \t\r\n]+ -> skip ;
