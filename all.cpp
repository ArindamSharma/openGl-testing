#include<iostream>
#include<math.h>//sin,cos,sqrt
#include<unistd.h>//sleep
#include<vector>//vector
#include<string>
#include<GL/glut.h>
#include"colors.h"//custom colors for rgb function

#define ld long double
#define ll long long
#define Array1D(x) vector<x>
#define Array2D(x) vector<Array1D(x)>
#define Array3D(x) vector<Array2D(x)>

#define PI 3.14159265 //Value of PI
#define deg *0.0174532925//Conversion to degree from radiant (PI/180=0.0174532925)
#define globalprec 1000
#define ldrand (ld)(rand()%globalprec)+(1.0/(ld)(rand()%globalprec))
#define intrand (rand()%globalprec)

using namespace std;
ld mx,my;
bool check;
// int window_size[]={700,700};//Size of Window {height,width}
// int viewport_size[]={650,650};//Size of Viewport {height,width}
int window_size[]={864,1152};//{height,width}
int viewport_size[]={768,1024};//{height,width}

//function decleration
Array1D(ld) rgb(int r, int g, int b);

template <typename T>
T customScaling(T x,Array1D(ld) inputRange,Array1D(ld) outputRange){
    ld tmp1=-inputRange[0];
    // inputRange[0]+=tmp1;
    inputRange[1]+=tmp1;
    ld tmp2=-outputRange[0];
    // outputRange[0]+=tmp2;
    outputRange[1]+=tmp2;
    x+=tmp1;
    x=x/(inputRange[1]);
    x*=outputRange[1];
    x-=tmp2;
    return x;
    // return ((x/(inputRange[1]-inputRange[0]))*(outputRange[1]-outputRange[0]))+outputRange[0];
}
template<typename T>
void print3D(Array3D(T) a){
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
template<typename T>
void print2D(Array2D(T) a){
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
template<typename T>
void print1D(Array1D(T) a){
    cout<<"[";
    for( ll i = 0; i < a.size(); i++ ){
        cout<<a[i]<<",";
    }
    cout<<"\b]"<<endl;
}

void init(Array1D(ld) color ,ld alpha=1.0){
    glClearColor(color[0], color[1], color[2], 1); //Window Background Colour
    // glClearColor(0.5, 0.5, 0.5,1); //Window Background Colour
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
void reshape_callback(int w, int h){
    int my_w=glutGet(GLUT_WINDOW_WIDTH),
    my_h=glutGet(GLUT_WINDOW_HEIGHT);
    window_size[0]=my_h;
    window_size[1]=my_w;
    glViewport(
        ((my_w-viewport_size[1])/2),//width
        ((my_h-viewport_size[0])/2),//height
        viewport_size[1],//width
        viewport_size[0]//height
    );
    glutPostRedisplay();
}
void mouse_callback(int button, int state, int x, int y){{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        check=true;
        mx = x-(window_size[1]/2.0);
        my = -y+(window_size[0]/2.0);
        // scalling window size to viewport_size[0]
        // mx=(mx/viewport_size[1])*viewport_size[0]*2;
        // my=(my/viewport_size[0])*viewport_size[0]*2;
        // cout<<"("<<mx<<","<<my<<")"<<endl;
    glutPostRedisplay();
    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){//undo(clear)the drawing
        init(steelblue);
        check = false;
    glutPostRedisplay();
    }
}}

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

Array1D(ld) rgb(int r, int g, int b){
    /*Used for the pre define color Library */
    Array1D(ld) f;
    f.push_back((double)r/255.0);
    f.push_back((double)g/255.0);
    f.push_back((double)b/255.0);
    return f;
}
Array1D(ld) rgb_invert(int r, int g, int b){
    Array1D(ld) f=rgb(r,g,b);
    f[0]=1-f[0];
    f[1]=1-f[1];
    f[2]=1-f[2];
    return f;
}
Array1D(ld) rgb_brightness(Array1D(ld) &color,ld brigntness_percentage){
    color[0]*=brigntness_percentage/100;
    color[1]*=brigntness_percentage/100;
    color[2]*=brigntness_percentage/100;
    return color;
}
Array1D(ld) getPixelColor(Array1D(ld) p,ld stepsize=1,bool see_point=false){
    unsigned char pixel[4];
    if(see_point){
    print1D((Array1D(ld)){
        customScaling(p[0],{(ld)-viewport_size[1],(ld)viewport_size[1]},{0,(ld)window_size[1]}),
        customScaling(p[1],{(ld)-viewport_size[0],(ld)viewport_size[0]},{0,(ld)window_size[0]})
        });
    }
    glReadPixels(
        customScaling(p[0],{(ld)-viewport_size[1],(ld)viewport_size[1]},{0,(ld)window_size[1]}),
        customScaling(p[1],{(ld)-viewport_size[0],(ld)viewport_size[0]},{0,(ld)window_size[0]}),
        
        stepsize,stepsize,GL_RGB,GL_UNSIGNED_BYTE,pixel);
    // return rgb((ld)pixel[0],(ld)pixel[1],(ld)pixel[2]);
    return {(ld)pixel[0],(ld)pixel[1],(ld)pixel[2]};
}

void plotPoint(Array1D(ld) color,Array2D(ld) pointsArray,ld point_size=5,bool see_points=false){
    /* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
    glPointSize(point_size);
    glBegin(GL_POINTS);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0],pointsArray[i][1]);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}
void plotLine(Array1D(ld) color,Array2D(ld) pointsArray,ld line_width=5,bool see_points=false){
    /* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
    glLineWidth(line_width);
    glBegin(GL_LINES);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0],pointsArray[i][1]);
            // glVertex2fv((GLfloat *)&pointsArray[i]);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}
void plotLineLoop(Array1D(ld) color,Array2D(ld) pointsArray,ld line_width=5,bool see_points=false){
    /* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
    glLineWidth(line_width);
    glBegin(GL_LINE_LOOP);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0],pointsArray[i][1]);
            // glVertex2fv((GLfloat *)&pointsArray[i]);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}
void plotPolygon(Array1D(ld) color,Array2D(ld) pointsArray,bool see_points=false){
    /* The function plot with the points in range of -viewport_size[0] to viewport_size[0] . Here viewport_size[0] is the Global Variable*/
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < pointsArray.size(); i++ ){
            glVertex2f(pointsArray[i][0],pointsArray[i][1]);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(pointsArray);}
}
void plotBoundary_box(Array2D(ld) myfigure,ld line_width=5,bool see_points=false){
    
    ld min_x=myfigure[0][0],
    min_y=myfigure[0][1],
    max_x=myfigure[0][0],
    max_y=myfigure[0][1];

    for(int i=0;i<myfigure.size();i++){//for x
        if(myfigure[i][0]<min_x){min_x=myfigure[i][0];}
        if(myfigure[i][0]>max_x){max_x=myfigure[i][0];}
        if(myfigure[i][1]<min_y){min_y=myfigure[i][1];}
        if(myfigure[i][1]>max_y){max_y=myfigure[i][1];}
    }
    // // bounding Box
    plotLineLoop(blue,{
        {max_x,max_y},
        {min_x,max_y},

        {min_x,min_y},
        {max_x,min_y}
    },line_width,see_points);
}
void plotPoint_single(Array1D(ld) color,ld x,ld y,ld stepsize,bool see_points=false){
    ld half=(stepsize/2);
    plotPolygon(color,{
            {x-half,y-half},
            {x-half,y+half},
            {x+half,y+half},
            {x+half,y-half}
        });
    if(see_points){print1D( (Array1D(ld)){(ld)x,(ld)y} );}
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
void plotCircle_MLD(Array1D(ld) color,Array1D(ld) center,ld radius,ld stepsize,bool see_points=false){
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

void fillcolor_BF4(Array1D(ld) p,Array1D(ld) fillcolor,Array1D(ld) boundarycolor,ld stepsize=1,ld thickness=5,bool see_points=false){
    Array1D(ld) color=getPixelColor({p[0],p[1]});
    // cout<<(color!=fillcolor && color!=boundarycolor)<<endl;
    bool condition =
    color[0]!=fillcolor[0] && 
    color[1]!=fillcolor[1] && 
    color[2]!=fillcolor[2] &&
    color[0]!=boundarycolor[0] && 
    color[1]!=boundarycolor[1] && 
    color[2]!=boundarycolor[2];
    // if((color!=fillcolor) && (color!=boundarycolor)){
    if(condition){
        plotPoint(fillcolor,{{p[0],p[1]}},thickness,see_points);//filling desired color
        glFlush();
        fillcolor_BF4({p[0]+stepsize,p[1]},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF4({p[0]-stepsize,p[1]},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF4({p[0],p[1]+stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF4({p[0],p[1]-stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
    }
    // cout<<"end"<<endl;
}
void fillcolor_BF8(Array1D(ld) p,Array1D(ld) fillcolor,Array1D(ld) boundarycolor,ld stepsize=1,ld thickness=5,bool see_points=false){
    Array1D(ld) color=getPixelColor({p[0],p[1]});
    bool condition =
    color[0]!=fillcolor[0] && 
    color[1]!=fillcolor[1] && 
    color[2]!=fillcolor[2] &&
    color[0]!=boundarycolor[0] && 
    color[1]!=boundarycolor[1] && 
    color[2]!=boundarycolor[2];
    // if((color!=fillcolor) && (color!=boundarycolor)){
    if(condition){
        plotPoint(fillcolor,{{p[0],p[1]}} ,thickness,see_points);
        glFlush();
        fillcolor_BF8({p[0]+stepsize,p[1]},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF8({p[0],p[1]+stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF8({p[0]-stepsize,p[1]},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF8({p[0],p[1]-stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);

        fillcolor_BF8({p[0]+stepsize,p[1]+stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF8({p[0]+stepsize,p[1]-stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF8({p[0]-stepsize,p[1]+stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
        fillcolor_BF8({p[0]-stepsize,p[1]-stepsize},fillcolor,boundarycolor,stepsize,thickness,see_points);
    }
}
void fillcolor_floodfill(Array1D(ld) p,Array1D(ld) oldcolor,Array1D(ld) newcolor,ld stepsize=1,ld thickness=5,bool see_points=false){
    Array1D(ld) color=getPixelColor({p[0],p[1]});
    bool condition =
    color[0]==oldcolor[0] && 
    color[1]==oldcolor[1] && 
    color[2]==oldcolor[2];
    // if(color==oldcolor){
    if(condition){
        plotPoint(newcolor,{{p[0],p[1]}},thickness,see_points);
        glFlush();
        fillcolor_floodfill({p[0]+stepsize,p[1]},oldcolor,newcolor,stepsize,thickness,see_points);
        fillcolor_floodfill({p[0]-stepsize,p[1]},oldcolor,newcolor,stepsize,thickness,see_points);
        fillcolor_floodfill({p[0],p[1]+stepsize},oldcolor,newcolor,stepsize,thickness,see_points);
        fillcolor_floodfill({p[0],p[1]-stepsize},oldcolor,newcolor,stepsize,thickness,see_points);

        fillcolor_floodfill({p[0]+stepsize,p[1]+stepsize},oldcolor,newcolor,stepsize,thickness,see_points);
        fillcolor_floodfill({p[0]+stepsize,p[1]-stepsize},oldcolor,newcolor,stepsize,thickness,see_points);
        fillcolor_floodfill({p[0]-stepsize,p[1]-stepsize},oldcolor,newcolor,stepsize,thickness,see_points);
        fillcolor_floodfill({p[0]-stepsize,p[1]+stepsize},oldcolor,newcolor,stepsize,thickness,see_points);
    }
}

Array2D(ld) translate(Array2D(ld) figure,Array1D(ld) factor){
    Array2D(ld) f;
    for(int i=0;i<figure.size();i++){
        f.push_back({figure[i][0]+factor[0],figure[i][1]+factor[1]});
    }
    return f;
}
Array1D(ld) find_center(Array2D(ld) figure){
    ld maxx=figure[0][0];
    ld maxy=figure[0][1];
    ld minx=figure[0][0];
    ld miny=figure[0][1];
    for(int i=0;i<figure.size();i++){
        if(maxx<figure[i][0]){maxx=figure[i][0];}
        if(maxy<figure[i][1]){maxy=figure[i][1];}
        if(minx>figure[i][0]){minx=figure[i][0];}
        if(miny>figure[i][1]){miny=figure[i][1];}
    }
    return {minx+((maxx-minx)/2),miny+((maxy-miny)/2)};
}
Array2D(ld) rotate(Array2D(ld) figure,ld degree,bool origin=false){
    Array2D(ld) f;
    if(origin){
        for(int i=0 ;i<figure.size();i++){
            f.push_back({
                figure[i][0]*cos(degree deg)-figure[i][1]*sin(degree deg),
                figure[i][1]*cos(degree deg)+figure[i][0]*sin(degree deg),
            });
        }
        return f;
    }
    else{
        Array1D(ld) a=find_center(figure);
        for(int i=0;i<a.size();i++){a[i]*=-1;}
        Array2D(ld) final=translate(figure,a);
        for(int i=0;i<final.size();i++){
            ld x=final[i][0],y=final[i][1];
            final[i][0]=x*cos(degree deg)-y*sin(degree deg);
            final[i][1]=y*cos(degree deg)+x*sin(degree deg);
        }
        return translate(final,find_center(figure));
    }
}
Array2D(ld) scale(Array2D(ld) figure,ld factor){
    Array1D(ld) a=find_center(figure);
    for(int i=0;i<a.size();i++){a[i]*=-1;}
    Array2D(ld) f=translate(figure,a);
    for(int i=0;i<f.size();i++){
        f[i][0]*=factor;
        f[i][1]*=factor;
    }
    f=translate(f,find_center(figure));
    return f;
}

Array2D(ld) getcirclepoints(Array1D(ld) origin,ld r,Array1D(ld) angles,ld precision=0.1){
    Array2D(ld) circlepoints;
    for(ld i=angles[0];i<angles[1];i+=precision){
        circlepoints.push_back({(origin[0]+r*cos(i deg)),(origin[1]+r*sin(i deg))});
    }
    return circlepoints;
}
Array2D(ld) getellipsepoints(Array1D(ld) origin, ld a,ld b ,ld precision=0.8,ld thick=5,bool see=false){
    Array2D(ld) result;
    for(ld i=0;i<360;i+=precision){
        result.push_back({(origin[0]+a*cos(i deg)),(origin[1]+b*sin(i deg))});
    }
    return result;
}

Array2D(ld) font_letter(char l,ld precision=0.1){
    Array2D(ld) letter;
    int temp=l;
    if(temp==65){
        // cout<<"the Letter used is A"<<endl;
        LinearEquation a1({2,0},{-2,0});//horizontal
        LinearEquation a2({3,-2},{0,4});//right
        LinearEquation a3({-3,-2},{0,4});//left
        for(ld i=-2;i<2;i+=precision*2){ letter.push_back({i,a1.y_value(i)});}
        for(ld i=0;i<3;i+=precision){ letter.push_back({i,a2.y_value(i)});}
        for(ld i=-3;i<0;i+=precision){ letter.push_back({i,a3.y_value(i)});}
        return letter;
    }
    else if(temp==66){
        // cout<<"the Letter used is B"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(ld x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(ld i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper
        for(ld x=0;x>-2;x-=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(ld i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(-0.5+1.5*sin(i deg))});}//semicircle bottom
        for(ld x=0;x>-2;x-=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        return letter;
    }
    else if(temp==67){
        // cout<<"the Letter used is C"<<endl;
        for(ld i=45;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper
        for(ld y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//left
        for(ld i=180;i<315;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        return letter;
    }
    else if(temp==68){
        // cout<<"the Letter used is D"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(ld x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(ld i=90;i>0;i-=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle
        for(ld y=2;y>0;y-=precision*2){ letter.push_back({2,y});}//right
        for(ld i=0;i>-90;i-=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle
        for(ld x=0;x>-2;x-=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        return letter;
    }
    else if(temp==69){
        // cout<<"the Letter used is E"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(ld x=-2;x<1.5;x+=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        return letter;
    }
    else if(temp==70){
        // cout<<"the Letter used is F"<<endl;
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        return letter;
    }
    else if(temp==71){
        // cout<<"the Letter used is G"<<endl;
        for(ld i=23;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper
        for(ld y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(ld i=180;i<337;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        ld lx=letter[letter.size()-1][0],ly=letter[letter.size()-1][1];
        for(ld y=ly;y<0.5;y+=precision*2){ letter.push_back({lx,y});}// vertical right
        for(ld x=lx;x>0;x-=precision*2){ letter.push_back({x,0.5});}//horizontal middle
        return letter;
    }
    else if(temp==72){
        // cout<<"the Letter used is H"<<endl;
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,1});}//horizontal
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({2,y});}//right
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        // print2D(letter);
        return letter;
    }
    else if(temp==73){
        // cout<<"the Letter used is I"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({0,y});}//vertical
        return letter;
    }
    else if(temp==74){
        // cout<<"the Letter used is J"<<endl;
        for(ld i=180;i<360;i+=precision*75){letter.push_back({(1+1*cos(i deg)),(-1+1*sin(i deg))});}//semicircle
        for(ld y=-1;y<4;y+=precision*2){ letter.push_back({2,y});}//right vertical
        return letter;
    }
    else if(temp==75){
        // cout<<"the Letter used is K"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-1.5,y});}//vertical
        Array1D(ld) p1={1.5,4},p2={1.5,-2},p3={-1.25,1};
        LinearEquation a2(p1,p3);//right
        LinearEquation a3(p2,p3);//left
        for(ld x=p1[0];x>p3[0];x-=precision){ letter.push_back({x,a2.y_value(x)});}//top
        for(ld x=p3[0];x<p2[0];x+=precision){ letter.push_back({x,a3.y_value(x)});}//bottom
        return letter;
    }
    else if(temp==76){
        // cout<<"the Letter used is L"<<endl;
        for(ld y=4;y>-2;y-=precision*2){ letter.push_back({-2,y});}//left
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,-2});}//horizontal top
        return letter;
    }
    else if(temp==77){
        // cout<<"the Letter used is M"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        Array1D(ld) p1={-2,4},p3={0,0},p2={2,4};
        LinearEquation a2(p1,p3);//left
        LinearEquation a3(p3,p2);//right
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        for(ld x=p3[0];x<p2[0];x+=precision){ letter.push_back({x,a3.y_value(x)});}//right
        for(ld y=4;y>-2;y-=precision*2){ letter.push_back({2,y});}//right
        return letter;
    }
    else if(temp==78){
        // cout<<"the Letter used is N"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        Array1D(ld) p1={-2,4},p3={2,-2};
        LinearEquation a2(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({2,y});}//right
        return letter;
    }
    else if(temp==79){
        // cout<<"the Letter used is O"<<endl;
        for(ld i=90;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper left
        for(ld y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(ld i=180;i<360;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        for(ld y=0;y<2;y+=precision*2){ letter.push_back({2,y});}//vertical right
        for(ld i=0;i<90;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
        return letter;
    }
    else if(temp==80){
        // cout<<"the Letter used is P"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(ld x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(ld i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper
        for(ld x=0;x>-2;x-=precision*2){ letter.push_back({x,1});}//horizontal middle
        return letter;
    }
    else if(temp==81){
        // cout<<"the Letter used is Q"<<endl;
        for(ld i=90;i<180;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper left
        for(ld y=2;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(ld i=180;i<360;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        for(ld y=0;y<2;y+=precision*2){ letter.push_back({2,y});}//vertical right
        for(ld i=0;i<90;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
        for(ld i=225;i<270;i+=precision*75){letter.push_back({(2+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle upper right
        return letter;
    }
    else if(temp==82){
        // cout<<"the Letter used is R"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({-2,y});}//left
        for(ld x=-2;x<0;x+=precision*2){ letter.push_back({x,4});}//horizontal top 
        for(ld i=90;i>-90;i-=precision*75){letter.push_back({(0+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper
        for(ld x=0;x>-2;x-=precision*2){ letter.push_back({x,1});}//horizontal middle
        Array1D(ld) p1={0,1},p3={2,-2};
        LinearEquation a2(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        
        return letter;
    }
    else if(temp==83){
        // cout<<"the Letter used is S"<<endl;
        for(ld i=45;i<90;i+=precision*75){letter.push_back({(0.5+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
        for(ld x=0.5;x>-0.5;x-=precision*2){ letter.push_back({x,4});}//horizontal top
        for(ld i=90;i<270;i+=precision*75){letter.push_back({(-0.5+1.5*cos(i deg)),(2.5+1.5*sin(i deg))});}//semicircle upper left
        for(ld x=-0.5;x<0.5;x+=precision*2){ letter.push_back({x,1});}//horizontal middle
        for(ld i=90;i>-90;i-=precision*75){letter.push_back({(0.5+1.5*cos(i deg)),(-0.5+1.5*sin(i deg))});}//semicircle lower right
        for(ld x=0.5;x>-0.5;x-=precision*2){ letter.push_back({x,-2});}//horizontal bottom
        for(ld i=270;i>202.5;i-=precision*75){letter.push_back({(-0.5+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle lower left
        return letter;
    }
    else if(temp==84){
        // cout<<"the Letter used is T"<<endl;
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({0,y});}//left
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top
        return letter;
    }
    else if(temp==85){
        // cout<<"the Letter used is U"<<endl;
        for(ld y=4;y>0;y-=precision*2){ letter.push_back({-2,y});}//vertical left
        for(ld i=180;i<360;i+=precision*75){letter.push_back({(0+2*cos(i deg)),(0+2*sin(i deg))});}//semicircle bottom
        for(ld y=0;y<4;y+=precision*2){ letter.push_back({2,y});}//vertical right
        return letter;
    }
    else if(temp==86){
        // cout<<"the Letter used is V"<<endl;
        Array1D(ld) p1={-2,4},p3={0,-2};
        LinearEquation a2(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        p3={2,4},p1={0,-2};
        LinearEquation a1(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a1.y_value(x)});}//left
        return letter;
    }
    else if(temp==87){
        // cout<<"the Letter used is W"<<endl;
        // letter=rotate(font_letter('M',precision),180);
        for(ld y=4;y>-2;y-=precision*2){ letter.push_back({-2,y});}//left
        Array1D(ld) p1={-2,-2},p3={0,2},p2={2,-2};
        LinearEquation a2(p1,p3);//left
        LinearEquation a3(p3,p2);//right
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        for(ld x=p3[0];x<p2[0];x+=precision){ letter.push_back({x,a3.y_value(x)});}//right
        for(ld y=-2;y<4;y+=precision*2){ letter.push_back({2,y});}//right
        return letter;
    }
    else if(temp==88){
        // cout<<"the Letter used is X"<<endl;
        Array1D(ld) p1={-2,4},p3={2,-2};
        LinearEquation a2(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        p3={2,4},p1={-2,-2};
        LinearEquation a1(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a1.y_value(x)});}//left
        return letter;
    }
    else if(temp==89){
        // cout<<"the Letter used is Y"<<endl;
        Array1D(ld) p1={-2,4},p3={0,1};
        LinearEquation a2(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a2.y_value(x)});}//left
        p3={2,4},p1={0,1};
        LinearEquation a1(p1,p3);//left
        for(ld x=p1[0];x<p3[0];x+=precision){ letter.push_back({x,a1.y_value(x)});}//left
        
        for(ld y=-2;y<1;y+=precision*2){ letter.push_back({0,y});}//left
        return letter;
    }
    else if(temp==90){
        // cout<<"the Letter used is Z"<<endl;
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,4});}//horizontal top
        Array1D(ld) p1={2,4},p3={-2,-2};
        LinearEquation a1(p1,p3);//left
        for(ld x=p1[0];x>p3[0];x-=precision){ letter.push_back({x,a1.y_value(x)});}//left
        for(ld x=-2;x<2;x+=precision*2){ letter.push_back({x,-2});}//horizontal top
        return letter;
    }

    
    else if(temp==97){
        // cout<<"the Letter used is a"<<endl;
        return letter;
    }
    else if(temp==98){
        // cout<<"the Letter used is b"<<endl;
        return letter;
    }
    else if(temp==99){
        // cout<<"the Letter used is c"<<endl;
        return letter;
    }
    else if(temp==100){
        // cout<<"the Letter used is d"<<endl;
        return letter;
    }
    else if(temp==101){
        // cout<<"the Letter used is e"<<endl;
        return letter;
    }
    else if(temp==102){
        // cout<<"the Letter used is f"<<endl;
        return letter;
    }
    else if(temp==103){
        // cout<<"the Letter used is g"<<endl;
        return letter;
    }
    else if(temp==104){
        // cout<<"the Letter used is h"<<endl;
        return letter;
    }
    else if(temp==105){
        // cout<<"the Letter used is i"<<endl;
        return letter;
    }
    else if(temp==106){
        // cout<<"the Letter used is j"<<endl;
        return letter;
    }
    else if(temp==107){
        // cout<<"the Letter used is k"<<endl;
        return letter;
    }
    else if(temp==108){
        // cout<<"the Letter used is l"<<endl;
        return letter;
    }
    else if(temp==109){
        // cout<<"the Letter used is m"<<endl;
        return letter;
    }
    else if(temp==110){
        // cout<<"the Letter used is n"<<endl;
        return letter;
    }
    else if(temp==111){
        // cout<<"the Letter used is o"<<endl;
        return letter;
    }
    else if(temp==112){
        // cout<<"the Letter used is p"<<endl;
        return letter;
    }
    else if(temp==113){
        // cout<<"the Letter used is q"<<endl;
        return letter;
    }
    else if(temp==114){
        // cout<<"the Letter used is r"<<endl;
        return letter;
    }
    else if(temp==115){
        // cout<<"the Letter used is s"<<endl;
        return letter;
    }
    else if(temp==116){
        // cout<<"the Letter used is t"<<endl;
        return letter;
    }
    else if(temp==117){
        // cout<<"the Letter used is u"<<endl;
        return letter;
    }
    else if(temp==118){
        // cout<<"the Letter used is v"<<endl;
        return letter;
    }
    else if(temp==119){
        // cout<<"the Letter used is w"<<endl;
        return letter;
    }
    else if(temp==120){
        // cout<<"the Letter used is x"<<endl;
        return letter;
    }
    else if(temp==121){
        // cout<<"the Letter used is y"<<endl;
        return letter;
    }
    else if(temp==122){
        // cout<<"the Letter used is z"<<endl;
        return letter;
    }
    else{
        cout<<"Error in Cheractor"<<endl;
        exit(1);
    }
}
void textRendering(string str,Array1D(ld) location,Array1D(ld) color,ld mysize=8){
    ld strsize=str.size();
    ld space_btw_letter=6;
    strsize=-(strsize*mysize*space_btw_letter)/2.0;
    for(int i=0;i<str.size();i++){
        strsize+=mysize*space_btw_letter;
        ld fontthickness=mysize/2;
        Array2D(ld) l=scale(font_letter(str[i],1.25/mysize),mysize);
        Array1D(ld) origin={location[0]*mysize+strsize,location[1]*mysize};
        // for(ll j=0;j<l.size();j++){//letter outline
        //     plotPolygon(black, getcirclepoints({origin[0]+l[j][0],origin[1]+l[j][1]},fontthickness,{0,360},0.5) );
        //     glFlush();
        // }
        for(ll j=0;j<l.size();j++){//actual letter
            plotPolygon(color, getcirclepoints({origin[0]+l[j][0],origin[1]+l[j][1]},fontthickness-mysize/10,{0,360},0.5) );
            glFlush();
        }
        // glFlush();
    }
}


void ellipse(Array1D(ld) color,Array1D(ld) origin, ld a,ld b ,ld precision=0.8,ld thick=5,bool see=false){
    for(ld i=0;i<360;i+=precision){
        plotPoint(color,{
            {(origin[0]+a*cos(i deg)),(origin[1]+b*sin(i deg))}
        },thick,see);
    }
}
void circle(Array1D(ld) color,Array1D(ld) origin, ld r ,ld precision=0.8,ld thick=5,bool see=false){
    for(ld i=0;i<360;i+=precision){
        plotPoint(color,{
            {(origin[0]+r*cos(i deg)),(origin[1]+r*sin(i deg))}
        },thick,see);
    }
}
void sphere(Array1D(ld) color,Array1D(ld) origin,ld radius,int vlines=5,int hlines=5,ld precision =0.8,ld thickness=2.5,bool see=false){
    circle(color,origin,radius,precision,thickness,see);//circumfrence
    ld temp;
    //vertical lines
    if((vlines%2)!=0){//odd
        vlines=(vlines-1)/2;
        plotLine(color,{
                {origin[0]+0,origin[1]+radius},{origin[0]+0,origin[1]-radius}
            },thickness/2,see);//vertical line
        ld temp=radius/(vlines+1);
        for(int i=temp;i<radius;i+=temp){
            ellipse(color,origin,i,radius,precision,thickness,see);
        }
    }
    else{
        temp=(2*radius)/(vlines+1);
        for(ld i=temp/2;i<radius;i+=temp){
            ellipse(color,origin,i,radius,precision,thickness,see);
        }
    }
    //horizontal lines
    temp=(2*radius)/(hlines+1);
    ld sradius=radius*radius;
    for(ld y=temp-radius;y<radius;y+=temp){
        ld x=sqrt(sradius-(y*y));
        // Line(color,{  {origin[0]-x,origin[1]+y},{origin[0]+x,origin[1]+y}   },thickness/2,see);
        ellipse(color,{origin[0],origin[1]+y},x,temp/3,precision,thickness,see);
    }
}

// void getspherepoints(Array1D(ld) origin,ld radius,int vlines=5,int hlines=5,ld precision =0.8,ld thickness=2.5,bool see=false){
//     Array2D(ld) result;
//     // circle(color,origin,radius,precision,thickness,see);//circumfrence
//     for(ld i=0;i<360;i+=precision){result.push_back({(origin[0]+radius*cos(i deg)),(origin[1]+radius*sin(i deg))});}//circumfrence
//     ld temp;
//     //vertical lines
//     if((vlines%2)!=0){//odd
//         vlines=(vlines-1)/2;
//         plotLine(color,{{origin[0]+0,origin[1]+radius},{origin[0]+0,origin[1]-radius}},thickness/2,see);//vertical line
//         ld temp=radius/(vlines+1);
//         for(int i=temp;i<radius;i+=temp){
//             ellipse(color,origin,i,radius,precision,thickness,see);
//         }
//     }
//     else{
//         temp=(2*radius)/(vlines+1);
//         for(ld i=temp/2;i<radius;i+=temp){
//             ellipse(color,origin,i,radius,precision,thickness,see);
//         }
//     }
//     //horizontal lines
//     temp=(2*radius)/(hlines+1);
//     ld sradius=radius*radius;
//     for(ld y=temp-radius;y<radius;y+=temp){
//         ld x=sqrt(sradius-(y*y));
//         // Line(color,{  {origin[0]-x,origin[1]+y},{origin[0]+x,origin[1]+y}   },thickness/2,see);
//         ellipse(color,{origin[0],origin[1]+y},x,temp/3,precision,thickness,see);
//     }
// }

void displaysolarsystem(void){
    init(rgb(0, 3, 51));
    cout.precision(10);
    srand(time(0));
    ld earthorbit_a=400,earthorbit_b=50;
    ld moonorbit_a=100,moonorbit_b=20;
    ld sunradius=100,earthradius=50,moonradius=20;
    ld rotation_earth_wrt_sun=10;
    ld rate_of_rotation_moon_wrt_earth=3;
    ld earth_to_moon_angle=0;
    
        // Array2D(ld) starset1,starset2,starset3;
        // for(int i=0;i<intrand;i++){
        //     starset1.push_back({ldrand,ldrand}); starset2.push_back({ldrand,ldrand}); starset3.push_back({ldrand,ldrand});
        //     starset1.push_back({-ldrand,ldrand}); starset2.push_back({-ldrand,ldrand}); starset3.push_back({-ldrand,ldrand});
        //     starset1.push_back({-ldrand,-ldrand}); starset2.push_back({-ldrand,-ldrand}); starset3.push_back({-ldrand,-ldrand});
        //     starset1.push_back({ldrand,-ldrand}); starset2.push_back({ldrand,-ldrand}); starset3.push_back({ldrand,-ldrand});
            
        // }//stars
        
    for(ld rot=0;rot<360*rotation_earth_wrt_sun;rot+=1/rate_of_rotation_moon_wrt_earth){
        ld x=(earthorbit_a*cos(rot deg)),y=(earthorbit_b*sin(rot deg));
        ld sun_to_earth_angle=(int)rot%360;
        Array1D(ld) mooncolor=grey;
        Array1D(ld) earthcolor=green;
        Array1D(ld) suncolor=rgb(207, 182, 0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0;i<intrand;i++){plotPoint(white,{{ldrand,ldrand},{-ldrand,ldrand},{-ldrand,-ldrand},{ldrand,-ldrand}},2);}//stars
        ellipse(darkgray,{0,0},earthorbit_a,earthorbit_b,0.8,0.5);//sun orbit
        if(sun_to_earth_angle>0 && sun_to_earth_angle<=90){
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius/2})
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius/2})
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},customScaling(sun_to_earth_angle,{0,90},{earthradius,earthradius*(3.0/5)}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
            sphere(suncolor,{0,0},sunradius,16,16,0.8,2);//sun
        }
        else if(sun_to_earth_angle>90 && sun_to_earth_angle<=180){
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{90,180},{earthradius*(3.0/5),earthradius}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
            sphere(suncolor,{0,0},sunradius,16,16,0.8,2);//sun
        }
        else if(sun_to_earth_angle>180 && sun_to_earth_angle<=270){
            sphere(suncolor,{0,0},sunradius,16,16,0.8,1.5);//sun
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},customScaling(sun_to_earth_angle,{180,270},{earthradius,earthradius*(7.0/5)}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;

        }
        else if(sun_to_earth_angle>270 && sun_to_earth_angle<=360){
            sphere(suncolor,{0,0},sunradius,16,16,0.8,2);//sun
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{0,90},{moonradius,moonradius*(4.0/5)}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{90,180},{moonradius*(4.0/5),moonradius}),4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{180,270},{moonradius,moonradius*(6.0/5)}),4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},customScaling(sun_to_earth_angle,{270,360},{earthradius*(7.0/5),earthradius}));//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},customScaling(earth_to_moon_angle,{270,360},{moonradius*(6.0/5),moonradius}),4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
        }
        glFlush();
    }
}
void displaytext(void){
    init(silver);
    plotPolygon(grey,{{(ld)viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)-viewport_size[1]},{(ld)viewport_size[0],(ld)-viewport_size[1]}});
    ld textsize=20;
    // textRendering("LABENDSEM",{0,30},crimson,textsize);
    // textRendering("TEXTRENDERING",{0,20},black,textsize);
    // textRendering("PRESENTATIONBY",{0,10},yellow,textsize);
    // textRendering("ARINDAMSHARMA",{0,0},lightblue,textsize);
    // textRendering("TA",{0,-10},cyan,textsize);
    // textRendering("JOSHIPRATEEK",{0,-20},darkgreen,textsize);
    // textRendering("GUIDEDBY",{0,-30},cyan,textsize);
    // textRendering("PROFMASILAMANISIR",{0,-40},darkgreen,textsize);

    textRendering("GRAPHICS",{-2,5},lightblue,textsize);
    textRendering("ARINDAM",{-2,-5},lightblue,textsize);
    // textRendering("CED17I022",{-2,-15},lightblue,textsize);
    glFlush();
}
void display1(void){
    init(steelblue);
    plotPolygon(gainsboro,{{1.0,1.0},{1.0,-1.0},{-1.0,-1.0},{-1.0,1.0}});//background
    ld stepsize=1;
    ld precision=0.025;
    for(ld i=0;i<1;i+=precision){//Axis points
        plotPoint(black,{
            {i,0.0},
            {0.0,i},
            {-i,0.0},
            {0.0,-i}
        },3);
    }
    for(ld i=0;i<=1;i+=precision*stepsize){//Grid
        plotLine(blue,{
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
        plotPolygon(green,{
            {round(x/prec)*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),(round(y/prec)+1*(y/fabs(y)))*(prec)},
            {round(x/prec)*(prec),(round(y/prec)+1*(y/fabs(y)))*(prec)},            
        });
    }
    glFlush();
}
void display2(void){
    init(steelblue);
    plotPolygon(gainsboro,{{(ld)viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)-viewport_size[1]},{(ld)viewport_size[0],(ld)-viewport_size[1]},});
    //for stepsize 
    plotLine(black,{//axes
            // {viewport_size[0],0},{-viewport_size[0],0},
            // {0,viewport_size[0]},{0,-viewport_size[0]},

            // {viewport_size[0],0},{-0,0},
            // {0,viewport_size[0]},{0,-0},
            
            // {viewport_size[0],10},{-0,10},
            // {10,viewport_size[0]},{10,-0}
        },1.5);

    Array2D(ld) myfigure={{20,25},{-10,-30},{-50,70}};
    plotLineLoop(black,myfigure,10);
    
     
    if(check){ 
        // print1D({mx,my});
        // Array1D(ld) pixel=getPixelColor({mx,my});
        // Point(rgb((ld)pixel[0],(ld)pixel[1],(ld)pixel[2]),{{mx,my}},1);
        // BF4({mx,my},green,black,5);
        // floodfill({mx,my},getPixelColor({mx,my}),green,5);
        fillcolor_BF8({mx,my},green,black,5);
    }
    glFlush();  // flushes the frame buffer to the screen
}
void display3(void){
    init(steelblue);
    // plotPolygon(lightpink,{{(ld)viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)-viewport_size[1]},{(ld)viewport_size[0],(ld)-viewport_size[1]},});
    plotPolygon(gainsboro,{{(ld)viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)viewport_size[1]},{(ld)-viewport_size[0],(ld)-viewport_size[1]},{(ld)viewport_size[0],(ld)-viewport_size[1]},});
    
    Array2D(ld) myfigure={{20,25},{-10,-30},{-50,70}};
    plotLineLoop(black,myfigure,5);
    glFlush();
    // if(check){ 
    for(ld j=-viewport_size[0];j<=viewport_size[0];j+=.525){
        for(ld i=-viewport_size[0];i<=viewport_size[0];i+=.525){
            // Point(red,{{mx,my}});
            // Array1D(ld) pixel=getPixelColor({i,j},true);
            Array1D(ld) pixel=getPixelColor({i,j});
            // print1D({(ld)pixel[0],(ld)pixel[1],(ld)pixel[2]});
            // print1D({i,j});
            plotPoint(rgb((ld)pixel[0],(ld)pixel[1],(ld)pixel[2]),{{i,j}},2);
            // Point(green,{{i,j}},3);
        }
        glFlush();
    }

    glFlush();
}
void display4(void){
    init(steelblue);
    plotPolygon(forestgreen,{
        {(ld)viewport_size[0],(ld)viewport_size[1]},
        {(ld)-viewport_size[0],(ld)viewport_size[1]},
        {(ld)-viewport_size[0],(ld)-viewport_size[1]},
        {(ld)viewport_size[0],(ld)-viewport_size[1]},
    });
    Array2D(ld) myfigure={
        {20,25},
        {-50,70},
        {-10,-30},
        // {78,-58},
        };
    plotLineLoop(darkgoldenrod,myfigure,5,true);
    plotLineLoop(darkgreen,translate(myfigure,{10,20}),5,true);
    plotLineLoop(darkblue,scale(myfigure,2));
    plotLineLoop(pink,rotate(myfigure,40,true));
    plotLineLoop(magenta,rotate(myfigure,-40));
    
    glFlush();  // flushes the frame buffer to the screen
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(window_size[1],/*width*/window_size[0]/*height*/);
    // glutInitWindowPosition(100, 100);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_size[1])/2,(glutGet(GLUT_SCREEN_HEIGHT)-window_size[0])/2);
    glutCreateWindow("Experimental Tab1");
    gluOrtho2D(-window_size[1]/2,window_size[1]/2,-window_size[0]/2,window_size[0]/2);//origin center
    glutDisplayFunc(displaytext);
    glutReshapeFunc(reshape_callback);
    // glutMouseFunc(mouse_callback);
    glutMainLoop();
    return 0;
}