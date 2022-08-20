/*
References:

https://inversepalindrome.com/blog/how-to-create-a-random-string-in-cpp

*/

#include<iostream>
#include <random>
#include<unistd.h>
#include<cstring>
using namespace std;


void generating_s_l_n_c(int,char* [],int *,int *,int *,int *);
int random_number_generator_streets(int *);
int random_number_generator_linesegments(int *n);
int random_wait_time_generator(int *l);
string random_string(std::size_t length);



bool check_valid(vector<pair<int,int>>);
bool intersects(pair<int,int>,pair<int,int>,pair<int,int>,pair<int,int>);
bool same_points(pair<int,int> p1,pair<int,int> p2);
int get_orientation(
    std::pair<int, int> p,
    std::pair<int, int> q,
    std::pair<int, int> r);
bool self_intersecting_segments(
    std::pair<int,int> p1,
    std::pair<int,int> p2,
    std::pair<int,int> q1,
    std::pair<int,int> q2);
bool onSegment(pair<int,int> p, pair<int,int> q, pair<int,int> r);

//int get_orientation(pair<int,int>,pair<int,int>,pair<int,int>);

int attempt = 0;
int main(int argc,char *argv[])
{
    vector <string> street_name;
    vector<pair<int,int>> coordinates;
    vector<vector<pair<int,int>>> stpoints;
     string street;
    //int attempt = 0;
    int line_segments;
    int s,l,n,c,number_of_streets,wait_time;

    generating_s_l_n_c(argc,argv,&s,&l,&n,&c);
    while(!cin.eof())
    {
        pair<int,int> x_y;
        number_of_streets=random_number_generator_streets(&s);
        street_name.clear();
        wait_time=random_wait_time_generator(&l);

        for(int i=0;i<number_of_streets;i++)
            {

                attempt = 0;
                string str,str1,str_final;
                str=random_string(27);
                str1="\"Street ";
                str_final=str1+str+"\"";
                street_name.push_back(str_final);
                line_segments=random_number_generator_linesegments(&n);

                    //coordinates.clear();
                //do{
                    coordinates.clear();
                    vector<pair<int,int>> temp;
                    for(int j=0;j<=line_segments;)
                    {
                        if (attempt >25 )
                        {

                            cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                            exit(0);
                        }
                            std::uniform_int_distribution<int> d(-c, c);

                            std::random_device rd1; // uses RDRND or /dev/urandom
                            //int x[2]={};
                            //int y[2]={};
                            //for (int k=0;k<2;k++)
                            //{

                                int x=d(rd1);
                                int y=d(rd1);
                                x_y.first=x;
                                x_y.second=y;
                                //coordinates.push_back(x_y);
                                temp.push_back(x_y);
                                if (check_valid(temp))
                                {
                                    coordinates.push_back(x_y);
                                    j++;
                                }
                                else
                                {
                                    temp.pop_back();
                                    continue;
                                }
                            //}

                    }
                    temp.clear();
                    //attempt++;


                //}while (not check_valid(coordinates));






            stpoints.push_back(coordinates);

    }

    street="";
    for(int i=0;i<number_of_streets;i++)
    {
        street=street+"add "+street_name[i]+" ";
        for(auto &p: stpoints[i])
        {

            street=street+ "("+to_string(p.first)+","+to_string(p.second)+") ";

        }
        street=street+"\n";
    }
        street=street+"gg";
        cout<<street<<endl;

    sleep(wait_time);
    //sleep(1);

    street="";
    for(int i=0;i<number_of_streets;i++)
    {

        street=street+"rm "+street_name[i];
        street=street+"\n";


    }
    cout<<street;
    stpoints.clear();

}

    return 0;
}

bool same_points(
    std::pair<int,int> p1,
    std::pair<int,int> p2){
    int x1 = p1.first;
    int y1 = p1.second;
    int x2 = p2.first;
    int y2 = p2.second;

    return (x1 == x2) && (y1 == y2);
}


int get_orientation(
    std::pair<int, int> p,
    std::pair<int, int> q,
    std::pair<int, int> r){

    //Calculating determinant of vectors PQ and QR
    float det = (float)((q.first - p.first)*(r.second - q.second) -
          (r.first - q.first)*(q.second - p.second));
    if (det < 0){
        return 1;
    }else if (det > 0){
        return 2;
    }else{
        return 0;
    }
}
bool self_intersecting_segments(
    std::pair<int,int> p1,
    std::pair<int,int> p2,
    std::pair<int,int> q1,
    std::pair<int,int> q2){

    int o1 = get_orientation(p1, p2, q1);
    int o2 = get_orientation(p1, p2, q2);
    int o3 = get_orientation(q1, q2, p1);
    int o4 = get_orientation(q1, q2, p2);

    if ((o1 != o2) && (o3 != o4))
    {
        return true;
    }
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
        if (o1 == 0 && onSegment(p1, p2, q1))
    {

        return true;
    }

        // p1, q1 and q2 are colinear and q2 lies on segment p1q1
        if (o2 == 0 && onSegment(p1, q2, q1))
    {
         return true;
    }
        // p2, q2 and p1 are colinear and p1 lies on segment p2q2
        if (o3 == 0 && onSegment(p2, p1, q2))
    {
        return true;
    }
        // p2, q2 and q1 are colinear and q1 lies on segment p2q2
        if (o4 == 0 && onSegment(p2, q1, q2))
    {
        return true;
    }


    else{
        return false;
    }
}

