# import pulp as p

# '''
# 1) variaveis do problema

# n fábricas, F ={f1,...,fn}
# m países, P ={p1,...,pm}
# t crianças C ={c1,...,ct}

# 2) restricoes das variaveis

# pminj <= num de presentes de pais pj <= pmaxj
# stock de brinquedos disponíveis para distribuição da fabrica fi <= fmaxi

# 3) funcao objetivo

# número máximo de crianças que poderão ver os seus pedidos satisfeitos 
# respeitando as restrições do problema
# '''

# # problema
# problem = p.LpProblem("P3", p.LpMaximize)

# fabrica_to_pais = {}
# fabricas_crianca = {}
# crianca_to_pais = {}

# # numero total de fabricas, paises e criancas
# n, m, t = input().split()
# n = int(n)
# m = int(m)
# t = int(t)

# # names
# n_names = [str(i) for i in range(1, n+1)]
# m_names = [str(i) for i in range(1, m+1)]
# t_names = [str(i) for i in range(1, t+1)]

# # vars
# n_vars = p.LpVariable.dicts("fabricas", n_names, 0, None, p.LpInteger)
# m_vars = p.LpVariable.dicts("paises", m_names, None, None, p.LpInteger)
# t_vars = p.LpVariable.dicts("criancas", t_names, 0, None, p.LpInteger)
# x = p.LpVariable.dicts('x', (t_names, n_names), 0, 1, p.LpBinary)
# x = {(t, n): x[t][n] for t in t_names for n in n_names}

# for _ in range(n):
#     # fabrica, pais, stock
#     fabrica, pais, stock = input().split()
#     n_vars[fabrica].upBound = int(stock)
#     fabrica_to_pais[fabrica] = pais

# for _ in range(m):
#     pais, pmaxj, pminj = input().split()
#     m_vars[pais].lowBound = int(pminj)
#     m_vars[pais].upBound = int(pmaxj)

# for _ in range(t):
#     crianca, pais, *fabricas = input().split()
#     fabricas_crianca[crianca] = fabricas
#     crianca_to_pais[crianca] = pais

# for crianca in t_names:
#     problem += p.lpSum(x[(crianca, fabrica)] for fabrica in fabricas_crianca[crianca]) <= 1

# for fabrica in n_names:
#     problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names if fabrica in fabricas_crianca[crianca]) <= n_vars[fabrica].upBound

# for pais in m_names:
#     problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if fabrica_to_pais[fabrica] == pais) >= m_vars[pais].lowBound
#     problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if fabrica_to_pais[fabrica] == pais) <= m_vars[pais].upBound

# # for pais in m_names:    
# #     problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if crianca_to_pais[crianca] == pais) >= m_vars[pais].lowBound  # Limite mínimo de distribuição
        
# #     problem += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if crianca_to_pais[crianca] == pais and fabrica_to_pais[fabrica] != pais) <= m_vars[pais].upBound  # Limite máximo de distribuição

# problem.solve()

import pulp as p

# # Ler os dados de entrada
n, m, t = map(int, input().split())  # número de fábricas, países e crianças

# Fábricas
# fabrica_info = {}
# for _ in range(n):
#     i, j, fmaxi = map(int, input().split())
#     fabrica_info[i] = {'pais': j, 'estoque': fmaxi}

# # Países
# pais_info = {}
# for _ in range(m):
#     j, pmaxj, pminj = map(int, input().split())
#     pais_info[j] = {'pmax': pmaxj, 'pmin': pminj}

# # Crianças
# crianca_info = {}
# for _ in range(t):
#     k, j, *fabricas = map(int, input().split())
#     crianca_info[k] = {'pais': j, 'fabricas': fabricas}

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

# Definir o problema de otimização
problema = p.LpProblem("Distribuicao_Brinquedos", p.LpMaximize)

# Variáveis binárias: x[crianca][fabrica] indica se a criança recebe um brinquedo dessa fábrica
x = p.LpVariable.dicts('x', (t_names, n_names), cat='Binary')
x = {(t, n): x[t][n] for t in t_names for n in n_names}
print(x)

# # Função objetivo: Maximizar o número de crianças satisfeitas
problema += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca])

