#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//hey!
//hlo

int ReturnDistance(char* cArr1, char* cArr2)
{
	int iRow, iCol;
	iCol = strlen(cArr1);
	iRow = strlen(cArr2);
	int iArr[iRow +1][iCol +1];
	iArr[0][0] = 0;

	int i,j;
	for(i = 1; i<iCol+1; i++)
	{
		iArr[0][i] = iArr[0][i-1] + 1;
	}
	for(j = 1; j<iRow+1; j++)
	{
		iArr[j][0] = iArr[j-1][0] + 1;
	}


	for(j=1 ;j<iCol+1; j++)
	{
		for(i = 1; i<iRow+1;i++)
		{
			if(cArr1[j] == cArr2[i])
			{
				if((iArr[i-1][j] <= iArr[i-1][j-1]) &&(iArr[i-1][j] <= iArr[i][j-1]))
				{
					iArr[i][j] = iArr[i-1][j];
				}
				if((iArr[i-1][j-1] <= iArr[i-1][j]) && (iArr[i-1][j-1] <= iArr[i][j-1]))
				{
					iArr[i][j] = iArr[i-1][j-1];
				}
				if((iArr[i][j-1] <= iArr[i-1][j]) && (iArr[i][j-1] <= iArr[i-1][j-1]))
				{
					iArr[i][j] = iArr[i][j-1];
				}
			}
			else
			{
				if((iArr[i-1][j] <= iArr[i-1][j-1]) && (iArr[i-1][j] <= iArr[i][j-1]))
				{
					iArr[i][j] = iArr[i-1][j] +1;
				}
				if((iArr[i-1][j-1] <= iArr[i-1][j]) && (iArr[i-1][j-1] <= iArr[i][j-1]))
				{
					iArr[i][j] = iArr[i-1][j-1]+1;
				}
				if((iArr[i][j-1] <= iArr[i-1][j]) && (iArr[i][j-1] <= iArr[i-1][j-1]))
				{
					iArr[i][j] = iArr[i][j-1] +1;
				}
			}
		}
	}

	return iArr[iRow+1][iCol+1];

}

void newfile(char* temp)
{
	int len,i;
	len = strlen(temp);
	for(i=0;i<len;i++)
	{
		temp[i] = tolower(temp[i]);
		if(temp[i] >= 33 && temp[i] <= 47)
		{
			temp[i] = '\0';
		}
		if(temp[i] == '?')
		{
			temp[i] = '\0';
	 	}
	}
}

int* ComputeHistogram(char word[][100], char spam_train[][100],char ham_train[][100],int * rep_strings , int num_wrds)
{
	
	
	int min,temp,i,j , i_min = 0;
	int* cArr = (int*)malloc(20*sizeof(int));
	
	for(i=0; i<20;i++)
	{
		cArr[i] = 0;
	}
	
	for(i=0; i<num_wrds; i++)
	{
		min = ReturnDistance(word[i], spam_train[rep_strings[0]]);
		for(j=0; j<10 ; j++)
		{
			temp = ReturnDistance(word[i], spam_train[rep_strings[j]]);
			if(temp<min)
			{
				min = temp;
				i_min = j;
				
			}
		}
		for(j=10; j<20; j++)
		{
			temp = ReturnDistance(word[i], ham_train[rep_strings[j]]);
			if(temp<min)
			{
				min = temp;
				i_min = j;
			}
		}
		cArr[i_min] += 1;
		
	}
	return cArr;
		
}

void ComputeL1Distance(int **Hist_tc , int** Hist_tsc)
{
	int i, j,sum[542],temp,note[542] , ind, mod ;//i is for testing cases ,,, j is for training case,,, training cases are under testing ones
	float ham=0, spam=20;
		
	int z,sum1, sum2, i_min;
	for(i=0; i<542; i++)
	{
		sum1 =0,i_min=111;
		for(j=0;j<20;j++){
			
			sum1=sum1+(Hist_tsc[i][j]-Hist_tc[111][j])*(Hist_tsc[i][j]-Hist_tc[111][j]);
		}
		for(z=0;z<542;z++){
			sum2=0;
			for(j=0;j<20;j++){
				sum2 += (Hist_tsc[i][j]-Hist_tc[z][j])*(Hist_tsc[i][j]-Hist_tc[z][j]);
			}
			if(sum2<=sum1){
				sum1=sum2;
				i_min=z;
			}
		}
		if(i<41 && i_min<41)
			spam++;
		if(i>=41 && i_min>=41)
			ham++;
		
	}
	printf("%f-----%f\n", spam, ham);
	float fInt;
	fInt = ((spam + ham)/542)*100;
	printf("percent efficiency = %f", fInt);
}

