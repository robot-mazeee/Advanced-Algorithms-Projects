from matplotlib import pyplot as plt
import subprocess, time

# fazer pip install matplotlib no termianal/shell/CommandPrompt

# MUDAR O NOME DO VOSSO PROJETO NA LINHA 16 de resto ta tudo 
# feito por vcs só têm de correr este ficheiro na diretoria
# onde tem o vosso projeto e gerador (com nome gera.cpp)

# numero de inputs que querem (ajustável)
num_inputs = 5

generator_path = 'gera.cpp'
generator_exe = 'gerador'
project_path = 'Projeto2.cpp'
project_exe = 'proj'
input_file = 'input.in'

def calculate_comp(n, m, l):
    # retornar função de complexidade, por exemplo:
    # se temos O(n^4m^2) return n**4 * m**2
    return l**3

def generate_input_size():
    input_size = []
    n_values = []
    m_values = []
    l_values = []

    n = 50
    div = n // num_inputs
    for _ in range(num_inputs):
        n_values.append(div)
        div += div

    m = 100
    div = m // num_inputs
    for _ in range(num_inputs):
        m_values.append(div)
        div += div

    l = 10
    div = l // num_inputs
    for _ in range(num_inputs):
        l_values.append(div)
        div += div

    m_values = sorted(m_values)
    n_values = sorted(n_values)
    l_values = sorted(l_values)
    
    for i in range(num_inputs):
        input_size.append([n_values[i], m_values[i], l_values[i]])
    
    return input_size

def run(input_size):
    times = []

    # compilar o gerador
    subprocess.run(["g++", generator_path, "-o", generator_exe])

    # executar o gerador com n e m e l
    for size in input_size:
        n = size[0]
        m = size[1]
        l = size[2]

        # executar o gerador
        with open(input_file, "w") as file:
            program_args = [str(n), str(m), str(l)]
            subprocess.run(["./" + generator_exe] + program_args, stdout=file)

        # calcular tempo do ficheiro de input (tambem corre o programa)
        time = round(calculate_time(), 2)
        times.append(time)

    return times

def calculate_time():
    # compilar o projeto
    subprocess.run(["g++", project_path, "-o", project_exe])

    # abrir o ficheiro gerado
    with open("input.in", "r") as file:
        # tempo de inicio
        start_time = time.perf_counter()
        # correr o projeto
        subprocess.run(["./" + project_exe], stdin=file, stdout=subprocess.DEVNULL, text=True)
        # tempo de fim
        end_time = time.perf_counter()

    return end_time - start_time

def f(input_size):
    comp = []

    for size in input_size:
        comp.append(calculate_comp(size[0], size[1], size[2]))

    return comp

def main():
    # tamanho do input [n, m, l]
    input_size = generate_input_size()
    print(input_size)
    input_size = [[10, 20, 5]]
    # calcular tempo de cada input
    times = run(input_size)
    # calcular f(n, m)
    comp = f(input_size)

    print('Complexidade:', comp)
    print('Time:', times)

    # desenhar os pontos
    plt.scatter(comp, times, color="blue")
    # desenhar a linha
    plt.plot(comp, times)
    plt.xlabel('f(n,m)')
    plt.ylabel('Time (s)')
    plt.title('Análise teórica')
    plt.show()

main()