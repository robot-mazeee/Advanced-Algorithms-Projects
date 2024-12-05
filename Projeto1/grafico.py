from matplotlib import pyplot as plt

def calculate_comp(n, m):
    return n**2 * m**3

input_size = [[10, 100], [20, 200], [40, 275], [60, 400], [75, 500], [80, 750], [85, 800], [95, 800], [95, 900], [100, 1000]]
time = [0.326, 0.535, 1.740, 3.957, 5.971, 7.609, 8.712, 10.494, 10.982, 12.291]

# calcular f(n, m)
comp = []
for i in range(len(input_size)):
    comp.append(calculate_comp(input_size[i][0], input_size[i][1]))

plt.scatter(comp, time, color="blue")
plt.plot(comp, time)
plt.xlabel('f(n,m)')
plt.ylabel('Time (s)')
plt.title('Análise teórica')
plt.show()