#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
using namespace std;
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <Windows.h> //libreria para utilizar Sleep()

struct votante{
	char dui[15];
	char dui_registrado[15];
};//fin struct votante

struct RegistroJRV{
	char nombre[20];
	char apellido[20];
	char dui[15];
	char cargo[15];
};//fin struct RegistroJRV

/*Prototipo de Funciones*/
void NumeroJunta(char junta[]);
void iniciaVotacion(int total, int total2, votante lista[], char buscar_dui[], int &pp, int &upn, int &nulo);
void registroIntegrantes(RegistroJRV ingreso[],char urna[],int &numero);

int main(){system("color B");
char num_urna[15]; //variable de captura para numero de urna
int opc; //variable para opciones del menu
int total_reg = 0, vto_reg = 0;//total de registros
int vto_pp = 0, vto_upn = 0, vto_nulo = 0; //variables de de conteo para votos registrados
int totvotos = 0, integrantes=0; //total de votos; integrantes=numero de integrantes de la JRV
int abstenciones = 0; //numero de abstenciones en las votacione
char buscar_dui[15]; //variable de captura para numero de dui

//flujo de acceso para archivos
ifstream leerarchivo;//modo lectura
fstream escribirarchivo;//modo escritura
ofstream salidaarchivo;//modo acta txt

votante registro[100]; //matriz de 100 vaiable de tipo votante
RegistroJRV registro_Urna[100];//matriz de 100 variables tipo RegistroJRV
leerarchivo.open("Padron_electoral.txt", ios::in);
if (leerarchivo.is_open()){
	while (!leerarchivo.eof()){
		total_reg++;
		leerarchivo.getline(registro[total_reg].dui, 15); //recuperamos dui
	}//fin recuperamos dui if
}else{
	escribirarchivo.open("Padron_electoral.txt", ios::out);
	escribirarchivo << "10203040-1" << endl; escribirarchivo << "10203040-2" << endl; escribirarchivo << "10203040-3" << endl;
	escribirarchivo << "10203040-4" << endl; escribirarchivo << "10203040-5" << endl; escribirarchivo << "10203040-6" << endl;
	escribirarchivo << "10203040-7" << endl; escribirarchivo << "10203040-8" << endl; escribirarchivo << "10203040-9" << endl;
	escribirarchivo.close();//cierra el acceso al archivo en modo escritura
}//fin if-else .is_open
leerarchivo.close();//cierra acceso a archivo en modo lectura

cout << "Iniciando proceso de votacion";Sleep(0500); cout << "..."; Sleep(0300); cout << "..."; Sleep(0600); cout << "...." << endl << endl << endl;
system("pause");
NumeroJunta(num_urna); //llamado a funcion NumeroJunta.
do{
	system("cls");
	cout<<setw(53)<<"Sistema de Votacion 2014"<<endl; 
	cout << setw(54) << "Tribunal Supremo Electoral" << endl;
	cout << setw(43) << "Junta No " << num_urna << endl;
	cout << endl << "\n\t1. Registrar JRV" << endl;
	cout << "\t2. Iniciar Proceso de votacion" << endl;
	cout << "\t3. Resultados de la votacion" << endl;
	cout << "\t4. Mostrar Acta" << endl;
	cout << "\ta. Imprimir Acta.txt" <<endl;
	cout << "\tb. Imprimir Acta.html" <<endl;
	cout << "\t5. Salir" << endl << endl;
	cout << "  Opcion: "; opc = getche();cout << endl << endl;
	switch (opc){
		case'1':
			system("cls");
			registroIntegrantes(registro_Urna, num_urna, integrantes);//lamado a funcion registroIntegrantes
			break;
			case'2':
				system("cls");
				cout << "Procesando Informacion";Sleep(0500); cout << "..."; Sleep(0300); cout << "..."; Sleep(0600); cout << "...." << endl << endl << endl;
				leerarchivo.open("votos_registrados.txt", ios::in);
				if (leerarchivo.is_open()){
					while (!leerarchivo.eof()){
						vto_reg++;
						leerarchivo.getline(registro[vto_reg].dui_registrado, 15);
					}//fin while
				}
				else{
					escribirarchivo.open("votos_registrados.txt", ios::out);
					escribirarchivo.close();
				}//fin if-else
				leerarchivo.close();
				system("pause");system("cls");
				cout << setw(53) << "Sistema de Votacion 2014" << endl;
				cout << setw(54) << "Tribunal Supremo Electoral" << endl;
				cout << setw(43) << "Junta No " << num_urna << endl;
				cout << "Ingrese su Numero de DUI: "; fflush(stdin);
				cin.getline(buscar_dui, 15);
				iniciaVotacion(total_reg, total_reg, registro, buscar_dui, vto_pp, vto_upn, vto_nulo);
				break;
				case'3':
					system("cls");
					cout << setw(53) << "Sistema de Votacion 2014" << endl;
					cout << setw(54) << "Tribunal Supremo Electoral" << endl;
					cout << setw(43) << "Junta No " << num_urna << endl;
					totvotos = vto_pp + vto_upn + vto_nulo;  abstenciones = total_reg - totvotos;
					cout << "\n\nTotal de votos efectuados = " << totvotos << endl;
					cout << "--------------------------------------------" << endl;
					cout << "voto PP   = " << vto_pp << endl;
					cout << "voto UPN  = " << vto_upn << endl;
					cout << "voto NULO = " << vto_nulo << endl;
					cout << "Abstenciones = " << abstenciones << endl;
					break;
					case'4':
						system("cls");
						cout.setf(ios::fixed);
						cout << setw(53) << "Sistema de Votacion 2014" << endl;
						cout << setw(54) << "Tribunal Supremo Electoral" << endl;
						cout << endl << endl << endl;cout << setw(45) << "Acta Final" << endl << endl;
						cout << "JRV Numero: " << num_urna << endl;
						cout << " #" << setw(8) << "DUI" << setw(25) << "NOMBRE" << setw(23) << "CARGO" << endl;
						
						for (int x = 0; x <integrantes; x ++){
							cout << x + 1 << setw(15) << registro_Urna[x].dui << setw(25) << registro_Urna[x].nombre <<
								setw(20) << registro_Urna[x].cargo << endl;
						}//fin for x
						totvotos = vto_pp + vto_upn + vto_nulo;
						cout << "\n\n\nTotal de votos efectuados: " << totvotos << endl;
						cout << "--------------------------------------------" << endl;
						cout << "voto PP   = " << vto_pp << endl;
						cout << "voto UPN  = " << vto_upn << endl;
						cout << "voto NULO = " << vto_nulo << endl;
						abstenciones = total_reg - totvotos;
						cout << "Abstenciones: " << abstenciones << endl;
						
						if(vto_pp>vto_upn){ // si pp es mayor a upn entonces el ganador es pp
							cout<<"El ganador es: \"PP\" con "<<vto_pp<<" votos"<<endl;
						} else if(vto_pp<vto_upn){ // si pp es menor a upn entonces el ganador es upn
							cout<<"El ganador es: \"UPN\" con "<<vto_upn<<" votos"<<endl;
						} else if(vto_pp==vto_upn){ //si son iguales entonces hay un empate
							cout<<"HA SIDO UN EMPATE "<<endl;
						}        
						cout << "Observaciones :";
						break;
						
						case'5':
							cout << "\nCerrando Sistema de Votacion";
							Sleep(0500); cout << "..."; Sleep(0300); cout << "..."; Sleep(0600); cout << "....";Sleep(0500); cout << "..."; Sleep(0300); cout << "."; Sleep(0600); cout << ".."  << endl << endl << endl;
							remove("Acta.html");
							remove("Acta.txt");
							remove("IntegrantesJRV.txt");
							remove("votos_registrados.txt");
							break;
							
							case'a':case'A':
								salidaarchivo.open("Acta.txt",ios::out);
								salidaarchivo<<setw(53)<<"Sistema de Votacion 2014"<<endl;
								salidaarchivo<<setw(54)<<"Tribunal supremo electoral"<<endl;
								salidaarchivo<<setw(40)<<"JRV  \""<<num_urna<<"\""<<endl;
								salidaarchivo<< setw(45) << "Acta Final" << endl << endl;
								salidaarchivo<< "JRV Numero: " << num_urna << endl;
								salidaarchivo<< " #" << setw(8) << "DUI" << setw(25) << "NOMBRE" << setw(23) << "CARGO" << endl;
								
								for (int x = 0; x <integrantes; x ++){
									salidaarchivo << x + 1 << setw(15) << registro_Urna[x].dui << setw(25) << registro_Urna[x].nombre <<setw(20) << registro_Urna[x].cargo << endl;
								}//fin for x
								totvotos = vto_pp + vto_upn + vto_nulo;  abstenciones = total_reg - totvotos;
								salidaarchivo<< "\n\n\nTotal de votos efectuados: " << totvotos << endl;
								salidaarchivo<< "--------------------------------------------" << endl;
								salidaarchivo<< "voto PP   = " << vto_pp << endl;
								salidaarchivo<< "voto UPN  = " << vto_upn << endl;
								salidaarchivo<< "voto NULO = " << vto_nulo << endl;
								salidaarchivo<< "Abstenciones: " << abstenciones << endl;
								
								if(vto_pp>vto_upn){ // si pp es mayor a upn entonces el ganador es pp
									salidaarchivo<<"El ganador es: \"PP\" con "<<vto_pp<<" votos"<<endl;
								} else if(vto_pp<vto_upn){ // si pp es menor a upn entonces el ganador es upn
									salidaarchivo<<"El ganador es: \"UPN\" con "<<vto_upn<<" votos"<<endl;
								} else if(vto_pp==vto_upn){//si son iguales entonces hay un empate
									salidaarchivo<<"HA SIDO UN EMPATE "<<endl;
								}        
								salidaarchivo<<" Observaciones: "<<endl;
								
								salidaarchivo.close();
								cout<<"\n\n Archivo Acta.txt fue creado satisfactoriamente";
								break;
	case 'b':case'B'://hace lo mismo que opcion 'a', pero en formato web
		salidaarchivo.open("Acta.html",ios::out);
		salidaarchivo<<"<html>\n<body bgcolor=\"#1e5799\">\n";
		salidaarchivo<<"<br><p align=\"center\"><table  bgcolor=\"white\" border=\"1\"  "<<"width=\"90%\">\n<tr>"<<endl;
		salidaarchivo<<endl<<"<tr>"<<"<td  rowspan=\"10\">"<<"<p align=\"center\"> Numero de junta: "<<num_urna<<"</td>"<<"</tr>";
		salidaarchivo<<endl<<"<th bgcolor=\"C6FCE0\" color=\"white\"> # "<<"</th><th bgcolor=\"C6FCE0\" color=\"white\">"<<setw(25)<<"Dui"<<"</th><th bgcolor=\"C6FCE0\" color=\"white\">"<<setw(12)<<"Nombre"<<"</th><th bgcolor=\"C6FCE0\" color=\"white\">"<<setw(11)<<"Cargo"<<"</th>"<<endl;
		salidaarchivo<<endl<<"<tr>\n";
		for (int x = 0; x <integrantes; x ++){
			salidaarchivo <<"<td>"<<setw(3)<< x + 1 <<"</td><td>"<< setw(15) << registro_Urna[x].dui <<"</td><td>"<< setw(25) << registro_Urna[x].nombre <<"</td><td>"<<setw(20) << registro_Urna[x].cargo <<"</td></tr>"<< endl;
		}//fin for x
		salidaarchivo<<"\n</table></p>\n</tr>"<<endl;
		salidaarchivo<<"<p align=\"center\"><table  bgcolor=\"white\" border=\"1\"  "<<"width=\"90%\">\n<tr>"<<endl;
		totvotos = vto_pp + vto_upn + vto_nulo;  abstenciones = total_reg - totvotos;
		salidaarchivo<<"<td rowspan=\"4\">"<<"<p align=\"center\"> \n\n\nTotal de votos efectuados: "<< totvotos <<"</td>"<< endl;
		salidaarchivo<<"<th bgcolor=\"C6FCE0\" color=\"#C6FCE0\">"<< " <p align=\"center\"> voto PP   = " << vto_pp <<"</th>";
		salidaarchivo<<"<th bgcolor=\"C6FCE0\" color=\"#C6FCE0\">"<< "<p align=\"center\"> voto UPN  = " << vto_upn <<"</th>";
		salidaarchivo<<"<th bgcolor=\"C6FCE0\" color=\"#C6FCE0\">"<< "<p align=\"center\"> voto NULO = " << vto_nulo <<"</th>";
		salidaarchivo<<"<th bgcolor=\"C6FCE0\" color=\"#C6FCE0\">"<< "<p align=\"center\"> Abstenciones: " << abstenciones <<"</th>"<<"</tr>";
		salidaarchivo<<"\n</table></p>\n</tr>"<<endl;
		salidaarchivo<<"<p align=\"center\"><table  bgcolor=\"white\" border=\"1\"  "<<"width=\"90%\">\n<tr>"<<endl;
		if(vto_pp>vto_upn){ // si pp es mayor a upn entonces el ganador es pp
			salidaarchivo<<"<td rowspan=\"4\">"<<"<p align=\"center\"> El ganador es: \"PP\" con "<<vto_pp<<" votos"<<"</td>"<<"</tr>";
		} else if(vto_pp<vto_upn){ // si pp es menor a upn entonces el ganador es upn
			salidaarchivo<<"<td rowspan=\"4\">"<<"<p align=\"center\"> El ganador es: \"UPN\" con "<<vto_upn<<" votos"<<"</td>"<<"</tr>";
		} else if(vto_pp==vto_upn){//si son iguales entonces hay un empate
			salidaarchivo<<"<tr>"<<"<td rowspan=\"4\">"<<"<p align=\"center\"> HA SIDO UN EMPATE "<<"</td>"<<"</tr>";
		} //fin else-fin ganador      
		salidaarchivo<<"<tr>"<<"<td rowspan=\"4\">"<<" <p align=\"center\"> Observaciones: "<<"</td>"<<"</tr>";
		salidaarchivo<<"\n</table></p>\n</tr></body>\n</html>\n";     
		salidaarchivo.close();
		cout<<"\n\n Informacion exportada a pag. web Acta.html";
		break;
	default:
		cout << endl << "\tComando no valido!" << endl << endl;
		break;
	}//fin switch opcn
	cout << endl << "Presione una tecla para continuar..." << endl; getch();
} while (opc != '5');
}//fin funcion principal main()

