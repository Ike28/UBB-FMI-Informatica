#include "BookValidator.h"
#include "PriceException.h"
#include "NameException.h"
#include "StockException.h"

BookValidator::BookValidator()
{
}

void BookValidator::validate(Book other)
{
	if (other.getPret() < 1)
		throw PriceException("\nPretul introdus nu poate fi mai mic decat 1.");
	if (strcmp(other.getTitlu(), "") == 0)
		throw NameException("\nTitlul cartii nu poate fi nul.");
	if (strcmp(other.getAutor(), "") == 0)
		throw NameException("\nNumele autorului nu poate fi nul.");
	if (strcmp(other.getGen(), "") == 0)
		throw NameException("\nGenul cartii nu poate fi nul.");
	if (other.getStoc() < 0)
		throw StockException("\nStocul nu poate fi mai mic decat 0.");
}
