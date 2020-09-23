#include<iostream>
#include<math.h>
#include<vector>
#include<GL/glut.h>

#define ld long double
#define ll long long
#define Array1D(x) vector<x>
#define Array2D(x) vector<Array1D(x)>
#define Array3D(x) vector<Array2D(x)>

#define PI 3.14159265 //Value of PI
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)
#include"colors.h" //predefine custom colors library in same directory
#define PPI 100//all 2 digit values

using namespace std;

int window_size[]={700,700};//Size of Window {height,width}
int viewport_size[]={650,650};//Size of Viewport {height,width}

Array1D(ld) rgb(int r, int g, int b){
    /*Used for the pre define color Library */
    Array1D(ld) f;
    f.push_back((double)r/255.0);
    f.push_back((double)g/255.0);
    f.push_back((double)b/255.0);
    return f;
}

void init(Array1D(ld) color ,ld alpha=1.0){
    glClearColor(color[0], color[1], color[2], 1); //Window Background Colour
    // glClearColor(0.5, 0.5, 0.5,1); //Window Background Colour
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void reshape_callback(int w, int h){
    glViewport(
        ((glutGet(GLUT_WINDOW_WIDTH)-viewport_size[1])/2),//width
        ((glutGet(GLUT_WINDOW_HEIGHT)-viewport_size[0])/2),//height
        viewport_size[1],//width
        viewport_size[0]//height
    );
}

void print3D(Array3D(ld) a){
    cout<<"[";
    for( ll i = 0; i < a.size(); i++){
        if(i==0){cout<<"[";}
        else{cout<<endl<<" [";}
        for( ll j = 0; j < a[i].size(); j++ ){
            if(j==0){cout<<"\b[[";}
            else{cout<<endl<<"  [";}
            for( ll k = 0; k < a[i][j].size(); k++){
                cout<<a[i][j][k]<<",";
            }
            cout<<"\b]";
        }
        cout<<"]";
    }
    cout<<"]"<<endl;
}
void print2D(Array2D(ld) a){
    cout<<"[[";
    ll i=0;
    for( ll j = 0; j < a[i].size(); j++ ){
        cout<<a[i][j]<<",";
    }
    cout<<"\b]";
    for( ll i = 1; i < a.size(); i++){
        cout<<endl<<" [";
        for( ll j = 0; j < a[i].size(); j++ ){
            cout<<a[i][j]<<",";
        }
        cout<<"\b]";
    }
    cout<<"]"<<endl;
}
void print1D(Array1D(ld) a){
    cout<<"[";
    for( ll i = 0; i < a.size(); i++ ){
        cout<<a[i]<<",";
    }
    cout<<"\b]"<<endl;
}

class LinearEquation{
private:
    /* data */
public:
    ld m,c;
    LinearEquation(Array1D(ld) p1,Array1D(ld) p2){
        m=(p2[1]-p1[1])/(p2[0]-p1[0]);
        c=p1[1]-(m*p1[0]);
    }
    LinearEquation(ld a,ld b,ld c){
        // ax+by+c=0
        m=-(a/b);
        c=-(c/b);
    }
    LinearEquation(Array1D(ld) p,ld slope){
        // ax+by+c=0
        m=slope;
        c=p[1]-(m*p[0]);
    }
    ld y_value(ld x){return m*x+c;}
    ld x_value(ld y){return (y-c)/m;}
    ld Func(ld x,ld y){return (m*x)+c-y;}
};

class Figure{
private:
    /* The function in this class plot with the points in range of -1.0 to 1.0 */
public:
    void Point(Array1D(ld) color,Array2D(ld) pointsArray,ld point_size=5,bool see_points=false){
    /* The function in this class plot with the points in range of -1.0 to 1.0 */
        glPointSize(point_size);
        glBegin(GL_POINTS);//rect outline
            glColor3f(color[0],color[1], color[2]);//color of outline of rect
            for ( int i = 0; i < pointsArray.size(); i++ ){
                glVertex2f(pointsArray[i][0],pointsArray[i][1]);
            }
        glEnd();
        // glFlush();
        if(see_points){
            print2D(pointsArray);
        }
    }
    void Line(Array1D(ld) color,Array2D(ld) pointsArray,ld line_width=5,bool see_points=false){
    /* The function in this class plot with the points in range of -1.0 to 1.0 */
        glLineWidth(line_width);
        glBegin(GL_LINES);//rect outline
            glColor3f(color[0],color[1], color[2]);//color of outline of rect
            for ( int i = 0; i < pointsArray.size(); i++ ){
                glVertex2f(pointsArray[i][0],pointsArray[i][1]);
                // glVertex2fv((GLfloat *)&pointsArray[i]);
            }
        glEnd();
        // glFlush();
        if(see_points){
            print2D(pointsArray);
        }
    }
    void Polygon(Array1D(ld) color,Array2D(ld) pointsArray,bool see_points=false){
    /* The function in this class plot with the points in range of -1.0 to 1.0 */
        glBegin(GL_POLYGON);//rect outline
            glColor3f(color[0],color[1], color[2]);//color of outline of rect
            for ( int i = 0; i < pointsArray.size(); i++ ){
                glVertex2f(pointsArray[i][0],pointsArray[i][1]);
            }
        glEnd();
        // glFlush();
        if(see_points){
            print2D(pointsArray);
        }
    }
};

void plotPoint(Array1D(ld) color,Array2D(ld) pointsArray,ld point_size=5,bool see_points=false){
    /* The function plot with the points in range of -PPI to PPI . Here PPI is the Global Variable*/
    glPointSize(point_size);
    glBegin(GL_POINTS);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0]/PPI,pointsArray[i][1]/PPI);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}
