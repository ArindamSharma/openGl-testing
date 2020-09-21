#include<iostream>
#include<math.h>
#include<vector>
#include<GL/glut.h>
#include<omp.h>

#define ld long double
#define ll long long
#define Array1D_i vector<int>
#define Array1D_ld vector<ld>
#define Array2D_ld vector<Array1D_ld>
#define Array3D_ld vector<Array2D_ld>

#define PI 3.14159265
#define deg *0.0174532925//(PI/180=0.0174532925)
#include"colors.h"
#define PPI 100//all 2 digit values
using namespace std;

//{height,width}
int window_size[]={700,700};
int viewport_size[]={650,650};

Array1D_ld rgb(int r, int g, int b){
    Array1D_ld f;
    f.push_back((double)r/255.0);
    f.push_back((double)g/255.0);
    f.push_back((double)b/255.0);
    return f;
}

void init(Array1D_ld color ,ld alpha=1.0){
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

void print3D(Array3D_ld a){
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
void print2D(Array2D_ld a){
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
void print1D(Array1D_ld a){
    cout<<"[";
    for( ll i = 0; i < a.size(); i++ ){
        cout<<a[i]<<",";
    }
    cout<<"\b]"<<endl;
}

void Point(Array1D_ld color,Array2D_ld array,ld point_size=5,bool see_points=false){
    glPointSize(point_size);
    glBegin(GL_POINTS);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0]/PPI,array[i][1]/PPI);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(array);}
}
void Line(Array1D_ld color,Array2D_ld array,ld line_width=5,bool see_points=false){
    glLineWidth(line_width);
    glBegin(GL_LINES);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0]/PPI,array[i][1]/PPI);
            // glVertex2fv((GLfloat *)&array[i]);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(array);}
}
void Polygon(Array1D_ld color,Array2D_ld array,bool see_points=false){
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0]/PPI,array[i][1]/PPI);
        }
    glEnd();
    // glFlush();
    if(see_points){print2D(array);}
}

class Figure{
private:
    /* data */
public:
    void Point(Array1D_ld color,Array2D_ld array,ld point_size=5,bool see_points=false){
        glPointSize(point_size);
        glBegin(GL_POINTS);//rect outline
            glColor3f(color[0],color[1], color[2]);//color of outline of rect
            for ( int i = 0; i < array.size(); i++ ){
                glVertex2f(array[i][0],array[i][1]);
            }
        glEnd();
        // glFlush();
        if(see_points){
            print2D(array);
        }
    }
    void Line(Array1D_ld color,Array2D_ld array,ld line_width=5,bool see_points=false){
        glLineWidth(line_width);
        glBegin(GL_LINES);//rect outline
            glColor3f(color[0],color[1], color[2]);//color of outline of rect
            for ( int i = 0; i < array.size(); i++ ){
                glVertex2f(array[i][0],array[i][1]);
                // glVertex2fv((GLfloat *)&array[i]);
            }
        glEnd();
        // glFlush();
        if(see_points){
            print2D(array);
        }
    }
    void Polygon(Array1D_ld color,Array2D_ld array,bool see_points=false){
        glBegin(GL_POLYGON);//rect outline
            glColor3f(color[0],color[1], color[2]);//color of outline of rect
            for ( int i = 0; i < array.size(); i++ ){
                glVertex2f(array[i][0],array[i][1]);
            }
        glEnd();
        // glFlush();
        if(see_points){
            print2D(array);
        }
    }
};

class LinearEquation{
private:
    /* data */
public:
    ld m,c;
    LinearEquation(Array1D_ld p1,Array1D_ld p2){
        m=(p2[1]-p1[1])/(p2[0]-p1[0]);
        c=p1[1]-(m*p1[0]);
    }
    LinearEquation(ld a,ld b,ld c){
        // ax+by+c=0
        m=-(a/b);
        c=-(c/b);
    }
    LinearEquation(Array1D_ld p,ld slope){
        // ax+by+c=0
        m=slope;
        c=p[1]-(m*p[0]);
    }
    ld y_value(ld x){return m*x+c;}
    ld x_value(ld y){return (y-c)/m;}
    ld Func(ld x,ld y){return (m*x)+c-y;}
};
class Vertex{
private:
    /* data */
public:
    ld x,y;
    Vertex(ld a,ld b){x=a;y=b;}
    Array1D_ld mapped(){return {x/10,y/10};}
};

