// 	Yuya Oguchi
//	COEN 146 Lab6
//	5/17/2016
//
//	Explanation to why you get wrong number for large private keys:
//	power function given in c returns double value which is not enough when you compute
//	large power such as 23 to power of 94, so it will overflow and return the keys with
//	values in negative range.
//	
//	Some solution I came up with:
//	I implemented error detection so if the shared keys are in negative range, you know 
//	the number was raised too high, so I ask user again for new private keys to try 
//	again. Now this extends the values you can check for, but if the number is super
//	large, it could potentially overflow multiple times, causing this to not detect 
//	wrong numbers correctly. However, it does check for quiet some range as the
//	testing of base 23 to power of 94 was successfully detected as error.
//
//	There is not much you can do in C so my implementation is one of the ways to improve
//	 the error detection, but not perfect. Another way would have been to come up with 
//	 power function that returns space big enough to hold more bits, but then again 
//	 there will always be power number that can over flow it, so it depends on how far 
//	 you want to check. In my case, it detected the test case of base 23 with power 94, 
//	 which I would say is enough.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

int main(){

int p = 1;
int r = 1;
int a = 1;
int b = 1;
int i =0;
long int pubkey1, pubkey2;
long int sharedkey1, sharedkey2;
bool overflowdetection =0;

// set prime number p
while (p == 1){
	printf("enter prime number\n");
	scanf("%i",&p);
	for(i =2; i <sqrt((double)p);i++){
		if(p%i == 0){
			p = 1;
			printf("Number given is not prime \n");
			break;
		}
	}
}

//set primitive root r
while (r ==1){
	printf("enter primitive root (number lower than your root usually works)\n");
	scanf("%i",&r);
	if (r >= p){
		r = 1;
	}
}

while(overflowdetection ==0){
	//secret key1 a for user 1
	printf("input user 1 private key \n");
	scanf("%i",&a);

	//secret key2 b for user 2
	printf("input user 2 private key \n");
	scanf("%i",&b);

	//compute user 1 public key 
	pubkey1 = pow((double)r,(double)a);
	pubkey1 = pubkey1 % p;

	//compute user 2 public key
	pubkey2 = pow((double)r,(double)b);
	pubkey2 = pubkey2 % p;

	if((pubkey1 > 0) &&(pubkey2 > 0)){
		overflowdetection = 1;
	} else{
		printf("key overflow detected. Try again new private key with smaller values.\n");
	}
}
//print pub keys
printf("Pub key1: %ld\n",pubkey1);
printf("Pub key2: %ld\n",pubkey2);

//assume public keys are exhanged here

//compute shared key for user 1
sharedkey1 = pow((double)pubkey2, (double)a);
sharedkey1 = sharedkey1 % p;

//compute shared key for user 1
sharedkey2 = pow((double)pubkey1,(double)b);
sharedkey2 = sharedkey2 % p;


//check shared key
if(sharedkey1 == sharedkey2){
	printf("This is trusted connection with both computer shared key of %ld\n", sharedkey1);
}else{
	printf("Do not trust this connection. Shared keys differ with %ld and %ld\n",sharedkey1,sharedkey2);
}





return 0;
}
