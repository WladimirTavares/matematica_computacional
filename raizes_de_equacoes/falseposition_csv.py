import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import math

def falseposition(a,b,tol,itermax,f):
	
	with open('rfValues.csv', 'w') as csv:

		csv.write('k, a, b, c, f(c)\n')
		c = (a*f(b)-b*f(a))/(f(b)-f(a))
		k = 0

		csv.write(str(k)+','+str(a)+','+str(b) + ',' + str(c) + ',' +str(f(c)) +  '\n')
		while math.fabs(b-a)>= tol and math.fabs(f(c)) >= tol:
			if f(a)*f(c) < 0:
				b = c
			else:
				a = c
			
			
			c = (a*f(b)-b*f(a))/(f(b)-f(a))
			csv.write(str(k)+','+str(a)+','+str(b) + ',' + str(c) +',' +str(f(c)) +  '\n')
		
			k = k + 1

	print("Solucao encontrada = %f" % (c) )
	print("Num de iteracoes   = %d" % (k) )
	print("Intervalo da raiz  = (%f,%f)"% (a,b) )	
	print("Erro absoluto      = %f"   % math.fabs(f(c)))	


	
def f1(x):
	return pow(x,2) - 2

def f2(x):
  return 2*pow(x,3) - 4*pow(x,2) + 3*x



def main():
	falseposition(-1,0.5,1e-3,100,f2)

if __name__ == "__main__":
    main()
