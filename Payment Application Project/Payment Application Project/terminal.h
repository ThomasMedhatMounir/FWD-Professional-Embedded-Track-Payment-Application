/*terminal.h*/
#ifndef TERMINAL_H
#define TERMINAL_H
/*************************************************************************/
/*needed files*/
#include"std_types.h"
#include"card.h"
/*************************************************************************/
/*card data */
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;
/*************************************************************************/
/*return val of card data */
typedef enum EN_terminalError_t
{
	ter_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;
/*************************************************************************/
/*function prototype*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);
/*************************************************************************/
#endif /*TERMINAL_H*/
