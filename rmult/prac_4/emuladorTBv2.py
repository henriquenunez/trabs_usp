# -*- coding: windows-1252 -*-
import socket
import random
import time
import threading
import queue
import sys
import ipaddress
 
# Tama�os de cabeceras a la hora de restar tokens
CAB_IP = 20 #bytes
CAB_UDP = 8 #bytes
CAB_ETH = 12+8+6+6+2+4 # Incluye pre�mbulos e inter-frame gap, en bytes
MTU_ETH = 1500 #bytes

# Tama�o del buffer de recepci�n
BUFFER=4000000

# Escenarios que hay en el programa
TAMANOS_CUBO = [5000, 10000, 20000, 25000, 5000, 10000, 20000, 25000, 5000, 10000, 20000, 25000, 5000] # Bytes
TASAS_TOKEN = [200, 100, 50, 40, 400, 200, 100, 80, 250, 125, 63, 50, 300] # N�mero de adiciones al cubo por segundo

num_tokens = MTU_ETH # N�mero de tokens que a�adimos en cada adici�n. M�s adelante se decide si a�adir adem�s los bytes de cabecera ETHERNET

cubo=0 # Cubo en el que se ir�n poniendo los tokens

cola = queue.Queue() # Estructura de la cola que se utiliza para token bucket


# Esta clase de hilo se encarga de llenar el cubo del token bucket
class LlenarCubo(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
	def run(self):
		# Se usa la variable global cubo, que el otro hilo ir� vaciando
		global cubo
		
		# Inicialmente se llena el cubo con todos los tokens
		cubo=tamano_cubo
		
		# Posteriormente se comprueba si hay que rellenarlo o sigue lleno
		while True:
			if cubo<tamano_cubo:
				if cubo+num_tokens>tamano_cubo : # El cubo no puede rebosar
					cubo=tamano_cubo
				else:
					cubo+=num_tokens
			#print(cubo)
			# Esperamos para seguir llenando el cubo
			time.sleep(1/tasa_token)

# Esta clase de hilo se encarga de sacar los paquetes de la cola seg�n la tasa fijada por el Token Bucket y enviarlos a la red
class Desencolar(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)

	def run(self):
		# Se usan las variables globales cola, que se ir� rellenando en el hilo principal y aqu� vaciando
		# y cubo, que se ir� vaciando aqu�, y rellenando en otro hilo
		global cola, cubo

		while True :
			if not cola.empty() : # Si la cola no est� vac�a
				datos = cola.get()
				# Se obtiene el n�mero de tokens a vaciar del cubo
				len_datos=len(datos)+CAB_ETH+CAB_IP+CAB_UDP
				#print("datos:",len_datos)
				while len_datos>cubo: # No hay tokens suficientes
					# Esperamos a que se llene el cubo, durmiendo mientras tanto.
					#print(0)
					time.sleep(0.001) # dormimos en cuantos de 1 ms
				# Quitamos los tokens necesarios del cubo
				cubo-=len_datos
				#print(cubo)
				# Enviamos finalmene el paquete
				sockC.sendto(datos, (ip_destino.exploded, puerto_destino))


# Thread principal
if __name__ == "__main__":
	# Toma de par�metros
	if len(sys.argv) !=6 :
		print("Numero de argumentos invalido")
		print("Sintaxis: emuladorTB ip_escucha puerto_escucha ip_destino puerto_destino escenario")
		sys.exit()

	# Se comprueba que los puertos sean puertos, las direcciones direcciones, y el escenario un n�mero
	try :
		ip_escucha=ipaddress.IPv4Address(sys.argv[1])
		ip_destino=ipaddress.IPv4Address(sys.argv[3])
	except:
		print("No se ha introducido una direccion IP valida")
		sys.exit()
	try :
		puerto_escucha = int(sys.argv[2])
		puerto_destino = int(sys.argv[4])
		escenario = int(sys.argv[5])
	except:
		print("No se ha introducido un numero valido")
		print("Sintaxis: emuladorTB ip_escucha puerto_escucha ip_destino puerto_destino escenario")
		sys.exit()
		
	# Se comprueba que no se pida un escenario inexistente
	if escenario<1 or escenario>len(TAMANOS_CUBO) :
		print("El escenario solicitado no existe")
		print("Sintaxis: emuladorTB ip_escucha puerto_escucha ip_destino puerto_destino escenario")
		sys.exit()
		
	print("Escenario utilizado:",escenario)
		
	# A partir del escenario se obtiene el tama�o del cubo y la tasa de llenado que utilizar� el emulador
	tamano_cubo = TAMANOS_CUBO[escenario-1] 
	tasa_token = TASAS_TOKEN[escenario-1] 
	
	print("El tamano del cubo es de",tamano_cubo,"bytes")
	print("La tasa de relleno de token es de",tasa_token,"tokens/s")
	
	# Si el destino es Ethernet, no se tiene en cuenta su cabecera para contar los tokens
	if ip_destino.is_loopback :
		CAB_ETH=0

	# Se fija el tama�o cada adici�n de tokens
	num_tokens = MTU_ETH+CAB_ETH
	print("Cada adici�n a�ade",num_tokens,"tokens")
		
	# Se crea un socket para recibir (servidor)
	sockS = socket.socket(socket.AF_INET, # Internet
							socket.SOCK_DGRAM) # UDP

	sockS.bind((ip_escucha.exploded, puerto_escucha))

	# se modifica el tamano de la cola, para poder recibir r�fagas de paquetes sin p�rdidas
	sockS.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, BUFFER)

	# Se crea un socket para enviar (cliente)
	sockC = socket.socket(socket.AF_INET, # Internet
							socket.SOCK_DGRAM) # UDP


	# Se arranca el thread de rellenado del cubo
	threadLlenado = LlenarCubo()
	threadLlenado.start()


	# Se arranca el thread de desencolado
	threadDesencolado = Desencolar()
	threadDesencolado.start()

	
	while True:
		# Se recibe un paquete
		data, addr = sockS.recvfrom(2048) # se pueden recibir segmentos de hasta 2048 bytes, lo normal es que no sean mayores de 1472

		# Se meten los datos recibidos en la cola, que ir�n siendo desencolados por el thread de desencolado
		cola.put(data)
