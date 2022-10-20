/*************************************************************************/
/*needed files*/
#include<stdio.h>
#include<string.h>
#include"server.h"
/*************************************************************************/
ST_accountsDB_t accounts[255] =
{
	{
		.balance = 10000.00,
		.primaryAccountNumber = "5012345678901234564"
	},
	{0}
};
/*************************************************************************/
ST_transaction_t transaction[255] = 
{
	{
		.cardHolderData.cardExpirationDate = 0,
		.cardHolderData.cardHolderName = 0,
		.cardHolderData.primaryAccountNumber = 0,
		.terminalData.maxTransAmount = 0.0,
		.terminalData.transactionDate = 0,
		.terminalData.transAmount = 0.0,
		.transactionSequenceNumber = 0,
		.transState = 0
	},
	{0}
};
/*************************************************************************/
uint8_t state = 9 ;
/*************************************************************************/
/*recieve transaction data */
/*This function will take all transaction data and validate its data*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	uint16_t n = 0;
	uint8_t val = 9;
	for (n = 0; n < 255; n++)
	{
		if (strcmp(accounts[n].primaryAccountNumber, transData->cardHolderData.primaryAccountNumber) == 0)
		{
			break;
		}
		else
		{
			/*do nothing*/
		}
	}
	if (isValidAccount(&transData->cardHolderData) != ser_OK)
	{
		val = DECLINED_STOLEN_CARD;
	}
	else if (transData->terminalData.transAmount > accounts[n].balance)
	{
		val = DECLINED_INSUFFECIENT_FUND;
	}
	else
	{
		accounts[n].balance -= transData->terminalData.transAmount;
		val = APPROVED;
	}
	state = val;
	return val;
}
/*************************************************************************/
/*is vaild account*/
/*This function will take card data and validate these data.*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	uint8_t val;
	for (uint8_t i = 0; i < 255; i++)
	{
		if (strcmp(accounts[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
		{
			val = ser_OK;
			break;
		}
		else
		{
			val = ACCOUNT_NOT_FOUND;
		}
	}
	return val;
}
/*************************************************************************/
/*is amount available*/
/*This function will take terminal data and validate these data.*/
/*ST_terminalData_t* termData will not be enough data to execute the function
so i passed ST_transaction_t* transData instead */
EN_serverError_t isAmountAvailable(ST_transaction_t* transData)
{	
	uint16_t n = 0;
	uint8_t val;
	for (n = 0; n < 255; n++)
	{
		if (strcmp(accounts[n].primaryAccountNumber, transData->cardHolderData.primaryAccountNumber) == 0)
		{
			val = ser_OK;
			break;
		}
		else
		{
			val = ACCOUNT_NOT_FOUND;
		}
	}
	if (transData->terminalData.transAmount > accounts[n].balance)
	{

		return LOW_BALANCE;
	}
	else
	{
		return ser_OK;
	}
	
}
/*************************************************************************/
/*save transaction*/
/*This function will take all transaction data into the transactions database.*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	uint8_t n = 0,flag = 0;
	while (strcmp(accounts[n].primaryAccountNumber, transaction[n].cardHolderData.primaryAccountNumber) == 0)
	{
		if (n == 255)
		{
			flag = 1;
			break;
		}
		else
		{
			n++;  // transaction number++
		}
	}
	if (n == 255 && flag == 1)
	{
		return SAVING_FAILED;
	}
	else
	{
		transaction[n].cardHolderData = transData->cardHolderData;
		transaction[n].terminalData = transData->terminalData;
		transaction[n].transactionSequenceNumber = n + 1024;
		transaction[n].transState = state;
		printf("your current balance is %f \n", accounts[n].balance);
		return ser_OK;
	}
}
/*************************************************************************/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	uint8_t val = 0;
	for (uint8_t i = 0; i < 255; i++)
	{
		if (transaction[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			transData = &transaction[i];
			val = ser_OK; 
			break;
		}
		else
		{
			val = TRANSACTION_NOT_FOUND;;
		}
	}
	printf("\n Transaction Data\n");
	puts(transData->cardHolderData.primaryAccountNumber);
	puts(transData->cardHolderData.cardHolderName);
	puts(transData->cardHolderData.cardExpirationDate);
	printf("max amount : %f\n",transData->terminalData.maxTransAmount);
	puts(transData->terminalData.transactionDate);
	printf("trans amount : %f\n", transData->terminalData.transAmount);
	printf("sqn : %d\n", transData->transactionSequenceNumber);
	printf("state : %d\n", transData->transState);
	return val;
}
/*************************************************************************/