# # Restrições:
# 1. Respeitar a capacidade de estoque das fábricas
for fabrica in n_names:
    problema += p.lpSum(x[(crianca, fabrica)] for crianca in t_names if fabrica in fabricas_crianca[crianca]) <= n_vars[fabrica].upBound

# 2. Respeitar os limites de distribuição de cada país
for pais in m_names:
    problema += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[crianca] if fabrica_to_pais[fabrica] == pais) >= m_vars[pais].lowBound
    problema += p.lpSum(x[(crianca, fabrica)] for crianca in t_names for fabrica in fabricas_crianca[fabrica] if fabrica_to_pais[fabrica] == pais) <= m_vars[pais].upBound

# 3. Cada criança pode receber no máximo um brinquedo de uma fábrica
for crianca in t_names:
    problema += p.lpSum(x[(crianca, fabrica)] for fabrica in fabricas_crianca[crianca]) <= 1

# Resolver o problema
problema.solve()

# Exibir os resultados
if p.LpStatus[problema.status] == 'Optimal':
    print("Solução ótima encontrada:")
    # for k in range(1, t+1):
    #     for f in crianca_info[k]['fabricas']:
    #         if p.value(x[k][f]) == 1:
    #             print(f'Criança {k} recebe brinquedo da fábrica {f}')
else:
    print("Não foi possível encontrar uma solução ótima.")





# import pulp

# # Função para resolver o problema
# def distribuir_brinquedos(n, m, t, dados_fábricas, dados_pais, pedidos_crianças):
#     # Criando o problema de otimização
#     prob = pulp.LpProblem("Distribuicao_Brinquedos", pulp.LpMaximize)

#     # Definindo as variáveis de decisão: x_ijk (binária)
#     x = pulp.LpVariable.dicts("x", ((i, k, j) for i in range(n) for k in range(t) for j in range(m)), cat='Binary')

#     # Função objetivo: maximizar o número de brinquedos distribuídos
#     prob += pulp.lpSum(x[i, k, j] for i in range(n) for k in range(t) for j in range(m))

#     # Restrição de capacidade das fábricas
#     for i in range(n):
#         prob += pulp.lpSum(x[i, k, j] for k in range(t) for j in range(m)) <= dados_fábricas[i][2], f"Capacidade_Fábrica_{i+1}"

#     # Restrição de limite de exportação dos países
#     for j in range(m):
#         prob += pulp.lpSum(x[i, k, j] for i in range(n) for k in range(t)) <= dados_pais[j][1], f"Limite_Exportacao_Pais_{j+1}"

#     # Restrição de demanda mínima de brinquedos por país
#     for j in range(m):
#         prob += pulp.lpSum(x[i, k, j] for i in range(n) for k in range(t)) >= dados_pais[j][2], f"Demanda_Minima_Pais_{j+1}"

#     # Restrição de que cada criança pode receber no máximo um brinquedo
#     for k in range(t):
#         prob += pulp.lpSum(x[i, k, j] for i in range(n) for j in range(m)) <= 1, f"Max_1_Brinquedo_Criança_{k+1}"

#     # Resolvendo o problema
#     prob.solve()

#     # Exibindo os resultados
#     resultados = []
#     for i in range(n):
#         for k in range(t):
#             for j in range(m):
#                 if pulp.value(x[i, k, j]) == 1:
#                     resultados.append(f"Criança {k+1} recebeu brinquedo da fábrica {i+1} (País {j+1})")
    
#     return resultados

# # Exemplo de entrada
# n = 3
# m = 2
# t = 5
# dados_fábricas = [(1, 1, 10), (2, 1, 20), (3, 2, 30)]
# dados_pais = [(1, 15, 5), (2, 30, 10)]
# pedidos_crianças = [(1, 1, [1, 2]), (2, 1, [1, 3]), (3, 1, [2, 3]), (4, 2, [3, 1]), (5, 2, [1, 2])]

# # Chamada da função
# resultados = distribuir_brinquedos(n, m, t, dados_fábricas, dados_pais, pedidos_crianças)

# # Exibindo o resultado
# for resultado in resultados:
#     print(resultado)