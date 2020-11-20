#include<iostream>
#include<math.h>//sin,cos,sqrt
#include<unistd.h>//sleep
#include<vector>//vector
#include<string>
#include<GL/glut.h>
#include"colors.h"//custom colors for rgb function
using namespace std;

#define ld long double
#define ll long long
#define Array1D(x) vector<x>
#define Array2D(x) vector<Array1D(x)>
#define Array3D(x) vector<Array2D(x)>

#define PI 3.14159265
#define deg *0.0174532925//(PI/180=0.0174532925)
#define prec 1000
#define ldrand (ld)(rand()%prec)+(1.0/(ld)(rand()%prec))
#define intrand (rand()%prec)
using namespace std;

int window_size[]={864,1152};//{height,width}
int viewport_size[]={768,1024};//{height,width}

template <typename T>
T customScaling(T x,Array1D(ld) inputRange,Array1D(ld) outputRange){
    ld tmp1=-inputRange[0];// inputRange[0]+=tmp1;
    inputRange[1]+=tmp1;
    ld tmp2=-outputRange[0];// outputRange[0]+=tmp2;
    outputRange[1]+=tmp2;
    x+=tmp1;
    x=x/(inputRange[1]);
    x*=outputRange[1];
    x-=tmp2;
    return x;
    // return ((x/(inputRange[1]-inputRange[0]))*(outputRange[1]-outputRange[0]))+outputRange[0];
}
Array1D(ld) rgb(int r, int g, int b){
    Array1D(ld) f;
    f.push_back((double)r/255.0);
    f.push_back((double)g/255.0);
    f.push_back((double)b/255.0);
    return f;
}
Array1D(ld) rgb_invert(Array1D(ld) color){
    Array1D(ld) f=color;
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
    glutPostRedisplay();
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
void plotPoint(Array1D(ld) color,Array2D(ld) array,ld point_size=5,bool see_points=false){
    // glClear(GL_COLOR_BUFFER_BIT); 
    glPointSize(point_size);
    glBegin(GL_POINTS);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0],array[i][1]);
        }
    glEnd(); // glFlush();
    if(see_points){print2D(array);}
}
void plotLine(Array1D(ld) color,Array2D(ld) array,ld line_width=5,bool see_points=false){
    glLineWidth(line_width);
    // glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_LINES);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0],array[i][1]);
            // glVertex2fv((GLfloat *)&array[i]);
        }
    glEnd(); // glFlush();
    if(see_points){print2D(array);}
}
void plotLineLoop(Array1D(ld) color,Array2D(ld) array,ld line_width=5,bool see_points=false){
    glLineWidth(line_width);
    // glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_LINE_LOOP);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0],array[i][1]);
            // glVertex2fv((GLfloat *)&array[i]);
        }
    glEnd(); // glFlush();
    if(see_points){print2D(array);}
}
void plotPolygon(Array1D(ld) color,Array2D(ld) array,bool see_points=false){
    // glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0],array[i][1]);
        }
    glEnd(); // glFlush();
    if(see_points){print2D(array);}
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
void plotellipse(Array1D(ld) color,Array1D(ld) origin, ld a,ld b ,ld precision=0.8,ld thick=5,bool see=false){
    for(ld i=0;i<360;i+=precision){
        plotPoint(color,{
            {(origin[0]+a*cos(i deg)),(origin[1]+b*sin(i deg))}
        },thick,see);
    }
}
void plotcircle(Array1D(ld) color,Array1D(ld) origin, ld r ,ld precision=0.8,ld thick=5,bool see=false){
    for(ld i=0;i<360;i+=precision){
        plotPoint(color,{
            {(origin[0]+r*cos(i deg)),(origin[1]+r*sin(i deg))}
        },thick,see);
    }
}
Array2D(ld) getcirclepoints(Array1D(ld) origin,ld r,Array1D(ld) angles,ld precision=0.1){
    Array2D(ld) circlepoints;
    for(ld i=angles[0];i<angles[1];i+=precision){
        circlepoints.push_back({(origin[0]+r*cos(i deg)),(origin[1]+r*sin(i deg))});
    }
    return circlepoints;
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
        for(ld i=22.5;i<90;i+=precision*75){letter.push_back({(0.5+2*cos(i deg)),(2+2*sin(i deg))});}//semicircle upper right
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
        Array1D(ld) origin={location[0]+strsize,location[1]*mysize};
        for(ll j=0;j<l.size();j++){//letter outline
            plotPolygon(black, getcirclepoints({origin[0]+l[j][0],origin[1]+l[j][1]},fontthickness,{0,360},0.5) );
            // glFlush();
        }
        for(ll j=0;j<l.size();j++){//actual letter
            plotPolygon(color, getcirclepoints({origin[0]+l[j][0],origin[1]+l[j][1]},fontthickness-mysize/10,{0,360},0.5) );
            // glFlush();
        }
        glFlush();
    }
}
void display1(void){
    init(silver);
    plotPolygon(forestgreen,{
        {(ld)viewport_size[0],(ld)viewport_size[1]},
        {(ld)-viewport_size[0],(ld)viewport_size[1]},
        {(ld)-viewport_size[0],(ld)-viewport_size[1]},
        {(ld)viewport_size[0],(ld)-viewport_size[1]},
    });
    ld textsize=4;
    textRendering("LABENDSEM",{0,30},crimson,textsize);
    textRendering("TEXTRENDERING",{0,20},black,textsize);
    textRendering("PRESENTATIONBY",{0,10},yellow,textsize);
    textRendering("ARINDAMSHARMA",{0,0},lightblue,textsize);
    textRendering("TA",{0,-10},cyan,textsize);
    textRendering("JOSHIPRATEEK",{0,-20},darkgreen,textsize);
    textRendering("GUIDEDBY",{0,-30},cyan,textsize);
    textRendering("PROFMASILAMANISIR",{0,-40},darkgreen,textsize);
    glFlush();
}
int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_size[1]/*width*/,window_size[0]/*height*/);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_size[1])/2,(glutGet(GLUT_SCREEN_HEIGHT)-window_size[0])/2);
    glutCreateWindow("Lab End Sem Exam 19-11-2020 Text-Rendering");
    gluOrtho2D(-window_size[1]/2,window_size[1]/2,-window_size[0]/2,window_size[0]/2);//origin center
    
    glutDisplayFunc(display1);
    glutReshapeFunc(reshape_callback);
    glutMainLoop();
    return 0;
}