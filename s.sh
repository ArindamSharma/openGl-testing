export DISPLAY=localhost:0
if [ $1 ];then
    if g++ $1.cpp -lglut -lGL -lGLU -fopenmp -o $1.out; then    
        echo "File :- $1.cpp"
        ./$1.out
        rm $1.out
    fi
else
    echo "Please run again with the name of file after ./$0 ( CLA without extention )"
    echo "example:-  ./$0 <filename>"
    exit 1
fi