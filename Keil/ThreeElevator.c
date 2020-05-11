#include <reg52.h>
#include<intrins.h>

sbit DS=P0^5;
sbit SH_CP=P0^4;
sbit ST_CP=P0^6;

sbit p10=P1^0;
sbit p11=P1^1;
sbit p12=P1^2;
sbit p13=P1^3;
sbit p14=P1^4;
sbit p15=P1^5;
sbit p16=P1^6;
sbit p17=P1^7;
sbit p20=P2^0;
sbit p21=P2^1;
sbit p22=P2^2;
sbit p23=P2^3;
sbit p24=P2^4;
sbit p25=P2^5;
sbit p26=P2^6;
sbit p27=P2^7;

sbit DS1=P3^0;
sbit DS2=P3^1;
sbit DS3=P3^2;
sbit DS4=P3^3;
sbit DS5=P3^4;
sbit ST_CP2=P3^5;
sbit SH_CP2=P3^6;
sbit P37 = P3^7;

int Elevator1=0,Elevator2=0;Elevator3=0;
int up1=0,up2=0,up3=0,down1=0,down2=0,down3=0;	
unsigned char e1=0,e2=0,e3=0,e2ae3=0,up=0,down=0;
void delay(int x){
	while(x>0){x--;}
}


void display_elevator(){

	 unsigned char  Data;
	 char i=0;

	 P0=Elevator1+1;

	 Data =(Elevator2+1)|((Elevator3+1)<<4);

	
   for(i;i<8;i++)
   {
		    SH_CP = 0; 
		 
        DS=0x80&Data;
		 
        Data=_crol_(Data,1); 
 
        SH_CP = 1;          
        _nop_();
 
   }  
   
   ST_CP = 1;         
	 
   _nop_();
   _nop_();

	
}
void display_LED(){
	int i=0;
	unsigned char Data1,Data2,Data3,Data4,Data5;

	Data1=e1^0xff;
	Data2=e2^0xff;
	Data3=e3^0xff;
	Data4=up^0xff;
	Data5=down^0xff;

	for(i;i<8;i++)
	{
		SH_CP2 = 0; 
		 
		DS1=0x80&Data1;
		DS2=0x80&Data2;
		DS3=0x80&Data3;
		DS4=0x80&Data4;
		DS5=0x80&Data5;

		 
		Data1=_crol_(Data1,1); 
		Data2=_crol_(Data2,1); 
		Data3=_crol_(Data3,1); 
		Data4=_crol_(Data4,1); 
		Data5=_crol_(Data5,1); 

 
		SH_CP2 = 1;          
		_nop_();
 
  }    
   
   ST_CP2 = 1;         
	 ST_CP2 = 0;
	
   _nop_();
   _nop_();
	
	
			delay(400);

}
void move(int *pup1,int *pup2,int *pup3,int *pdown1,int *pdown2,int *pdown3,unsigned char *pe1,unsigned char *pe2,unsigned char *pe3,int *pElevator1,int *pElevator2,int *pElevator3){
	int f;
	bit flag;
	/*-----Elevator1--------*/
	//Ascent
	if(*pup1){
		f=7;flag=1;
		//Move
		while(f>*pElevator1){
			//Inside
			if(*pe1&(1<<f)){flag=0;(*pElevator1)++;break;}
			//Up
			if(up&(1<<f)){
				//Elevator2
				if((f+1)%2!=0){
					if(*pdown2||*pElevator2<=*pElevator1||*pElevator2>f){flag=0;(*pElevator1)++;break;}
				}
				//Elevator3
				else{
					if(*pdown3||*pElevator3<=*pElevator1||*pElevator3>f){flag=0;(*pElevator1)++;break;}
				}
			}
			//Down
			if(down&(1<<f)){
				if((f+1)%2!=0){
					if(*pdown2||*pElevator2<=*pElevator1||*pElevator2>f){flag=0;(*pElevator1)++;break;}
				}
				else{
					if(*pdown3||*pElevator3<=*pElevator1||*pElevator3>f){flag=0;(*pElevator1)++;break;}
				}
			}
			f--;
		}
		//Reached
		if(flag)*pup1=0;
		//Reset the value of variates
		else{
			if(*pElevator1==f){
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe1=*pe1&((1<<f)^255);
			}
			else{
				up=up&((1<<*pElevator1)^255);
				*pe1=*pe1&((1<<*pElevator1)^255);
			}
		}
	}
	//Descent
	else if(*pdown1){
		f=0;flag=1;
		//Move
		while(f<*pElevator1){
			//Inside
			if(*pe1&(1<<f)){flag=0;(*pElevator1)--;break;}
			//Down
			if(down&(1<<f)){
				//Elevator2
				if((f+1)%2!=0){
					if(*pup2||*pElevator2>=*pElevator1||*pElevator2<f){flag=0;(*pElevator1)--;break;}
				}
				//Elevator3
				else{
					if(*pup3||*pElevator3>=*pElevator1||*pElevator3<f){flag=0;(*pElevator1)--;break;}
				}

			}
			//Up
			if(up&(1<<f)){
				//Elevator2
				if((f+1)%2!=0){
					if(*pup2||*pElevator2>=*pElevator1||*pElevator2<f){flag=0;(*pElevator1)--;break;}
				}
				//Elevator3
				else{
					if(*pup3||*pElevator3>=*pElevator1||*pElevator3<f){flag=0;(*pElevator1)--;break;}
				}
			}
			f++;
		}
		//Reached
		if(flag)*pdown1=0;
		//Reset the value of variates
		else{
			if(*pElevator1==f){
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe1=*pe1&((1<<f)^255);
			}
			else{
				down=down&((1<<*pElevator1)^255);
				*pe1=*pe1&((1<<*pElevator1)^255);
			}
		}
	}
	//Static
	else{
		f=7;
		while(f>=0){
			if(f>*pElevator1){
				if(*pe1&(1<<f)){*pup1=1;break;}
				if(up&(1<<f)){
					if((f+1)%2!=0){
						if(*pdown2&&*pElevator2<f||*pElevator2<*pElevator1||*pElevator2==*pElevator1&&!*pup2||*pElevator2>f&&*pElevator2-f>=f-*pElevator1){*pup1=1;break;}
					}
					else{
						if(*pdown3&&*pElevator3<f||*pElevator3<*pElevator1||*pElevator3==*pElevator1&&!*pup3||*pElevator3>f&&*pElevator3-f>=f-*pElevator1){*pup1=1;break;}
					}
					
				}
				if(down&(1<<f)){
					if((f+1)%2!=0){
						if(*pup2&&*pElevator2>f||*pElevator2<*pElevator1||*pElevator2==*pElevator1&&!*pup2||*pElevator2>f&&*pElevator2-f>=f-*pElevator1){*pup1=1;break;}
					}
					else{
						if(*pup3&&*pElevator3>f||*pElevator3<*pElevator1||*pElevator3==*pElevator1&&!*pup3||*pElevator3>f&&*pElevator3-f>=f-*pElevator1){*pup1=1;break;}
					}
				}
			}
			else if(f<*pElevator1){
				if(*pe1&(1<<f)){*pdown1=1;break;}
				if(down&(1<<f)){
					if((f+1)%2!=0){
						if(*pup2&&*pElevator2>f||*pElevator2>*pElevator1||*pElevator2==*pElevator1&&!*pdown2||*pElevator2<f&&*pElevator1-f<=f-*pElevator2){*pdown1=1;break;}
					}
					else{
						if(*pup3&&*pElevator3>f||*pElevator3>*pElevator1||*pElevator3==*pElevator1&&!*pdown3||*pElevator3<f&&*pElevator1-f<=f-*pElevator3){*pdown1=1;break;}
					}
					
				}
				if(up&(1<<f)){
					if((f+1)%2!=0){
						if(*pdown2&&*pElevator2<f||*pElevator2>*pElevator1||*pElevator2==*pElevator1&&!*pdown2||*pElevator2<f&&*pElevator1-f<=f-*pElevator2){*pdown1=1;break;}
					}
					else{
						if(*pdown3&&*pElevator3<f||*pElevator3>*pElevator1||*pElevator3==*pElevator1&&!*pdown3||*pElevator3<f&&*pElevator1-f<=f-*pElevator3){*pdown1=1;break;}
					}
								
				}
			}
			else{
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe1=*pe1&((1<<f)^255);
			}
			f--;
		}
	}

	
	
	/*------Elevator2----------*/
	if(*pup2){
		f=7;flag=1;
		while(f>*pElevator2){
			if(*pe2&(1<<f)){flag=0;(*pElevator2)++;break;}
			if((f+1)%2!=0)
			{
				if(up&(1<<f)){
						if(*pdown1||*pElevator1<=*pElevator2||*pElevator1>f){flag=0;(*pElevator2)++;break;}
				}
				if(down&(1<<f)){
						if(*pdown1||*pElevator1<=*pElevator2||*pElevator1>f){flag=0;(*pElevator2)++;break;}
				}				
			}

			f--;
		}
		if(flag)*pup2=0;
		else{
			if(*pElevator2==f){
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe2=*pe2&((1<<f)^255);
			}
			else{
				up=up&((1<<*pElevator2)^255);
				*pe2=*pe2&((1<<*pElevator2)^255);
			}
		}
	}
	else if(*pdown2){
		f=0;flag=1;
		while(f<*pElevator2){
			if(*pe2&(1<<f)){flag=0;(*pElevator2)--;break;}
			if((f+1)%2!=0){
				if(down&(1<<f)){
					if(*pup1||*pElevator1>=*pElevator2||*pElevator1<f){flag=0;(*pElevator2)--;break;}
				}
				if(up&(1<<f)){
					if(*pup1||*pElevator1>=*pElevator2||*pElevator1<f){flag=0;(*pElevator2)--;break;}
				}	
			}
			f++;
		}
		if(flag)*pdown2=0;
		else{
			if(*pElevator2==f){
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe2=*pe2&((1<<f)^255);
			}
			else{
				down=down&((1<<*pElevator2)^255);
				*pe2=*pe2&((1<<*pElevator2)^255);
			}
		}
	}
	else{
		f=7;
		while(f>=0){
			if(f>*pElevator2){
				if(*pe2&(1<<f)){*pup2=1;break;}
				if((f+1)%2!=0){
					if(up&(1<<f)){
						if(*pdown1&&*pElevator1<f||*pElevator1<*pElevator2||*pElevator1==*pElevator2&&!*pup1||*pElevator1>f&&*pElevator1-f>f-*pElevator2){*pup2=1;break;}

					}
					if(down&(1<<f)){
						if(*pup1&&*pElevator1>f||*pElevator1<*pElevator2||*pElevator1==*pElevator2&&!*pup1||*pElevator1>f&&*pElevator1-f>f-*pElevator2){*pup2=1;break;}
					}
				}
			}
			else if(f<*pElevator2){
				if(*pe2&(1<<f)){*pdown2=1;break;}
				if((f+1)%2!=0){
					if(down&(1<<f)){
						if(*pup1&&*pElevator1>f||*pElevator1>*pElevator2||*pElevator1==*pElevator2&&!*pdown1||*pElevator1<f&&*pElevator2-f<f-*pElevator1){*pdown2=1;break;}
					}
					if(up&(1<<f)){
						if(*pdown1&&*pElevator1<f||*pElevator1>*pElevator2||*pElevator1==*pElevator2&&!*pdown1||*pElevator1<f&&*pElevator2-f<f-*pElevator1){*pdown2=1;break;}
					}
				}
			}
			else{
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe2=*pe2&((1<<f)^255);
			}
			f--;
		}
	}
		
		/*------Elevator3----------*/
	if(*pup3){
		f=7;flag=1;
		while(f>*pElevator3){
			if(*pe3&(1<<f)){flag=0;(*pElevator3)++;break;}
			if((f+1)%2==0||f==0){
				if(up&(1<<f)){
						if(*pdown1||*pElevator1<=*pElevator3||*pElevator1>f){flag=0;(*pElevator3)++;break;}
				}
				if(down&(1<<f)){
						if(*pdown1||*pElevator1<=*pElevator3||*pElevator1>f){flag=0;(*pElevator3)++;break;}
				}
			}
			f--;
		}
		if(flag)*pup3=0;
		else{
			if(*pElevator3==f){
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe3=*pe3&((1<<f)^255);
			}
			else{
				up=up&((1<<*pElevator3)^255);
				*pe3=*pe3&((1<<*pElevator3)^255);
			}
		}
	}
	else if(*pdown3){
		f=0;flag=1;
		while(f<*pElevator3){
			if(*pe3&(1<<f)){flag=0;(*pElevator3)--;break;}
			if((f+1)%2==0||f==0){
				if(down&(1<<f)){
					if(*pup1||*pElevator1>=*pElevator3||*pElevator1<f){flag=0;(*pElevator3)--;break;}
				}
				if(up&(1<<f)){
					if(*pup1||*pElevator1>=*pElevator3||*pElevator1<f){flag=0;(*pElevator3)--;break;}
				}
			}
			f++;
		}
		if(flag)*pdown3=0;
		else{
			if(*pElevator3==f){
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe3=*pe3&((1<<f)^255);
			}
			else{
				down=down&((1<<*pElevator3)^255);
				*pe3=*pe3&((1<<*pElevator3)^255);
			}
		}
	}
	else{
		f=7;
		while(f>=0){
			if(f>*pElevator3){
				if(*pe3&(1<<f)){*pup3=1;break;}
				if((f+1)%2==0||f==0){
					if(up&(1<<f)){
						if(*pdown1&&*pElevator1<f||*pElevator1<*pElevator3||*pElevator1==*pElevator3&&!*pup1||*pElevator1>f&&*pElevator1-f>f-*pElevator3){*pup3=1;break;}

					}
					if(down&(1<<f)){
						if(*pup1&&*pElevator1>f||*pElevator1<*pElevator3||*pElevator1==*pElevator3&&!*pup1||*pElevator1>f&&*pElevator1-f>f-*pElevator3){*pup3=1;break;}
					}
				}
			}
			else if(f<*pElevator3){
				if(*pe3&(1<<f)){*pdown3=1;break;}
				if((f+1)%2==0||f==0){				
					if(down&(1<<f)){
						if(*pup1&&*pElevator1>f||*pElevator1>*pElevator3||*pElevator1==*pElevator3&&!*pdown1||*pElevator1<f&&*pElevator3-f<f-*pElevator1){*pdown3=1;break;}
					}
					if(up&(1<<f)){
						if(*pdown1&&*pElevator1<f||*pElevator1>*pElevator3|*pElevator1==*pElevator3&&!*pdown1||*pElevator1<f&&*pElevator3-f<f-*pElevator1){*pdown3=1;break;}
					}
				}
			}
			else{
				up=up&((1<<f)^255);
				down=down&((1<<f)^255);
				*pe3=*pe3&((1<<f)^255);
			}
			f--;
		}
	}
		
	
	
}
void main(){
	int i;
	bit push=1;

	display_elevator();
	while(1){
			i=0;
			ST_CP2 = 0;
			P37 = 1;
		
		while(i<120){
			if((p13&p17&p20&p24&P37)^push){
				if(push){
					push=0;
					if(!p17){
						up=up|(1<<(p14|p15*2|p16*4))&0x7f;
					}
					if(!p13){
						down=down|(1<<(p10|p11*2|p12*4))&0xfe;
					}
					if(!p20){
						e1=e1|(1<<(p23|p22*2|p21*4));
					}
					if(!p24){
						e2ae3 = (1<<(p27|p26*2|p25*4));
						if((e2ae3&0x55)!=0)
						{
							e2 = e2|e2ae3;
						}
						else
						{
							e3 = e3|e2ae3;
						}

					}
					if(!P37)
					{
						e3 = e3|0x01;
					}
				}
				else{
					push=1;
				}
			}
			i++;
			display_LED();
		}
		
		move(&up1,&up2,&up3,&down1,&down2,&down3,&e1,&e2,&e3,&Elevator1,&Elevator2,&Elevator3);

		

		display_elevator();
	}
}