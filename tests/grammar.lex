0,(^var| var |\nvar |\n\rvar )
1,(=)
2,(;)
3,(\+)
4,(-)
5,(^print| print |\nprint |\n\rprint )
6,(\()
7,(\))
8,(\n|\n\r)
9,([\s\S]*?)( |^var| var |\nvar |\n\rvar |=|;|\+|-|^print| print |\nprint |\n\rprint |\(|\)|\(.+?\)|\n|\r|\n\r)

expr -> `regex `
for -> for ( `expr` ; `expr` ; `expr` ) `expr`
id -> `regex`