#include "Discordiador.h"

#include <string.h>
#include "utils.h"

int main(void)
{
	int conexion_i_mongo_storel
	int conexion_mi_ram_hq;
	char* ip_i_mongo_store;
	char* ip_mi_ram_hq;
	char* puerto_i_mongo_store;
	char* puerto_mi_ram_hq;


	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	config = leer_config();
	leer_consola(logger);

	ip_i_mongo_store = config_get_string_value(config, "IP_I_MONGO_STORE");
	ip_mi_ram_hq = config_get_string_value(config, "IP_MI_RAM_HQ");

	puerto_i_mongo_store = config_get_string_value(config, "PUERTO_I_MONGO_STORE");
	puerto_mi_ram_hq = config_get_string_value(config, "PUERTO_MI_RAM_HQ");

	conexion_i_mongo_store = crear_conexion(ip_i_mongo_store, puerto_i_mongo_store);
	conexion_mi_ram_hq = crear_conexion(ip_mi_ram_hq,puerto_mi_ram_hq);

	enviar_mensaje("Hola I-Mongo-Store, soy el Discordiador", conexion_i_mongo_store);
	enviar_mensaje("Hola Mi-Ram-HQ, soy el Discordiador", conexion_mi_ram_hq);

	//paquete(conexion);

	terminar_programa(conexion_mi_ram_hq,conexion_i_mongo_store, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log* logger = log_create("discordiador.log","Discordiador",true, LOG_LEVEL_INFO);
	log_info(logger, "Log De Discordiador Creado");
	return logger;
}

t_config* leer_config(void)
{
	t_config* config = config_create("discordiador.config");
	if (config == NULL){
		exit (1);
	}
	return config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	leido = readline(">");

	while(strcmp(leido, "") != 0){
		log_info(logger, leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);
}

void paquete(int conexion)
{
	char* leido;
	t_paquete* paquete;

	paquete = crear_super_paquete();

	leido = readline(">");

	while(strcmp(leido, "") != 0){
			agregar_a_paquete(paquete, leido, strlen(leido) + 1);
			free(leido);
			leido = readline(">");
		}
	free(leido);
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);

}

void terminar_programa(int una_conexion, int otra_conexion, t_log* logger, t_config* config)
{
	liberar_conexiones(una_conexion, otra_conexion);
	log_destroy(logger);
	config_destroy(config);
}
