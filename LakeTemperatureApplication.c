#include <stdio.h>
int coldest (double *average_temp, int size)
{
	int i = 0, lakeNum = 0;
	double coldest = 0;
	for (i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			coldest = *average_temp;
		}
		else if (*average_temp < coldest)
		{
			coldest = *average_temp;
			lakeNum = i;
		}
		average_temp++;
	}
	return lakeNum;
}
int warmest (double *average_temp, int size)
{
	int i = 0, lakeNum = 0;
	double warmest = 0;
	for (i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			warmest = *average_temp;
		}
		else if (*average_temp > warmest)
		{
			warmest = *average_temp;
			lakeNum = i;
		}
		average_temp++;
	}
	return lakeNum;
}
int below_Average(double average_Temp, double total_Average)
{
	if (average_Temp < total_Average)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int above_Average(double average_Temp, double total_Average)
{
	if (average_Temp > total_Average)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
char getLakeName (int lakeNum)
{
	char lakeChar;
	switch (lakeNum)
	{
	case 0:
		lakeChar = 'S';
		break;
	case 1:
		lakeChar = 'M';
		break;
	case 2:
		lakeChar = 'H';
		break;
	case 3:
		lakeChar = 'E';
		break;
	case 4:
		lakeChar = 'O';
		break;
	case 5:
		lakeChar = 'C';
		break;
	}
	return lakeChar;
}
double warmest_temp_lake(double *arr, int *day)
{
	int i = 0;
	double warmest = 0;
	for (i = 0; i < 365; i++)
	{
		if (i == 0)
		{
			warmest = *arr;
		}
		else if (*(arr + i) > warmest)
		{
			warmest = *(arr + i);
			*day = i;
		}
	}
	return warmest;
}
double coldest_temp_lake(double *arr, int *day)
{
	int i = 0;
	double coldest = 0;
	for (i = 0; i < 365; i++)
	{
		if (i == 0)
		{
			coldest = *arr;
		}
		else if (*(arr + i) < coldest)
		{
			coldest = *(arr + i);
			*day = i;
		}
	}
	return coldest;
}


void format(int day)
{
    char months[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    int y=day, month, i;
    int daysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    for (i=1;i<12;i++)
    {
        daysInMonth[i]+= daysInMonth[i-1]; 
    }
    for (i=0;i<12;i++)
    {
        if (day<=daysInMonth[i])
        {
            month=i;
            if (i!=0)
            {
                y-=daysInMonth[i-1];
            }
            i=12;
        }
    }
 
    if(y < 10)
        printf("\t0%d ",y);        
    else
        printf("\t%d ",y);
    printf(" %-8s \n",months[month]);
}

int main (void)
{
	FILE *in;
	int i = 0, j = 0, lake_Coldest_Num = 0, lake_Warmest_Num = 0, day = 0, dayDate = 0, month = 0;
	double temp = 0, sum = 0, total_average = 0, total_sum = 0, warmest_temp[6], coldest_temp[6];
	double temp_chart[365][8], average_temp[6], sup[365], mich[365], huron[365], eerie[365], ontario[365], stClair[365];
	char warmest_Lake, coldest_Lake;
	in = fopen("c:\\CPS\\TempChart.txt", "r");
	for (i = 0; i < 365; i++)
	{
		for (j = 0; j < 8; j++)
		{
			fscanf(in, "%lf", &temp);
			temp_chart[i][j] = temp;
		}
	}
	for (i = 2; i < 8; i++)
	{
		for (j = 0; j < 365; j++)
		{
			sum += temp_chart[j][i];
			switch (i)
			{
			case 2:
				sup[j] = temp_chart[j][i];
				break;
			case 3:
				mich[j] = temp_chart[j][i];
				break;
			case 4:
				huron[j] = temp_chart[j][i];
				break;
			case 5:
				eerie[j] = temp_chart[j][i];
				break;
			case 6:
				ontario[j] = temp_chart[j][i];
				break;
			case 7:
				stClair[j] = temp_chart[j][i];
				break;
			}
		}
		average_temp[i-2] = sum / 365;
		sum = 0; 
	}
	
	printf("LEGEND\nS:SUPERIOR\nM:MICHIGAN\nH:HURON\nE:EERIE\nO:ONTARIO\nC:ST.CLAIR\n\n"); 
	printf("AVERAGE OF LAKES (ORDER: S - M - H - E - O - C)\n");
	for (i = 0; i < 6; i++)
	{
		printf("%0.2lf ", average_temp[i]);
		total_sum += average_temp[i];
	}
	total_average = total_sum / 6;
	printf("\n\nAVERAGE TEMPERATURE 6 LAKES: %0.2lf\n", total_average);
	lake_Coldest_Num = coldest(average_temp, 6);
	lake_Warmest_Num = warmest(average_temp, 6);
	coldest_Lake = getLakeName(lake_Coldest_Num);
	warmest_Lake = getLakeName(lake_Warmest_Num);
	
	printf("\nCOLDEST AND WARMEST LAKE\n"); 
	printf("Coldest Lake: %c \nWarmest Lake: %c \n\n", coldest_Lake, warmest_Lake);
	printf("ABOVE AND BELOW AVERAGE LAKE RATING\n"); 
	for (i = 0; i < 6; i++)
	{
		if (below_Average(average_temp[i], total_average) == 1)
		{
			printf("Below Average Lake: %c \n", getLakeName(i));
		}
		if (above_Average(average_temp[i], total_average) == 1)
		{
			printf("Above Average Lake: %c \n", getLakeName(i));
		}
	}
	
	printf("\nDISPLAYING WARMEST AND COLDEST TEMPERATURES OF LAKES AND DATES\n"); 
	
	printf("Warmest Temp Sup: %0.2lf ", warmest_temp_lake(sup, &day));
	printf("\tDay: %d", day + 1);
	format(day + 1); 
	
	printf("Warmest Temp Mich: %0.2lf ", warmest_temp_lake(mich, &day));
	printf("\tDay: %d", day + 1);
	format(day + 1); 
	
	printf("Warmest Temp Huron: %0.2lf ", warmest_temp_lake(huron, &day));
	printf("\tDay: %d", day + 1);
	format(day + 1); 
	
	printf("Warmest Temp Erie: %0.2lf ", warmest_temp_lake(eerie, &day));
	printf("\tDay: %d", day + 1);
	format(day + 1); 
	
	printf("Warmest Temp Ontario: %0.2lf ", warmest_temp_lake(ontario, &day));
	printf("\tDay: %d", day + 1);
	format(day + 1); 
	
	printf("Warmest Temp St. Clair: %0.2lf ", warmest_temp_lake(stClair, &day));
	printf("\tDay: %d", day + 1);
	format(day + 1); 
	
	printf("Coldest Temp Sup: %0.2lf ", coldest_temp_lake(sup, &day));
	printf("\t\tDay: %d\t", day + 1);
	format(day + 1); 
	
	printf("Coldest Temp Mich: %0.2lf ", coldest_temp_lake(mich, &day));
	printf("\tDay: %d\t", day + 1);
	format(day + 1); 
	
	printf("Coldest Temp Huron: %0.2lf ", coldest_temp_lake(huron, &day));
	printf("\tDay: %d\t", day + 1);
	format(day + 1); 
	
	printf("Coldest Temp Erie: %0.2lf ", coldest_temp_lake(eerie, &day));
	printf("\tDay: %d\t", day + 1);
	format(day + 1); 
	
	printf("Coldest Temp Ontario: %0.2lf ", coldest_temp_lake(ontario, &day));
	printf("\tDay: %d\t", day + 1);
	format(day + 1); 
	
	printf("Coldest Temp St. Clair: %0.2lf ", coldest_temp_lake(stClair, &day));
	printf("\tDay: %d\t", day + 1);
	format(day + 1); 
	
	fclose(in);
	return(0);
}

