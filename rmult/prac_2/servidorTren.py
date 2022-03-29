######################
#	servidorTren.py  #
#	Prácticas RM     #
######################


import statistics
import sys
import socket
import struct
import time
from urllib.request import DataHandler
from statistics import mean

MAX_ETHERNET_DATA=1500
MIN_ETHERNET_DATA=46
ETH_HDR_SIZE=14+4+8+12 # Cabecera Ethernet + CRC + Preambulo + Interframe gap
IP_HDR_SIZE=20
UDP_HDR_SIZE=8
RTP_HDR_SIZE=12

MAX_WAIT_TIME=4
MAX_BUFFER=100000000

packet_list=[]
B_MASK=0xFFFFFFFF
DECENASMICROSECS=100000


# RECOMENDADO TAMAÑO 1400 PAQUETE Y 1000 N_Paquetes
if __name__ == "__main__":
	if len(sys.argv)!=3:
		print ('Error en los argumentos:\npython3 servidorTren.py ip_escucha puerto_escucha\n')
		exit(-1)

	ipListen=sys.argv[1]
	portListen=int(sys.argv[2])

	sock_listen = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # UDP
	sock_listen.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF,MAX_BUFFER)
	sock_listen.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	sock_listen.bind((ipListen,portListen))
	sock_listen.settimeout(MAX_WAIT_TIME)
	
	#Recibimos los paquetes y salimos del bucle cuando no se reciban paquetes en MAX_WAIT_TIME segundos
	while True:
		try:
			data, addr = sock_listen.recvfrom(2048)
			#Para cada paquete recibido añadimos a la lista de paquetes
			#una tupla que contiene los datos del paquete y el tiempo en que 
			#se recibió dicho paquete
			packet_list.append((data,time.time()))

		except socket.timeout:
			break

	npackets=0
	inst_bandwidth_list = []
	inst_delays = []
	seq_numbers = []
	for idx, packet in enumerate(packet_list):
		#Para cada paquete recibido extraemos de la cabecera
		#cada uno de los campos necesarios para hacer los cálculos

		data=packet[0]
		header=struct.unpack('!HHII',data[0:12])
		seq_number=header[1]
		seq_numbers.append(seq_number)
		send_time_trunc=header[2]
		trainLength=header[3]
		#ATENCIÓN: El tiempo de recepción está en formato: segundos.microsegundos
		#Usar este tiempo para calcular los anchos de banda
		reception_time = packet[1]
		interarrival = 0.0
		if idx > 0:
			interarrival=packet_list[idx][1] - packet_list[idx-1][1]
			tam_packet = (len(data) + UDP_HDR_SIZE + IP_HDR_SIZE)
			inst_bandwidth = ((tam_packet * 8) / interarrival) / 1000
			print('Ancho de banda instantaneo: ' + str(round(inst_bandwidth,2)) + ' Kbps' )
			inst_bandwidth_list.append(inst_bandwidth)
		npackets+=1
		#Truncamos el tiempo de recepción a centésimas de milisegundos 
		#(o decenas de microsegundos, segun se quiera ver) y 32 bits
		#para poder calcular el OWD en la misma base en que está el tiempo
		#de envío del paquete
		reception_time_trunc=int(reception_time*DECENASMICROSECS)&B_MASK
		inst_delay = (reception_time_trunc-send_time_trunc)/100
		print('Retardo instantaneo en un sentido (ms): ',inst_delay)
		inst_delays.append(inst_delay)




		###########################PRÁCTICA##############################################
		#                                                                               #
		# Añadir cálculos necesarios para obtener ancho de banda (instantáneo,medio,    #
		# máximo,mínimo) retardo en un sentido (instantáneo, medio, máximo y mínimo)     #
		# ATENCIÓN: los tiempos truncados están en centésimas de milisegundos           # 
		#         (o decenas de microsegundos, segun se quiera ver)                     #
		# a la hora de calcular retardos se debe tener en cuenta                        #
		#################################################################################

	first_time = packet_list[0][1]
	last_time = packet_list[-1][1]
	train_time = last_time - first_time

	if ipListen == "127.0.0.1":
		train_tam = (len(data) + IP_HDR_SIZE + UDP_HDR_SIZE) * (len(packet_list)-1)
	else:
		train_tam = (len(data) + IP_HDR_SIZE + UDP_HDR_SIZE+ ETH_HDR_SIZE) * (len(packet_list)-1)

	#print('Tiempo entre primer y último paquete: ' + str(train_time))
	#print('Tamaño del tren de paquetes: ' + str(train_tam) + ' Bytes')

	med_bandwidth = ((train_tam * 8) / train_time) / 1000
	
	print('Ancho de Banda medio: ' + str(round(med_bandwidth,2)) + ' Kbps')	
	print('Ancho de Banda MAX: ' + str(round(max(inst_bandwidth_list),2)) + ' Kbps')
	print('Ancho de Banda MIN: ' + str(round(min(inst_bandwidth_list),2)) + ' Kbps')

	print('Retardo medio: ' + str(round(mean(inst_delays),3)) + ' ms')
	print('Retardo MAX: ' + str(round(max(inst_delays),3)) + ' ms')
	print('Retardo MIN: ' + str(round(min(inst_delays),3)) + ' ms')


	###########################PRÁCTICA##############################################
	#                                                                               #
	# Añadir cálculos necesarios para obtener pérdida de paquetes y variación del   #
	# retardo                                                                       #
	#################################################################################

	n_packets = header[3]

	packetLoss = ((n_packets - len(seq_numbers)) / n_packets) * 100
	print('Perdida de paquetes: ' + str(round(packetLoss,3)) + ' %')

	jitter = statistics.stdev(inst_delays)
	print('Variación del retardo: ', round(jitter,3))
	#################################################################################




