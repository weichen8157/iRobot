
enum{
    UNKNOWN,
    FREE,
    OBSTACLE,
    WALL,
    FULL
};

struct CAR{
    volatile float x;// car position
    volatile float y;
    const float sizeX;// car size
    const float sizeY;
    char mode;          // running mode,0:first run
    char direction; // 0:North 1:East 2:South 3:West
};

typedef struct{
    char *row;
    int fill;
}COL;

COL *col;
CAR car;

void init();
void detect();
void updatemap();
void planpath();
void move();

int map[32][32];

void init(){
    car.x=1;
    car.y=1;
    sizeX=0.4;
    sizeY=0.4;
    mode=0;
    col = (COL*)malloc(sizeof(COL)*256);
    col[0].row = (char*)calloc(256,sizeof(char));
    col[1].row[1]=FREE;
    col[0].fill=1;
    car.direction = 0;
    int i,j;
    for(i=0;i<32;i++){
        for(j=0;j<32;j++){
            map[i][j] = FREE;
            if(j==0||i==0||i==31||j==31||(5 < j && j < 15 && 0<=i && i<=10)||(9<=j && j<=10 && 13<=i && i<=31)||(26<=j && j<=30 && 23<=i && i<=30))
                map[i][j] = OBSTACLE; 
        }
    }
}


void planpath(){
    if(car.direction == 0) { //N
        if(col[car.x].row[car.y+1] != FREE) {
            car.direction++; //N to E   
        }
    }
    else if(car.direction == 2) { //S
        if(col[car.x].row[car.y-1] != FREE) {
            car.direction--; //S to E       
        }   
    }
    else if(car.direction == 1) { //E
        if( (col[car.x].row[car.y+1] != FREE) && (col[car.x].row[car.y-1] == FREE) ) 
            car.direction++; //E to S
        else if ( (col[car.x].row[car.y-1] != FREE) && (col[car.x].row[car.y+1] == FREE) )
            car.direction--; //E to N    
    }    
    

}  

void detect(){	
   	
		for(i=car.y;i>0;i--){
			if(col[car.x].row[i]==O)	SouthO=car.y-col[car.x].row[i];
			break;
		}
		for(i=car.x;i<32;i++){
			if(col[i]==O)			EastO=col[i]-car.x;
			break;
		}
		for(i=car.x;i>0;i--){
			if(col[i]==0)			WestO=car.x-col[i];
			break;
		}
	
		for(i=car.y;i<32;i++){
			if(col[car.x].row[i]==O)	NorthO=col[car.x].row[i]-car.y;
			break;
		}
	
	
	if(car.direction==0){
		dis=NorthO;
	}

	if(car.direction==2){
		dis=SouthO;
	}
}
