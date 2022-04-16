#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

//CALEN PRIVILEGIS DE ROOT per executar això correctament o procés amb CAP_NET_ADMIN capability
//LA INTERFICIE ES GENERA DE MANERA TEMPORAL I QUAN ES FINALITZA EL PROCÉS S'ESBORRA

int createTunDevice()
{
	//contindrà el file descriptor de l'arxiu o driver que gestiona els dispositius de xarxa
	int tunfd;

	//struct que utilitzarem per configurar la nostra interfície virtual de xarxa
	//ifreq se usa para configurar direcciones IP, activar interfaces y 
	//configurar información de interfaz como MTU. 
	//Contiene el nombre y el contenido específico de una interfaz 
	//(es una comunidad, puede ser dirección IP, dirección de difusión, máscara de subred, número MAC, MTU u otro contenido).
	struct ifreq ifr; 

	// inicialitza totes les dades de l'struct a char(0) = null character.
	memset (&ifr,0,sizeof(ifr));

	//https://man7.org/linux/man-pages/man7/netdevice.7.html
	// configurem les flags del struct
	//IFF_TUN indica que estem creant una interfície TUN
	ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

	//Obrim l'arxiu (es un arxiu que gestiona un driver) en mode escriptura i lectura
	// ens retorna el file descriptor de l'arxiu
	tunfd = open("/dev/net/tun",O_RDWR);

	//utilitzant aquesta Kernel call podem configurar el driver de xarxa
	ioctl(tunfd, TUNSETIFF, &ifr) ;
	
	return tunfd;
}
int main(){

	//creem l'interfície virtual de xarxa TUN
	int tunfd = createTunDevice();
	printf("TUN file descriptor: %d \n", tunfd);
	
	
	//excecuta un terminal
	//haurem d'escriure exit per sortir
	char *argv[2];
	argv[0] = "/bin/bash";
	argv[1] = NULL;
	execve("/bin/bash", argv, NULL);
	
	return 0;
}


