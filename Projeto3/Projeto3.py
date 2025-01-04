import pulp as p

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

fabrica_to_pais = {}
fabricas_crianca = {}
crianca_to_pais = {}

# numero total de fabricas, paises e criancas
n, m, t = input().split()
n = int(n)
m = int(m)
t = int(t)

# names
n_names = [str(i) for i in range(1, n+1)]
m_names = [str(i) for i in range(1, m+1)]
t_names = [str(i) for i in range(1, t+1)]

# vars
n_vars = p.LpVariable.dicts("fabricas", n_names, 0, None, p.LpInteger)
m_vars = p.LpVariable.dicts("paises", m_names, None, None, p.LpInteger)
t_vars = p.LpVariable.dicts("criancas", t_names, 0, None, p.LpInteger)
x = p.LpVariable.dicts('x', (t_names, n_names), 0, 1, p.LpBinary)
x = {(t, n): x[t][n] for t in t_names for n in n_names}

# loop das fabricas
for _ in range(n):
    # fabrica, pais, stock
    fabrica, pais, stock = input().split()
    n_vars[fabrica].upBound = int(stock)
    fabrica_to_pais[fabrica] = pais

# loops dos paises
for _ in range(m):
    pais, pmaxj, pminj = input().split()
    m_vars[pais].lowBound = int(pminj)
    m_vars[pais].upBound = int(pmaxj)

# loop das criancas
for _ in range(t):
    crianca, pais, *fabricas = input().split()
    fabricas_crianca[crianca] = fabricas
    crianca_to_pais[crianca] = pais
    problem += p.lpSum(x[(crianca, fabrica)] for fabrica in fabricas) <= 1

for fabrica in n_names:
    problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names if fabrica in fabricas_crianca[crianca]) <= n_vars[fabrica].upBound

for pais in m_names:    
    problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if crianca_to_pais[crianca] == pais) >= m_vars[pais].lowBound 

    problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if crianca_to_pais[crianca] != pais and fabrica_to_pais[fabrica] == pais) <= m_vars[pais].upBound

# Função objetivo
problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca])

problem.solve(p.PULP_CBC_CMD(msg=False))

if p.LpStatus[problem.status] == 'Optimal':
    print(int(p.value(problem.objective)))
else:
    print(-1)