void NumeroJunta(char junta[]){
	system("cls");
	cout.setf(ios::fixed);
	cout << setw(53) << "Sistema de Votacion 2014" << endl;
	cout << setw(54) << "Tribunal Supremo Electoral" << endl;
	cout<<"\nPrograma dedicado al sistema de votaciones electorales periodo 2014"<<endl<<endl;
	cout<<"Reglamento:"<<endl;
	cout<<"**> Solo podra realizar el voto una vez"<<endl;
	cout<<"**> Dui que no este registrado en padron sera anulado"<<endl;
	cout<<"**> Voto doble sera anulado"<<endl;
	cout<<"**> Tendra que registrarse previamente en el padron electoral"<<endl;
	cout<<"**> Podra agregar las anomalias de la JRV en observaciones"<<endl;
	cout<<"**> Para salir de la votacion usar F12 "<<endl;
	cout<<"**> Votara unicamente con su numero de \"DUI\"";
	cout << endl << endl;system("pause");system("cls");
	cout << setw(53) << "Sistema de Votacion 2014" << endl;
	cout << setw(54) << "Tribunal Supremo Electoral" << endl;
	cout << "\nDefina el Numero de Urna: ";
	cin.getline(junta, 15);
}//fin funcion iniciaVotacion

void iniciaVotacion(int total, int total2,votante lista[], char buscar_dui[], int &pp, int &upn, int &nulo){
	int comprobante=0;int comprobante1=0;
	char opciones;
	ofstream archivo;//flujo de acceso para archivos
	
	do{
		system("cls");
		for (int a=1; a <= total2; a++){
			if (strcmp(buscar_dui, lista[a].dui_registrado)==0){
				comprobante1=1;
			}//fin if comprobante1
		}//fin for a
		
		if (comprobante1 != 0){
			cout << "Atencion DUI " << buscar_dui << " Ya finaliz" << char(162) << " su proceso de votaci" << char(162) << "n" << endl;
		}else{
			for (int i = 1; i <= total; i++){
				if (strcmp(buscar_dui, lista[i].dui) == 0){
					comprobante = 1;
				}//fin de if
			}//fin de for i
			
			if (comprobante != 0){
				cout << "\n\n\tEscoja Uno de los Partidos Electos" << endl;
				cout << "\t1. Partido Popular" << endl;
				cout << "\t2. Union Patri" << char(162) << "tica Nacional" << endl;
				cout << "\t3. Ninguno de los dos (X)" << endl;
				cout << "\n\nOPCION SELECCIONADA: ";
				opciones = getche();
				switch (opciones){
					case'1':
						pp++;
						archivo.open("votos_registrados.txt",ios::app);
						archivo<<buscar_dui<< endl;
						archivo.close();
						break;
						case'2':
							upn++;
							archivo.open("votos_registrados.txt",ios::app);
							archivo<<buscar_dui<< endl;
							archivo.close();
							break;
							case'3':
								nulo++;
								archivo.open("votos_registrados.txt",ios::app);
								archivo<<buscar_dui<< endl;
								archivo.close();
								break;
				default:
					nulo++;
					archivo.open("votos_registrados.txt",ios::app);
					archivo << buscar_dui << endl;
					archivo.close();
				}//fin switch opciones
			}
			else{
				cout << "Su numero de DUI " << buscar_dui << " No esta Registrado en el Padron Electoral!!" << endl;
			}//fin if-else comprobante
		}//fin if-else comprobante1 
		cout << "\n\n\tPresione la tecla F12 para salir!!" << endl;
		getch() == 0;
	} while (getch() != 134);
}//fin funcion iniciaVotacion()

