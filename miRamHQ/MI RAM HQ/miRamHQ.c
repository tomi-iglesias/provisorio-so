#include "miRamHQ.h"


int main(void)
{
	void iterator(char* value)
	{
		printf("%s\n", value);
	}

	logger = log_create("miRamHQ.log", "MiRamHQ", 1, LOG_LEVEL_DEBUG);
	config = config_create("miRamHQ.config");

	ip_mi_ram_hq = config_get_string_value(config, "IP_MI_RAM_HQ");
	puerto_mi_ram_hq = config_get_string_value(config, "PUERTO_MI_RAM_HQ");

	int server_fd = iniciar_servidor(ip_mi_ram_hq,puerto_mi_ram_hq);
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);

	t_list* lista;
	while(1)
	{
		int cod_op = recibir_operacion(cliente_fd);
		switch(cod_op)
		{
		case MENSAJE: // @suppress("Symbol is not resolved")
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE: // @suppress("Symbol is not resolved")
			lista = recibir_paquete(cliente_fd);
			printf("Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger, "Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}
