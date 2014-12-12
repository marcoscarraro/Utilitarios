#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* includes necessiarios para o socket no windows, devem vir antes da biblioteca do windows.h */
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#include <windows.h>
#include <ntsecapi.h>
#include <string.h>
#include <stdint.h>

/*
Compilado utilizando dev c++ x64

Atenção antes de compilar Ferramentas->Opções do Compilador
Na caixa "Adicionar estes comandos à linha de comando do liker"
Adicione estes dois parametros para o bom funcionamento

-static-libgcc -lws2_32											

Este "programa" faz um get para atualizar informações de usuários em uma pagina de um projeto utilizando CodeiGniter.
Perceba que ele utiliza como navegador o nome de "NavegadorSecreto", isso para que na pagina do CodeiGniter eu somente
 aceito conexões deste navegador.
 
 Obs:. As informações aqui são ficticias, tais como usuário, senha, ip e url.
 Obs2:. Lembre-se que sempre que nunca deve-se passar login e senha pela rede em texto puro, utilize alguma criptografia como
   sha1, md5 e em ultimos casos um base64 com salt.

No fim ele ainda pega o retorno que a pagina deu para verificar se tudo ocorreu bem.

*/
 
int main(int argc , char *argv[]){
    WSADATA wsa;
    SOCKET skt;
    struct sockaddr_in server;
    char message[20480] , server_reply[2000];
    int recv_size;

    /* Inicializando a biblioteca do windows winsock */
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Falha ao tentar iniciar a biblioteca. Codigo de erro : %d",WSAGetLastError());
        return 1;
    }
     
  	 /* criando o socket */
    if((skt = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
        printf("Erro ao tentar criar o socket : %d" , WSAGetLastError());
    }
 
    /* informacoes para o socket conectar */  
    server.sin_addr.s_addr = inet_addr("192.168.1.222");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
 
    /* Conecta no Servidor */
    if (connect(skt,(struct sockaddr *)&server , sizeof(server)) < 0){
        puts("Erro ao conectar no servidor.");
        return 1;
    }
    
    
  /* Envia o get 
	*
	*/
	sprintf(message,"GET /pagina/teste/update/usuarioxyz/senhausuariozy HTTP/1.1\r\nHost: 192.168.1.222\r\nConnection: */*\r\nUser-Agent: NavegadorSecreto\r\n\r\n",teste);
    
	if(send(skt,message,strlen(message),0)<0) {
        puts("Erro ao enviar a requisicao para o servidor.");
        return 1;
    }
    
    
    /* Recebe o retorno */
    if((recv_size = recv(skt , server_reply,2000,0)) == SOCKET_ERROR){
        puts("Erro ao receber o retorno.");
    }
     
 	if(strstr(server_reply,"#OK#")){
 		puts("OK APLICOU\n");
 	} else if(strstr(server_reply,"#ERRO#")){
 		puts("ERRO APLICOU\n");
 	} else{
 		puts("ERRO DESCONHECIDO NADA FEITO\n");
 	}
 
  
    /* Fecha a conexao */
  	closesocket(skt);
  
    return 0;
}
