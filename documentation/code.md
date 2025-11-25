# Directivas principales:
PROJECT: Nombre del projecto
BEGIN: Punto de inicio en 0
END: Punto de fin en (-1ULLL)(MAX_ULONGLONG)
SOURCES: Archivo fuente del codigo que se ejecuta
WORKSPACES: Carpeta donde se genera el codigo principal
USERWORKSPACES: Directiva que a partir de la entrada del usuario define una nueva ruta
__NOW__: Directiva del tiempo en segundos como valor entero
NOW: Directiva de tiempo con formato corto de cadena de caracteres
TRUE: Valor verdadero para casos boleanos
FALSE: Valor false para casos boleanos
FILE: Valor para la funcion generate que indica archivo
FOLDER: Valor para la funcion generate que indica carpeta

# Estuctura del codigo
funcion_1 : funcion_2 : ... : funcion_sin_concatenacion
funcion_3 : [
    funcion_4_con_mismo_nivel : ... : funcion_sin_concatenacion
]
end
.nombre_de_etiqueta_1:
...
Caracter nulo.nombre_de_etiqueta_2:
...

## Aclaraciones:
1. Si no se desea agregar mas etiquetas, todo el codigo se leera hasta el final del archivo
2. Si se agregan mas etiquetas deben ir delante un caracter nulo
3. Todas las funciones dentro de [] estan con el mismo valor de retorno de la funcion concatenada al bloque

# Funciones
1. dir(cadena_de_caracteres): crea un tipo de direcion de path a partir de un string con ""
2. generate(nombre, si_es_una_carpeta): crea un nuevo archivo/carpeta con el nombre especificado dentro de un valor de retorno de tipo Path
3. write(pocision_de_inicio, numero_de_caracteres, cadena_de_caracteres_de_etiqueta): escribe segun los parametros especificados todo el texto que se desee desde la lectura de la etiqueta, hasta el final del archivo o un caracter nulo
4. end: finaliza la lectura de codigo ejecutivo y pasa al modo de lectura de texto de copia si es necesario
5. Todo texto despues de end que comience con un . y termine en : se considerara una etiqueta