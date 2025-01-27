/*********************************************************************
 * 
 * Departamento de Inform�tica de Sistema y Computadores (DISCA)
 * Universidad Politecnica de Valencia.                         
 * 
 * Author: Sergio S�ez (ssaez@disca.upv.es)
 *	   Pedro L�pez (plopez@disca.upv.es)
 * 
 * File: tipos.h
 *  
 * Description: 
 *    Contiene las definiciones de tipos comunes
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *********************************************************************/

#ifndef tipos_H
#define tipos_H

/***** Includes ***********************************************/

#include <sys/types.h>

/***** Constants **********************************************/

#define KB			(1024)

#define TAM_MEMO_DATOS		(16*KB)
#define TAM_MEMO_INSTRUC	(1*KB)

/*** Excepciones */

#define EXC_NONE		0

#define EXC_MEM_INST		1
#define EXC_MEM_DAT		2

#define EXC_TRAP(t)		(32+(t))

/***** Types **************************************************/

typedef unsigned char	byte;	/* Un byte: 8 bits */
typedef short		half;	/* Media palabra: 16 bits */
// typedef long		word;	/* Una palabra: 32 bits */
typedef int		word;	/* Una palabra: 32 bits */

typedef unsigned long 	ulong;

typedef enum 
{
  NO=0, 
  SI=1
} boolean;			/* Valor l�gico */

typedef enum 
{
  t_ninguno, 
  t_word, 
  t_float
} tipo_t;			/* Tipo de dato utilizado */

typedef enum 
{
  m_ninguno, 
  m_datos, 
  m_instruc
} modo_t;			/* Segmento de memoria accedido */

/*** Estructuras esp�cificas ****/

typedef byte	codop_t;	/* C�digo de operaci�n */

typedef enum 
{
  FormatoR, 
  FormatoI, 
  FormatoJ
} formato_t;			/* El formato J no esta implementado */

typedef enum {
  parada, 
  cortocircuito, 
  ninguno
} riesgos_d_t;

typedef enum {
  stall, 
  pnt, 
  ds3,
  ds2,
  ds1
} riesgos_c_t;

typedef enum {
  html, 
  res_ciclo, 
  res_final
} sal_t;
 
/*** Formato de instruccion ****/

typedef struct {
  codop_t	codop;
  formato_t	tipo;

  byte		Rfuente1,	/* �ndice del registro fuente 1 */
		Rfuente2;	/* �ndice del registro fuente 2 */
  byte		Rdestino;	/* �ndice del registro destino */
  half		inmediato;	/* Valor Inmediato */
} instruccion_t;

/*** Banco de registros ********/

typedef struct {
  word		valor;		/* Valor del registro */
} reg_int_t;

/*** Registros inter-etapas ************************************************/

/*** Registros intermedios *******************/


typedef struct {
  instruccion_t	IR;		/* IR */
  word		NPC;       	/* PC+4 */

  word		iPC;		
  long		orden;		/* Informaci�n de visualizaci�n */
} IF_ID_t;

typedef struct {
  instruccion_t	IR;		/* IR */
  word		NPC;       	/* PC+4 */
  word		Ra,		/* Valores de los registros*/
  		Rb;
  word		Imm;		/* Inmediato con signo extendido */

  word		iPC;		
  long		orden;		/* Informaci�n de visualizaci�n */
} ID_EX_t;

typedef struct {
  instruccion_t	IR;		/* IR */
  word		ALUout;		/* Resultado */
  word	        data;	        /* Dato a escribir */
  boolean	cond;		/* Resultado condicion de salto */

  word		iPC;		
  long		orden;		/* Informaci�n de visualizaci�n */
} EX_MEM_t;

typedef struct {
  instruccion_t	IR;		/* IR */
  word		ALUout;		/* Resultado */
  word		MEMout;		/* Resultado */

  word		iPC;		
  long		orden;		/* Informaci�n de visualizaci�n */
} MEM_WB_t;

/*** Estructuras internas de la ruta de datos de coma flotante *************/

/*** Segmento de memoria ********/

typedef struct {
  word	inicio;
  word	final;
} segmento_t;

/*** Memoria de datos ***********/

typedef union {
  word		mword[TAM_MEMO_DATOS/sizeof(word)];
  float		mfloat[TAM_MEMO_DATOS/sizeof(float)];
} memoria_datos_t;

/*** Memoria de instrucciones ***/

typedef instruccion_t	memoria_intrucciones_t[TAM_MEMO_INSTRUC];

/***** Macros *************************************************/

#define dir_word(d) (word)((d) / sizeof(word))
#define dir_float(d) (word)((d) / sizeof(float))

#define esta_alineada_dir_word(d) (((d) % sizeof(word)) == 0 )
#define esta_alineada_dir_float(d) (((d) % sizeof(float)) == 0 )

#endif /* end tipos.h */