void plotLine(Array1D(ld) color,Array2D(ld) pointsArray,ld line_width=5,bool see_points=false){
    /* The function plot with the points in range of -PPI to PPI . Here PPI is the Global Variable*/
    glLineWidth(line_width);
    glBegin(GL_LINES);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0]/PPI,pointsArray[i][1]/PPI);
            // glVertex2fv((GLfloat *)&pointsArray[i]);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}
void plotPolygon(Array1D(ld) color,Array2D(ld) pointsArray,bool see_points=false){
    /* The function plot with the points in range of -PPI to PPI . Here PPI is the Global Variable*/
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0]/PPI,pointsArray[i][1]/PPI);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}

void plotPoint_single(Array1D(ld) color,ld x,ld y,ld stepsize,bool see_points=false){
    ld half=(stepsize/2);
    Polygon(color,{
            {x-half,y-half},
            {x-half,y+half},
            {x+half,y+half},
            {x+half,y-half}
        });
    if(see_points){print1D(  {(ld)x,(ld)y} );}
}

void plotPoint_quad(Array1D(ld) color,Array1D(ld) center, ld x,ld y, ld stepsize,bool see_points=false){
    plotPoint_single(color,x+center[0],y+center[1],stepsize,see_points);
    plotPoint_single(color,-x+center[0],-y+center[1],stepsize,see_points);
    plotPoint_single(color,-x+center[0],y+center[1],stepsize,see_points);
    plotPoint_single(color,x+center[0],-y+center[1],stepsize,see_points);
}