int* finalising_rep(char words[][100],int* indx_rep_wrds, int * clust_no_arr , int no_of_words, int clust_no)
{
	//mai cluster ki arr dsaalungi and it will return rep of each cluster jo ek int array h
	int i,j,iRepDist, ino = 0,iDist;
	int iSum[no_of_words];
	for(i = 0;i<no_of_words;i++)
	{
		iSum[i] = 0;
	}
	int* new_rep = (int*)malloc(sizeof(int)*clust_no);
	for(i = 0;i<clust_no;i++)
	{
		for(j = 0;j<no_of_words;j++)
		{
			if(clust_no == clust_no_arr[j])
			{
				iDist = ReturnDistance(words[indx_rep_wrds[clust_no]], words[j]);
				iSum[j] += iDist;
				ino++; 
			}
		}
		if(ino != 0)
		{
			for(j = 0; j<no_of_words; j++)
			{
				iRepDist = iSum[j]/ino;
				while(iRepDist != 0)
				{
					if(i == clust_no_arr[j]);
					{	
						if(iRepDist == ReturnDistance(words[j], words[indx_rep_wrds[clust_no]]));
						{
							new_rep[i] = j;
							break;
						}
					}
					iRepDist--;
				}
			}
			
		}
		else
		{
			iRepDist = 0;
			new_rep[i] = indx_rep_wrds[i];
		}
		
	}	
	
	return new_rep;	
}

int* make_cluster(char  train_words[][100], int* train_rep_no, int no_wrds, int no_clstrs)
{
	int* clust_no_arr =(int *) malloc(sizeof(int)*no_wrds) ;
	int i,j;
	for(i=0; i<no_wrds; i++)
	{
		int min = ReturnDistance(train_words[i], train_words[train_rep_no[0]]);
		int i_min = 0;//initialise
		for(j = 0; j<no_clstrs; j++)
		{
			int temp = ReturnDistance(train_words[i],train_words[train_rep_no[j]]);
			if(temp<min)
			{
				min = temp;
				i_min = j;
			}
		}
		clust_no_arr[i] = i_min;

	}
	return clust_no_arr;
	    
}

