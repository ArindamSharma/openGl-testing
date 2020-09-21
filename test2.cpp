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
#define deg *(PI/180)

#define PPI 0.01
#define myheight 512
#define mywidth 512
using namespace std;

Array1D_ld rgb(int r, int g, int b){
    Array1D_ld f;
    f.push_back((double)r/255.0);
    f.push_back((double)g/255.0);
    f.push_back((double)b/255.0);
    return f;
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

void poly_with_outline(Array1D_ld color,Array2D_ld array,bool see_points=false){
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        for ( int i = 0; i < array.size(); i++ ){
            glVertex2f(array[i][0],array[i][1]);
        }
    glEnd();
    glFlush();
    if(see_points){
        print2D(array);
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

void displayHome(void){
    glClearColor(0.5, 0.5, 0.5,0.5); //Background Colour
    glClear(GL_COLOR_BUFFER_BIT);
    image a;
    a.init(myheight, mywidth,myheight, mywidth);
    // print2D(a.quad_points(256,256,0.1));
    Array3D_ld img={ 
        {{2,3,4},{34,5,6},{4,6,6}},
        {{4,4,3},{12,3,34},{45,34,5}},
        {{5,5,4},{2,3,5},{6,3434,34}}  
    },img2;
    // print3D(img);
    ld t1=omp_get_wtime();
    // poly_with_outline(rgb(123,35,145),a.quad_points(196,181,0.1),true);
    ll f=0;
    ll i=0,j=0,c=0;
    ll mc[3];
    FILE *A;
    A=fopen("sample.tiff","rb");
    // A=fopen("lena_color.tiff","rb");
    // A=fopen("lena_color1.tiff","rb");
    while (!feof(A)){
        // int tmp_color=fgetc(A);
        mc[c]=fgetc(A);
        // cout<<tmp_color<<" ";
        if(c==2){
            poly_with_outline(rgb(mc[2],mc[1],mc[0]),a.quad_points(i,j));
            // printf("[%lld,%lld,%lld]\n",mc[0],mc[1],mc[2]);
            j++;
            c=0;
        }
        else{c++;}
        if(j==mywidth){
            j=0;
            i++;
        }
        f++;
    }
    // cout<<f<<endl;
    fclose(A);
    ld t2=omp_get_wtime()-t1;
    cout<<"time :- "<<t2<<" sec"<<endl;
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(mywidth, myheight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Experimental Tab");
    glutDisplayFunc(displayHome);
    glutMainLoop();
    return 0;
}