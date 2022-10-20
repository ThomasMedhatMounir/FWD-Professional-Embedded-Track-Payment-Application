/*************************************************************************/
/*needed files*/
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"terminal.h"
/*************************************************************************/
/*get transaction data */
/*This function will ask for the transaction data and store it in terminal data. dd/mm/yyyy*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	struct tm st_time;
	time_t data = time(0);
	localtime_s(&st_time,&data);
	uint8_t day = 0, month = 0;
	uint16_t year = 0;
	day = st_time.tm_mday;
	month = 1 + st_time.tm_mon;
	year = 1900 + st_time.tm_year;
	termData->transactionDate[0] = (day/ 10)+48;
	termData->transactionDate[1] = (day % 10)+48;
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = (month / 10)+48;
	termData->transactionDate[4] = (month % 10)+48;
	termData->transactionDate[5] = '/';
	termData->transactionDate[6] = (year / 1000)+48;
	termData->transactionDate[7] = (year / 100 - (termData->transactionDate[6] - 48) * 10) + 48;
	termData->transactionDate[8] = (year / 10 - (termData->transactionDate[7]-48) * 10 - (termData->transactionDate[6] - 48) * 100) + 48;
	termData->transactionDate[9] = (year % 10)+48;
	termData->transactionDate[10] = NULL;
	printf("Today is : ");
	puts(termData->transactionDate);
	/*check if name contains error*/
	if (termData->transactionDate[0] == NULL || strlen(termData->transactionDate) != 10
		|| termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/'
		|| termData->transactionDate[0] > '3' || termData->transactionDate[1] > '9'
		|| (termData->transactionDate[0] == '3' && termData->transactionDate[1] > '1')
		|| termData->transactionDate[3] > '1' || termData->transactionDate[4] > '9'
		|| (termData->transactionDate[3] == '1' && termData->transactionDate[4] > '2')
		)
	{
		/*if there is error */
		return WRONG_DATE;
	}
	else
	{
		/*no error */
		return ter_OK;
	}

}
/*************************************************************************/
/*is card expired*/
/*This function compares the card expiry date with the transaction date*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{	
	uint8_t val = 9;
	uint8_t month_card = 0 , year_card = 0, month_tran = 0, year_tran = 0;
	month_card = (cardData.cardExpirationDate[0]-48) * 10 + (cardData.cardExpirationDate[1] - 48);
	year_card = (cardData.cardExpirationDate[3]-48) * 10 + (cardData.cardExpirationDate[4] - 48);
	month_tran = (termData.transactionDate[3] - 48) * 10 + (termData.transactionDate[4]-48);
	year_tran = (termData.transactionDate[8]-48) * 10 + (termData.transactionDate[9] - 48);
	if (year_tran > year_card)
	{
		return EXPIRED_CARD;	
	}
	else
	{
		val = ter_OK;
	}
	if (val == ter_OK && year_tran != year_card)
	{
		return val;
	}
	else
	{
		if (month_tran > month_card)
		{
			return EXPIRED_CARD;
		}
		else
		{
			return ter_OK;
		}
	}
}
/*************************************************************************/
/*is a vaild card PAN */
/*This function checks if the PAN is a Luhn number or not.*/
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint8_t n=0 ,temp=0,sum=0;
	/*get number of digits*/
	n = strlen(cardData->primaryAccountNumber) ;
	for (int8_t i = strlen(cardData->primaryAccountNumber)-1; i >= 0; i--)
	{
		if ((n-i)==0)
		{
			temp = (cardData->primaryAccountNumber[i] - 48) * 2;
		}
		else
		{
			n--;
			n--;
			temp = (cardData->primaryAccountNumber[i] - 48);
		}
		if (temp > 9)
		{
			sum += temp % 10;
			sum += temp / 10;
		}
		else
		{
			sum += temp;
		}
	}
	if (sum % 10 == 0)
	{
		return ter_OK;
	}
	else
	{
		return INVALID_CARD;
	}
}
/*************************************************************************/
/*get transaction amount*/
/*This function asks for the transaction amount and saves it into terminal data.*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	/*intialize with zero*/
	termData->transAmount = 0.0;
	/*ask user to enter the name then get the name*/
	printf("Please Enter Transaction amount : ");
	scanf_s("%f",&(termData->transAmount));
	/*check for error if amount less than zero or equal zero */
	if (termData->transAmount <= 0)
	{
		/*if yes*/
		return INVALID_AMOUNT;
	}
	else
	{
		/*if no*/
		return ter_OK;
	}
}
/*************************************************************************/
/*is below max amount*/
/*This function compares the transaction amount with the terminal max amount.*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	/*check if the value is larger than the max amount or not*/
	if (termData->transAmount > termData->maxTransAmount)
	{
		/*if yes*/
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		/*if no*/
		return ter_OK;
	}
}
/*************************************************************************/
/*set max amount*/
/*This function sets the maximum allowed amount into terminal data.*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	/*initalize to zero*/
	termData->maxTransAmount = 5000.0;
	/*check for error if amount less than zero or equal zero */
	/*printf("Please Enter Max Transaction amount : ");
	scanf_s("%f", &termData->maxTransAmount);*/
	/*check if the value is larger than the max amount or not*/
	if (termData->maxTransAmount <= 0)
	{
		/*if yes*/
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		/*if no*/
		printf("max amount is %f \n", termData->maxTransAmount);
		return ter_OK;
	}
}
/*************************************************************************/