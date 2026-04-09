#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <regex>
#include <cstdlib>
#include <stdbool.h>
#include <stdexcept>

using namespace std;

void opcion_a(FILE *archivo);
void opcion_b(FILE *archivo_destinos, FILE *archivo_vuelos);
void opcion_c(FILE *archivo);
void opcion_d(FILE *archivo);

int main()
{
    FILE *archivo_vuelos, *archivo_destinos;

    char opcion[3];

    do
    {
        do
        {
            system("cls");
            cout << "REGISTRO AEROPORTUARIO" <<endl;
            cout << "a. Registro  de destinos" <<endl;
            cout << "b. Registro de vuelos" <<endl;
            cout << "c. Listado de destinos " <<endl;
            cout << "d. Listado de vuelos" <<endl;
            cout << "e. Salir" <<endl;
            cin >> opcion;
            cin.ignore();

            if(strcmp(opcion, "a")!=0 && strcmp(opcion, "b")!=0 && strcmp(opcion, "c")!=0 && strcmp(opcion, "d")!=0 && strcmp(opcion, "e")!=0)
            {
                cout << endl << "ERROR: Esa opcion no existe!!" << endl;
                system("pause");
            }

        }while (strcmp(opcion, "a")!=0 && strcmp(opcion, "b")!=0 && strcmp(opcion, "c")!=0 && strcmp(opcion, "d")!=0 && strcmp(opcion, "e")!=0);
    

        switch(opcion[0])
        {
            case 'a':
                try
                {
                    archivo_destinos=fopen("destinos.txt", "ab+");

                    if(archivo_destinos == NULL)
                        throw runtime_error("ERROR: no se pudo abrir el archivo");

                    opcion_a(archivo_destinos);
                    fclose(archivo_destinos);
                }

                catch(const runtime_error& e)
                {
                    cerr << e.what() << endl;
                }

            break;
            case 'b':

                try
                {
                    archivo_destinos=fopen("destinos.txt", "r");
                    archivo_vuelos=fopen("viajes.txt", "ab+");

                    if(archivo_destinos == NULL || archivo_vuelos == NULL)
                        throw runtime_error("ERROR: no se pudo abrir el archivo");

                    opcion_b(archivo_destinos, archivo_vuelos);
                    fclose(archivo_destinos);
                    fclose(archivo_vuelos);
                }

                catch(const runtime_error& e)
                {
                    cerr << e.what() << endl;
                }

            break;
            case 'c':

                try
                {
                    archivo_destinos=fopen("destinos.txt", "r");

                    if(archivo_destinos == NULL)
                        throw runtime_error("ERROR: no se pudo abrir el archivo");

                    opcion_c(archivo_destinos);
                    fclose(archivo_destinos);
                }

                catch(const runtime_error& e)
                {
                    cerr << e.what() << endl;
                }

            break;
            case 'd':

                try
                {
                    archivo_vuelos = fopen("viajes.txt", "r");

                    if(archivo_vuelos == NULL)
                        throw runtime_error("ERROR: no se pudo abrir el archivo");

                    opcion_d(archivo_vuelos);
                    fclose(archivo_vuelos);
                }

                catch(const runtime_error& e)
                {
                    cerr << e.what() << endl;
                }

            break;
        }
    } while (strcmp(opcion, "e") != 0);
    

}



bool buscar_destino(FILE *archivo_destinos, FILE *archivo_vuelos, string respuesta)
{
    regex patron_desc("[A-Z][A-Za-z ]+");
    int indicador;
    string clave, descripcion, precio, respuesta2;
    char cclave[15], cdescripcion[150], cprecio[10];

    do
    {
        indicador = 0;
        rewind(archivo_destinos);
        while (fscanf(archivo_destinos, "%[^,],%[^,],%[^\n]\n", cclave, cdescripcion, cprecio) == 3)
        {
            clave = cclave;
            descripcion = cdescripcion;
            precio = cprecio;

            if(descripcion == respuesta)
            {
                indicador = 1;

                cout << "Destino elegido: " << endl;
                cout << left << setw(25) << "Clave del destino: " << setw(10) << clave << endl;
                cout << left << setw(25) << "Descripcion: " << setw(10) << descripcion << endl;
                cout << left << setw(25) << "Precio: " << setw(10) << precio << endl << endl;

                do
                {
                    cout << "Es correcto? (si/no)";
                    getline(cin, respuesta2);

                    if(respuesta2 != "si" && respuesta2 != "no")
                        cout << endl << "ERROR: Ingrese \"si\" o \"no\"" << endl;

                }while(respuesta2 != "si" && respuesta2 != "no");

                if(respuesta2 == "no")
                {
                    rewind(archivo_destinos);
                    do
                    {
                        cout << "Introduzca el destino deseado" << endl;
                        getline(cin, respuesta);

                        if(!regex_match(respuesta, patron_desc))
                            cout << "Utilice el formato de descripcion correcto (Empieza en una letra mayuscula y contiene solo letras y espacios)" << endl;

                    }while(!regex_match(respuesta, patron_desc));
                }
                return true;             
            }
        }

        if(indicador == 0)
        {
            cout << endl << "ERROR:No existen destinos con la descripcion ingresada." << endl
                 << "Asegurese que ingreso la descripcion correctamente o registre el destino en la opcion \"a\" del menu principal" << endl;
            return false;
        }

    }while(respuesta2 == "no");
}