void Plot_line(Array1D_ld p1,Array1D_ld p2,Array1D_ld color,ld stepsize,ld precision){
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
        Polygon(color,{
            {round(x/prec)*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
            {round(x/prec)*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
        });
    }
}

Figure A;
void Plot_line(Vertex p1,Vertex p2,Array1D_ld color,ld stepsize,ld precision){
    int c=0;
    LinearEquation myeq(p1.mapped(),p2.mapped());
    ld prec=(stepsize*precision);
    if(p1.x==p2.x){
        swap(p1.x,p1.y);
        swap(p2.x,p2.y);
        c++;
    }
    for(ld i=(p1.x/10);i<(p2.x/10);i+=precision){
        ld x=i,y=myeq.y_value(i);
        if(c>0){swap(x,y);}
        A.Polygon(color,{
            {round(x/prec)*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),round(y/prec)*(prec)},
            {(round(x/prec)+1*(x/fabs(x)))*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
            {round(x/prec)*(prec),(round(y/prec)+1*(x/fabs(x)))*(prec)},
        });
        // A.Point(black,{{x,y}},5,true);
    }
}
class image{
private:    
    ld screen_height;
    ld screen_width;
    ll row_length;
    ll column_length;
    
    Array2D_ld quad(Array1D_ld center,ld size){
        Array2D_ld f;
        f.push_back({(center[0]+(size/2)),(center[1]+(size/2))});
        f.push_back({(center[0]+(size/2)),(center[1]-(size/2))});
        f.push_back({(center[0]-(size/2)),(center[1]-(size/2))});
        f.push_back({(center[0]-(size/2)),(center[1]+(size/2))});
        return f;
    }
public:
    void init(ld height,ld width,ll row,ll col){
        screen_height=height;
        screen_width=width;
        row_length=row;
        column_length=col;
    }
    Array2D_ld quad_points(ll ai,ll aj,ld ppi=PPI){
        ld h=(-screen_width/2)+(aj*screen_width/column_length);
        ld w=(screen_height/2)-(ai*screen_height/row_length);
        h=h/(screen_width/2);
        w=w/(screen_height/2);
        return quad({h,w},ppi);
    }
};
void plot_single_pixel(Array1D_ld color,ld x,ld y,ld stepsize,bool see_points=false){
    ld half=(stepsize/2);
    Polygon(color,{
            {x-half,y-half},
            {x-half,y+half},
            {x+half,y+half},
            {x+half,y-half}
        });
    if(see_points){print1D(  {(ld)x,(ld)y} );}
}
void DDA(Array1D_ld color,Array1D_ld p1,Array1D_ld p2,ld stepsize,bool see_points=false){
    LinearEquation eq(p1,p2);
    // cout<<eq.m<<endl;
    // ld half=(stepsize/2);
    int x=round(p1[0]),y=round(p1[1]);
    ld xf=p1[0],yf=p1[1];
    
    plot_single_pixel(color,x,y,stepsize,see_points);
    if(fabs(eq.m)<=1){
        while(x<p2[0]){
            x=x+stepsize;//stepsize should be 1
            yf=y+eq.m*stepsize;//stepsize should be 1
            y=round(yf);
            plot_single_pixel(color,x,y,stepsize,see_points);
        }
    }
    else{
        while(y<p2[1]){
            y=y+stepsize;//stepsize should be 1
            xf=x+(1.0/eq.m)*stepsize;//stepsize should be 1
            x=round(xf);
            plot_single_pixel(color,x,y,stepsize,see_points);
        }
    }
}
void MLD(Array1D_ld color,Array1D_ld p1,Array1D_ld p2,ld stepsize,bool see_points=false){
    // only for first octate
    ld x=p1[0],y=p1[1];
    ld dy=p2[1]-p1[1],dx=p2[0]-p1[0];
    ld d=2*dy-dx;
    ld dE=(2*dy)*stepsize;
    ld dNE=2*(dy-dx)*stepsize;
    // plot
    plot_single_pixel(color,x,y,stepsize,see_points);
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
        plot_single_pixel(color,x,y,stepsize,see_points);
    }
}
void MLD_modified(Array1D_ld color,Array1D_ld p1,Array1D_ld p2,ld stepsize,Array1D_ld toggler,bool see_points=false){
    ld x=p1[0],y=p1[1];
    ld dy=p2[1]-p1[1],dx=p2[0]-p1[0];
    ld d=2*dy-dx;
    ld dE=(2*dy)*stepsize;
    ld dNE=2*(dy-dx)*stepsize;
    // plot
    plot_single_pixel(color,(toggler[0]*x+toggler[1]*y),(toggler[2]*x+toggler[3]*y),stepsize,see_points);
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
        plot_single_pixel(color,(toggler[0]*x+toggler[1]*y),(toggler[2]*x+toggler[3]*y),stepsize,see_points);
    }
}
void MLD_all(Array1D_ld color,Array1D_ld p1,Array1D_ld p2,ld stepsize,bool see_points=false){
    ld m=(p2[1]-p1[1])/(p2[0]-p1[0]);
    if(m<=1 && m>=0 && p1[0]<p2[0]){
        MLD_modified(color,p1,p2,stepsize,{1,0,0,1},see_points); // plot x,y
    }//octate 1
    else if(m>1 && p1[1]<p2[1]){
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        MLD_modified(color,p1,p2,stepsize,{0,1,1,0},see_points); // plot y,x
    }//octate 2
    else if(m<-1 && p1[1]<p2[1]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        MLD_modified(color,p1,p2,stepsize,{0,-1,1,0},see_points);// plot -y,x
    }//octate 3
    else if(m<=0 && m>=-1 && p2[0]<p1[0]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        MLD_modified(color,p1,p2,stepsize,{-1,0,0,1},see_points);// plot -x,y
    }//octate 4
    else if(m<=1 && m>0 && p2[0]<p1[0]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        p1[1]=-p1[1];p2[1]=-p2[1];
        MLD_modified(color,p1,p2,stepsize,{-1,0,0,-1},see_points);// plot -x,-y
    }//octate 5
    else if(m>1 && p2[1]<p1[1]){
        p1[0]=-p1[0];p2[0]=-p2[0];
        p1[1]=-p1[1];p2[1]=-p2[1];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        MLD_modified(color,p1,p2,stepsize,{0,-1,-1,0},see_points);// plot -y,-x
    }//octate 6
    else if(m<-1 && p2[1]<p1[1]){
        p1[1]=-p1[1];p2[1]=-p2[1];
        swap(p1[0],p1[1]);swap(p2[0],p2[1]);
        MLD_modified(color,p1,p2,stepsize,{0,1,-1,0},see_points);// plot y,-x
    }//octate 7
    else if(m<0 && m>=-1 && p1[0]<p2[0]){
        p1[1]=-p1[1];p2[1]=-p2[1];
        MLD_modified(color,p1,p2,stepsize,{1,0,0,-1},see_points);// plot x,-y
    }//octate 8
}
void display1(void){
    init(steelblue);
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