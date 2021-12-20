Log [elementos: 0]


ok
Log [elementos: 1]
[1;1.000000;0] 

ok
Log [elementos: 2]
[3;3.000000;0] [1;1.000000;1] 

ok
Log [elementos: 3]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] 

ok
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.000000;3] 

nok (5)
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.000000;3] 

nok (6)
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.000000;3] 

ok
Log [elementos: 4]
[0;15.000000;0] [3;3.000000;1] [2;2.000000;2] [1;1.000000;3] 

ok
Log [elementos: 4]
[0;15.000000;0] [3;4.000000;1] [2;2.000000;2] [1;1.000000;3] 

nok (9) - esperado, pois a nova prioridade nao eh maior
Log [elementos: 4]
[0;15.000000;0] [3;4.000000;1] [2;2.000000;2] [1;1.000000;3] 

nok (10) - esperado, elemento com id=4 nao existe
Log [elementos: 4]
[0;15.000000;0] [3;4.000000;1] [2;2.000000;2] [1;1.000000;3] 

Prioritario: 0, 15.000000
Log [elementos: 3]
[3;4.000000;0] [1;1.000000;1] [2;2.000000;2] 

Prioritario: 3, 4.000000
Log [elementos: 2]
[2;2.000000;0] [1;1.000000;1] 

Prioritario: 2, 2.000000
Log [elementos: 1]
[1;1.000000;0] 

Prioritario: 1, 1.000000
Log [elementos: 0]


Fila vazia (5)
Log [elementos: 0]


Fila vazia (6)
Log [elementos: 0]


Fila vazia (7)
Log [elementos: 0]


ok
Log [elementos: 1]
[1;1.000000;0] 

ok
Log [elementos: 2]
[3;3.000000;0] [1;1.000000;1] 

ok
Log [elementos: 3]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] 

ok
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.500000;3] 

nok (14)
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.500000;3] 



Reduzindo prioridade
nok (15)
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.500000;3] 

nok (16) - esperado, nova prioridade eh maior
Log [elementos: 4]
[3;3.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.500000;3] 

ok
Log [elementos: 4]
[3;2.000000;0] [1;1.000000;1] [2;2.000000;2] [0;0.500000;3] 

ok
Log [elementos: 4]
[2;2.000000;0] [1;1.000000;1] [3;1.500000;2] [0;0.500000;3] 

nok (19) - esperado, elemento com id=4 nao existe
Log [elementos: 4]
[2;2.000000;0] [1;1.000000;1] [3;1.500000;2] [0;0.500000;3] 