bool validar_fechas(string fecha1, string fecha2)
{
    string fecha1_2, fecha2_2, dia, mes, ano;

    dia = fecha1.substr(0, 2);
    mes = fecha1.substr(3, 2);
    ano = fecha1.substr(6, 4);

    fecha1= ano + "-" + mes + "-" + dia;

    dia = fecha2.substr(0, 2);
    mes = fecha2.substr(3, 2);
    ano = fecha2.substr(6, 4);

    fecha2= ano + "-" + mes + "-" + dia;

    if(fecha1 < fecha2)
        return true;
    else
        return false;
}


bool validar_existencia(FILE *archivo, string respuesta)
{
    char cclave[10], cdescripcion[50], cprecio[10];
    string clave;

    rewind(archivo);
    while(fscanf(archivo, "%[^,],%[^,],%[^\n]\n", cclave, cdescripcion, cprecio) == 3)
    {
        clave = cclave;

        if(respuesta == clave)
            return true;
    }

    return false;
}


void opcion_a(FILE *archivo) //clave del destino, descripcion y precio.
{

    regex patron_clave(R"(M_[0-9]{4})"), patron_desc("[A-Z][A-Za-z ]+"), patron_precio("[1-9][0-9]{2,4}\\.[0-9]{2}");
    string clave, respuesta, descripcion, precio;

    cout << "REGISTRO DE DESTINOS" <<endl;

    do
    {
        do
        {
            cout << "-- > Para continuar al registro, ingrese \"si\". \n-- > Para salir, presione 0" << endl;
            getline(cin, respuesta);

        }while(respuesta != "si" && respuesta != "0");

        if(respuesta == "si")
        {
            system("cls");
            do
            {
                try
                {
                    cout << "Introduzca la clave del destino (siguiendo el formato M_####)" << endl;
                    getline(cin, clave);

                    if(!regex_match(clave, patron_clave))
                        throw invalid_argument("ERROR: Formato no valido");

                }
                    catch(const invalid_argument& e)
                    {
                        cerr << e.what() << endl;
                    }

                if(!regex_match(clave, patron_clave))
                    cout << endl << "ERROR: Recuerde seguir el formato: M_####, donde \"#\" es un numero" << endl;
                
                if(regex_match(clave, patron_clave) && validar_existencia(archivo, clave))
                    cout << endl << "ERROR: La clave " << clave << " ya existe en el registro" << endl;
                
            }while(!regex_match(clave, patron_clave) || validar_existencia(archivo, clave));

            do
            {
                cout << "Introduzca el nombre del destino" << endl;
                getline(cin, descripcion);

                if(!regex_match(descripcion, patron_desc))
                    cout << endl << "ERROR: La descripcion debe comenzar con una letra mayuscula seguida de letras y/o espacios" << endl;

            } while (!regex_match(descripcion, patron_desc));

            do
            {
                cout << "Introduzca el precio a este destino" << endl;
                getline(cin, precio);

                if(!regex_match(precio, patron_precio))
                    cout << endl << "ERROR: El precio debe ser de minimo $100 y maximo $99999, y debe incluir" <<endl
                         << "los primeros dos decimales del precio. Ej. \"100.00\"" <<endl;

            } while (!regex_match(precio, patron_precio));

            fprintf(archivo, "%s,%s,%s\n", clave.c_str(), descripcion.c_str(), precio.c_str());

        }

        if(respuesta != "0" && respuesta != "si")
            cout << endl << "ERROR: ingrese \"si\" o \"0\"" << endl;

    }while (respuesta == "si");
    
    system("cls");
}

