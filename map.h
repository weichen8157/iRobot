
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
    int mode;          // running mode,0:first run
};

typedef struct{
    char *row;
    int fill;
}COL;

COL *col;
CAR car;

void init();


void init(){
    car.x=0;
    car.y=0;
    sizeX=0.4;
    sizeY=0.4;
    mode=0;
    col = (COL*)malloc(sizeof(COL)*256);
    col[0].row = (char*)calloc(256,sizeof(char));
    col[0].row[0]=FREE;
    col[0].fill=1;
}
