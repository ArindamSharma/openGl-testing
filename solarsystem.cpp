#include<iostream>
#include<math.h>//sin,cos,sqrt
#include<unistd.h>//sleep
#include<vector>//vector
#include<GL/glut.h>
#include"../colors.h"//custom colors for rgb function

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

int window_size[]={768,1024};//{height,width}
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
void init(Array1D(ld) color ,ld alpha=1.0){
    glClearColor(color[0], color[1], color[2], 1); //Window Background Colour
    // glClearColor(0.5, 0.5, 0.5,1); //Window Background Colour
    glClear(GL_COLOR_BUFFER_BIT);  
    glFlush();
}
void reshape_callback(int w, int h){
    // int my_w=glutGet(GLUT_WINDOW_WIDTH),my_h=glutGet(GLUT_WINDOW_HEIGHT);
    // window_size[0]=my_h;
    // window_size[1]=my_w;
    // glViewport(
    //     ((my_w-viewport_size[1])/2),//width
    //     ((my_h-viewport_size[0])/2),//height
    //     viewport_size[1],//width
    //     viewport_size[0]//height
    // );
    glViewport(
        ((glutGet(GLUT_WINDOW_WIDTH)-viewport_size[1])/2),//width
        ((glutGet(GLUT_WINDOW_HEIGHT)-viewport_size[0])/2),//height
        viewport_size[1],//width
        viewport_size[0]//height
    );
    glutPostRedisplay();
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
void Point(Array1D(ld) color,Array2D(ld) array,ld point_size=5,bool see_points=false){
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
void Line(Array1D(ld) color,Array2D(ld) array,ld line_width=5,bool see_points=false){
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
void LineLoop(Array1D(ld) color,Array2D(ld) array,ld line_width=5,bool see_points=false){
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
void Polygon(Array1D(ld) color,Array2D(ld) array,bool see_points=false){
    // glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0],array[i][1]);
        }
    glEnd(); // glFlush();
    if(see_points){print2D(array);}
}
void ellipse(Array1D(ld) color,Array1D(ld) origin, ld a,ld b ,ld precision=0.8,ld thick=5,bool see=false){
    for(ld i=0;i<360;i+=precision){
        Point(color,{
            {(origin[0]+a*cos(i deg)),(origin[1]+b*sin(i deg))}
        },thick,see);
    }
}
void circle(Array1D(ld) color,Array1D(ld) origin, ld r ,ld precision=0.8,ld thick=5,bool see=false){
    for(ld i=0;i<360;i+=precision){
        Point(color,{
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
        Line(color,{
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
void display1(void){
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
        for(int i=0;i<intrand;i++){Point(white,{{ldrand,ldrand},{-ldrand,ldrand},{-ldrand,-ldrand},{ldrand,-ldrand}},2);}//stars
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
void display3(void){
    init(rgb(13, 23, 71));
    cout.precision(10);
    srand(time(0));
    ld earthorbit_a=500,earthorbit_b=50;
    ld moonorbit_a=100,moonorbit_b=20;
    ld sunradius=150,earthradius=50,moonradius=20;
    ld rotation_earth_wrt_sun=1;
    ld rate_of_rotation_moon_wrt_earth=4;
    ld earth_to_moon_angle=0;
    for(ld rot=0;rot<360*rotation_earth_wrt_sun;rot+=1/rate_of_rotation_moon_wrt_earth){
        ld x=(earthorbit_a*cos(rot deg)),y=(earthorbit_b*sin(rot deg));
        ld sun_to_earth_angle=(int)rot%360;
        Array1D(ld) mooncolor=grey;
        Array1D(ld) earthcolor=green;
        Array1D(ld) suncolor=rgb(207, 182, 0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0;i<intrand;i++){Point(white,{{ldrand,ldrand},{-ldrand,ldrand},{-ldrand,-ldrand},{ldrand,-ldrand}},2);}//stars
        ellipse(darkgray,{0,0},earthorbit_a,earthorbit_b,0.8,3);//sun orbit
        if(sun_to_earth_angle>0 && sun_to_earth_angle<=90){
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{0,90},{100.0,50.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
            sphere(suncolor,{0,0},sunradius,16,16,0.8,1.5);//sun
        }
        else if(sun_to_earth_angle>90 && sun_to_earth_angle<=180){
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{90,180},{50.0,100.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
            sphere(suncolor,{0,0},sunradius,16,16,0.8,1.5);//sun
        }
        else if(sun_to_earth_angle>180 && sun_to_earth_angle<=270){
            sphere(suncolor,{0,0},sunradius,16,16,0.8,1.5);//sun
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{180,270},{100.0,200.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;

        }
        else if(sun_to_earth_angle>270 && sun_to_earth_angle<=360){
            sphere(suncolor,{0,0},sunradius,16,16,0.8,1.5);//sun
            if(earth_to_moon_angle>0 && earth_to_moon_angle<=90){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{0,90},{100.0,50.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>90 && earth_to_moon_angle<=180){
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{90,180},{50.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},earthradius);//earth
            }
            else if(earth_to_moon_angle>180 && earth_to_moon_angle<=270){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{180,270},{100.0,200.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            else if(earth_to_moon_angle>270 && earth_to_moon_angle<=360){
                sphere(rgb_brightness(earthcolor,customScaling(sun_to_earth_angle,{270,360},{200.0,100.0})),{x,y},earthradius);//earth
                sphere(rgb_brightness(mooncolor,customScaling(earth_to_moon_angle,{270,360},{200.0,100.0})),{(x+moonorbit_a*cos(earth_to_moon_angle deg)),(y+moonorbit_b*sin(earth_to_moon_angle deg))},moonradius,4,4,0.8,1.5);//moon
            }
            earth_to_moon_angle+=rate_of_rotation_moon_wrt_earth;
            earth_to_moon_angle=(int)earth_to_moon_angle%360;
        }
        glFlush();
    }
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_size[1]/*width*/,window_size[0]/*height*/);
    
    // glutInitWindowPosition(100, 100);
    // glutInitWindowPosition(5, 5);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_size[1])/2,(glutGet(GLUT_SCREEN_HEIGHT)-window_size[0])/2);
    glutCreateWindow("Solar System");
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    gluOrtho2D(-window_size[1]/2,window_size[1]/2,-window_size[0]/2,window_size[0]/2);//origin center
    
    glutDisplayFunc(display1);
    glutReshapeFunc(reshape_callback);
    glutMainLoop();
    return 0;
}