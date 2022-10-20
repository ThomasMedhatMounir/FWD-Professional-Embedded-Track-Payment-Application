/*************************************************************************/
#include"app.h"
#include<stdio.h>
/*************************************************************************/
int main()
{
    appStart();
    return 0;
}
/*************************************************************************/
void appStart(void)
{
    printf("Welcome to Payment Application Program\n\n");
    ST_transaction_t transData;
    /*************************************************************************/
    /*card*/ 
    printf("\nCard Data\n");
    /*************************************************************************/
    /*get card holder name*/
    while (getCardHolderName(&transData.cardHolderData) != OK)
    {
        printf("wrong name \n");
        printf("Please try again\n");
    }
    printf("valid name \n");
    /*************************************************************************/
    /*get card expiry date*/
    while (getCardExpiryDate(&transData.cardHolderData) != OK)
    {
        printf("wrong expiry data \n");
        printf("Please try again\n");
    }
    printf("valid expiry data \n");
    /*************************************************************************/
    /*get card PAN*/
    while (getCardPAN(&transData.cardHolderData) != OK)
    {
        printf("wrong card PAN \n");
        printf("Please try again\n");
    }
    printf("right card PAN \n");
    /*************************************************************************/
    /*terminal*/
    printf("\nTerminal Data\n");
    /*************************************************************************/
    /*get current date*/
    getTransactionDate(&transData.terminalData);
    /*************************************************************************/
    /*check if the card is expired*/
    if (isCardExpired(transData.cardHolderData,transData.terminalData) != ter_OK)
    {
        printf("expired card \n");
        printf("\nEnd of Payment Application Program\n");
        return;
    }
    else
    {
        printf("not expired card \n");
    }
    /*************************************************************************/
    /*check if the card is valid luhn number*/
    if (isValidCardPAN(&transData.cardHolderData) != ter_OK)
    {
        printf("not valid card  \n");
        printf("\nEnd of Payment Application Program\n");
        return;
    }
    else
    {
        printf("valid card PAN \n");
    }
    /*************************************************************************/
    /*ask for transaction amounr*/
    while (getTransactionAmount(&transData.terminalData) != ter_OK)
    {
        printf("not valid amount \n");
        printf("Please try again\n");
    }
    printf("valid amount \n");
    /*************************************************************************/
    /*set max amount*/
    setMaxAmount(&transData.terminalData);
    /*************************************************************************/
    /*check if below the max amount*/
    if (isBelowMaxAmount(&transData.terminalData) != ter_OK)
    {
        printf("amount exceeding limit \n");
        printf("\nEnd of Payment Application Program\n");
        return;
    }
    else
    {
        printf("valid amount below limit \n");
    }
    /*************************************************************************/
    /*server*/
    printf("\nServer Data\n");
    /*************************************************************************/
    /*recieve transaction data*/
    uint8_t val = recieveTransactionData(&transData);
    /*************************************************************************/
    /*if approved*/
    if (val == APPROVED)
    {
        printf("Approved transaction \n");
    }
    /*************************************************************************/
    /*if stolen card*/
    else if (val == DECLINED_STOLEN_CARD)
    {
        printf("DECLINED_STOLEN_CARD \n");
        printf("\nEnd of Payment Application Program\n");
        return;
    }
    /*************************************************************************/
    /*if no amount*/
    else if (val == DECLINED_INSUFFECIENT_FUND)
    {
        printf("insuffecient funds \n");
        printf("\nEnd of Payment Application Program\n");
        return;
    }
    /*************************************************************************/
    else
    {
        /*do nothing*/
    }
    /*************************************************************************/
    /*save the transaction*/
    if (saveTransaction(&transData) != ser_OK)
    {
        printf("saving faild \n");
        printf("\nEnd of Payment Application Program\n");
        return;
    }
    else
    {
        printf("Saved\n");
    }
    /*************************************************************************/
    /*get the transaction Data*/
    getTransaction(1024, &transData);
    /*************************************************************************/
    /*END*/
    return;
}
/*************************************************************************/
