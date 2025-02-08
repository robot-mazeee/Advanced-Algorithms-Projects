import pulp as p

# ola stor :)

'''
1) variaveis do problema

n fábricas, F ={f1,...,fn}
m países, P ={p1,...,pm}
t crianças C ={c1,...,ct}

2) restricoes das variaveis

pminj <= num de presentes de pais pj <= pmaxj
stock de brinquedos disponíveis para distribuição da fabrica fi <= fmaxi

3) funcao objetivo

número máximo de crianças que poderão ver os seus pedidos satisfeitos 
respeitando as restrições do problema
'''

# problema
problem = p.LpProblem("P3", p.LpMaximize)

# numero total de fabricas, paises e criancas
n, m, t = input().split()
n = int(n)
m = int(m)
t = int(t)

# names
n_names = [str(i) for i in range(1, n+1)]
t_names = [str(i) for i in range(1, t+1)]

# dicionarios
fabrica_to_pais = {}
fabrica_max = {}
pais_min = {}
pais_max = {}

pais_to_export = {var: 0 for var in range(1, m+1)}
pais_to_non_export = {var: 0 for var in range(1, m+1)}
fabrica_to_stock = {var: 0 for var in n_names}

# loop das fabricas
for _ in range(n):
    # fabrica, pais, stock
    fabrica, pais, stock = input().split()
    fabrica_max[fabrica] = int(stock)
    fabrica_to_pais[fabrica] = pais

# loops dos paises
for _ in range(m):
    pais, pmaxj, pminj = input().split()
    pais_min[int(pais)] = int(pminj)
    pais_max[int(pais)] = int(pmaxj)

# loop das criancas
funcao_objetivo = 0
for _ in range(t):
    crianca, pais, *fabricas = input().split()

    x = p.LpVariable.dicts('x', [(int(crianca), int(fabrica)) for fabrica in fabricas], 0, 1, p.LpBinary)

    gifts_received = 0
    for fabrica in fabricas:
        value = x[(int(crianca), int(fabrica))]
        gifts_received += value
        funcao_objetivo += value
        fabrica_to_stock[fabrica] += value
        pais_to_non_export[int(pais)] += value
        if fabrica_to_pais[fabrica] != pais:
            pais_to_export[int(fabrica_to_pais[fabrica])] += value
            
    problem += gifts_received <= 1

for pais in range(1, m+1):
    problem += pais_to_non_export[pais] >= pais_min[pais]
    problem += pais_to_export[pais] <= pais_max[pais]

for fabrica in n_names:
    problem += fabrica_to_stock[fabrica] <= fabrica_max[fabrica]

# Função objetivo
problem += funcao_objetivo

problem.solve(p.PULP_CBC_CMD(msg=False))

if p.LpStatus[problem.status] == 'Optimal':
    print(int(p.value(problem.objective)))
else:
    print(-1)