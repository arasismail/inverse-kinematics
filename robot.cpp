//Robotun 1. eklemi referans noktansý (0,0) olarak alýnmýþtýr.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define l1 200	// uzunluklar mm cinsinden girilmiþtir...
#define l2 200	// uzunluklar mm cinsinden girilmiþtir...

#define pi 3.14159265

//---------------------------------------------------------
// Randyan derece dönüþümünün yapýldýðý fonksiyon

double convert(double radian){
   return(radian * (180/pi));
}

//----------------------------------------------------------
// X ve Y noktasý için ters kinematik formülleri ile 1.acý deðeri ve 2.acý deðeri bulama 

double derece2c1(double px, double py){
	
	return(atan2((sqrt(1-pow(((px*px+py*py-l2*l2-l1*l1)/(2*l2*l1)),2))),((px*px+py*py-l2*l2-l1*l1)/(2*l2*l1))));
}

double derece2c2(double px, double py){
	
	return(atan2(-1*(sqrt(1-pow(((px*px+py*py-l2*l2-l1*l1)/(2*l2*l1)),2))),((px*px+py*py-l2*l2-l1*l1)/(2*l2*l1))));
}

double derece1c1(double px, double py, double der2rad){
	
	return(atan2(py,px)+atan2(sqrt(py*py+px*px-(l2*cos(der2rad)+l1)*(l2*cos(der2rad)+l1)),(l2*cos(der2rad)+l1)));
}

double derece1c2(double px, double py, double der2rad){

	return(atan2(py,px)-atan2(sqrt(py*py+px*px-(l2*cos(der2rad)+l1)*(l2*cos(der2rad)+l1)),(l2*cos(der2rad)+l1)));
}

//---------------------------------------------------------------------
// 1.acý ve 2.acý için x ve y noktasý hesaplama (ileri kinematik)

double kontrolpx(double derece1, double derece2){

	return(l1*cos(derece1)+l2*cos(derece1+derece2));
}

double kontrolpy(double derece1, double derece2){

	return(l1*sin(derece1)+l2*sin(derece1+derece2));
}

//---------------------------------------------------------

int main(int argc, char *argv[]) {
	
	int i,j,k,l,xu,yu;
	char tx[200],ty[200];
    float xd=0,yd=0;

	if(argv[1][0]=='x'){
	
	xu=strlen(argv[1]);
		for(i=0;i<xu;i++){
		    
			j=i+1;	
			tx[i]=argv[1][j];
		}
		
	xd=atof(tx);
	
	}
	else{ 
	
		printf("\nX degeri icin hatali giris yapildi.\n");
		return 0;
	}
	
	
	
	if(argv[2][0]=='y'){
	
	yu=strlen(argv[2]);
		for(k=0;k<yu;k++){
		    
			l=k+1;	
			ty[k]=argv[2][l];
		}
		
	yd=atof(ty);
	}
	else{ 
	
		printf("\nY degeri icin hatali giris yapildi.\n");
		return 0;
	}
	

	double px,py,der2rc1,der2c1,der2rc2,der2c2,der1rc1,der1c1,der1rc2,der1c2,konpx1,konpy1,konpx2,konpy2,konpx3,konpy3,konpx4,konpy4,maxkont;
		
	px=(double)xd;
	py=(double)yd;
	
	maxkont=(sqrt(px*px+py*py));
	
	if((l1+l2)<maxkont){
		printf("\nMaksimum hareket alani disina cikildi.\n");
		return 0;
	}else{

	
	
	der2rc1 = derece2c1(px,py);
	der2c1 = convert(der2rc1);
	
	der2rc2 = derece2c2(px,py);
	der2c2=convert(der2rc2);

	der1rc1 =derece1c1(px,py,der2rc1);
	der1c1 = convert(der1rc1);
	
	der1rc2 =derece1c2(px,py,der2rc1);
	der1c2 = convert(der1rc2);
	

	konpx1=kontrolpx(der1rc1,der2rc1);
	konpy1=kontrolpy(der1rc1,der2rc1);
	
	konpx2=kontrolpx(der1rc1,der2rc2);
	konpy2=kontrolpy(der1rc1,der2rc2);
	
	konpx3=kontrolpx(der1rc2,der2rc1);
	konpy3=kontrolpy(der1rc2,der2rc1);
	
	konpx4=kontrolpx(der1rc2,der2rc2);
	konpy4=kontrolpy(der1rc2,der2rc2);
	
	
	if((float)px==(float)konpx1 & (float)py==(float)konpy1){
		
		printf("\n Motor 1 acisi: %.5lf derece, Motor 2 acisi: %.5lf derece\n",der1c1,der2c1);
	}
	
	if((float)px==(float)konpx2 & (float)py==(float)konpy2){
		
		printf("\n Motor 1 acisi: %.5lf derece, Motor 2 acisi: %.5lf derece\n",der1c1,der2c2);
	}
	
	if((float)px==(float)konpx3 & (float)py==(float)konpy3){
		
		printf("\n Motor 1 acisi: %.5lf derece, Motor 2 acisi: %.5lf derece\n",der1c2,der2c1);
	}
		
	if((float)px==(float)konpx4 & (float)py==(float)konpy4){
		
		printf("\n Motor 1 acisi: %.5lf derece, Motor 2 acisi: %.5lf derece\n",der1c2,der2c2);
	}	
	
	
	}	
	
	return 0;
	
}