void plotLine_DDA(Array1D(ld) color,Array1D(ld) p1,Array1D(ld) p2,ld stepsize,bool see_points=false){
    /*Drawing line using DDA algorithm in and only for first octate*/
    LinearEquation eq(p1,p2);
    int x=round(p1[0]),y=round(p1[1]);
    ld xf=p1[0],yf=p1[1];
    
    plotPoint_single(color,x,y,stepsize,see_points);
    if(fabs(eq.m)<=1){
        while(x<p2[0]){
            x=x+stepsize;//stepsize should be 1
            yf=y+eq.m*stepsize;//stepsize should be 1
            y=round(yf);
            plotPoint_single(color,x,y,stepsize,see_points);
        }
    }
    else{
        while(y<p2[1]){
            y=y+stepsize;//stepsize should be 1
            xf=x+(1.0/eq.m)*stepsize;//stepsize should be 1
            x=round(xf);
            plotPoint_single(color,x,y,stepsize,see_points);
        }
    }
}
void plotLine_MLD(Array1D(ld) color,Array1D(ld) p1,Array1D(ld) p2,ld stepsize,bool see_points=false){
    /*Drawing line using MLD in and only for first octate*/
    ld x=p1[0],y=p1[1];
    ld dy=p2[1]-p1[1],dx=p2[0]-p1[0];
    ld d=2*dy-dx;
    ld dE=(2*dy)*stepsize;
    ld dNE=2*(dy-dx)*stepsize;
    // plot
    plotPoint_single(color,x,y,stepsize,see_points);
    while (x<p2[0]){
        if(d<=0){
            d=d+dE;//  (/_\d)E = 2dy and stepsize should be 1
        }
        else{
            d=d+(dNE);//  (/_\d)NE = 2(dy-dx)and stepsize should be 1
            y=y+(1*stepsize);//and stepsize should be 1
        }
        x=x+(1*stepsize);//and stepsize should be 1
        // plot
        plotPoint_single(color,x,y,stepsize,see_points);
    }
}
void plotLine_MLD_modified(Array1D(ld) color,Array1D(ld) p1,Array1D(ld) p2,ld stepsize,Array1D(ld) toggler,bool see_points=false){
    /*Drawing line using MLD in any one octate based on toggle variable*/
    ld x=p1[0],y=p1[1];
    ld dy=p2[1]-p1[1],dx=p2[0]-p1[0];
    ld d=2*dy-dx;
    ld dE=(2*dy)*stepsize;
    ld dNE=2*(dy-dx)*stepsize;
    // plot
    plotPoint_single(color,(toggler[0]*x+toggler[1]*y),(toggler[2]*x+toggler[3]*y),stepsize,see_points);
    while (x<p2[0]){
        if(d<=0){
            d=d+dE;//  (/_\d)E = 2dy and stepsize should be 1
        }
        else{
            d=d+(dNE);//  (/_\d)NE = 2(dy-dx)and stepsize should be 1
            y=y+(1*stepsize);//and stepsize should be 1
        }
        x=x+(1*stepsize);//and stepsize should be 1
        // plot
        plotPoint_single(color,(toggler[0]*x+toggler[1]*y),(toggler[2]*x+toggler[3]*y),stepsize,see_points);
    }
}
void plotLine_MLD_all(Array1D(ld) color,Array1D(ld) p1,Array1D(ld) p2,ld stepsize,bool see_points=false){
    /*Drawing line using MLD in any octates*/
    ld m=(p2[1]-p1[1])/(p2[0]-p1[0]);
    if(m<=1 && m>=0 && p1[0]<p2[0]){
        plotLine_MLD_modified(color,p1,p2,stepsize,{1,0,0,1},see_points); // plot x,y
    }//octate 1
    else if(m>1 && p1[1]<p2[1]){
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,1,1,0},see_points); // plot y,x
    }//octate 2
    else if(m<-1 && p1[1]<p2[1]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,-1,1,0},see_points);// plot -y,x
    }//octate 3
    else if(m<=0 && m>=-1 && p2[0]<p1[0]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        plotLine_MLD_modified(color,p1,p2,stepsize,{-1,0,0,1},see_points);// plot -x,y
    }//octate 4
    else if(m<=1 && m>0 && p2[0]<p1[0]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        p1[1]=-p1[1];p2[1]=-p2[1];
        plotLine_MLD_modified(color,p1,p2,stepsize,{-1,0,0,-1},see_points);// plot -x,-y
    }//octate 5
    else if(m>1 && p2[1]<p1[1]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        p1[1]=-p1[1];p2[1]=-p2[1];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,-1,-1,0},see_points);// plot -y,-x
    }//octate 6
    else if(m<-1 && p2[1]<p1[1]){
        p1[1]=-p1[1];p2[1]=-p2[1];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        plotLine_MLD_modified(color,p1,p2,stepsize,{0,1,-1,0},see_points);// plot y,-x
    }//octate 7
    else if(m<0 && m>=-1 && p1[0]<p2[0]){
        p1[1]=-p1[1];p2[1]=-p2[1];
        plotLine_MLD_modified(color,p1,p2,stepsize,{1,0,0,-1},see_points);// plot x,-y
    }//octate 8
}

