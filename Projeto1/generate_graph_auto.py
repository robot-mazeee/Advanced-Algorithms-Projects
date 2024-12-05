from matplotlib import pyplot as plt
import numpy as np
import subprocess, random, time

# fazer pip install matplotlib no termianal/shell/CommandPrompt

# MUDAR O NOME DO VOSSO PROJETO NA LINHA 15 de resto ta tudo 
# feito por vcs só têm de correr este ficheiro na diretoria
# onde tem o vosso projeto e gerador

# numero de inputs que querem (ajustável)
num_inputs = 15

generator_path = 'gerador.cpp'
generator_exe = 'gerador'
project_path = 'Projeto1.cpp'
project_exe = 'proj'
input_file = 'input.in'

def calculate_comp(n, m):
    # retornar função de complexidade, por exemplo:
    # se temos O(n^4m^2) return n**4 * m**2
    return m**3 * n**2

def generate_input_size():
    input_size = []
    n_values = []
    m_values = []

    for _ in range(num_inputs):
        n = random.randint(1, 100)
        m = random.randint(1, 1000)
        n_values.append(n)
        m_values.append(m)

    m_values = sorted(m_values)
    n_values = sorted(n_values)
    
    for i in range(num_inputs):
        input_size.append([n_values[i], m_values[i]])
    
    # print(input_size)
    return input_size

def run(input_size):
    times = []

    # compilar o gerador
    subprocess.run(["g++", generator_path, "-o", generator_exe])

    # executar o gerador com n e m
    for size in input_size:
        n = size[0]
        m = size[1]

        # executar o gerador
        with open(input_file, "w") as file:
            program_args = [str(n), str(m)]
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
        comp.append(calculate_comp(size[0], size[1]))

    return comp

def main():
    # tamanho do input [n, m]
    input_size = generate_input_size()
    input_size = [[5, 50], [10, 100], [15, 150], [20, 200], [25, 250], [30, 300], [35, 350], [40, 400], [45, 450], [50, 500], [55, 550], [60, 600], [65, 650], [70, 700], [75, 750], [80, 800], [85, 850], [90, 900], [95, 950], [100, 1000]]
    # calcular tempo de cada input
    times = run(input_size)
    # calcular f(n, m)
    comp = f(input_size)

    # Degree 1 para ser linear
    coefficients = np.polyfit(np.array(comp), np.array(times), 2)
    slope, intercept = coefficients
    # equação da linha
    y_pred = slope * np.array(comp) + intercept

    print(comp)
    print(times)

    # desenhar os pontos
    plt.scatter(comp, times, color="blue")
    # desenhar a linha
    plt.plot(comp, y_pred)
    plt.xlabel('f(n,m)')
    plt.ylabel('Time (s)')
    plt.title('Análise teórica')
    plt.show()

main()