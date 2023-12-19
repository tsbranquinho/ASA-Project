# !!!! meter os tempos na variável tempos e o x na variável tamanhos
# !!!! para evitar possíveis erros metam os tamanhos com string e os tempos como inteiros
# !!!! o array dos tamanhos tem de ter dimensão igual ao dos tempos
import matplotlib.pyplot as plt


#Primeiro gráfico
tamanhos = ["100","200","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500"]
tempos = [1.3,4.6,13.9,30.5,66.5,127.6,214,334.3,478.4,702.6,914.4,1346.2,1662.6,2183.2,2646.1]

plt.plot(tamanhos, tempos, marker = '|', alpha=1)
plt.xlabel('N')
plt.ylabel('Tempo (ms)')
plt.title('Resultados', fontsize=10)     # meter o título entre as plicas

plt.show()


#Segundo gráfico
tamanhos = ["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"]
tempos = [0.015,0.061,0.18,0.48,1.2,2.9,6.8,15,35,78,170,370,810,1750,3750]


plt.plot(tamanhos, tempos, marker = '|', alpha=1)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Esperado', fontsize=10)     # meter o título entre as plicas

plt.show()