bool onSegment(pair<int,int> p, pair<int,int> q, pair<int,int> r)
{
        if (q.first<= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
                q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))

    {
        return true;
    }

        return false;
}
bool check_valid(vector<pair<int,int>> coordinates)
{
    int number_of_coordinates = coordinates.size();
    for (int p1=0; p1 < number_of_coordinates; p1++){
        for (int p2=p1+1; p2 <number_of_coordinates; p2++){
            //same coordinates
            if (same_points(coordinates[p1],  coordinates[p2])){
                    attempt++;
                                        return false;
            }
            //overlapping segments
            if(p1+2 < number_of_coordinates && p2+2 < number_of_coordinates){
                if (self_intersecting_segments(coordinates[p1],  coordinates[p1+1],
                                               coordinates[p2+1],  coordinates[p2+2])){
                    attempt++;
                                        return false;
                }
            }
        }
    }
    return true;
}





void generating_s_l_n_c(int argc,char* arguement_array[],int *s,int* l, int *n,int *c)
{

    int count_s=0,count_l=0,count_n=0,count_c=0;

    for(int i=1;i<argc;i+=2)
    {

        if(strcmp(arguement_array[i],"-s")==0)
        {
            *s=atoi(arguement_array[i+1]);

            count_s=1;
        }
        if(strcmp(arguement_array[i],"-l")==0)
        {
            *l=atoi(arguement_array[i+1]);

            count_l=1;
        }
        if(strcmp(arguement_array[i],"-n")==0)
        {
            *n=atoi(arguement_array[i+1]);




            count_n=1;
        }
        if(strcmp(arguement_array[i],"-c")==0)
        {
            *c=atoi(arguement_array[i+1]);





            count_c=1;
        }
    }
    if (count_s==0)
    {
        *s=10;
    }
    if (count_l==0)
    {
        *l=5;
    }
    if (count_n==0)
    {
        *n=5;
    }
    if(count_c==0)
    {
        *c=20;
    }

}

string random_string(std::size_t length)
{
    const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

int random_number_generator_streets(int *s)
{
     std::uniform_int_distribution<int> d(2, *s);

    std::random_device rd1; // uses RDRND or /dev/urandom
    int number_of_streets_generator=d(rd1);
    return number_of_streets_generator;

}
int random_number_generator_linesegments(int *n)
{
     std::uniform_int_distribution<int> d(1, *n);

    std::random_device rd1; // uses RDRND or /dev/urandom
    int number_of_linesegments_generator=d(rd1);
    return number_of_linesegments_generator;

}

int random_wait_time_generator(int *l)
{
    std::uniform_int_distribution<int> d(5, *l);

    std::random_device rd1; // uses RDRND or /dev/urandom
    int wait_time_generator=d(rd1);
    return wait_time_generator;
}

bool intersects(std::pair<int, int> p1, std::pair<int, int> p2, std::pair<int, int> p3, std::pair<int, int> p4) {
    int x1 = p1.first;
    int y1 = p1.second;
    int x2 = p2.first;
    int y2 = p2.second;
    int x3 = p3.first;
    int y3 = p3.second;
    int x4 = p4.first;
    int y4 = p4.second;
    float m1;
    float b1;
    float m2;
    float b2;
    int segment1_xminimum = std::min(x1, x2);
    int segment1_xmaximum = std::max(x1, x2);
    int segment2_xminimum = std::min(x3, x4);
    int segment2_xmaximum = std::max(x3, x4);
    int segment1_yminimum = std::min(y1, y2);
    int segment1_ymaximum = std::max(y1, y2);
    int segment2_yminimum = std::min(y3, y4);
    int segment2_ymaximum = std::max(y3, y4);
    int x_interval_maximum = std::max(segment1_xminimum, segment2_xminimum);
    int x_interval_minimum = std::min(segment1_xmaximum, segment2_xmaximum);
    int y_interval_maximum = std::max(segment1_yminimum, segment2_yminimum);
    int y_interval_minimum = std::min(segment1_ymaximum, segment2_ymaximum);
    // check for vertical overlapping lines
    if ( x1 == x2 && x2 == x3 && x3 == x4 ) {
        if ( (y_interval_minimum <= y1 && y1 <= y_interval_maximum) ||
             (y_interval_minimum <= y2 && y2 <= y_interval_maximum) ||
             (y_interval_minimum <= y3 && y3 <= y_interval_maximum) ||
             (y_interval_minimum <= y4 && y4 <= y_interval_maximum) )  {
            return true;
        }
    } else if ( x1 != x2 && x3 != x4) {
        m1 = (y2-y1)/(x2-x1);
        b1 = y1-m1*x1;
        m2 = (y4-y3)/(x4-x3);
        b2 = y3-m2*x3;
        // check if line equations are equal
        if (m1 == m2 && b1 == b2) {
            if (
             ( (x_interval_minimum <= x1 && x1 <= x_interval_maximum) ||
             (x_interval_minimum <= x2 && x2 <= x_interval_maximum) ||
             (x_interval_minimum <= x3 && x3 <= x_interval_maximum) ||
             (x_interval_minimum <= x4 && x4 <= x_interval_maximum) )
             &&
             ( (y_interval_minimum <= y1 && y1 <= y_interval_maximum) ||
             (y_interval_minimum <= y2 && y2 <= y_interval_maximum) ||
             (y_interval_minimum <= y3 && y3 <= y_interval_maximum) ||
             (y_interval_minimum <= y4 && y4 <= y_interval_maximum) )
                )
            {
            return true;
            }
        }
    }
    float xnumerator = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    float xdenominator = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    float ynumerator = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    float ydenominator = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    if (xdenominator == 0 || ydenominator == 0) {
        return false;
    }
    float xcoordinate = xnumerator / xdenominator;
    float ycoordinate = ynumerator / ydenominator;
    if ( x_interval_minimum <= xcoordinate && xcoordinate <= x_interval_maximum &&
        y_interval_minimum <= ycoordinate && ycoordinate <= y_interval_maximum ) {
            return true;
        }
    return false;
}
