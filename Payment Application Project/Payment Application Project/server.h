/*server.h*/
#ifndef SERVER_H
#define SERVER_H
/*************************************************************************/
/*needed files*/
#include"std_types.h"
#include"card.h"
#include"terminal.h"
/*************************************************************************/
/*card data */
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
/*************************************************************************/
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;
/*************************************************************************/
typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
/*************************************************************************/
/*return val of card data */
typedef enum EN_serverError_t
{
	ser_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;
/*************************************************************************/
/*function prototype*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_transaction_t* transData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
/*************************************************************************/
#endif /*SERVER_H*/