void opcion_b(FILE *archivo_destinos, FILE *archivo_vuelos) //COMPRAR BOLETO A UN DESTINO EXISTENTE EN destinos.txt
{

    regex patron_clave(R"(M_[0-9]{4})"), patron_fecha("([0][1-9]|[1-2][0-9]|[3][0-1])\\-(0[1-9]|1[0-2])\\-(202[5-9]|20[3-9][0-9])"), patron_desc("[A-Z][A-Za-z ]+");
    string respuesta, respuesta2, clave, descripcion, precio, partida, regreso;
    char cclave[15], cdescripcion[150], cprecio[10];
    float precio_float;
    int indicador = 0;

    cout << "COMPRA DE BOLETOS" << endl;

    if(fscanf(archivo_destinos, "%[^,],%[^,],%[^\n]\n", cclave, cdescripcion, cprecio)==3)
    {
        do
        {
            do
            {
                cout << " -- > Para registrar, introduzca el nombre del destino deseado." << endl
                     << " -- > Para conocer los destinos disponibles ingrese 0" << endl
                     << " -- > Para regresar al menu principal ingrese -1" << endl;
                getline(cin, respuesta);

                if(respuesta != "0" && !regex_match(respuesta, patron_desc) && respuesta != "-1")
                    cout << endl << "ERROR: Escriba una respuesta valida por favor." << endl << endl;

            }while (respuesta != "0" && !regex_match(respuesta, patron_desc) && respuesta != "-1");

            if(regex_match(respuesta, patron_desc))
            {
                
                if(buscar_destino(archivo_destinos, archivo_vuelos, respuesta))
                {
                    indicador=0;
                    rewind(archivo_destinos);
                    while (fscanf(archivo_destinos, "%[^,],%[^,],%[^\n]\n", cclave, cdescripcion, cprecio) == 3 && indicador == 0)
                    {
                        clave = cclave;
                        descripcion = cdescripcion;
                        precio = cprecio;

                        if(descripcion == respuesta)
                            indicador = 1;
                    }                    
                    //cout << "INDICADOR: " << indicador << endl;
                    cout << endl << "Se ha seleccionado el destino: " << respuesta << endl;

                    do
                    {
                        cout << "Desea un viaje redondo? (si/no)" << endl;
                        getline(cin, respuesta2);

                        if(respuesta2 != "si" && respuesta2 != "no")
                            cout << endl << "ERROR: Ingrese \"si\" o \"no\"" << endl;

                    }while (respuesta2 != "si" && respuesta2 != "no");
                    
                    if(respuesta2 == "si")
                    {
                        precio_float = stof(precio);

                        cout << fixed << setprecision(2) << "El precio para un viaje redondo al destino " << respuesta << " es $" << 2*precio_float << endl;
                        
                        do
                        {
                            do
                            {
                                cout << "Introduzca la fecha del viaje de ida (DD-MM-AAAA): ";
                                getline(cin, partida);

                                if(!regex_match(partida, patron_fecha))
                                    cout << endl << "ERROR: Ingrese una fecha valida. Siga el formato (DD-MM-AAAA) y asegurese de que la fecha no sea de antes del 2025" << endl;

                            }while(!regex_match(partida, patron_fecha));

                            do
                            {
                                cout << "Introduzca la fecha del viaje de regreso (DD-MM-AAAA): ";
                                getline(cin, regreso);

                                if(!regex_match(regreso, patron_fecha))
                                    cout << endl << "ERROR: Ingrese una fecha valida. Siga el formato (DD-MM-AAAA) y asegurese de que la fecha no sea de antes del 2025" << endl;

                            }while(!regex_match(regreso, patron_fecha));

                            if(!validar_fechas(partida, regreso))
                                cout << endl << "ERROR: La fecha de regreso no puede ser de antes de la fecha de partida." << endl;

                        }while(!validar_fechas(partida, regreso));

                        fprintf(archivo_vuelos, "%s,%.2f,%s,%s\n", descripcion.c_str(), 2*precio_float, partida.c_str(), regreso.c_str());

                        cout << "Viaje redondo registrado." << endl;
                    }
                    else
                    {
                        regreso = "NA";
                        precio_float = stof(precio);
                        cout << "El precio para un viaje sencillo al destino " << descripcion << " es $" << precio_float << endl;
                        do
                        {
                            cout << "Introduzca la fecha del viaje (DD-MM-AAAA): ";
                            getline(cin, partida);

                            if(!regex_match(partida, patron_fecha))
                                cout << endl << "ERROR: Ingrese una fecha valida. Siga el formato (DD-MM-AAAA) y asegurese de que la fecha no sea de antes del 2025" << endl;

                        }while(!regex_match(partida, patron_fecha));

                        fprintf(archivo_vuelos, "%s,%.2f,%s,%s\n", descripcion.c_str(), precio_float, partida.c_str(), regreso.c_str());

                        cout << "Viaje registrado." << endl;
                    }
                    
                }
                    
                    
            }
            else
            {
                if(respuesta == "0")
                        opcion_c(archivo_destinos);
                else
                {    
                    if(respuesta == "-1")
                        return;
                    else
                        cout << endl << "ERROR: Introduzca solo una clave de formato \"M_####\", el numero 0 o -1." << endl;
                }
            }

        }while(respuesta != "-1");
    }
    else
        cout << endl << "ERROR: No hay destinos registrados. Entre al registro de destinos antes de comprar boletos." << endl;

    system("cls");
}


