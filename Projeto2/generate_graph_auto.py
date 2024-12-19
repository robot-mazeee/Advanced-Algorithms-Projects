from matplotlib import pyplot as plt
import subprocess, time, math
import numpy as np

# fazer pip install matplotlib no termianal/shell/CommandPrompt

# MUDAR O NOME DO VOSSO PROJETO NA LINHA 16 de resto ta tudo 
# feito por vcs só têm de correr este ficheiro na diretoria
# onde tem o vosso projeto e gerador (com nome gera.cpp)

num_inputs = 50
generator_path = 'gera.cpp'
generator_exe = 'gerador'
project_path = 'Projeto2.cpp'
project_exe = 'proj'
input_file = 'input.in'

def calculate_comp(n, m, l):
    # retornar função de complexidade, por exemplo:
    # se temos O(n^4m^2) return n**4 * m**2
    # return n*l**2*math.log2(l)
    # return m
    return m * math.log2(n*l)

def generate_input_size():
    input_size = []
    for i in range(0, num_inputs):
        n = 50000+(i+1)*5000
        m = 100000+(i+1)*10000
        l = int(100+20*math.log(i+1))
        input_size.append([n, m, l])

    return input_size

# def generate_input_size():
#     input_size = []
#     n_values = []
#     m_values = []
#     l_values = []

#     n = 5000
#     const = n // num_inputs
#     for _ in range(num_inputs):
#         n_values.append(n)
#         n -= const

#     m = 10000
#     const = m // num_inputs
#     for _ in range(num_inputs):
#         m_values.append(m)
#         m -= const

#     l = 100
#     const = l // num_inputs
#     for _ in range(num_inputs):
#         l_values.append(l)
#         l -= const

#     m_values = sorted(m_values)
#     n_values = sorted(n_values)
#     l_values = sorted(l_values)
    
#     for i in range(num_inputs):
#         input_size.append([n_values[i], m_values[i], l_values[i]])
    
#     return input_size

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
            program_args = [str(n), str(m), str(l), '1']
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
        result = subprocess.run(["./" + project_exe], stdin=file, capture_output=True, text=True)

        # tempo de fim
        end_time = time.perf_counter()

        output = result.stdout
        print(output)

    return end_time-start_time

def f(input_size):
    comp = []

    for size in input_size:
        comp.append(calculate_comp(size[0], size[1], size[2]))

    return comp

def main():
    # tamanho do input [n, m, l]
    input_size = generate_input_size()
    # input_size = [[5, 22, 6], [10, 34, 7], [15, 46, 8], [20, 58, 9], [25, 70, 10], [30, 82, 11], [35, 94, 12], [40, 106, 13], [45, 118, 14], [50, 130, 15], [55, 142, 16], [60, 154, 17], [65, 166, 18], [70, 178, 19], [75, 190, 20], [80, 202, 21], [85, 214, 22], [90, 226, 23], [95, 238, 24], [100, 250, 25]]

    # comp = [3654120904.3760986, 5225211910.264772, 6584439982.700927, 7890434671.906378, 9205614235.177628, 11506852879.165094, 12774727839.333637, 13909159851.749222, 15325830029.708645, 16335660568.454744, 17630003635.505848, 18979929643.055378, 20094734072.472073, 21542388699.890034, 22725155548.772762, 23935169033.761276, 25172714957.52016, 27731549098.88157]
    # times = [0.74, 0.91, 1.22, 1.01, 1.1, 1.24, 1.35, 1.64, 1.45, 1.57, 1.61, 1.68, 1.94, 2.02, 2.03, 2.32, 2.04, 2.97]
    # calcular tempo de cada input
    times = run(input_size)
    # calcular f(n, l)
    comp = f(input_size)

    # Degree 1 para ser linear
    coefficients = np.polyfit(np.array(comp), np.array(times), 1)
    print(coefficients)
    slope, intercept = coefficients
    # equação da linha
    line = slope * np.array(comp) + intercept

    print('Complexidade:', comp)
    print('Time:', times)

    # desenhar os pontos
    plt.scatter(comp, times, color="blue")
    # desenhar a linha
    plt.plot(comp, line)
    plt.xlabel('f(n,l)')
    plt.ylabel('Time (s)')
    plt.title('Análise teórica')
    plt.show()

main()