import matplotlib.pyplot as plt
import numpy as np

# Dados
metodos = ['Busca Sequencial', 'Busca Binária']
tamanhos = ['Pequenos', 'Médios', 'Grandes']

# Tempos para 1000 repetições (s)
tempo_1000 = {
    'Pequenos': [4.724, 0.008],
    'Médios': [23.687, 0.009],
    'Grandes': [55.675, 0.009]
}

# Tempos para 1 busca (μs)
tempo_1 = {
    'Pequenos': [47.240, 0.08],
    'Médios': [236.870, 0.09],
    'Grandes': [556.750, 0.09]
}

# Comparações para 1000 repetições (milhões)
comp_1000 = {
    'Pequenos': [1800, 1.5],
    'Médios': [9000, 1.7],
    'Grandes': [21000, 1.8]
}

# Comparações para 1 busca
comp_1 = {
    'Pequenos': [18000, 15],
    'Médios': [90000, 17],
    'Grandes': [210000, 18]
}

# Configuração do gráfico
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 12))
plt.subplots_adjust(hspace=0.4, wspace=0.3)

# Gráfico de Tempo para 1000 repetições
x = np.arange(len(metodos))
width = 0.25
for i, tamanho in enumerate(tamanhos):
    ax1.bar(x + i*width, tempo_1000[tamanho], width, label=tamanho)
ax1.set_ylabel('Tempo (s)')
ax1.set_title('Tempo para 1000 Buscas (escala logarítmica)')
ax1.set_yscale('log')
ax1.set_xticks(x + width)
ax1.set_xticklabels(metodos)
ax1.legend()

# Gráfico de Tempo para 1 busca
for i, tamanho in enumerate(tamanhos):
    ax2.bar(x + i*width, tempo_1[tamanho], width, label=tamanho)
ax2.set_ylabel('Tempo (μs)')
ax2.set_title('Tempo para 1 Busca (escala logarítmica)')
ax2.set_yscale('log')
ax2.set_xticks(x + width)
ax2.set_xticklabels(metodos)
ax2.legend()

# Gráfico de Comparações para 1000 repetições
for i, tamanho in enumerate(tamanhos):
    ax3.bar(x + i*width, comp_1000[tamanho], width, label=tamanho)
ax3.set_ylabel('Comparações (milhões)')
ax3.set_title('Comparações para 1000 Buscas (escala logarítmica)')
ax3.set_yscale('log')
ax3.set_xticks(x + width)
ax3.set_xticklabels(metodos)
ax3.legend()

# Gráfico de Comparações para 1 busca
for i, tamanho in enumerate(tamanhos):
    ax4.bar(x + i*width, comp_1[tamanho], width, label=tamanho)
ax4.set_ylabel('Comparações')
ax4.set_title('Comparações para 1 Busca (escala linear)')
ax4.set_xticks(x + width)
ax4.set_xticklabels(metodos)
ax4.legend()

plt.show()