void opcion_c(FILE *archivo_destinos)
{
    string clave, descripcion, precio;
    char cclave[10], cdescripcion[100], cprecio[10];
    int indicador=0;
    rewind(archivo_destinos);

    cout << "LISTADO DE DESTINOS" << endl << endl;


    while (fscanf(archivo_destinos, "%[^,],%[^,],%[^\n]\n", cclave, cdescripcion, cprecio) == 3)
    {
        clave = cclave;
        descripcion = cdescripcion;
        precio = cprecio;
        cout << left << setw(25) << "Clave del destino: " << setw(10) << clave << endl;
        cout << left << setw(25) << "Descripcion: " << setw(10) << descripcion << endl;
        cout << left << setw(25) << "Precio: " << setw(10) << precio << endl << endl;

        indicador = 1;
    }

    if(indicador != 1)
        cout << "No se han registrado destinos aun." << endl << endl;

    system("pause");
}

void opcion_d(FILE *archivo_vuelos)
{
    int opcion, indicador=0;
    regex patron_fecha("([0][1-9]|[1-2][0-9]|[3][0-1])\\-(0[1-9]|1[0-2])\\-(202[5-9]|20[3-9][0-9])");
    string destino, precio, fecha_partida, fecha_regreso, respuesta;
    char cdestino[50], cprecio[10], cfecha_partida[15], cfecha_regreso[15];

    do
    {

        cout << "1. Mostrar todos los vuelos registrados" << endl
             << "2. Mostrar los vuelos de una fecha" << endl;
        cin >> opcion;
        cin.ignore();

        if(opcion != 1 && opcion != 2)
        {
            cout << endl << "ERROR: Respuesta no valida" << endl << endl;
        }

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

    }while(opcion != 1 && opcion != 2);

    switch(opcion)
    {
        case 1:
            while (fscanf(archivo_vuelos, "%[^,],%[^,],%[^,],%[^\n]\n", cdestino, cprecio, cfecha_partida, cfecha_regreso) == 4)
            {
                destino = cdestino;
                precio = cprecio;
                fecha_partida = cfecha_partida;
                fecha_regreso = cfecha_regreso;

                cout << left << setw(25) << "Destino: " << setw(25) << destino << endl;
                cout << left << setw(25) << "Precio: " << setw(25) << precio << endl;
                cout << left << setw(25) << "Fecha de partida: " << setw(25) << fecha_partida << endl;
                cout << left << setw(25) << "Fecha de regreso: " << setw(25) << fecha_regreso << endl << endl;

                indicador = 1;
            }

            if (indicador != 1)
                cout <<" -- No se han registrado vuelos aun --" << endl << endl;
            
            system("pause");
        break;
        case 2:
            do
            {
                cout << "Introduzca la fecha a consultar (DD-MM-AAAA): ";
                getline(cin, respuesta);

                if(!regex_match(respuesta, patron_fecha))
                    cout << endl <<"ERROR: Introudzca la fecha en el formato correcto. Recuerde usar fechas de 2025 en adelante." << endl << endl;

            }while(!regex_match(respuesta, patron_fecha));
            
            cout << endl;

            while (fscanf(archivo_vuelos, "%[^,],%[^,],%[^,],%[^\n]\n", cdestino, cprecio, cfecha_partida, cfecha_regreso) == 4)
            {
                destino = cdestino;
                precio = cprecio;
                fecha_partida = cfecha_partida;
                fecha_regreso = cfecha_regreso;

                if(fecha_partida == respuesta || fecha_regreso == respuesta)
                {
                    cout << left << setw(25) << "Destino: " << setw(25) << destino << endl;
                    cout << left << setw(25) << "Precio: " << setw(25) << precio << endl;
                    cout << left << setw(25) << "Fecha de partida: " << setw(25) << fecha_partida << endl;
                    cout << left << setw(25) << "Fecha de regreso: " << setw(25) << fecha_regreso << endl << endl;
                    indicador = 1;
                }

            }

            if (indicador != 1)
                cout << " -- No se han encontrado vuelos en esa fecha --" << endl << endl;
            
            system("pause");
        break;
    }


}