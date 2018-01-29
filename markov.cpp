#include <iostream>
using namespace std;
#define iteration 1000

#define width 4
#define height 3
// [3][4]
/*    _ _ _ _
	0|_|_|_|_|
	1|_|_|_|_|
	2|_|_|_|_|
      0 1 3 4
*/
double reward[height][width];
double value[height][width];
int direction[height][width]; //1 right;2 up; 3 left;4 down
bool noblock[height][width];

void initialization(){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			reward[i][j] = -0.02;
			value[i][j] = 0;
			direction[i][j] =0;
			noblock[i][j] = true;
		}
	}
	reward[0][3] = 1.0;
	reward[1][3] = -1.0;
	noblock[1][1] = false;
}

void showtable(){
	printf("Reward:\n");
	for(int i = 0; i < height; i++){
		for  (int j = 0; j < width; j++){
			printf("%f ",reward[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("V star table:\n");
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			printf("%f ",value[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("PI table:\n");
	for(int i = 0; i < height; i++){
		for  (int j = 0; j < width; j++){
			printf("%d ",direction[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
double maxPV(int i,int j){
	int n;
	int direct;
	double max=-100.0;
	double a=0.0;
	double b=0.0;
	double c=0.0;

	for (n = 4; n>= 1 ; n--){
		double tempmax = 0.0;
		//向右
		if (n == 1){
			a = value[i][j+1];
			b = value[i+1][j];
			c = value[i-1][j];
			if (i==0)
				c = value[i][j];
			if (i==2)
				b = value[i][j];
			if (j==3)
				a = value[i][j];
			tempmax = 0.8*a +0.1*b+0.1*c;
			if (tempmax>max){
				max = tempmax;
				direct = n; 
			}
		}

		//向上
		if (n == 2){
			a = value[i-1][j];
			b = value[i][j+1];
			c = value[i][j-1];
			if (i==0)
				a = value[i][j];
			if (j==0)
				c = value[i][j];
			if (j==3)
				b = value[i][j];
			tempmax = 0.8*a +0.1*b+0.1*c;
			if (tempmax>max){
				max = tempmax;
				direct = n; 
			}
		}

		//向左
		if (n == 3){
			a = value[i][j-1];
			b = value[i-1][j];
			c = value[i+1][j];
			if (j==0)
				a = value[i][j];
			if (i==0)
				b = value[i][j];
			if (i==2)
				c = value[i][j];
			tempmax = 0.8*a +0.1*b+0.1*c;
			if (tempmax>max){
				max = tempmax;
				direct = n; 
			}
		}
		//向下
		if (n == 4){
			a = value[i+1][j];
			b = value[i][j-1];
			c = value[i][j+1];
			if (i==2)
				a = value[i][j];
			if (j==0)
				b = value[i][j];
			if (j==3)
				c = value[i][j];
			tempmax = 0.8*a +0.1*b+0.1*c;
			if (tempmax>max){
				max = tempmax;
				direct = n; 
			}
		}
	}
	direction[i][j] = direct;
	return max;
}

int main(int argc, char const *argv[]){
	initialization();
	int numberOfIter = 1;

	while(numberOfIter<100){
		int i,j,direct;
		for (j = 0; j < width ; j++){
			for (i = 0; i < height; i++){


				if (noblock[i][j]){
					if((i==0)&&(j==3))
						value[i][j] = 1.0;
					else if((i==1)&&(j==3))
						value[i][j] = -1.0;
					else 
						value[i][j] = reward[i][j] + maxPV(i,j);

				}
			}
		}
	numberOfIter++;
	}
	showtable();
	return 0;
}