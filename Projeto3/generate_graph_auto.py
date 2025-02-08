from matplotlib import pyplot as plt
import subprocess, time
import numpy as np

# AJUSTAVEL
num_inputs = 50

generator_path = 'gera3.py'
project_path = 'Projeto3.py'
input_file = 'input.in'

def calculate_variables(n, t):
    return n*t

def generate_input_size():
    increments = 10
    initial_values = (10, 3)
    input_size = []
    for i in range(0, num_inputs):
        n = initial_values[0] + i * increments
        m = initial_values[1] + i * increments
        t = 5 * n
        input_size.append([n, m, t])

    return input_size

def run(input_size):
    times = []

    # executar o gerador com n e m e t
    for size in input_size:
        n = size[0]
        m = size[1]
        t = size[2]

        # executar o gerador
        with open(input_file, "w") as file:
            program_args = [str(n), str(m), str(t), '0', '10', '10']
            subprocess.run(["python", generator_path] + program_args, stdout=file)

        # calcular tempo do ficheiro de input (tambem corre o programa)
        time = round(calculate_time(), 2)
        times.append(time)

    return times

def calculate_time():
    # abrir o ficheiro gerado
    with open("input.in", "r") as file:
        # tempo de inicio
        start_time = time.perf_counter()

        # correr o projeto
        result = subprocess.run(["python", project_path], stdin=file, capture_output=True, text=True)

        # tempo de fim
        end_time = time.perf_counter()

        output = result.stdout
        print('Output:', output)

    return end_time-start_time

def get_variables(input_size):
    variables = []

    for size in input_size:
        variables.append(calculate_variables(size[0], size[2]))

    return variables

def main():
    # tamanho do input [n, m, t]
    input_size = generate_input_size()
    # calcular tempo de cada input
    times = run(input_size)
    variables = get_variables(input_size)
    
    degree = 2
    coef = np.polyfit(variables, times, degree)
    poly_fn = np.poly1d(coef)

    print('Inputs:', input_size)
    print('Time:', times)

    # desenhar os pontos
    plt.scatter(variables, times, label="Dados experimentais", alpha=0.5, color="blue")
    # desenhar a curva
    plt.plot(variables, poly_fn(variables))
    plt.xlabel('Número de variáveis')
    plt.ylabel('Tempo (s)')
    plt.title('Avaliação Experimental dos Resultados')
    plt.show()

main()