void plotLine_custom(Array1D(ld) p1,Array1D(ld) p2,Array1D(ld) color,ld stepsize,ld precision){
    int c=0;
    LinearEquation myeq(p1,p2);
    ld prec=(stepsize*precision);
    if(p1[0]==p2[0]){
        swap(p1[0],p1[1]);
        swap(p2[0],p2[1]);
        c++;
    }
    for(ld i=(p1[0]);i<(p2[0]);i+=precision/10){
        ld x=i,y=myeq.y_value(i);
        if(c>0){swap(x,y);}
        plotPolygon(color,{
            {round(x/prec)*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
            {round(x/prec)*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
        });
    }
}

void plorCircle_MLD(Array1D(ld) color,Array1D(ld) center,ld radius,ld stepsize,bool see_points=false){
        // only for 2 octant
    ld x=0,y=radius,d=1-radius;
    // draw circle
    plotPoint_single(color,x,y,stepsize,see_points);
    while (y>x){
        if(d<0){
            d=d+2*x+3;
        }
        else{
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x=x+1;
        // draw circle
        plotPoint_single(color,x,y,stepsize,see_points);
    }
}
void plotCircle_MLD_modified(Array1D(ld) color,Array1D(ld) center,ld radius,ld stepsize,Array1D(ld) toggler,bool see_points=false){
        // only for 2 octant
    ld x=0,y=radius,d=1-radius;
    // draw circle
    plotPoint_single(color,
    (toggler[0]*x+toggler[1]*y+   (abs(toggler[0])*center[0]+abs(toggler[1])*center[1])  ),
    (toggler[2]*x+toggler[3]*y+   (abs(toggler[2])*center[0]+abs(toggler[3])*center[1])  ),
    stepsize,see_points);
    while (y>x){
        if(d<0){
            d=d+2*x+3;
        }
        else{
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x=x+1;
        // draw circle
        plotPoint_single(color,
        (toggler[0]*x+toggler[1]*y+   (abs(toggler[0])*center[0]+abs(toggler[1])*center[1])  ),
        (toggler[2]*x+toggler[3]*y+   (abs(toggler[2])*center[0]+abs(toggler[3])*center[1])  ),
        stepsize,see_points);
    }
}
void plotCircle_MLD_all(Array1D(ld) color,Array1D(ld) center,ld radius,ld stepsize,bool see_points=false){
    
    plotCircle_MLD_modified(color,center,radius,stepsize,{0,1,1,0},see_points);//1 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{1,0,0,1},see_points);//2 octate

    plotCircle_MLD_modified(color,center,radius,stepsize,{-1,0,0,1},see_points);// 3 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{0,-1,1,0},see_points);// 4 octate

    plotCircle_MLD_modified(color,center,radius,stepsize,{0,-1,-1,0},see_points);// 5 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{-1,0,0,-1},see_points);// 6 octate

    plotCircle_MLD_modified(color,center,radius,stepsize,{1,0,0,-1},see_points);// 7 octate
    plotCircle_MLD_modified(color,center,radius,stepsize,{0,1,-1,0},see_points);// 8 octate
}
void plotEllipse_MLD(Array1D(ld) color,Array1D(ld) center,ld a,ld b,ld stepsize,bool see_points=false){
    int x=0,y=b;
    int sa=a*a,sb=b*b;
    int d1=sb-sa*b+0.25*sa;
    //draw
    plotPoint_quad(color,center,x,y,stepsize,see_points);
    
    while(sa*(y-0.5)>sb*(x+1)){
        if(d1<0){
            d1+=sb*((x<<1)+3);
        }
        else{
            d1+=sb*((x<<1)+3)+sa*(-(y<<1)+2);
            y--;
        }
        x++;
        // draw
        plotPoint_quad(color,center,x,y,stepsize,see_points);
        
    }
    int d2=sb*(x+0.5)*(x+0.5)+sa*(y-1)*(y-1)-sa*sb;
    //draw
    plotPoint_quad(color,center,x,y,stepsize,see_points);
    
    while(y>0){
        if(d2<0){
            d2+=sb*((x<<1)+2)+sa*(-(y<<1)+3);
            x++;
        }
        else{
            d2+=sb*(-(y<<1)+3);
        }
        y--;
        // draw
        plotPoint_quad(color,center,x,y,stepsize,see_points);
    }

}
void display1(void){
    init(steelblue);
    Figure A;
    A.Polygon(gainsboro,{{1.0,1.0},{1.0,-1.0},{-1.0,-1.0},{-1.0,1.0}});//background
    ld stepsize=1;
    ld precision=0.025;
    for(ld i=0;i<1;i+=precision){//Axis points
        A.Point(black,{
            {i,0.0},
            {0.0,i},
            {-i,0.0},
            {0.0,-i}
        },3);
    }
    for(ld i=0;i<=1;i+=precision*stepsize){//Grid
        A.Line(blue,{
            {1.0,i},{-1.0,i},
            {i,1.0},{i,-1.0},

            {1.0,-i},{-1.0,-i},
            {-i,1.0},{-i,-1.0}
        },1);
    }
    // Ellipse
    ld a=1,b=0.5;
    ld prec=(stepsize*precision);
    for(ld i=0;i<360;i+=prec){
        ld x=a*cos(i deg),y=b*sin(i deg);
        A.Polygon(green,{
            {round(x/prec)*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),(round(y/prec)+1*(y/fabs(y)))*(prec)},
            {round(x/prec)*(prec),(round(y/prec)+1*(y/fabs(y)))*(prec)},

            
        });
    }
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(
        window_size[1],//width
        window_size[0]//height
    );
    // glutInitWindowPosition(100, 100);
    
    glutInitWindowPosition(
        (glutGet(GLUT_SCREEN_WIDTH)-window_size[1])/2,
        (glutGet(GLUT_SCREEN_HEIGHT)-window_size[0])/2
    );
    glutCreateWindow("Experimental Tab1");
    // init(grey);
    glutDisplayFunc(display1);
    glutReshapeFunc(reshape_callback);

    glutMainLoop();
    return 0;
}