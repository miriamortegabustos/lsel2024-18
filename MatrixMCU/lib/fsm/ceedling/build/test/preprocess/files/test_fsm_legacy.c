#include "build/test/mocks/mock_test_fsm.h"
#include "../include/fsm.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


/**

 * @file test_fsm_legacy.c

 * @author 

 * @author 

 * @brief Tests for existing fsm module

 * @version 0.1

 * @date 2024-04-09

 * 

 */



/**

 * @brief Stub or Callback for fsm_malloc that calls real malloc. 

 * 

 * @param[in] s Amount of bytes to allocate

 * @param[in] n Amount of calls to this function

 * 

 * @return pointer to allocated memory if success; NULL if fails

 * 

 */

static void* cb_malloc(size_t s, int n) {

    return malloc(s);

}



/**

 * @brief Stub or Callback for fsm_free that calls real free. 

 * 

 * @param[in] p Pointer to allocated memory to free

 * @param[in] n Amount of calls to this function

 * 

 */

static void cb_free(void* p, int n) {

    return free(p);

}



void setUp(void)

{

}



void tearDown(void)

{

}



/**

 * @brief Comprueba que la funcion de fsm_new devuelve NULL 

 *        y no llama a fsm_malloc si la tabla de transiciones es NULL 

 */

void test_fsm_new_nullWhenNullTransition(void)

{

    fsm_trans_t tt[] = {

        //{},

        {-1, NULL, -1, NULL}

    };



    fsm_t *f = (fsm_t*)1;



    f = fsm_new(tt);



    TEST_ASSERT_EQUAL (NULL, f);

}



/**

 * @brief Comprueba que la funcin de inicializacin devuelve -1 si el puntero a la maquina de estado es NULL 

 *

 */

void test_fsm_init_MinusOneWhenNullFsm(void)

{

    fsm_trans_t tt[] = {

        //{},

        {-1, NULL, -1, NULL}

    };



    fsm_t *f = NULL;



    int ini = fsm_init(f, tt);



    TEST_ASSERT_EQUAL (-1, ini);

}



/**

 * @brief Funcin de inicializacion devuelve -1 si la tabla de transiciones es nula

 * 

 */

void test_fsm_init_MinusOneWhenNullTransitions(void)

{

    fsm_t *f = (fsm_t*)1;



    fsm_trans_t* tt = NULL;



    int ini = fsm_init(f, tt);

    

    TEST_ASSERT_EQUAL (-1, ini);

}



/**

 * @brief Funcin de inicializacion devuelve el numero de transiciones

 * 

 */

void test_fsm_init_returnNumberOfTransitions(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {1, is_true, 0, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;



    int retVal = fsm_init(&f, tt);

    

    TEST_ASSERT_EQUAL (2, retVal);

}



/**

 * @brief Funcin de inicializacion devuelve 0 si hay ms de 128 transiciones

 * 

 */

void test_fsm_init_returnZeroIfNumberOfTransitionsOver128(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL},

        {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {0, is_true, 1, NULL}, {1, is_true, 0, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;



    int retVal = fsm_init(&f, tt);

    

    TEST_ASSERT_EQUAL (0, retVal);

}



/**

* @brief La mquina de estados devuelve NULL 

*        y no llama a fsm_malloc si el estado de origen 

*        de la primera transicin es -1 (fin de la tabla)

*/

void test_fsm_nullWhenFirstOrigStateIsMinusOne (void) {

    fsm_trans_t tt[] = {

        {-1, is_true, 1, do_nothing}

    };

    fsm_t *f = (fsm_t*)1;

    f = fsm_new(tt);

    

    TEST_ASSERT_EQUAL (NULL, f);

}



/**

 * @brief La mquina de estados devuelve NULL y no llama a fsm_malloc si el estado de destino de la primera transicin es -1 (fin de la tabla)

 * 

 */

void test_fsm_nullWhenFirstDstStateIsMinusOne (void) {

  

    fsm_trans_t tt[] = {

        {0, is_true, -1, do_nothing}

    };

    fsm_t *f = (fsm_t*)1;

    f = fsm_new(tt);

    

    TEST_ASSERT_EQUAL (NULL, f);



}



/**

 * @brief Devuelve puntero no NULL y llama a fsm_malloc (Stub) al crear la maquina de estados con una transicin vlida con funcin de actualizacin (salida) NULL o no NULL.

 *        Aadida tambim test con funcin de guarda NULL y no NULL.

 *        Hay que liberar la memoria al final llamando a free

 * 

 */

TEST_CASE(is_true, NULL)

TEST_CASE(is_true, do_nothing)

TEST_CASE(NULL, NULL)

TEST_CASE(NULL, do_nothing)



void test_fsm_new_nonNullWhenOneValidTransitionCondition(fsm_input_func_t in, fsm_output_func_t out)

{

    fsm_trans_t tt[] = {

        {0, in, 1, out},

        {-1, NULL, -1, NULL}

    };



    fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(0);

    fsm_t *f = fsm_new(tt);

    

    TEST_ASSERT_NOT_EQUAL (NULL, f);



    free(f);

}



/**

 * @brief Estado inicial corresponde al estado de entrada de la primera transicin de la lista al crear una maquiina de estados y es valido. 

 * 

 */

void test_fsm_new_fsmGetStateReturnsOrigStateOfFirstTransitionAfterInit(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {-1, NULL, -1, NULL}

    };



    fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(0);

    fsm_t *f = fsm_new(tt);

    

    TEST_ASSERT_EQUAL (0, fsm_get_state(f));

    free(f);

}



/**

 * @brief La maquina de estado no transiciona si la funcion devuelve 0

 * 

 */

void test_fsm_fire_isTrueReturnsFalseMeansDoNothingIsNotCalledAndStateKeepsTheSame(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    fsm_init(&f, tt);



    //is_true_AddCallback(is_true);

    is_true_ExpectAnyArgsAndReturn(0);

    fsm_fire(&f);



    TEST_ASSERT_EQUAL (0, fsm_get_state(&f));

}



/**

 * @brief Fsm fire devuelve -1 si no hay transiciones para el estado actual.

 * 

 */

void test_fsm_fire_returnsMinusOneIfNotTranitionsForCurrentState(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    fsm_init(&f, tt);

    fsm_set_state(&f, 1);



    int ret_value = fsm_fire(&f);



    TEST_ASSERT_EQUAL (-1, ret_value);

}



/**

 * @brief Fsm fire devuelve 0 si hay transiciones para el estado actual pero ninguna se cumple.

 * 

 */

void test_fsm_fire_returnsZeroIfTranitionsExistButNoneAreTrue(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    fsm_init(&f, tt);



    is_true_ExpectAnyArgsAndReturn(0);

    int ret_value = fsm_fire(&f);



    TEST_ASSERT_EQUAL (0, ret_value);

}



/**

 * @brief Fsm fire devuelve 1 si transiciona.

 * 

 */

void test_fsm_fire_returnsOneIfTranition(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    fsm_init(&f, tt);



    is_true_ExpectAnyArgsAndReturn(1);

    int ret_value = fsm_fire(&f);



    TEST_ASSERT_EQUAL (1, ret_value);

}



/**

 * @brief Comprueba que el puntero pasado a fsm_fire es pasado a la funcin de guarda cuando se comprueba una transicin

 * 

 */

void test_fsm_fire_checkFunctionCalledWithFsmPointerFromFsmFire(void)

{



    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    fsm_init(&f, tt);



    //is_true_AddCallback(is_true);

    is_true_ExpectAndReturn(&f,0);

    fsm_fire(&f);



    //TEST_ASSERT_EQUAL (0, fsm_get_state(f));

}



/** 

 * @brief Comprueba que el fsm_fire funciona y tiene el estado correcto cuando la transicin devuelve true (cambia) y cuando devuelve false (mantiene)

 * 

 */

TEST_CASE(false, 0)

TEST_CASE(true, 1)

void test_fsm_fire_checkFunctionIsCalledAndResultIsImportantForTransition(bool returnValue, int expectedState)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };

    fsm_t f;

    fsm_init(&f, tt);

    

    is_true_ExpectAnyArgsAndReturn(returnValue);

    fsm_fire(&f);



    TEST_ASSERT_EQUAL (expectedState, fsm_get_state(&f));

}



