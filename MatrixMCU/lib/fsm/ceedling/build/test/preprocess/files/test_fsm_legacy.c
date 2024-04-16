#include "build/test/mocks/mock_test_fsm.h"
#include "../include/fsm.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


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

    fsm_t *f = (fsm_t*)1;



    f = fsm_new(NULL);  // tabla de transiciones es NULL



    TEST_ASSERT_EQUAL (NULL, f);

}



/**

 * @brief Comprueba que la funcin de inicializacin devuelve false si el puntero a la maquina de estado es NULL

 *

 */

void test_fsm_init_falseWhenNullFsm(void)

{

    fsm_trans_t tt[] = {{ 0, is_true, 1, do_nothing},

                        {-1, NULL, -1, NULL}};

    bool res=true;



    res=fsm_init(NULL,tt);     // Maquina de estados NULL



    TEST_ASSERT_EQUAL (false,res);



}



/**

 * @brief Funcin de inicializacion devuelve false si la tabla de transiciones es nula

 *

 */

void test_fsm_init_falseWhenNullTransitions(void)

{

    fsm_t *f = (fsm_t*)1;



    bool res=true;



    res=fsm_init(f,NULL);     //Tabla de transiciones es NULL



    TEST_ASSERT_FALSE (res);



}



/**

* @brief La mquina de estados devuelve NULL

*        y no llama a fsm_malloc si el estado de origen

*        de la primera transicin es -1 (fin de la tabla)

*/

void test_fsm_nullWhenFirstOrigStateIsMinusOne (void) {

  fsm_trans_t tt[] = {{-1, is_true, 1, do_nothing}};

  fsm_t *f = (fsm_t*)1;

  f = fsm_new(tt);

 

  TEST_ASSERT_EQUAL (NULL,f);

  //TEST_FAIL_MESSAGE("Implement the test");

}



/**

 * @brief La mquina de estados devuelve NULL y no llama a fsm_malloc si el estado de destino de la primera transicin es -1 (fin de la tabla)

 *

 */

void test_fsm_nullWhenFirstDstStateIsMinusOne (void) {

  fsm_trans_t tt[] = {{1, NULL, -1, NULL}};



  fsm_t *f = (fsm_t*)1;

  f = fsm_new(tt);



  TEST_ASSERT_EQUAL (NULL,f );

  //TEST_IGNORE();

}



/**

 * @brief La mquina de estados devuelve NULL y no llama a fsm_malloc si la funcin de comprobacin de la primera transicin es NULL (fin de la tabla)

 *

 */

void test_fsm_nullWhenFirstCheckFunctionIsNull (void) {

    fsm_trans_t tt[] = {{0, NULL, 1, NULL},

                        {-1, NULL , -1, NULL}};

    fsm_t *f = (fsm_t*)1;

    f = fsm_new(tt);



    TEST_ASSERT_EQUAL (NULL,f );

  //TEST_IGNORE();

}



/**

 * @brief Devuelve puntero no NULL y llama a fsm_malloc (CALLBACK) al crear la maquina de estados con una transicin vlida con funcin de actualizacin (salida) NULL o no NULL.

 *        Hay que liberar la memoria al final llamando a free

 *

 */

TEST_CASE(NULL)

TEST_CASE(do_nothing)

void test_fsm_new_nonNullWhenOneValidTransitionCondition(fsm_output_func_t out)

{

    fsm_trans_t tt[] = {

        {0, is_true,1, out},

        {-1, NULL, -1, NULL}

    };



    fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(0);



    //is_true_ExpectAnyArgsAndReturn(true);

    // fsm_t *f = (fsm_t*)cb_malloc(sizeof(fsm_t),1);      //como le pasa la tabla de transiciones

    // f->p_tt = tt;

    // f->current_state = tt->orig_state;

    fsm_t * F1= fsm_new(tt);



    TEST_ASSERT_NOT_EQUAL(NULL,F1);

    free(F1);



    //TEST_FAIL_MESSAGE("falta tabla de tt");

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



    fsm_t f ;

    int res;

    fsm_init(&f, tt);

    res = fsm_get_state(&f);



    TEST_ASSERT_EQUAL_INT (0,res );



    //TEST_IGNORE();

}



