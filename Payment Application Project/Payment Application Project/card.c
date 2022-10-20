/*************************************************************************/
/*needed files*/
#include<stdio.h>
#include<string.h>
#include"card.h"
/*************************************************************************/
/*get name function */
/*This function will ask for the cardholder's name and store it into card data*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	/*set all values in name to 0*/
	for (uint8_t i = 0; i < 25; i++)
	{
		cardData->cardHolderName[i] = 0;
	}
	/*ask user to enter the name then get the name*/
	printf("Please Enter Card Holder Name : ");
	gets(cardData->cardHolderName);
	/*check if name contains error*/
	if (cardData->cardHolderName[0] == '/0' || strlen(cardData->cardHolderName) < 20
		|| strlen(cardData->cardHolderName) > 24)
	{
		/*if there is error*/
		return WRONG_NAME;
	}
	else
	{
		/*no error */
		return OK;
	}
}
/*************************************************************************/
/*get card expiry date*/
/*This function will ask for the card expiry date and store it in card data.  mm/yy*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	/*set all values in name to 0*/
	for (uint8_t i = 0; i < 6; i++)
	{
		cardData->cardExpirationDate[i] = 0;
	}
	/*ask user to enter the name then get the exp date*/
	printf("Please Enter Card Expiration Date : ");
	gets(cardData->cardExpirationDate);
	/*check if name contains error*/
	if (cardData->cardExpirationDate[0] == '/0' || strlen(cardData->cardExpirationDate) != 5
		|| cardData->cardExpirationDate[2] != '/'
		|| cardData->cardExpirationDate[0] > '1' || cardData->cardExpirationDate[1] > '9'
		|| (cardData->cardExpirationDate[0] == '1' && cardData->cardExpirationDate[1] > '2'))
	{
		/*if there is error */
		return WRONG_EXP_DATE;
	}
	else
	{
		/*no error */
		return OK;
	}
}
/*************************************************************************/
/*get card PAN */
/*This function will ask for the card's Primary Account Number and store it in card data.*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t val1 = 9 ,val2 = 9;
	/*set all values in name to '0'*/
	for (uint8_t i = 0; i < 20; i++)
	{
		cardData->primaryAccountNumber[i] = 0;
	}
	/*ask user to enter the name then get the PAN*/
	printf("Please Enter Card PAN : ");
	gets(cardData->primaryAccountNumber);
	/*check if name contains error*/
	for (uint8_t i = 0; i < strlen(cardData->primaryAccountNumber); i++)
	{
		if (cardData->primaryAccountNumber[i] >= '0' && cardData->primaryAccountNumber[i] <= '9')
		{
			val1 = OK;
		}
		else
		{
			val1 = WRONG_PAN;
			break;
		}
	}
	if ((cardData->primaryAccountNumber[0] == '/0')
		|| (strlen(cardData->primaryAccountNumber) < 16)
		|| (strlen(cardData->primaryAccountNumber)>19))
	{
		val2 = WRONG_PAN;
	}
	else
	{
		val2 = OK;
	}
	if (val1 == OK && val2 == OK)
	{
		return OK;
	}
	else
	{
		return WRONG_PAN;
	}
}
/*************************************************************************/