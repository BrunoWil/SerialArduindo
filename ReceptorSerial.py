import serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
arduino = serial.Serial()

portList = []

#use ttyUSB0 se for o caso, ou se for Windows, COMx.
for onePort in ports:
    portList.append(str(onePort))
    print(str(onePort))

val = input("select Port: COM")

for x in range(0,len(portList)):
    if portList[x].startswith("COM"+str(val)):
        portVal = "COM" + str(val)
        print(portList[x])

#arduino = serial.Serial('COM3',9600,timeout=2)
arduino.baudrate = 9600
arduino.port = portVal
arduino.timeout = 2
arduino.open()


texto=[]
tamanho=0
try:
    nome_arquivo = "imagem.pgm"
    arquivo = open(nome_arquivo, 'r+')
    
except FileNotFoundError:
    arquivo = open(nome_arquivo, 'w+')
    

flag=0
while True:
    if arduino.in_waiting:
    
        packet = arduino.readline()
        print(packet.decode('utf'))
        texto = packet.decode('utf')

        if(texto[0:8]=="Tamanho:"):
                tamanho=int(texto[8:-1])

        if(texto=="Inicio\r\n"):
            packet = arduino.readline()
            texto = packet.decode('utf')
            flag=2
        if(texto=="Fim\r\n"):
            flag=0

        if(flag>=1):
            if(flag==2):
                arquivo.writelines("P1\n")
                arquivo.writelines("{0} {1}\n\n".format(tamanho,tamanho))
                flag=1

            arquivo.writelines(texto[:-1])
            arquivo.flush()
    

            

arquivo.close()

