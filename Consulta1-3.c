#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BD",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//Consulta: Buscar el guanyador d'una partida a partir de l'identificador
	err=mysql_query (conn, "SELECT DISTINCT Partida.Guanyador FROM (Jugador, Partida, Jugadors) WHERE Partida.ID = '3' AND Jugador.ID = Jugadors.ID_J AND Partida.ID = Jugadors.ID_P");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else {
		while (row !=NULL) {
			printf("%s\n", row[0]);
			row = mysql_fetch_row (resultado);
		}
	}
	mysql_close (conn);
	exit(0);
}