/**

 * @brief La maquina de estado no transiciona si la funcion devuelve 0

 *

 */

void test_fsm_fire_isTrueReturnsFalseMeansDoNothingIsNotCalledAndStateKeepsTheSame(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {-1, NULL, -1, NULL}

    };



    is_true_ExpectAnyArgsAndReturn(false);

    fsm_t f;

    int res;

    fsm_init(&f, tt);

    fsm_fire(&f);

    res = fsm_get_state(&f);

    TEST_ASSERT_EQUAL_INT (0,res );



   // TEST_FAIL_MESSAGE("Revisar");

   //TEST_IGNORE();

}



/**

 * @brief Comprueba que el puntero pasado a fsm_fire es pasado a la funcin de guarda cuando se comprueba una transicin

 *

 */

void test_fsm_fire_checkFunctionCalledWithFsmPointerFromFsmFire(void)

{



    fsm_trans_t tt[] = {

        {0, is_true , 1, NULL},

        {1, is_true, 0, NULL},

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    int res;



    is_true_ExpectAndReturn(&f,true);



    fsm_init(&f, tt);



    fsm_fire(&f);



    res = fsm_get_state(&f);        // comprobar la transiscion

    TEST_ASSERT_EQUAL_INT (1,res );



   

    //TEST_IGNORE();

}



// Funcin de actualizacin de estado simulada que siempre devuelve true

bool always_true(void) {

    return true;

}



// Funcin de actualizacin de estado simulada que siempre devuelve false

bool always_false(void) {

    return false;

}



/**

 * @brief Comprueba que el fsm_fire funciona y tiene el estado correcto cuando la transicin devuelve true (cambia) y cuando devuelve false (mantiene)

 *

 */

TEST_CASE(false, 0)

TEST_CASE(true, 1)

void test_fsm_fire_checkFunctionIsCalledAndResultIsImportantForTransition(bool returnValue, int expectedState)

{

    // funcin de actualizacin de estado simulada que devuelve el valor proporcionado

    //bool (*updateFunc)(void) = returnValue ? always_true : always_false;



    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        {-1, NULL, -1, NULL}

    };

    fsm_t f;



     

    fsm_init(&f, tt);



    is_true_ExpectAnyArgsAndReturn(returnValue);

       

    fsm_fire(&f);

    TEST_ASSERT_EQUAL(expectedState, f.current_state);

    //TEST_IGNORE();

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

   

    fsm_t* FSM = fsm_new(tt);

    TEST_ASSERT_NULL(FSM);

    //TEST_IGNORE();

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



    fsm_free_ExpectAnyArgs();



    fsm_t f;

    fsm_init(&f, tt);



    fsm_destroy(&f);    



    //TEST_IGNORE();

}



/**

 * @brief Comprueba que solo se llame a la funcin de guarda que toca segn el estado actual

 *

 */



void test_fsm_fire_callsFirstIsTrueFromState0AndThenIsTrue2FromState1(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, NULL},

        //{1, is_true2, 0, NULL},   //Descomentar cuando se haya declarado una nueva funcin para mock is_true2

        {-1, NULL, -1, NULL}

    };



    fsm_t f;

    int res;

    fsm_init(&f, tt);

    res = fsm_get_state(&f);



    TEST_IGNORE();

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

    fsm_malloc_AddCallback(cb_malloc);

    fsm_malloc_ExpectAnyArgsAndReturn(0);



    fsm_t* F1 = fsm_new(tt);

    fsm_t* F2 = fsm_new(tt);



    TEST_ASSERT_NOT_EQUAL(F1,F2);

    //TEST_IGNORE();

}
