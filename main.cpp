// A C++ program to check if a given point lies inside a given polygon
// Refer http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// for explanation of functions onSegment(), orientation() and doIntersect()
#include <iostream>


#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <array>

using namespace std;

float distance(float x1,float y1,float x2,float y2,float x,float y);//retrn the perpendicular distance of a point from a line
int nearest_line(float arrx[],float arry[],float x,float y,int n);
void coordinate(float x1,float y1,float x2,float y2,float x,float y);


float final_pointx[100];
float final_pointy[100];
float already_inside_x[100];
float already_inside_y[100];
int inside_p=0;
int i_x=0;
int i_y=0;;
int r=0;


void sort(float number[], int n);
// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

struct Point
{
	int x;
	int y;
};
int check(Point polygon1[],Point p,int n);
void point1(Point polygon1[],Point p,int n,float x[],float y[]);
void point3(Point polygon1[],Point p,int n,float x[],float y[]);
void point2(Point polygon1[],Point p,int n,float x[],float y[]);
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // colinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(Point polygon[], int n, Point p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3) return false;

	// Create a point for line segment from p to infinite
	Point extreme = {INF, p.y};

	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;
	do
	{
		int next = (i+1)%n;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is colinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
			return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count&1; // Same as (count%2 == 1)
}

// Driver program to test above functions

void sort(float number[], int n) {

    /* Sort the given array number, of length n */
    int  i;
    float temp;
    int j;

    for (i =0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (number[i] > number[j]) {
                temp = number[j];
                number[j] = number[i];
                number[i] = temp;
            }
        }
    }
}

float distance(float x1,float y1,float x2,float y2,float x,float y)
{
    float m,c,p,dist=0.0;
    if(x2-x1==0)
    {
        dist=x2-x;
        return dist;
    }
    else if(y2-y1==0)
    {
        dist=y2-y;
        return dist;
    }
    else
    {
    m=(y2-y1)/(x2-x1);
    c=y1-(m*x1);
    p=sqrt((m*m)+1);
    dist=((m*x)-y+c);
    if(dist<0) dist=dist*(-1);
    dist=dist/p;
    return dist;
    }
}

int nearest_line(float arrx[],float arry[],float x,float y,int n)
{
    float dist;
    int p=0;
    float shortest=distance(arrx[0],arry[0],arrx[1],arry[1],x,y);
    for(int i=1;i<n;i++)
    {
        dist=distance(arrx[i],arry[i],arrx[i+1],arry[i+1],x,y);
        if(dist<shortest)
        {
            shortest=dist;
            p++;
        }
        return p;
}
}

void coordinate(float x1,float y1,float x2,float y2,float x,float y)
{
    float tempx,tempy;
    if(x2-x1==0)
    {
        tempx=x1;
        tempy=y;
    }
    else if(y2-y1==0)
    {
        tempy=y1;
        tempx=x;
    }
    else
    {
        float m,m1;
        m=(y2-y1)/(x2-x1);
        m1=(1/m)*(-1);
        tempx=((m*y)+x-y1+(m*x1))/(m-m1);
        tempy=(m*tempx)+y1-(m*x1);

    }
    final_pointx[r]=tempx;
    final_pointy[r]=tempy;
    r++;
    return;
}
int check(Point polygon1[],Point p,int n)

{float i,j;
    j=p.x;
    i=p.y;
  int  a=0;
      if(!(isInside(polygon1, n, p))){
         a++;}
        if((isInside(polygon1, n, p))){  already_inside_x[i_x]=p.x;
         already_inside_y[i_y]=p.y;
         i_x++;
          i_y++;
         inside_p++;
         }
	//isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";

     p = {j+1,i};
	//isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
	 if(!(isInside(polygon1, n, p))){
         a++;}
        if((isInside(polygon1, n, p))){  already_inside_x[i_x]=p.x;
         already_inside_y[i_y]=p.y;
         i_x++;
          i_y++;
          inside_p++;
         }

	 p = {j+1,i+1};
	//isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
	 if(!(isInside(polygon1, n, p))){
         a++;}
        if((isInside(polygon1, n, p))){  already_inside_x[i_x]=p.x;
         already_inside_y[i_y]=p.y;
         i_x++;
          i_y++;
          inside_p++;
         }

	 p = {j,i+1};
	  if(!(isInside(polygon1, n, p))){
         a++;}
        if((isInside(polygon1, n, p))){
                already_inside_x[i_x]=p.x;
         already_inside_y[i_y]=p.y;
         i_x++;
          i_y++;
          inside_p++;
         }
	//isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
	return a;
}
void point3(Point polygon1[],Point p,int n,float x[],float y[]){
    int index;
    float i,j;
    j=p.x;
    i=p.y;
    Point inside_point;
  //  isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
     if((isInside(polygon1, n, p)))
        inside_point=p;

      p = {j+1,i};
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if((isInside(polygon1, n, p)))
        inside_point=p;

      p = {j+1,i+1};
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if((isInside(polygon1, n, p)))
        inside_point=p;

      p = {j,i+1};
   //  isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if((isInside(polygon1, n, p)))
        inside_point=p;


       index = nearest_line(x,y,inside_point.x,inside_point.y,n);
       coordinate(x[index],y[index],x[index+1],y[index+1],inside_point.x,inside_point.y);
      printf("some point are inside\n");}