void registroIntegrantes(RegistroJRV ingreso[],char urna[],int &numero){//numero de integrantes en la JRV
	fstream archivo;//flujo de acceso para archivos
	
	cout << "Ingreso de Integrantes Para La Urna " << urna << endl;
	cout << "\n\nDefina el numero de Personas a integrar la Junta :";cin >> numero;
	if (numero < 0){
		cout << "Atencion verifique el numero de Integrantes de la JUNTA!!" << endl;
	}
	else{
		for (int b = 0; b < numero; b++){
			cout << "Registro de Integrante No " << b + 1 << endl;
			cout << "Numero de DUI: "; fflush(stdin); cin.getline(ingreso[b].dui, 15);
			cout << "Nombre: "; fflush(stdin); cin.getline(ingreso[b].nombre, 20);
			cout << "Apellidos: "; fflush(stdin); cin.getline(ingreso[b].apellido, 20);
			cout << "Cargo: "; fflush(stdin); cin.getline(ingreso[b].cargo, 15);
		}//fin for b
	}//fin if-else numero
	
	archivo.open("IntegrantesJRV.txt", ios::out);
	archivo << numero << endl;
	for (int j = 0; j < numero; j++){
		archivo << ingreso[j].dui << endl;
		archivo << ingreso[j].nombre << endl;
		archivo << ingreso[j].apellido << endl;
		archivo << ingreso[j].cargo << endl;    }//fin for j
	archivo.close();
	cout << "Procesando Informacion";Sleep(0500); cout << "..."; Sleep(0300); cout << "..."; Sleep(0600); cout << "...." << endl << endl << endl;
	cout << "\n\nIntegrantes Registradoss!!" << endl;
}//fin funcion RegistrosIntegrantes()
