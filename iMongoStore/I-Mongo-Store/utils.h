#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include</home/utnso/so-commons-library/src/commons/log.h>
#include</home/utnso/so-commons-library/src/commons/collections/list.h>
#include<commons/config.h>
#include<string.h>


typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

t_log* logger;
t_config* config;

void* recibir_buffer(int*, int);
int iniciar_servidor(char*,char*);
int esperar_cliente(int);
t_list* recibir_paquete(int);
void recibir_mensaje(int);
int recibir_operacion(int);

#endif /* CONEXIONES_H_ */
