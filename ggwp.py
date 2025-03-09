import matplotlib.pyplot as plt
import numpy as np

# Загрузка данных из файла
data = np.loadtxt('C:/Users/Alekc/source/repos/strdan/map-benc/res2.txt', delimiter='\t')

# Предполагаем, что первый столбец - это x, остальные - y
x = data[:, 0]

# Построение графиков
plt.figure(figsize=(12, 8))


plt.subplot(1, 3, 1)  # 2 строки, 3 столбца для 6 графиков
plt.plot(x, data[:, 1], x, data[:, 4])
plt.xlabel('Ключи')
plt.ylabel(f'Итерации')
plt.title(f'TreeMap & HashMap insert')
plt.legend()
plt.subplot(1, 3, 2)  # 2 строки, 3 столбца для 6 графиков
plt.plot(x, data[:, 2], x, data[:, 5])
plt.xlabel('Ключи')
plt.ylabel(f'Итерации')
plt.title(f'TreeMap & HashMap search')
plt.subplot(1, 3, 3)  # 2 строки, 3 столбца для 6 графиков
plt.plot(x, data[:, 3], x, data[:, 6])
plt.xlabel('Ключи')
plt.ylabel(f'Итерации')
plt.title(f'TreeMap & HashMap remove')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()