void point1(Point polygon1[],Point p,int n,float x[],float y[]){
     int index;
    float i,j;
    j=p.x;
    i=p.y;
    Point outside_point;
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
     if(!(isInside(polygon1, n, p)))
        outside_point=p;

      p = {j+1,i};
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if(!(isInside(polygon1, n, p)))
        outside_point=p;

      p = {j+1,i+1};
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if(!(isInside(polygon1, n, p)))
        outside_point=p;

      p = {j,i+1};
   //  isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if(!(isInside(polygon1, n, p)))
        outside_point=p;


       index = nearest_line(x,y,outside_point.x,outside_point.x,n);
      coordinate(x[index],y[index],x[index+1],y[index+1],outside_point.x,outside_point.y);
      printf("some point are inside\n");

  }

void point2(Point polygon1[],Point p,int n,float x[],float y[]){
   Point  outside_point;
    int index;
    float i,j;
    j=p.x;
    i=p.y;
// isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
     if(!(isInside(polygon1, n, p))){
        outside_point=p;
       index = nearest_line(x,y,outside_point.x,outside_point.y,n);
       coordinate(x[index],y[index],x[index+1],y[index+1],outside_point.x,outside_point.y);}

      p = {j+1,i};
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if(!(isInside(polygon1, n, p))){
        outside_point=p;
       index = nearest_line(x,y,outside_point.x,outside_point.y,n);
       coordinate(x[index],y[index],x[index+1],y[index+1],outside_point.x,outside_point.y);}

      p = {j+1,i+1};
    // isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if(!(isInside(polygon1, n, p)))
        {

         outside_point=p;
    index = nearest_line(x,y,outside_point.x,outside_point.y,n);
       coordinate(x[index],y[index],x[index+1],y[index+1],outside_point.x,outside_point.y);
        }
      p = {j,i+1};
   //  isInside(polygon1, n, p)? cout << "Yes ": cout << "No ";
      if(!(isInside(polygon1, n, p)))
    {

     outside_point=p;
       index = nearest_line(x,y,outside_point.x,outside_point.y,n);
       coordinate(x[index],y[index],x[index+1],y[index+1],outside_point.x,outside_point.y);}


      printf("some point are inside\n");

  }
int main()

{

    float xmin,xmax,ymin,ymax;
    float temp;
     int totalpoint,index;
     Point inside_point,outside_point;
     int t;
int i,j;
int a;

     printf("enter no of point in closed area");
   scanf("%d",&totalpoint);
   t=totalpoint;
   Point polygon1[t];

	int n = sizeof(polygon1)/sizeof(polygon1[0]);


   float x[totalpoint];
   float y[totalpoint];
   for(i=0;i<totalpoint;i++){
    printf("enter x co ordinate of point");
    scanf("%f",&x[i]);
    printf("enter y co ordinate of point");
    scanf("%f",&y[i]);
   }
   // = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
    for(i=0;i<t;i++){

         polygon1[i].x=x[i];

          polygon1[i].y=y[i];
    }





sort(x,t);
sort(y,t);

   printf("xmin=%.1f\nxmax=%.1f",x[0],x[t-1]);
    printf("ymin=%.1f\nymax=%.1f\n",y[0],y[t-1]);
    xmin=x[0];
    xmax=x[t-1];
      ymin=y[0];
    ymax=y[t-1];

   for(i=ymin;i<ymax;i++){
    for(j=xmin;j<xmax;j++){

      Point p = {j,i};
      a=check(polygon1,p,n);

        if(a==4){
    printf("block is outside\n");
    continue;
}
if(a==0)
   {

    printf("all point are inside\n");
    continue;

   }


  if(a==3){
     p = {j,i};
      point3(polygon1,p,t,x,y);


  }

     if(a==1){
     p = {j,i};
       point1(polygon1,p,t,x,y);
     }
    if(a==2){
            p = {j,i};

    point2(polygon1,p,t,x,y);


     p = {j,i};}

 }}


for(i=0;i<=r;i++){
    printf("x=%f y=%f\n",final_pointx[i],final_pointy[i]);
}
for(i=0;i<=inside_p;i++){
    printf("x=%f y=%f\n",already_inside_x[i],already_inside_y[i]);
}
printf("%d",inside_p);
	return 0;
}