void initialise_cluster()
{
	char spam_train[400][100];//20 diff rand cluster centre, 40 is max word length
	char ham_train[5000][100];//250 diff randcluster centre, 250*20 is where 20 is avg length of a line
	int* spam_train_rep = (int*)malloc(sizeof(int)*10);
	int* ham_train_rep = (int*)malloc(sizeof(int)*10);
	int *cluster_spam;//saare words ko ek ek cluster number assign krega
	int *cluster_ham;
	int *rep_strings = (int*)malloc(sizeof(int)*20);
	
	int iInd, jInd;	
	
	FILE * word_read = (FILE*) (fopen("to_be_read.txt","r"));
	for(iInd = 0; iInd<400; iInd++)
	{
		fscanf(word_read,"%s",spam_train[iInd]);
	} 
	fseek(word_read,-34000,SEEK_END);
	for(iInd = 0; iInd<5000; iInd++)
	{
		fscanf(word_read,"%s",ham_train[iInd]);
	}

	
	for(iInd = 0;iInd<10;iInd++)
	{
		spam_train_rep[iInd] = rand()%400;
		for(jInd=0; jInd<iInd-1;jInd++)
		{
			if(spam_train_rep[iInd] == spam_train_rep[jInd] ||  spam_train_rep[iInd] < 0)
			{	iInd--; continue;}
		}
		//printf("%d \n", spam_train_rep[iInd]);

	}

	for(iInd = 0;iInd<10;iInd++)
	{
		ham_train_rep[iInd] = rand()%1000;
		for(jInd=0; jInd<iInd-1;jInd++)
		{
			if(ham_train_rep[iInd] == ham_train_rep[jInd] || ham_train_rep[iInd] < 0)
			{	iInd--; continue;}
		}
		//printf("%d\n", ham_train_rep[iInd]);

	}
	
	int alpha;
	
	for(alpha = 0; alpha<3; alpha++)
	{
		cluster_spam = make_cluster(spam_train, spam_train_rep, 400,10);
		cluster_ham = make_cluster(ham_train, ham_train_rep, 5000, 10);
	
		spam_train_rep = finalising_rep(spam_train, spam_train_rep, cluster_spam, 400, 10);
		ham_train_rep = finalising_rep(ham_train, ham_train_rep, cluster_ham, 5000, 10);
		
	}
		printf("Spam representatives are--\n");
		for(iInd = 0;iInd<10;iInd++)
		{	
			printf("%s\n", spam_train[spam_train_rep[iInd]]);
			
		}
		printf("Ham representatives are--\n");
		for(iInd = 0;iInd<10;iInd++)
		{
			printf("%s\n", ham_train[ham_train_rep[iInd]]);
			//printf("hi\n");
		}

	int beta;
	for(beta = 0 ; beta<10 ; beta++)
	{
		rep_strings[beta] = spam_train_rep[beta];
	}
	
	for(beta = 10 ; beta<20 ; beta++)
	{
		rep_strings[beta] = ham_train_rep[beta-10];
	}		
	
	FILE* strings = (FILE*)(fopen("english.txt","r"));
	
	char cChar[1000];
	int iInt = 0;
	int ** Hist_t = (int**)malloc(sizeof(int*)*542);
	int ** Hist_ts = (int**)malloc(sizeof(int*)*542);
	//for training spam cases
	char word[500][100];
	int num_wrds;//i is the num of words finally
	int i = 0;
	
	while( iInt != 41)
	{
		i=0;
		fgets(cChar,1000,strings);
		char *cget=strtok(cChar," ");
		while(cget!=NULL)
		{
			 strcpy(word[i],cget);
			 cget=strtok(NULL," ");
			 i++;
		}
		num_wrds = i;
		//fputs(cChar,stdout);
		Hist_t[iInt] = ComputeHistogram(word, spam_train,ham_train , rep_strings, num_wrds);
		iInt++;
	}
	
	int gama=0;
	while(gama!=542)
	{
		fgets(cChar,1000,strings);
		gama++;
	}
	
	while(fgets(cChar,1000, strings) != NULL )
	{
		i = 0;
		char *cget1=strtok(cChar," ");
		while(cget1!=NULL)
		{
			 strcpy(word[i],cget1);
			 cget1=strtok(NULL," ");
			 i++;
		}
		num_wrds = i;
		Hist_t[iInt] = ComputeHistogram(word, spam_train,ham_train , rep_strings, num_wrds);
		iInt++;
	}
	
		
	fseek(strings,0, SEEK_SET);
	gama = 0;
	while(gama != 41)
	{
		fgets(cChar,500,strings );
		gama++;
	}
	
	iInt = 0;
	while(iInt != 542)
	{
		fgets(cChar,500,strings);
		i = 0;
		char *cget2=strtok(cChar," ");
		while(cget2!=NULL)
		{
			 strcpy(word[i],cget2);
			 cget2=strtok(NULL," ");
			 i++;
		}
		
		num_wrds = i;
		
		Hist_ts[iInt] = ComputeHistogram(word, spam_train, ham_train, rep_strings, num_wrds);
		iInt++;
	}
	
	ComputeL1Distance(Hist_t, Hist_ts);
	
	
}

int main()
{
		char cChar;
		FILE *filepointer1,*filepointer2;
		filepointer1 = fopen("english.txt","r");
		
		filepointer2 = fopen("to_be_read.txt","w");
		char temp[1000] ;
		
		while(fscanf(filepointer1,"%s",temp) != EOF)
		{
			newfile(temp);
			if(strlen(temp) <= 2)
			{
				continue;
			}
			if(strcmp(temp,"the") == 0)
			{
				continue;
			}
			if(strcmp(temp,"are") == 0)
			{
				continue;
			}
			fprintf(filepointer2,"%s ",temp);
		}

		initialise_cluster();
		
		fclose(filepointer2);
		
		fclose(filepointer1);

}



