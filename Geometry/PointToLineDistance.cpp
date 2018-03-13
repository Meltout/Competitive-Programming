double FindDistanceToSegment(double x1, double y1, double x2, double y2, double pointX, double pointY)
{
    double diffX = x2 - x1;
    double diffY = y2 - y1;
    if ((diffX == 0) && (diffY == 0))
    {
        diffX = pointX - x1;
        diffY = pointY - y1;
        return sqrt(diffX * diffX + diffY * diffY);
    }

    double t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / (diffX * diffX + diffY * diffY);

    if (t < 0)
    {
        //point is nearest to the first point i.e x1 and y1
        diffX = pointX - x1;
        diffY = pointY - y1;
    }
    else if (t > 1)
    {
        //point is nearest to the end point i.e x2 and y2
        diffX = pointX - x2;
        diffY = pointY - y2;
    }
    else
    {
        //if perpendicular line intersect the line segment.
        diffX = pointX - (x1 + t * diffX);
        diffY = pointY - (y1 + t * diffY);
    }

    //returning shortest distance
    return sqrt(diffX * diffX + diffY * diffY);
}

// MY IMPLEMENTATION
struct point{
 double x;
 double y;
};

double point_to_segment(point a,point b,point p)   // distance from point p to segment ab
{
    double diffX=b.x-a.x;
    double diffY=b.y-a.y;

    if(diffX==0 && diffY==0)
    {
       diffX=p.x-a.x;
       diffY=p.y-a.y;
       return sqrt(diffX*diffX+diffY*diffY);
    }

    double t=((p.x-a.x)*diffX+(p.y-a.y)*diffY)/(diffX * diffX + diffY * diffY);

    if(t<0) // p is closer to a
    {
        diffX=p.x-a.x;
        diffY=p.y-a.y;

        return sqrt(diffX * diffX + diffY * diffY);
    }
    if(t>1) // p is closer to b
    {
        diffX=p.x-b.x;
        diffY=p.y-b.y;

        return sqrt(diffX*diffX+diffY*diffY);
    }
     // there is perpendicular from p to ab
    diffX=p.x-(a.x+t*diffX);
    diffY=p.y-(a.y+t*diffY);

    return sqrt(diffX*diffX+diffY*diffY);

}
