// coneccion base de datos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"trabajos", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS); 
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            cout << "Conectado a la base de datos exitosamente." << endl;

            // Ejemplo de ejecución de una consulta
            SQLHSTMT hStmt;
            ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
            cout << "+----------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "|Numero de empleado" <<  "| Nombre           "  << "|Fecha de nac "  << "|RFC           "  << "|Nombre del centro:    "  << "|Descripcion del puesto " << "|¿Es directivo?" << endl;
            cout << "+----------------------------------------------------------------------------------------------------------------------+" << endl;
            // Ejemplo de consulta SELECT
            ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM EMPLEADO", SQL_NTS);
            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                int NUMERO_DE_EMPLEADO;
                SQLCHAR NOMBRE[50];
                SQLDATE FECHA_DE_NACIMIENTO[8];
                SQLCHAR RFC[50];
                SQLCHAR NOMBRE_DE_CENTRO[50];
                SQLCHAR DESCRIPCION_DEL_PUESTO[50];
                SQLCHAR ESDIRECTIVO [50];
                while (SQLFetch(hStmt) == SQL_SUCCESS) {
                    SQLGetData(hStmt, 1, SQL_C_LONG, &NUMERO_DE_EMPLEADO, 0, NULL);
                    SQLGetData(hStmt, 2, SQL_C_CHAR, NOMBRE, sizeof(NOMBRE), NULL);
                    SQLGetData(hStmt, 3, SQL_C_DATE, FECHA_DE_NACIMIENTO, sizeof(FECHA_DE_NACIMIENTO), NULL);
                    SQLGetData(hStmt, 4, SQL_C_CHAR, RFC, sizeof(RFC), NULL);
                    SQLGetData(hStmt, 5, SQL_C_CHAR, NOMBRE_DE_CENTRO, sizeof(NOMBRE_DE_CENTRO), NULL);
                    SQLGetData(hStmt, 6, SQL_C_CHAR, DESCRIPCION_DEL_PUESTO, sizeof(DESCRIPCION_DEL_PUESTO), NULL);
                    SQLGetData(hStmt, 7, SQL_C_CHAR, ESDIRECTIVO, sizeof(ESDIRECTIVO), NULL);
                    cout <<"|                " <<  NUMERO_DE_EMPLEADO << "|  " << NOMBRE <<"|           "<< FECHA_DE_NACIMIENTO  <<"|  "<< RFC <<"|     " << NOMBRE_DE_CENTRO <<"|               "<< DESCRIPCION_DEL_PUESTO << "|   " << ESDIRECTIVO << endl;
                    

                }
            }
               
            // Liberar el manejador de conexión
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        }
        else {
            cout << "Fallo la conexion a la base de datos" << endl;
        }

    // Desconectar y liberar gestores de entorno
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}