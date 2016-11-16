#ifndef ALGORITHM_COMMON
#define ALGORITHM_COMMON

#define	INDICATOR_NAME_LEN			20
#define ROM_SYMBOL_LEN				6
#define MAX_SYMBOL_COUNT			4096
#define LOG_MSG_LEN_CAPACITY		288
#define TIME_STRING_LENTH			30

#define CN_STOCK_MARKET				0
#define CN_SH_FUTURES_MARKET		1
#define CN_DL_FUTURES_MARKET		2
#define CN_ZZ_FUTURES_MARKET		3
#define CN_ZJ_FUTURES_MARKET		4

typedef struct
{
	unsigned char	exchange;
	char			symbol[ROM_SYMBOL_LEN+1];
}STRU_EXCH_SYMBOL;


#define DATA_SWAP_CAPACITY		8092
typedef struct
{
	void*				pDataSwap;
	int					nDataSwapCapacity;
	int					nDataRecCount;
	int					nDataSize;
	char				iPeriodType;				//period type, as P1M,P3M,P5M,P10M,P15M,P30M,P60M,P_DAILY,P_WEEKLY,P_MONTHLY
	enum				{P1M=0,P3M,P5M,P10M,P15M,P30M,P60M,P_DAILY,P_WEEKLY,P_MONTHLY};
}STRU_ORG_DATA_SWAP;

/*
 * structure for output array of signals.
 */
typedef struct
{
	int		iSignal;
	int		iDate;
	int		iTime;
	time_t	tmUTC;
	void TimeToUTC()
	{
		struct tm t;
		t.tm_year = iDate/10000 - 1900;
		t.tm_mon = iDate%10000/100 - 1 ;
		t.tm_mday = iDate%100;
		t.tm_hour = iTime/3600;
		t.tm_min = iTime%3600/60;
		t.tm_sec = iTime/60;
		tmUTC = mktime(&t);
	}
}STRU_SIGNAL;

/*
 * structure for portfolio status.
 */
typedef struct
{
	unsigned char		status;
	int					iDate;
	int					iTime;
	time_t				tmUTC;
	void TimeToUTC()
	{
		struct tm t;
		t.tm_year = iDate/10000 - 1900;
		t.tm_mon = iDate%10000/100 - 1;
		t.tm_mday = iDate%100;
		t.tm_hour = iTime/3600;
		t.tm_min = iTime%3600/60;
		t.tm_sec = iTime/60;
		tmUTC = mktime(&t);
	}
}STRU_PORTFOLIO_STATUS;

typedef struct 
{
	int				iMarketType;
	char			sIndName[INDICATOR_NAME_LEN];
	unsigned char	exchange;
	char			symbol[ROM_SYMBOL_LEN+1];
	char			iPeriodType;
	int				nDate;				
	int				iBarIndexInDay;			//the field is not useful while iPeriodType equals to P_DAILY or P_WEEKLY or P_MONTHLY
	int				iSignal;
	void ToPushString(char *sPushString)
	{
		sprintf(sPushString,"type=STRATEGY&a=%d&b=%s&c=%c&d=%s&e=%d&f=%d&g=%d&h=%d",
				iMarketType,sIndName,exchange,symbol,iPeriodType,nDate,iBarIndexInDay,iSignal);
	}
	void GetTimeSTring(char *sTimeString)
	{
		if(sTimeString == NULL) return ;

		switch(iPeriodType)
		{
		case STRU_ORG_DATA_SWAP::P1M:
		case STRU_ORG_DATA_SWAP::P3M:
		case STRU_ORG_DATA_SWAP::P5M:
		case STRU_ORG_DATA_SWAP::P10M:
		case STRU_ORG_DATA_SWAP::P15M:
		case STRU_ORG_DATA_SWAP::P30M:
		case STRU_ORG_DATA_SWAP::P60M:
			sprintf(sTimeString,"%d_%d",nDate,iBarIndexInDay);
			break;
		case STRU_ORG_DATA_SWAP::P_DAILY:
		case STRU_ORG_DATA_SWAP::P_WEEKLY:
		case STRU_ORG_DATA_SWAP::P_MONTHLY:
			sprintf(sTimeString,"%d",nDate);
			break;
		default:
			break;
		}
	}
}STRU_BAR_ID;

typedef struct  
{
	STRU_BAR_ID bar_id;
	std::string key;
}STRU_BAR_ID_WITH_KEY;


#define MAX_FLD_COUNT		255
#define MAX_REC_COUNT		8092

typedef struct  
{
	double	*result;
	int		nRecord;
}STRU_SINGLE_RESULT_SET;

typedef struct 
{
	int		iDate;
	int		iTime;
	time_t	tmUTC;
	double	*pFldList;
}STRU_RAW_RESULTS;

//this structure is more likely to be a matrix.
typedef struct  
{
	int					nMaxFldCount;
	int					nCurFldCount;
	int					nCurRecCount;
	double				*pMemDouble;
	STRU_RAW_RESULTS	*pRawResults;
}STRU_RAW_RESULTS_FILE;
#endif