/** 

 * @brief Comprueba que el fsm_fire funciona y tiene el estado correcto cuando la transicin es NULL (cambia)

 * 

 */

void test_fsm_fire_checkTransitionHappensIfInFunctionIsNull(void)

{

    fsm_trans_t tt[] = {

        {0, NULL, 1, NULL},

        {-1, NULL, -1, NULL}

    };

    fsm_t f;

    fsm_init(&f, tt);

    

    fsm_fire(&f);



    TEST_ASSERT_EQUAL (1, fsm_get_state(&f));

}





/**

 * @brief La creacin de una mquina de estados devuelve NULL si la reserva de memoria falla (Mock, no Stub)

 * 

 */

void test_fsm_new_nullWhenFsmMallocReturnsNull(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {1, is_true, 0, NULL},

        {-1, NULL, -1, NULL}

    };



    //fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(NULL);

    fsm_t *f = fsm_new(tt);

    

    TEST_ASSERT_EQUAL (NULL, f);

    free(f);

}



/**

 * @brief Llamar a fsm_destroy provoca una llamada a fsm_free (Mock, no Stub)

 * 

 */

void test_fsm_destroy_callsFsmFree(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {1, is_true, 0, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(0);

    fsm_t *f = fsm_new(tt);

    

    fsm_free_ExpectAnyArgs();

    fsm_destroy(f);

}



/**

 * @brief Llamar a fsm_destroy NO provoca una llamada a fsm_free si f es NULL (Mock, no Stub)

 * 

 */

void test_fsm_destroy_doesntCallsFsmFreeIfNull(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {1, is_true, 0, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t *f = NULL;

    

    fsm_destroy(f);

}



/**

 * @brief Comprueba que solo se llame a la funcin de guarda que toca segn el estado actual

 * 

 */

void test_fsm_fire_callsFirstIsTrueFromState0AndThenIsTrue2FromState1(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {1, is_true2, 0, NULL},   //Descomentar cuando se haya declarado una nueva funcin para mock is_true2

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    fsm_init(&f, tt);



    is_true_ExpectAnyArgsAndReturn(1);

    fsm_fire(&f);

    TEST_ASSERT_EQUAL (1, fsm_get_state(&f));



    is_true2_ExpectAnyArgsAndReturn(1);

    fsm_fire(&f);

    TEST_ASSERT_EQUAL (0, fsm_get_state(&f));



}



/**

 * @brief Comprueba que se pueden crear dos instancias de mquinas de estados simultnteas y son punteros distintos

 * 

 */

void test_fsm_new_calledTwiceWithSameValidDataCreatesDifferentInstancePointer(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(0);

    fsm_t *f1 = fsm_new(tt);

    fsm_malloc_ExpectAnyArgsAndReturn(0);

    fsm_t *f2 = fsm_new(tt);



    TEST_ASSERT_NOT_EQUAL (f1, f2);

}
